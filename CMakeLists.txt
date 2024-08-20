cmake_minimum_required(VERSION 3.10)
project(DillyDetection)

set(CMAKE_CXX_STANDARD 17)

add_executable(DILLYPOLYSCAN src/main.cpp src/FileAnalyzer.cpp src/SignatureDetector.cpp src/Logger.cpp)
