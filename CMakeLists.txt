cmake_minimum_required(VERSION 3.10)
project(RivalGrounds VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
add_subdirectory(vendor)

target_include_directories(RivalGROUNDS PRIVATE
	vendor/assimp-src/include
	vendor/entt-src/single_include/entt
	vendor/glad-build/include
	vendor/glm-src
	vendor/miniaudio-build/include
	vendor/imgui-src
	vendor/imgui-src/backends
	vendor/imgui-src/examples
	vendor/stb_image-build/include
)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(RivalGrounds ${SOURCES})

target_link_libraries(RivalGrounds PRIVATE ${OPENGL_LIBRARIES} CrossWindow glad glm assimp)
