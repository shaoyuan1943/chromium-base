# chromium-base

from the Google Chromium. That code include:
1. Base component and cross platform wrap, like file\process\thread\path...
2. Some high-performance container.
3. Lightweight smart pointer.
4. Callback and Bind.
5. Message loop and task.
6. Characters and timer.

## 如何编译
### Windows
要求: VS 2017 15.9或更高版本.  
打开 chromium-base\src\base.sln 文件之后选择目的平台直接编译即可.
### Linux
要求: CMake 3.6或更高版本，GCC 7.3或更高版本。  
1. 需要依赖glib，有些Linux发行版不带glib，需要自行安装，安装之后需要修改CMakeLists.txt中BASE\_INCLUDE\_PLATFORM\_DIRECTORIES这个变量所定义的glib头文件目录。
2. 进入scm目录，运行build\_base\_linux.sh脚本编译即可。
### macOS
要求: Xcode 10.1或更高版本  
1. 需要依赖libevent，推荐使用这个版本:https://chromium.googlesource.com/chromium/+/trunk/third_party/libevent  
2. 编译安装完成之后，Xcode打开 chromium-base\src\xcode\base.xcodeproj编译即可。  
3. 如果出现找不到libevent相关头文件或库的编译、链接错误，需要改下Build Setting中头文件和库文件搜索路径。  

## 如何使用
包含 ```base\base_export.h```文件或其他模块的头文件，链接base.dll/libbase.so/libbase.dylib即可。

## 文档
See chromium-base-api-use-manual.md