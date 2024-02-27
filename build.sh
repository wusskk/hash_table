#!/bin/bash

function help {
    echo "Usage: ./build.sh [OPTION] [ARGUMENT]"
    echo "Build the project, optionally run tests, or clean directories."
    echo
    echo "Options:"
    echo "  test          Build the project and run tests."
    echo "  clean         Clean the build directory."
    echo "  clean output  Clean the package tests/output and build directories."
    echo "  help          Display this help message."
}
function prepare_directories {
    # 检查并清理或创建目录
    for dir in "$@"; do
        if [ -d "$dir" ]; then
            echo "Cleaning $dir..."
            rm -rf "$dir/*"
        else
            echo "Creating $dir..."
            mkdir -p "$dir"
        fi
    done
}

function build_project {
    # 创建一个包含目录名的数组
    directories=(build package)

    # 准备目录
    prepare_directories "${directories[@]}"

    cd build

    # 检查是否有参数传入
    if [ "$1" == "test" ]; then
        prepare_directories tests/output
        # 如果参数是 "test"，则启用测试
        cmake -DBUILD_TESTS=ON ..
    else
        # 否则，禁用测试
        cmake ..
    fi

    # 构建项目
    make

    # 如果启用了测试，运行所有的测试可执行文件
    if [ "$1" == "test" ]; then
        echo "Running tests..."
        if command -v valgrind &> /dev/null; then
            for test in ../tests/output/*; do
                echo "Running $test with valgrind..."
                valgrind --leak-check=full $test
                echo
            done
        else
            for test in ../tests/output/*; do
                echo "Running $test..."
                $test
                echo
            done
        fi
    fi
}

function clean_directories {
    if [ "$1" == "output" ]; then
        # 如果第二个参数是 "output"，则清理 package 目录和 tests/output 目录
        echo "Cleaning package tests/output and build directories..."
        rm -rf package tests/output build
    else
        # 否则，清理 build 目录
        echo "Cleaning build directory..."
        rm -rf build
    fi
}

function main {
    # 检查是否有参数传入
    if [ "$1" == "help" ]; then
        # 如果参数是 "help"，则显示帮助信息
        help
    elif [ "$1" == "clean" ]; then
        clean_directories $2
    else
        # 否则，调用 build_project 函数
        build_project $1
    fi
}

# 调用 main 函数
main "$@"
