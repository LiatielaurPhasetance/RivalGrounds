include(FetchContent)
set(FETCHCONTENT_QUIET off)
set(FETCHCONTENT_BASE_DIR ${PROJECT_SOURCE_DIR}/vendor CACHE PATH "Missing description." FORCE)

message(STATUS "Downloading third party libraries using CMake's FetchContent and CPM")

FetchContent_Declare(
	glad
	GIT_REPOSITORY	https://github.com/Dav1dde/glad.git
	GIT_TAG			v2.0.4
	GIT_SHALLOW		TRUE
	SOURCE_SUBDIR	cmake
)
FetchContent_Declare(
	glm
	GIT_REPOSITORY https://github.com/g-truc/glm.git
	GIT_TAG 0.9.9.8
	GIT_SHALLOW		TRUE
)
FetchContent_Declare(
	entt
	GIT_REPOSITORY	https://github.com/skypjack/entt.git
	GIT_TAG			master
	GIT_SHALLOW		TRUE
)
FetchContent_Declare(
	freetype
	GIT_REPOSITORY	https://github.com/freetype/freetype.git
	GIT_TAG			master
	GIT_SHALLOW		TRUE
)
FetchContent_Declare(
	assimp
	GIT_REPOSITORY	https://github.com/assimp/assimp.git
	GIT_TAG			master
	GIT_SHALLOW		TRUE
)
FetchContent_Declare(
	CrossWindow
	GIT_REPOSITORY	https://github.com/alaingalvan/CrossWindow.git
	GIT_TAG			master
	GIT_SHALLOW		TRUE
)

glad_add_library(glad STATIC API gl:core=4.6 LOCATION ${PROJECT_SOURCE_DIR}/vendor/glad-build/${TARGET})
FetchContent_MakeAvailable(assimp glad glm CrossWindow freetype entt)

FetchContent_Declare(stb_image
	GIT_REPOSITORY https://github.com/nothings/stb.git
	GIT_TAG master
	CONFIGURE_COMMAND ""
	BUILD_COMMAND "")
FetchContent_MakeAvailable(stb_image)
add_library(stb_image INTERFACE)
file(COPY ${stb_image_SOURCE_DIR}/stb_image.h DESTINATION "${PROJECT_SOURCE_DIR}/vendor/stb_image-build/include/stb_image")
set(STBIMAGE_INSTALL_DIR "${PROJECT_SOURCE_DIR}/vendor/stb_image-build")

FetchContent_Declare(miniaudio
	GIT_REPOSITORY https://github.com/mackron/miniaudio.git
	GIT_TAG master
	CONFIGURE_COMMAND ""
	BUILD_COMMAND "")
FetchContent_MakeAvailable(miniaudio)
add_library(miniaudio INTERFACE)
file(COPY ${miniaudio_SOURCE_DIR}/miniaudio.h DESTINATION "${PROJECT_SOURCE_DIR}/vendor/miniaudio-build/include/miniaudio")
set(STBIMAGE_INSTALL_DIR "${PROJECT_SOURCE_DIR}/vendor/miniaudio-build")

CPMAddPackage(NAME imgui
	GITHUB_REPOSITORY ocornut/imgui
	GIT_TAG docking
	DOWNLOAD_ONLY YES)
if(imgui_ADDED)
	FILE(GLOB imgui_sources ${imgui_SOURCE_DIR}/*.cpp)
	file(GLOB IMGUI_HEADERS ${IMGUI_PATH}/*.h)
	FILE(GLOB imgui_sources_cpp ${imgui_SOURCE_DIR}/misc/cpp/*.cpp)

	set(IMGUI_DIR ${imgui_SOURCE_DIR})
	set(IMGUI_INCLUDE_DIR ${imgui_SOURCE_DIR})
	set(IMGUI_SOURCES ${imgui_sources} ${imgui_sources_cpp})

	add_library(imgui STATIC ${IMGUI_SOURCES} ${IMGUI_HEADERS} "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp" "${IMGUI_DIR}/backends/imgui_impl_opengl3.h" "${IMGUI_DIR}/backends/imgui_impl_opengl3_loader.h")
	target_compile_definitions(imgui PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD=1)
	target_include_directories(imgui PUBLIC ${IMGUI_DIR} "glfw-src/include" "glad-build/include")
	set_target_properties(imgui PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/vendor/imgui-build"
		LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/vendor/imgui-build"
		RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/vendor/imgui-build")
endif()

set_target_properties(assimp PROPERTIES FOLDER "Utilities/assimp")
set_target_properties(UpdateAssimpLibsDebugSymbolsAndDLLs PROPERTIES FOLDER "Utilities/assimp")
set_target_properties(glad PROPERTIES FOLDER "Utilities/glad")
#======================================
message(STATUS "Fetching thirdparty libraries done")
