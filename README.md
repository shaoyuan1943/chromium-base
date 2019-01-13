# chromium-base

from the Google Chromium. That code include:
1. Base component and cross platform wrap, like file\process\thread\path...
2. Some high-performance container.
3. Lightweight smart pointer.
4. Callback and Bind.
5. Message loop and task.
6. Characters and timer.

## How to compile
### Windows
Require: VS 2017 15.9 or later.  
Open chromium-base\src\base.sln file by VS 2017 and compile the project.
### Linux
Require:
### macOS
Require:

## How to use
Include base\base_export.h and the other header file what you want to use and link base.dll, at last run it.

## Document
See chromium-base-api-manual.md