cmake_minimum_required(VERSION 3.10)
project(RivalGrounds VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)

set(GLAD_SOURCES_DIR "${PROJECT_SOURCE_DIR}/build/vendor/glad")
add_subdirectory("${GLAD_SOURCES_DIR}/cmake")
glad_add_library(glad STATIC API gl:core=4.6)

add_subdirectory(${PROJECT_SOURCE_DIR}/build/vendor/CrossWindow)

set(STB_IMAGE_URL "https://raw.githubusercontent.com/nothings/stb/master/stb_image.h")
set(STB_IMAGE_DIR "${PROJECT_SOURCE_DIR}/build/vendor/stb_image")
set(STB_IMAGE_PATH "${STB_IMAGE_DIR}/stb_image.h")

# Create the stb_image directory if it doesn't exist
file(MAKE_DIRECTORY ${STB_IMAGE_DIR})

# Check if the file already exists
if(NOT EXISTS ${STB_IMAGE_PATH})
    message(STATUS "Downloading stb_image.h...")
    file(DOWNLOAD ${STB_IMAGE_URL} ${STB_IMAGE_PATH} STATUS download_status)
    if(NOT download_status EQUAL 0)
        message(FATAL_ERROR "Failed to download stb_image.h")
    endif()
else()
    message(STATUS "stb_image.h already exists, skipping download.")
endif()

include_directories(
	# vendor/stb_image
	${PROJECT_SOURCE_DIR}/build/vendor/CrossWindow/src/CrossWindow
)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/xmain.cpp)
xwin_add_executable(RivalGrounds "${SOURCES}")

target_link_libraries(
	RivalGrounds PRIVATE 
	CrossWindow
	glad
	# glm
	# assimp
	# imgui
	# miniaudio
	# entt
)
