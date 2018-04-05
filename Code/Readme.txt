EZOR: 10MAR2018
On Mac I can compile the project with g++ as follows:
g++ main.cpp context.cpp opencl.cpp opengl.cpp program.cpp  -o neutrino -I/Users/Erik/.CMVolumes/Erik\ Zorzin/Erik_Alessandro/Neutrino/include -framework OpenCL -framework OpenGL -lGLEW -lglfw

I used this as a debug for the Cmake compilation.

EZOR: 11MAR2018
I reorganized the folders. THe folder "cmake" is the one where cmake puts all its temporary stuff.
Can be deleted: cmake will recreate it the next time it is invoked.
I use the "Atom editor": I installed the packages:

1)  linter-gcc, configured this way;
    GCC executable path: /usr/local/bin/g++
    C flags: -c -Wall
    C++ flags: -c -Wall -std=c++11 -fsyntax-only
    GCC include paths: ./include/*
    GCC error limit: 0
    Suppress GCC warnings: unchecked
    String GCC prepends to Error:  errors
    String GCC prepends to warnings: warning
    String GCC prepends to notes: note
    Lint on-the-fly: checked
    Lint on-the-fly interval: 300
    Compile commands file: ./build/compile_commands.json

2)  build-cmake:
    Cmake executable: cmake
    Cmake lists: ...empty...
    Custom cmakr arguments: -DCMAKE_BUILD_TYPE=Debug
    Build location: $PROJECT_DIR/cmake
    Custom buils tool arguments: ...empty...
    Parallel build: checked

In order to build with cmake do as follows:
1) Atom editor: Packages-->Build-->Build project (F9)
2) After this, open a terminal, go to the "cmake" folder and do: make
3) The latter command will put the executable in build/mac or build/linux, according to the OS.
