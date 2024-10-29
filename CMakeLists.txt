cmake_minimum_required(VERSION 3.10)
project(RivalGrounds VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)

set(GLAD_SOURCES_DIR "${PROJECT_SOURCE_DIR}/vendor/glad")
add_subdirectory("${GLAD_SOURCES_DIR}/cmake" glad_cmake)
glad_add_library(glad STATIC API gl:core=4.6)

add_subdirectory(vendor/CrossWindow)
file(MAKE_DIRECTORY vendor/stb_image)

# Download stb_image.h
file(DOWNLOAD 
	"https://raw.githubusercontent.com/nothings/stb/master/stb_image.h"
	"vendor/stb_image/stb_image.h"
	STATUS download_status
)

# Check if the download was successful
if(NOT download_status EQUAL 0)
	message(FATAL_ERROR "Failed to download stb_image.h")
endif()

include_directories(
	vendor/stb_image
)

file(GLOB_RECURSE SOURCES src/*.cpp)
xwin_add_executable(RivalGrounds "${SOURCES}")

target_link_libraries(
	RivalGrounds PRIVATE 
	CrossWindow
	glad
	# glm
	# assimp
	# imgui
	# miniaudio
	stb_image
	# entt
)
