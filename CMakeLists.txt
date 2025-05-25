#Clang
#cmake -S . -B build/clang -G "MinGW Makefiles" -DCMAKE_MAKE_PROGRAM="C:\\msys64\\mingw64\\bin\\make.exe"

#MSVC
#cmake -S . -B build/msvc

cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

if(CMAKE_GENERATOR MATCHES "MinGW Makefiles")
    set(CMAKE_C_COMPILER "clang.exe")
    set(CMAKE_CXX_COMPILER "clang++.exe")
endif()



set(SOURCE_FILES
    src/window_widget.cpp
)
project(RGUI VERSION 0.1.0 LANGUAGES CXX C)

add_library(RGUI STATIC ${SOURCE_FILES})

target_include_directories(RGUI PUBLIC include)
target_compile_definitions(RGUI PRIVATE
    $<$<PLATFORM_ID:Windows>:PLATFORM_WINDOWS>
    $<$<PLATFORM_ID:Linux>:PLATFORM_LINUX>
    $<$<CXX_COMPILER_ID:Clang>:COMPILER_CLANG>
    $<$<CXX_COMPILER_ID:MSVC>:COMPILER_MSVC>
)