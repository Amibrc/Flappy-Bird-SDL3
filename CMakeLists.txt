cmake_minimum_required(VERSION 3.8)

project(FlappyBird)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

if(NOT SDLIMAGE_PNG)
	message(FATAL_ERROR "SDL3_image not support PNG format.")
endif()

add_executable(FlappyBird
	src/main.cpp
	src/AnimatedGameObject.cpp
	src/Bird.cpp
	src/Game.cpp
	src/GameObject.cpp
	src/NumberDisplay.cpp
	src/Pipe.cpp 
	src/PipePair.cpp
	src/PipePairsManager.cpp
	src/Score.cpp
	src/ScrollingLayer.cpp
	src/SDL_Base.cpp
	src/Stats.cpp
	
	src/MultiTextureObject.cpp)

target_link_libraries(FlappyBird PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)

add_custom_command(TARGET FlappyBird POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets"
    $<TARGET_FILE_DIR:FlappyBird>/assets)