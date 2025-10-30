cmake_minimum_required(VERSION 3.28)
project(GBEmulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS ON)

add_executable(GBEmulator main.cpp ./src/Emulator.cpp ./src/Cartridge.cpp src/Bus.cpp src/log.cpp)
