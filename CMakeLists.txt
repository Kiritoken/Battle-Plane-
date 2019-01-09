cmake_minimum_required(VERSION 3.13)
project(EBattle_Plane)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")

SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3")
set(CMAKE_CXX_FLAGS "-fPIC")

#Required packages
find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)
find_package(CUDA REQUIRED)
find_package(Thrust REQUIRED)
find_package(GLFW REQUIRED)
find_package(GLEW REQUIRED)

include_directories("${CUDA_INCLUDE_DIRS}")

#CUDA NVCC SETTINGS
list(APPEND CUDA_NVCC_FLAGS "-arch=sm_20;-std=c++11;-O2;-DVERBOSE;-D_FORCE_INLINES")
SET(CUDA_PROPAGATE_HOST_FLAGS OFF)


#link
LINK_LIBRARIES(glfw3)
LINK_LIBRARIES(X11)
LINK_LIBRARIES(Xxf86vm)
LINK_LIBRARIES(Xrandr)
LINK_LIBRARIES(pthread)
LINK_LIBRARIES(Xi)
LINK_LIBRARIES(Xcursor)
LINK_LIBRARIES(Xinerama)
LINK_LIBRARIES(GLU)
LINK_LIBRARIES(dl)
LINK_LIBRARIES(GLEW)
LINK_LIBRARIES(GL)

add_executable(EBattle_Plane src/main.cpp src/viewer/viewer.cpp src/viewer/viewer.h src/GameScene/game_scene.cpp src/GameScene/game_scene.h src/object/flying_object.cpp src/object/flying_object.h src/object/player_plane.cpp src/object/player_plane.h)