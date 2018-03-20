cmake_minimum_required(VERSION 3.0)
#set(CMAKE_VERBOSE_MAKEFILE ON)

# setup toolchain
set(CMAKE_SYSTEM_NAME "Generic")
set(DEVKITPRO $ENV{DEVKITPRO})
set(CMAKE_SYSTEM_PROCESSOR "armv8-a")
set(CMAKE_C_COMPILER "${DEVKITPRO}/devkitA64/bin/aarch64-none-elf-gcc")
set(CMAKE_CXX_COMPILER "${DEVKITPRO}/devkitA64/bin/aarch64-none-elf-g++")
set(CMAKE_ASM_COMPILER "${DEVKITPRO}/devkitA64/bin/aarch64-none-elf-as")
set(CMAKE_AR "${DEVKITPRO}/devkitA64/bin/aarch64-none-elf-gcc-ar" CACHE STRING "")
set(CMAKE_RANLIB "${DEVKITPRO}/devkitA64/bin/aarch64-none-elf-gcc-ranlib" CACHE STRING "")
set(CMAKE_C_FLAGS "-D__SWITCH__ -march=armv8-a -mtune=cortex-a57 -mtp=soft -fPIE -ffast-math -ffunction-sections -fdata-sections -I${DEVKITPRO}/libnx/include -I${DEVKITPRO}/portlibs/switch/include" CACHE STRING "C flags")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fno-rtti -fno-exceptions -std=gnu++11" CACHE STRING "C++ flags")
set(CMAKE_FIND_ROOT_PATH ${DEVKITPRO} ${DEVKITPRO}/devkitA64 ${DEVKITPRO}/libnx ${DEVKITPRO}/portlibs/switch)

project(nxlink_print)

# flags
set(FLAGS -Wall)

add_library(${PROJECT_NAME} source/main.c)
target_include_directories(${PROJECT_NAME} PUBLIC include ${DEVKITPRO}/libnx/include)
target_compile_options(${PROJECT_NAME} PUBLIC ${FLAGS})
target_link_libraries(${PROJECT_NAME} ${DEVKITPRO}/libnx/lib/libnx.a)
