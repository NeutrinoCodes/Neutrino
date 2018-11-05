message("Checking cmake version...")
cmake_minimum_required(VERSION 3.0)

message("")
message("################################################################################")
message("##################################### GCC ######################################")
message("################################################################################")
message("")

# Type: "make" in order to build the project.

message("Setting project name...")
project (neutrino)

message("Creating a SOURCES variable with a link to all cpp files to compile...")
set(SOURCES
src/color4.cpp
src/device.cpp
src/float1.cpp
src/float4.cpp
src/font.cpp
src/info.cpp
src/int1.cpp
src/int4.cpp
src/kernel.cpp
src/linear_algebra.cpp
src/main.cpp
src/neutrino.cpp
src/opencl.cpp
src/opengl.cpp
src/path.cpp
src/platform.cpp
src/point4.cpp
src/projective_geometry.cpp
src/queue.cpp
src/text4.cpp
src/window.cpp)

message("Adding an executable with the above sources...")
add_executable(neutrino ${SOURCES})

message("Setting the directories that should be included in the build command...")
target_include_directories(neutrino PRIVATE ${CMAKE_HOME_DIRECTORY}/include)

if(UNIX AND NOT APPLE)
  message("Setting LINUX variable, according to an existing LINUX (but not APPLE) OS...")
  set(LINUX TRUE)
endif()

if(APPLE)
  message("Setting directory for the Mac executable...")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build/mac)
endif(APPLE)

if(LINUX)
  message("Setting directory for the Linux executable...")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build/linux)
endif(LINUX)

if(APPLE)
  message("Setting the Mac libraries that should be linked in the build command...")
  target_link_libraries(neutrino "-framework OpenGL" "-framework OpenCL" "-lGLEW" "-lglfw" "-lm")
endif(APPLE)

if(LINUX)
  message("Setting the Linux libraries that should be linked in the build command...")
  target_link_libraries(neutrino "-lOpenGL" "-lOpenCL" "-lGLEW" "-lglfw" "-lm")
endif(LINUX)

# Type: "make run" to run the executable.
add_custom_target(run
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/neutrino
    VERBATIM )

message("Limiting number of reported gcc errors...[# = 20]")
set(GCC_MAX_ERRORS "-fmax-errors=20")
set(GCC_C14 "-std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_MAX_ERRORS} ${GCC_C14}")

message("DONE configuring GCC!")

message("")
message("################################################################################")
message("#################################### DOXYGEN ###################################")
message("################################################################################")
message("")

# Type: "make doc" in order to build the Doxygen documentation of the project.

message("Checking whether Doxygen is installed...")
find_package(Doxygen)
if (DOXYGEN_FOUND)
    message("Setting input and output files...")
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/../Docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    message("Requesting to configure the file...")
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("DONE configuring Doxygen!")

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation!")
endif (DOXYGEN_FOUND)
