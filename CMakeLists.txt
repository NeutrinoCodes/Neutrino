cmake_minimum_required(VERSION 3.0)

# Setting LINUX variable, according to an existing LINUX (but not APPLE) OS...
if(UNIX AND NOT APPLE)
  set(LINUX TRUE)
endif()

# Setting project name...
project (neutrino)

# Creating a SOURCES variable with a link to all cpp files to compile...
set(SOURCES
src/context.cpp
src/data.cpp
src/interop.cpp
src/main.cpp
src/opencl.cpp
src/opengl.cpp
src/program.cpp
src/utils.cpp)

# Setting directory for the Mac executable...
if(APPLE)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build/mac)
endif(APPLE)

# Setting directory for the Linux executable...
if(LINUX)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build/linux)
endif(LINUX)

# Adding an executable with the above sources...
add_executable(neutrino ${SOURCES})

# Setting the directories that should be included in the build command...
target_include_directories(neutrino PRIVATE ${CMAKE_HOME_DIRECTORY}/include)

# Setting the Mac libraries that should be linked in the build command...
if(APPLE)
  # Setting the libraries that should be linked in the build command...
  target_link_libraries(neutrino "-framework OpenGL" "-framework OpenCL" "-lGLEW" "-lglfw")
endif(APPLE)

# Setting the Linux libraries that should be linked in the build command...
if(LINUX)
  # Setting the libraries that should be linked in the build command...
  target_link_libraries(neutrino "-lOpenGL" "-lOpenCL" "-lGLEW" "-lglfw")
endif(LINUX)
