cmake_minimum_required(VERSION 3.0)
#set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_SYSTEM_NAME "Generic")

# delete cmake cache folder before changing this options
option(BUILD_NX "Build with NX (SWITCH) support" ON)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(BUILD_DEBUG true CACHE BOOL "Debug build")
endif ()

# setup toolchain
include(Toolchain.cmake)

project(nxnetprint)

# flags
set(FLAGS -Wall)

#####################
# NX PLATORM
#####################
if (BUILD_NX)
    set(INCLUDES
            include
            ${DEVKITPRO}/libnx/include
            ${DEVKITPRO}/portlibs/armv8-a/include/freetype2
            )
    list(APPEND SOURCES
            source/main.c
            )
    list(APPEND FLAGS -D__NX__
            -ffunction-sections -fomit-frame-pointer
            )
    set(LIBS
            ${DEVKITPRO}/libnx/lib/libnx.a
            )
endif (BUILD_NX)

add_library(nxnetprint ${SOURCES})
target_include_directories(nxnetprint PRIVATE ${INCLUDES})
target_compile_options(nxnetprint PRIVATE ${FLAGS})
target_link_libraries(nxnetprint ${LIBS})
