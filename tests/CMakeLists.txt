include_directories(${CMAKE_BINARY_DIR}/src ${CMAKE_SOURCE_DIR}/src
                    ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Qt6 REQUIRED COMPONENTS Test)

file(GLOB crochet_test_srcs "test*.cpp")
file(GLOB crochet_test_qobject_headers "test*.h")

file(GLOB crochet_app_h "../src/*.h")
file(GLOB crochet_app_cpp "${CMAKE_SOURCE_DIR}/src/*.cpp")
list(FILTER crochet_app_cpp EXCLUDE REGEX ".*/src/main\.cpp$")
list(APPEND crochet_app_cpp ${CMAKE_BINARY_DIR}/version.cpp)



file(GLOB crochet_ui_h "../src/*.ui")

set(crochet_app_resources
    ../crochet.qrc
    ../stitches/stitches.qrc
    )

add_executable(tests main.cpp ${crochet_test_srcs} ${crochet_test_qobject_headers}
    ${crochet_app_resources} ${crochet_app_cpp} ${crochet_ui_h})
set_target_properties(tests PROPERTIES AUTOUIC_SEARCH_PATHS "${CMAKE_SOURCE_DIR}/src")
target_link_libraries(tests PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Svg Qt6::SvgWidgets
    Qt6::Network Qt6::PrintSupport Qt6::Test)
