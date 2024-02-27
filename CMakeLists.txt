cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(hash_table)

# 添加 include 目录到头文件搜索路径
include_directories(include)

# 获取所有的源文件
file(GLOB SOURCES "src/*.c")

# 将 hash_table.c 编译成动态链接库
add_library(hash_table SHARED ${SOURCES})

target_compile_options(hash_table PRIVATE -Wall -Wextra -g -O0)


# 设置动态链接库的输出路径
set_target_properties(hash_table PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../package
)


# 添加一个选项，决定是否编译测试
option(BUILD_TESTS "Build tests" OFF)

if(BUILD_TESTS)
    # 获取所有的测试文件
    file(GLOB TEST_SOURCES "tests/*.c")

    # 对每个测试文件进行操作
    foreach(test_source ${TEST_SOURCES})
        # 获取文件的基本名称
        get_filename_component(test_name ${test_source} NAME_WE)

        # 添加要编译的测试文件
        add_executable(${test_name} ${test_source} ${SOURCES})

        # 添加编译选项
        target_compile_options(${test_name} PRIVATE -Wall -Wextra -g -O0)

        # 添加链接选项，链接动态库
        target_link_libraries(${test_name} hash_table m)

         # 设置测试可执行文件的输出路径
        set_target_properties(${test_name} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../tests/output
        )
    endforeach()
endif()