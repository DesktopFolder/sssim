cmake_minimum_required(VERSION 3.13) # We actually need this for target_sources I think
set (CMAKE_CXX_STANDARD 20) # Concepts! Uh, TODO
project(SSSim LANGUAGES C CXX) # C for glad

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3) # why doesn't this work with find..?

# we have very few dependencies, just glad/glfw
include_directories("${PROJECT_SOURCE_DIR}/3rd/glad/include")
include_directories(${GLFW_INCLUDE_DIRS})

# Include library, this is probably not the correct method to do this.
# But it works. Don't knock it till ya tried it.
include_directories("${PROJECT_SOURCE_DIR}/lib")

# Now we get glfw library. Hoorah.
link_directories(${GLFW_LIBRARY_DIRS})

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fno-omit-frame-pointer -fsanitize=address")

# Every single file goes here.
# What could go wrong?
# Use target_sources in conjunction with add_subdirectory
# to add more sources to this later on.
add_executable(SSSim
    3rd/glad/glad.c # oh yeah glad
    src/shape.cpp
    src/shaders.cpp
    src/window.cpp
    src/main.cpp
)

add_subdirectory(lib)

target_link_libraries(SSSim PUBLIC ${GLFW_LIBRARIES})
