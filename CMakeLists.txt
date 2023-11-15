cmake_minimum_required(VERSION 3.2)
project(OpenGL_Test)
set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)

if(NOT ${OPENGL_FOUND})
    message("OPENGL not found")
else()
	message("OPENGL found")
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)

add_definitions(-DGLEW_STATIC) # static linking for glew only
set(GL_STATIC_LIBRARIES "${CMAKE_SOURCE_DIR}/lib/glew32sd.lib;${CMAKE_SOURCE_DIR}/lib/glfw3.lib")
# set(GL_DYNAMIC_LIBRARIES "${CMAKE_SOURCE_DIR}/lib/glew32d.lib;${CMAKE_SOURCE_DIR}/lib/glfw3.lib")

add_executable(${PROJECT_NAME} main.cpp "Gamelogic.h" "Drawing.h") 
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY} ${GL_STATIC_LIBRARIES}
)