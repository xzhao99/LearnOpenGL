cmake_minimum_required(VERSION 3.20)

project(LearnOpenGL)

# Note: OpenGL version can be viewed using OpenGL Extension Viewer for Windows
# and glxinfo on Linux machines.
find_package(OpenGL REQUIRED)
if(OpenGL_FOUND)
  message(STATUS "OpenGL_INCLUDE_DIRS: ${OpenGL_INCLUDE_DIRS}")
  message(STATUS "OpenGL_LIBRARIES: ${OpenGL_LIBRARIES}")
endif()

find_package(glfw3 CONFIG REQUIRED)
if(glfw3_FOUND)
  message(STATUS "GLFW_INCLUDE_DIRS: ${glfw_INCLUDE_DIRS}")
  message(STATUS "GLFW_LIBRARIES: ${glfw_LIBRARIES}")
endif()

find_package(glad CONFIG REQUIRED)
if(glad_FOUND)
  message(STATUS "GLAD_INCLUDE_DIRS: ${glad_INCLUDE_DIRS}")
  message(STATUS "GLAD_LIBRARIES: ${glad_LIBRARIES}")
endif()

add_executable(draw_triangles ${CMAKE_SOURCE_DIR}/src/ch1_draw_triangles/draw_triangles.cpp)
target_link_libraries(draw_triangles PRIVATE ${OpenGL_LIBRARIES} glad::glad glfw)