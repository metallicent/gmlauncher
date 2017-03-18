cmake_minimum_required(VERSION 2.6)

project(gmlauncher)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB gmlaucher_includes "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

set(gmlauncher_src
	src/utils.cpp
	src/main.cpp
	src/launcherprogram.cpp
	src/theme.cpp
	src/screen.cpp
	src/menu.cpp
	src/menuentry.cpp
	src/menustructure.cpp
	src/menutemplate.cpp)

add_definitions(-g -Wall)

add_executable(gmlauncher ${gmlauncher_src})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})
target_link_libraries(gmlauncher ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY})

find_package(LibXml2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIR})
target_link_libraries(gmlauncher ${LIBXML2_LIBRARIES})

install(TARGETS gmlauncher DESTINATION bin)