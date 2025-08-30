cmake_minimum_required(VERSION 3.30.1)
project(pong)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

# Arquivos fonte
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/**/*.cpp")

include_directories(include)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Criar executável
add_executable(pong ${SOURCES})

# Linkar SDL2
target_link_libraries(pong ${SDL2_LIBRARIES})
