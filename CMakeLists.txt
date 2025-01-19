cmake_minimum_required(VERSION 3.10)
set(project_name 2d_renderer)
project(${project_name} VERSION 1.0)

if(POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)  # Prefer GLVND for OpenGL
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
message(STATUS "Project source dir: ${PROJECT_SOURCE_DIR}")
message(STATUS "Building project: ${PROJECT_NAME}")

if(MSVC)
    add_compile_options(/W4 /WX /Zi)
else()
    add_compile_options(-fdiagnostics-color=always -Wall -Wextra -Werror -std=c++17 -pedantic -g)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

# Including directories
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${SDL2_INCLUDE_DIRS}, ${OPENGL_INCLUDE_DIR} )



# File globbing for sources and headers
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp" "include/*.h")

# Update the add_executable to correctly reference all source files and headers
add_executable(${project_name} main.cpp ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${project_name} ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
