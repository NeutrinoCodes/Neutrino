message("Checking cmake version...")
cmake_minimum_required(VERSION 3.0)

message("")
message("################################################################################")
message("##################################### GCC ######################################")
message("################################################################################")
message("")

# Type: "make" in order to build the project.

if(UNIX AND NOT APPLE)
  message("Setting LINUX variable, according to an existing LINUX (but not APPLE) OS...")
  set(LINUX TRUE)
endif()

message("Setting project name...")
project (neutrino)

message("Creating a SOURCES variable with a link to all cpp files to compile...")
aux_source_directory("src/" SRC_DIR)

message("Creating a SOURCES variable with a link to all cpp files to compile...")
set(SOURCES ${SRC_DIR} ${GLAD_PATH}/src/glad.c)

if(APPLE)
  message("Setting directory for the Mac executable...")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build/mac)
endif(APPLE)

if(LINUX)
  message("Setting directory for the Linux executable...")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build/linux)
endif(LINUX)

message("Adding an executable with the above sources...")
add_executable(neutrino ${SOURCES})

if(APPLE)
message("Setting the directories that should be included in the build command for Mac...")
target_include_directories(
neutrino PRIVATE ${CMAKE_HOME_DIRECTORY}/include
${GLAD_PATH}/include
${GLFW_PATH}/include
)
endif(APPLE)

if(LINUX)
message("Setting the directories that should be included in the build command for Linux...")
target_include_directories(
neutrino PRIVATE ${CMAKE_HOME_DIRECTORY}/include
${GLAD_PATH}/include
${GLFW_PATH}/include
)
endif(LINUX)

if(WIN32)
message("Setting the directories that should be included in the build command for Windows...")
target_include_directories(
neutrino PRIVATE ${CMAKE_HOME_DIRECTORY}/include
${GLAD_PATH}/include
${GLFW_PATH}/include
${CL_PATH}/include
)
endif(WIN32)

if(APPLE)
  message("Setting the libraries that should be linked in the build command for Mac...")
  set(GLFW_LIBRARY ${GLFW_PATH}/lib-macos/libglfw.3.dylib)
  target_link_libraries(neutrino "-framework OpenGL" "-framework OpenCL" ${GLFW_LIBRARY} "-lm")
endif(APPLE)

if(LINUX)
  message("Setting the libraries that should be linked in the build command for Linux...")
  set(GLFW_LIBRARY ${GLFW_PATH}/lib-macos/libglfw.3.dylib)
  #target_link_libraries(neutrino "-lOpenGL" "-lOpenCL" "-ldl" "-lglfw" "-lm")  EZOR 28JUL2019: original.
  target_link_libraries(neutrino "-lOpenGL" "-lOpenCL" ${GLFW_LIBRARY} "-lm")   # To be tested.
endif(LINUX)

if(WIN32)
  message("Setting the libraries that should be linked in the build command for Windows...")
  set(GLFW_LIBRARY ${GLFW_PATH}/lib-vc2019/glfw3.lib)
  set(CL_LIBRARY ${CL_PATH}/lib/x64/OpenCL.lib)
  target_link_libraries(${PROJECT_NAME} ${CL_LIBRARY} ${GLFW_LIBRARY})
endif(WIN32)

# Type: "make run" to run the executable.
add_custom_target(run
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMAND neutrino
    VERBATIM )

message("Limiting number of reported gcc errors...[# = 20]")
set(GCC_MAX_ERRORS "-fmax-errors=20")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_MAX_ERRORS}")

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
