cmake_minimum_required(VERSION 3.7)
project(ImacGL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB HEADER_FILES ${YOUR_DIRECTORY}include/*.h )

file(GLOB SOURCE_FILES ${YOUR_DIRECTORY}src/*.cpp )

file(GLOB_RECURSE SHADER_FILES ${YOUR_DIRECTORY}/shaders/*.glsl)

set(OUTPUT_DIR ${YOUR_DIRECTORY}bin)

set(EXECUTABLE_OUTPUT_PATH ${OUTPUT_DIR})

include_directories( ${YOUR_DIRECTORY}lib/glimac/include  ${YOUR_DIRECTORY}lib/third-party/include)

add_subdirectory(lib/glimac)
set(LIB_LIST glimac -lmingw32 -lSDLmain -lSDL -lSDL_mixer -lfreeglut -lglew32s -lopengl32  )

add_executable(opengl ${SOURCE_FILES} ${HEADER_FILES} ${SHADER_FILES} src/niveau.cpp src/Triangle3D.cpp include/Triangle3D.h src/Sphere3D.cpp include/Sphere3D.h src/TransformMatrix.cpp include/TransformMatrix.h src/Object3D.cpp include/Object3D.h)
target_link_libraries(opengl ${LIB_LIST})




