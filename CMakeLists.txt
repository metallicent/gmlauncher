cmake_minimum_required(VERSION 2.6)

project(gmlauncher)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
FILE(GLOB gmlaucher_includes "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

set(gmlauncher_src
	src/main.cpp
	src/launcherprogram.cpp
	src/theme.cpp)

add_definitions(-g -Wall)

add_executable(gmlauncher ${gmlauncher_src})

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(gmlauncher ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

find_package(LibXml2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIR})
target_link_libraries(gmlauncher ${LIBXML2_LIBRARIES})
