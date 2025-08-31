cmake_minimum_required(VERSION 3.30.1)
project(pong)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Arquivos fonte
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/**/*.cpp")

include_directories(include)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})

# Criar executável
add_executable(pong ${SOURCES})
add_definitions(-DPROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

# Linkar SDL2
target_link_libraries(pong PRIVATE SDL2 SDL2_ttf)
