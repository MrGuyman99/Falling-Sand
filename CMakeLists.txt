cmake_minimum_required(VERSION 3.24)
project(FallingSandGame)

# Change To CXX_STANDARD 11 if on Mac
# See: https://github.com/raysan5/raylib/issues/1343
set(CMAKE_CXX_STANDARD 23)

if(APPLE)
	set(CMAKE_CXX_STANDARD 11)
endif()

# ===== Dependencies =====
include(FetchContent)

include(cmake/raylib.cmake)
include(cmake/imgui.cmake)
include(cmake/rlimgui.cmake)

# ===== Our Project =====
set(SOURCE_FILES
	src/main.cpp
	src/grid.cpp
	src/colors.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} rlimgui)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()