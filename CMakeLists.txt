cmake_minimum_required(VERSION 3.28)
project(GBEmulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR})

# Create a library with your emulator code
add_library(gbemulator_lib STATIC
        src/Emulator.cpp
        src/Cartridge.cpp
        src/Bus.cpp
        src/log.cpp
        src/CPU.cpp
)

# Main emulator executable
add_executable(GBEmulator
        main.cpp
)
target_link_libraries(GBEmulator PRIVATE gbemulator_lib)
