# @file app\CMakeLists.txt
# @author HinsShum hinsshum@qq.com
# @date 2022/03/10 16:27:42
# @encoding utf-8
# @brief Here's the first line of every CMakeLists.txt,
#        which is the required name of the file CMake looks for:
cmake_minimum_required(VERSION 3.1)

set(CFILES)
set(INCDIRS ${CMAKE_CURRENT_SOURCE_DIR}/inc)

# recursively call CMakeLists.txt
file(GLOB_RECURSE CMAKELISTS "CMakeLists.txt")
dirname(CMAKELISTS CMAKELISTS_DIRS)
filter_out(CMAKE_CURRENT_SOURCE_DIR CMAKELISTS_DIRS CMAKELISTS_DIRS)
foreach(SUB_DIR ${CMAKELISTS_DIRS})
    add_subdirectory(${SUB_DIR})
endforeach(SUB_DIR)

set(G_C_FILES ${G_C_FILES} ${CFILES} PARENT_SCOPE)
set(G_INC_VPATH ${G_INC_VPATH} ${INCDIRS} PARENT_SCOPE)