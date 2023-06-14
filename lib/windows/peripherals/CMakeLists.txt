# @file lib\windows\peripherals\CMakeLists.txt
# @author HinsShum hinsshum@qq.com
# @date 2022/03/11 15:46:32
# @encoding utf-8
# @brief Here's the first line of every CMakeLists.txt,
#        which is the required name of the file CMake looks for:
cmake_minimum_required(VERSION 3.1)

set(TARGET_LIB_NAME peripherals)
set(TARGET_C_FILES)
set(TARGET_INC_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/inc)

if(DEFINED RS232)
    list(APPEND TARGET_C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/rs232.c)
endif()

add_library(${TARGET_LIB_NAME} STATIC ${TARGET_C_FILES})
target_include_directories(${TARGET_LIB_NAME} PRIVATE ${TARGET_INC_DIRS} ${G_SOURCE_INCLUDE_DIRS})

set(G_LIBS ${G_LIBS} ${TARGET_LIB_NAME} PARENT_SCOPE)
set(G_INC_VPATH ${G_INC_VPATH} ${TARGET_INC_DIRS} PARENT_SCOPE)