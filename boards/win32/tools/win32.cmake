# @file boards\win32\tools\win32.cmake
# @author HinsShum hinsshum@qq.com
# @date 2021/11/11 13:19:48
# @encoding utf-8
# @brief Here's the first line of every win32.cmake,
#        which is the required name of the file CMake looks for:
cmake_minimum_required(VERSION 3.20)

# set current boards directroy to search path
set(G_INC_VPATH ${G_INC_VPATH} "${PROJECT_SOURCE_DIR}/boards/${BOARD_NAME}")
set(FREERTOS_CONFIG_FILE_DIRECTORY "${PROJECT_SOURCE_DIR}/boards/${BOARD_NAME}/config/port" CACHE STRING [FORCE])
set(FREERTOS_PORT "MSVC_MINGW" CACHE STRING [FORCE])
set(FREERTOS_BUILDIN "1")

add_definitions(-DprojCOVERAGE_TEST=1)
add_definitions(-DCONFIG_OPTIONS_FILE="config/options.h")

include(${PROJECT_SOURCE_DIR}/boards/${BOARD_NAME}/config/tiny-sdk.cmake)
include(${PROJECT_SOURCE_DIR}/boards/${BOARD_NAME}/config/lib.cmake)

# enter sub driectory
add_subdirectory("boards/${BOARD_NAME}/bsp")
add_subdirectory("boards/${BOARD_NAME}/src")
add_subdirectory("boards/${BOARD_NAME}/tasKs")
add_subdirectory("lib/windows/peripherals")
