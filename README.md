# Crochet Charts

This software is licensed under GPLv3. All original artwork is licensed under Creative Commons Attribution-ShareAlike ( cc by-sa 4.0 ).

## Setup a working environment

There are some git commit hooks that can be setup after you initially clone this repository by running:

./bin/seutp

You will need to install the following software:

All Platforms
--------------
+ Qt 6.2 or newer (qtbase, qtsvg)
+ cmake 3.16 or newer
+ a C++17 compiler
+ docbook
+ docbook-xsl-ns
+ Apache fop
+ xsltproc

Windows
--------
+ MinGW
+ NSIS
+ signtool 

Mac
----
+ Mac Developer tools Xcode
+ (Paid) Mac Developer account ( to sign the software )

Linux
------
+ build-essential
+ gcc and/or clang
+ doxygen

For ease of use there are some scripts in the bin folder that can help with the development process.

- build   - compile the software based on the selected options, ( -h for a list of options )
- tests   - run the unit tests and report the results in an easy to read format ( first you must build them ).
- profile - compile and run the software with profiling turned on.

