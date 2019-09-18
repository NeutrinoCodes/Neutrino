message("Checking cmake version...")
cmake_minimum_required(VERSION 3.0)

message("")
message("################################################################################")
message("################################ C/C++ COMPILER ################################")
message("################################################################################")

if(UNIX AND NOT APPLE)
  message("Setting LINUX variable, according to an existing LINUX (but not APPLE) OS...")
  set(LINUX TRUE)
endif()

project (neutrino)                                                              # Project name.
message("Project name = ${PROJECT_NAME}")

message("Setting project source directories...")
aux_source_directory("src/" SRC_DIR)                                            # Project sources.
set(SOURCES ${SRC_DIR} ${GLAD_PATH}/src/glad.c)

if(APPLE)
  message("Setting Mac build directory...")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build/mac)
endif(APPLE)

if(LINUX)
  message("Setting Linux build directory ...")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build/linux)
endif(LINUX)

message("Adding an executable with the above sources...")
add_executable(${PROJECT_NAME} ${SOURCES})

if(APPLE)
message("Setting Mac include directories...")
target_include_directories(
${PROJECT_NAME} PRIVATE ${CMAKE_HOME_DIRECTORY}/include
${GLAD_PATH}/include
${GLFW_PATH}/include
)
endif(APPLE)

if(LINUX)
message("Setting Linux include directories...")
target_include_directories(
${PROJECT_NAME} PRIVATE ${CMAKE_HOME_DIRECTORY}/include
${GLAD_PATH}/include
)
endif(LINUX)

if(WIN32)
message("Setting Windows include directories...")
target_include_directories(
${PROJECT_NAME} PRIVATE ${CMAKE_HOME_DIRECTORY}/include
${GLAD_PATH}/include
${GLFW_PATH}/include
${CL_PATH}/include
)
endif(WIN32)

if(APPLE)
  message("Setting Mac library directories...")
  set(GLFW_LIBRARY ${GLFW_PATH}/lib-macos/libglfw.3.dylib)
  target_link_libraries(${PROJECT_NAME} "-framework OpenGL" "-framework OpenCL" ${GLFW_LIBRARY} "-lm")
endif(APPLE)

if(LINUX)
  message("Setting Linux library directories...")
  set(GLFW_LIBRARY ${GLFW_PATH}/src/libglfw3.a)
  target_link_libraries(${PROJECT_NAME} "-lOpenGL" "-lOpenCL" "-ldl" "-lglfw" "-lm")  # EZOR 28JUL2019: original.
  #target_link_libraries(${PROJECT_NAME} "-lOpenGL" "-lOpenCL" ${GLFW_LIBRARY} "-lm")   # To be tested.
endif(LINUX)

if(WIN32)
  message("Setting Windows library directories...")
  set(GLFW_LIBRARY ${GLFW_PATH}/lib-vc2019/glfw3.lib)
  #set(CL_LIBRARY $"C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v10.1/lib/x64/OpenCL.lib")
  target_link_libraries(${PROJECT_NAME} ${CL_PATH}/lib/x64/OpenCL.lib ${GLFW_LIBRARY})
endif(WIN32)

add_custom_target(run
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMAND ${PROJECT_NAME}
    VERBATIM)

#message("Limiting number of reported gcc errors (# = 20)...")
#set(GCC_MAX_ERRORS "-fmax-errors=20")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_MAX_ERRORS}")

message("DONE!")

message("")
message("################################################################################")
message("#################################### DOXYGEN ###################################")
message("################################################################################")

message("Checking whether Doxygen is installed...")
find_package(Doxygen)
if (DOXYGEN_FOUND)
    message("Setting input and output files...")
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/../Docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    message("Requesting to configure the file...")
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("DONE!")

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation!")
endif (DOXYGEN_FOUND)

message("")
message("################################################################################")
message("################################# INSTRUCTIONS #################################")
message("################################################################################")

message("Now go to the \"./cmake\" directory created by this command and do one (or more) of the following things:")
message("")
message("1. Type: \"make\" in order to build the executable.")
message("2. Type: \"make run\" in order to build and run the executable.")
message("3. Type: \"make doc\" in order to build the Doxygen documentation of the project.")
message("")
message("################################################################################")
message("############################# CONFIGURATION REPORT #############################")
message("################################################################################")
