message("Checking cmake version...")
cmake_minimum_required(VERSION 3.0)

message("")
message("################################################################################")
message("##################################### GCC ######################################")
message("################################################################################")
message("")

message("Setting LINUX variable, according to an existing LINUX (but not APPLE) OS...")
if(UNIX AND NOT APPLE)
  set(LINUX TRUE)
endif()

message("Setting project name...")
project (neutrino)

message("Creating a SOURCES variable with a link to all cpp files to compile...")
set(SOURCES
src/context.cpp
src/data.cpp
src/interoperability.cpp
src/linear_algebra.cpp
src/main.cpp
src/opencl.cpp
src/opengl.cpp
src/program.cpp
src/projective_geometry.cpp
src/utilities.cpp)

message("Setting directory for the Mac executable...")
if(APPLE)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build/mac)
endif(APPLE)

message("Setting directory for the Linux executable...")
if(LINUX)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build/linux)
endif(LINUX)

message("Adding an executable with the above sources...")
add_executable(neutrino ${SOURCES})

message("Setting the directories that should be included in the build command...")
target_include_directories(neutrino PRIVATE ${CMAKE_HOME_DIRECTORY}/include)

message("Setting the Mac libraries that should be linked in the build command...")
if(APPLE)
  message("Setting the libraries that should be linked in the build command...")
  target_link_libraries(neutrino "-framework OpenGL" "-framework OpenCL" "-lGLEW" "-lglfw" "-lm" "-g")
endif(APPLE)

message("Setting the Linux libraries that should be linked in the build command...")
if(LINUX)
  message("Setting the libraries that should be linked in the build command...")
  target_link_libraries(neutrino "-lOpenGL" "-lOpenCL" "-lGLEW" "-lglfw" "-lm")
endif(LINUX)

message("GCC build started!")

message("")
message("################################################################################")
message("#################################### DOXYGEN ###################################")
message("################################################################################")
message("")

message("Indicating the documentation build as an option and setting it to ON by default...")
option(BUILD_DOC "Build documentation" ON)

message("Checking if Doxygen is installed...")
find_package(Doxygen)
if (DOXYGEN_FOUND)
    message("Setting input and output files...")
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/../Docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    message("Requesting to configure the file...")
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started!")

    # Note the option ALL which allows to build the docs together with the application:
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation!")
endif (DOXYGEN_FOUND)
