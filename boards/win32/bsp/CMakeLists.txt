# @file boards\win32\bsp\CMakeLists.txt
# @author HinsShum hinsshum@qq.com
# @date 2022/03/11 17:14:58
# @encoding utf-8
# @brief Here's the first line of every CMakeLists.txt,
#        which is the required name of the file CMake looks for:
cmake_minimum_required(VERSION 3.1)

file(GLOB CFILES "*.c")
set(CFILESOUT "")
filter_out(CFILESOUT CFILES CFILES)

set(G_C_FILES ${G_C_FILES} ${CFILES} PARENT_SCOPE)