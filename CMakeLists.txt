cmake_minimum_required(VERSION 2.8.8)

project(7colors)

set(CMAKE_C_FLAGS "-Werror -Wall -Wextra -g -Wmissing-declarations -Wno-unused-parameter ${CMAKE_C_FLAGS}")

set(sources src/structures.c src/utils.c src/display.c src/input.c src/board.c src/strategies.c src/game.c)

# The game binary
add_executable(7colors src/main.c ${sources})

# A binary containing the unit tests
add_executable(tests src/tests.c ${sources})

# Register the tests to the CMake mechanisms
ENABLE_TESTING()
ADD_TEST(unit-tests ./tests)
