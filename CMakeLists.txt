cmake_minimum_required(VERSION 3.28)
project(GBEmulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS ON)

# SDL3 Configuration
set(SDL3_PATH "${CMAKE_SOURCE_DIR}/libs/x86_64-w64-mingw32")

include_directories(${SDL3_PATH}/include)
link_directories(${SDL3_PATH}/lib)

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
        src/Timer.cpp
        src/ppu.cpp
)

# Main emulator executable
add_executable(GBEmulator
        main.cpp
)

# Link the emulator library and SDL3
target_link_libraries(GBEmulator PRIVATE
        gbemulator_lib
        SDL3
        mingw32
        imm32
        setupapi
        version
        winmm
)

# Copy SDL3.dll to build directory after build
add_custom_command(TARGET GBEmulator POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_PATH}/bin/SDL3.dll"
        $<TARGET_FILE_DIR:GBEmulator>
)