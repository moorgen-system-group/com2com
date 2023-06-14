# @file boards\win32\config\driver.cmake
# @author HinsShum hinsshum@qq.com
# @date 2022/03/11 16:48:09
# @encoding utf-8
# @brief Here's the first line of every driver.cmake,
#        which is the required name of the file CMake looks for:
cmake_minimum_required(VERSION 3.1)

set(SERIAL "y")
set(TIMER "y")
set(RESOURCE_MANAGER "y")
set(PINGPONG_BUFFER "y")
set(MAC_SERIAL "y")