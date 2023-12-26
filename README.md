## Overview

This is a simple script editing app for Kotlin. 
It is written in C++ and Qt. It uses kotlinc, the Kotlin command-line compiler, to run the scripts.

Here is a YouTube video showcasing the app's features https://youtu.be/372DdW9mgQY?si=68zVQvOeze4b9gHe (slightly long but it is timestamped)

## Requirements

### Windows
Kotlinc ***MUST*** be added to PATH. The winget package will not work. It creates a symlink of sorts, but it does not add kotlinc to PATH.
Manual installation is recommended.

**A Windows release is provided as a zip file which should work**. If it fails to work:
1. Clone this repository.
2. Make sure your Qt version is 6.4.X or higher (tested on 6.6.1).
3. Open it using Qt Creator (it specifically wants the CMakeLists.txt file).
4. Build & Run.
5. (optional) To create the package, build in Release mode and run `windeployqt "path/to/exe/folder"` (windeployqt is located in the Qt BIN folder).

### MacOS & Linux
Linux and MacOS are currently not supported. This is a limitation caused by the way processes are handled. This will be fixed in the future.

## Goals
I wish to further develop this project and as of now my next milestones are (in order of priority):
- Compatibility for Linux. Currently limited by the way processes are executed. Should be an easy fix.
- Compatibility for MacOS. Currently limited by the way processes are executed.
- Support file saving/loading. Have the current temp file as the default option, not the only option.
- Batch process exectuion. Should be achievable with threads.
- Better syntax highlighting.
- Code suggestions.
