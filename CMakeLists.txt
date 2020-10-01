cmake_minimum_required(VERSION 2.8.8)

project(7colors)

set(CMAKE_C_FLAGS   "-Werror -Wall -Wextra -g -Wmissing-declarations -Wno-unused-parameter ${CMAKE_C_FLAGS}")

set(sources board.c
    # YOUR CODE HERE: List your source files right after board.c (only the c files are mandatory)
)

# The game binary
add_executable(7colors main.c ${sources})

# A binary containing the unit tests
add_executable(tests tests.c ${sources})

# Register the tests to the CMake mechanisms
ENABLE_TESTING()
ADD_TEST(unit-tests ./tests)