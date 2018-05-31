# 使用CMake Tools插件（可选，如果这个项目去到一个没有这个插件的机器也同样可以生成项目）
include(CMakeToolsHelpers OPTIONAL)

# CMake 最低版本号要求
cmake_minimum_required(VERSION 3.5.1)

# 项目名称
project(Copy8cc)

#设置编译器
set(CMAKE_C_COMPILER "gcc-5")
set(CMAKE_CXX_COMPILER "g++-5")

#c++11标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#Debug或者Release -DCMAKE_BUILD_TYPE=Release 或者 -DCMAKE_BUILD_TYPE=Debug
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g3 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# 查找 boost 库
# set(Boost_USE_STATIC_LIBS OFF) 
# set(Boost_USE_MULTITHREADED ON)  
# set(Boost_USE_STATIC_RUNTIME OFF) 
# find_package(Boost 1.58 REQUIRED COMPONENTS system filesystem) 

# if(Boost_FOUND)
#     include_directories(${Boost_INCLUDE_DIRS})
#     link_directories(${Boost_LIBRARY_DIRS})
# endif()

# SET(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY})

# 查找头文件
include_directories(./src)

# 查找src目录下的所有源文件
# 并将名称保存到 DIR_ROOT_SRCS 变量
aux_source_directory(./src DIR_ROOT_SRCS)

# 指定生成目标
add_executable(Copy8cc ${DIR_ROOT_SRCS})

# 链接库
# target_link_libraries(AYCC ${USED_LIBS})
