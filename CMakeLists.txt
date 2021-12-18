cmake_minimum_required(VERSION 3.20)
project(PascalCompilerLinux)

set(CMAKE_CXX_STANDARD 14)

add_executable(PascalCompilerLinux main.cpp MyTokens.h MyCatCodes.h MyTypes.h cmake-build-debug/Emitter.cpp cmake-build-debug/Emitter.h MyOpcodes.h MyEmulator.cpp MyEmulator.h)
