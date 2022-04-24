cmake_minimum_required(VERSION 3.17)
project(myftp LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED true)

add_compile_options(
    "-std=gnu11" "-Wall" "-Wextra" "-Wpedantic" "-Wshadow" "-Wpointer-arith" "-Wattributes"
)

add_subdirectory(src)

add_custom_target(re
    COMMAND make clean && make
)

add_custom_target(fclean
    COMMAND make clean
    COMMAND rm -f ${PROJECT_NAME}
)