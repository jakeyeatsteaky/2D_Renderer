cmake_minimum_required(VERSION 3.10)
set(project_name dead_beef)
project(${project_name} VERSION 1.0)

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
include_directories(${PROJECT_SOURCE_DIR}/include
                    ${PROJECT_SOURCE_DIR}/third_party
                    ${PROJECT_SOURCE_DIR}/third_party/vk-bootstrap/src
                    ${PROJECT_SOURCE_DIR}/third_party/tinyobjloader)

message(STATUS "Building Lib: VMA")
add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/VulkanMemoryAllocator)
message(STATUS "Building Lib: GLM")
add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/glm)
message(STATUS "Building Lib: TinyOBJLoader")
add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/tinyobjloader)
message(STATUS "Building Lib: VkBootstrap")
set_directory_properties(PROPERTIES DIRECTORY ${PROJECT_SOURCE_DIR}/third_party/vk-bootstrap
                       COMPILE_OPTIONS "-w")
add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/vk-bootstrap)
message(STATUS "Building Lib: fastGLTF")
add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/fastgltf)

include_directories(${SDL2_INCLUDE_DIRS} ${Vulkan_INCLUDE_DIRS})

find_package(SDL2 REQUIRED)
find_package(Vulkan REQUIRED)

# File globbing for sources and headers
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp" "include/*.h")

# Update the add_executable to correctly reference all source files and headers
add_executable(${project_name} main.cpp ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${project_name} ${SDL2_LIBRARIES} ${Vulkan_LIBRARIES} GPUOpen::VulkanMemoryAllocator glm::glm )
