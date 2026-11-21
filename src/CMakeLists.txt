include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB crochet_srcs "*.cpp")
file(GLOB crochet_uis "*.ui")

set(crochet_resources
    ../crochet.qrc
    ../stitches/stitches.qrc
    )

set(crochet_qt_libs
    Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Svg Qt6::SvgWidgets
    Qt6::Network Qt6::PrintSupport)

if(WIN32)
    #generate the embeded icon for the exe file.
    set(crochet_win "${CMAKE_SOURCE_DIR}/crochet.rc")
    #Qt runtime dlls and plugins are bundled with windeployqt after building.
endif()

add_executable(${EXE_NAME} WIN32 MACOSX_BUNDLE
    ${crochet_srcs} ${crochet_uis} ${crochet_resources}
    ${crochet_version} ${crochet_win})

target_link_libraries(${EXE_NAME} PRIVATE ${crochet_qt_libs})

if(APPLE)
    set_target_properties(${EXE_NAME} PROPERTIES
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/cmake/modules/MacOSXBundleInfo.plist.in")

    if(APP_STORE)
        target_compile_definitions(${EXE_NAME} PRIVATE APPLE_APP_STORE=1)
    endif()

    get_target_property(_qmake_exe Qt6::qmake IMPORTED_LOCATION)
    get_filename_component(_qt_bin_dir "${_qmake_exe}" DIRECTORY)
    find_program(MACDEPLOYQT_EXECUTABLE macdeployqt HINTS "${_qt_bin_dir}")

    install(CODE "
        execute_process(
            COMMAND \"${MACDEPLOYQT_EXECUTABLE}\"
            \"${CMAKE_CURRENT_BINARY_DIR}/${EXE_NAME}.app/\"
            WORKING_DIRECTORY \"${CMAKE_BINARY_DIR}\"
            OUTPUT_VARIABLE _output)
        file(COPY \"${CMAKE_SOURCE_DIR}/images/${PROJECT_MACOSX_ICON}\"
            DESTINATION \"${CMAKE_CURRENT_BINARY_DIR}/${EXE_NAME}.app/Contents/Resources\")
    " COMPONENT Runtime)

    install(TARGETS ${EXE_NAME} BUNDLE DESTINATION . COMPONENT Runtime)
else()
    install(TARGETS ${EXE_NAME} BUNDLE DESTINATION . COMPONENT Runtime RUNTIME DESTINATION bin COMPONENT Runtime)
    if(WIN32)
        set_property(TARGET ${EXE_NAME} PROPERTY OUTPUT_NAME "${PROJECT_NAME}")
    endif()
endif()
