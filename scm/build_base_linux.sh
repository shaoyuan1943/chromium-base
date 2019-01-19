#!/bin/bash

ARCH_PLATFORM="^x64$"
ARCH_PLATFORM_NAME="x64"

if [[ $1 -eq "x86" ]]; then
    ARCH_PLATFORM="^x86$"
    ARCH_PLATFORM_NAME="x86"
fi 

# Debug
rm -rf ../build/base/$ARCH_PLATFORM_NAME/Debug
mkdir -p ../build/base/$ARCH_PLATFORM_NAME/Debug


cd ../build/base/$ARCH_PLATFORM_NAME/Debug
cmake ../../../../src -G "Unix Makefiles" -DBASE_ARCH_PLATFORM=$ARCH_PLATFORM -DCMAKE_BUILD_TYPE="Debug" -DBASE_BUILD_PLATFORM="^Linux$"
make -j

# back to original point
cd ../../../../scm

# Release
rm -rf ../build/base/$ARCH_PLATFORM_NAME/Release
mkdir -p ../build/base/$ARCH_PLATFORM_NAME/Release

cd ../build/base/$ARCH_PLATFORM_NAME/Release
cmake ../../../../src -G "Unix Makefiles" -DBASE_ARCH_PLATFORM=$ARCH_PLATFORM -DCMAKE_BUILD_TYPE="Release" -DBASE_BUILD_PLATFORM="^Linux$"
make -j

# back to original point
cd ../../../../scm

# build result
mkdir -p ../bin/base/$ARCH_PLATFORM_NAME/Debug
mkdir -p ../bin/base/$ARCH_PLATFORM_NAME/Release

cp ../build/base/$ARCH_PLATFORM_NAME/Debug/libbase.so ../bin/base/$ARCH_PLATFORM_NAME/Debug/
cp ../build/base/$ARCH_PLATFORM_NAME/Release/libbase.so ../bin/base/$ARCH_PLATFORM_NAME/Release/


