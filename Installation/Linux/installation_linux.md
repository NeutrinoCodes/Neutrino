# Linux installation

## Overview
Neutrino is a C++ library that facilitates writing parallel code running on GPU hardware combining the power of the OpenCL computational framework with the OpenGL graphics language (see https://www.neutrino.codes).

Neutrino can be successfully installed and used on Linux by using the **VScode** editor toolchain or manually from a command shell.

## Hardware requirements:
A GPU having the **OpenCL-OpenGL interoperability GPU mode** is necessary.

This can be verified by installing and using the `clinfo` command line tool. After its installation, on a command terminal do:\
`clinfo`\
\
In the text output (it can be long!) there should be a section regarding your GPU, similar to this one:\
...\
`Name:                                          GeForce GTX 1060 6GB`\
`Vendor:                                        NVIDIA Corporation`\
`Driver version:                                451.67`\
`Profile:                                       FULL_PROFILE`\
`Version:                                       OpenCL 1.2 CUDA`\
`Extensions:                                    cl_khr_global_int32_base_atomics cl_khr_global_int32_extended_atomics cl_khr_local_int32_base_atomics cl_khr_local_int32_extended_atomics cl_khr_fp64 cl_khr_byte_addressable_store cl_khr_icd cl_khr_gl_sharing cl_nv_compiler_options cl_nv_device_attribute_query cl_nv_pragma_unroll cl_nv_d3d10_sharing cl_khr_d3d10_sharing cl_nv_d3d11_sharing cl_nv_copy_opts cl_nv_create_buffer cl_khr_int64_base_atomics cl_khr_int64_extended_atomics`\
...\
\
Please verify the presence of the `cl_khr_gl_sharing` extension. Some old GPU models do not have it: those ones would not be compatible with Neutrino.

## Software requirements:
- OpenCL (runtime/loader + headers), coming along the installation of the graphics drivers.
- OpenGL (library + headers), coming along the installation of the graphics drivers.
- GIT (https://git-scm.com)
- GLAD (https://glad.dav1d.de/) *
- GLFW (https://www.glfw.org/)
- GMSH (https://gmsh.info/)
- VScode (https://code.visualstudio.com/) **
- CMake (https://cmake.org) **
- GraphViz (https://graphviz.org/)
- Doxygen (https://www.doxygen.nl/)

\* The GLAD loader should be generated from its webpage using the following settings:
- Language = C/C++
- gl = Version 4.6 (or higher)
- Profile = Core

After having generated it, download the zip file containing the code and extract it in a custom directory (see *Installation*).

\** When using the **VScode editor**, please follow the instructions (https://code.visualstudio.com/docs/cpp/config-linux) in order to install it and verify the installation of GCC, as well as the instructions (https://code.visualstudio.com/docs/cpp/cmake-linux) to verify the installation of Cmake and to install the Cmake Tools extension for VSCode.

We assume Neutrino is going to be installed in a directory named *NeutrinoCodes* containing the following subdirectories:
- glad
- glfw
- gmsh

From the command shell (either VScode's or system's), navigate into *NeutrinoCodes* and create a `libnu` directory using the command:\
`mkdir libnu`\
\
This will create the `libnu` directory.

From the command shell (either VScode's or system's), navigate into *NeutrinoCodes* and clone the Neutrino project using the command:\
`git clone https://github.com/NeutrinoCodes/neutrino.git` \
\
This will create the `neutrino` directory.

## Installation: (VScode toolchain)
Go to the `neutrino` directory and create a `.vscode` hidden directory:\
`mkdir .vscode`\
\
and create a new file `settings.json` in it, then fill it with the following information:\
`{`\
&nbsp;&nbsp;`"cmake.configureSettings":`\
&nbsp;&nbsp;`{`\
&nbsp;&nbsp;&nbsp;&nbsp;`"GLAD_PATH": "your_path_to_NeutrinoCodes/glad",`\
&nbsp;&nbsp;&nbsp;&nbsp;`"GLFW_PATH": "your_path_to_NeutrinoCodes/glfw",`\
&nbsp;&nbsp;&nbsp;&nbsp;`"GMSH_PATH": "your_path_to_NeutrinoCodes/gmsh",`\
&nbsp;&nbsp;&nbsp;&nbsp;`"CL_PATH": "your_path_to_OpenCL",`\
&nbsp;&nbsp;&nbsp;&nbsp;`"NEUTRINO_PATH": "your_path_to_NeutrinoCodes/libnu"`\
&nbsp;&nbsp;`}`\
`}`\
\
and save it.

At this point, Neutrino is configured for your system. 

In VScode, open a folder from the file menu and select NeutrinoCodes. Go to the left bar and locate the **CMake** button (it comes after the installation of the CMake Tools extension for VScode) and push it: a CMake panel will open, push the **Configure All Projects** button on it.

Go to the bottom bar and locate:
- the **Build variant** button: verify it has been selected to **[Release]**.
- the **Active kit** button: verify it has been selected according to your system's characteristics. e.g. **[Visual Studio Community 2019 Release - amd64]**.
- the **Target** button: verify it has been selected to **[install]**.
- the **Build** button: push it in order to build the Neutrino project.

At this point the NeutrinoCodes directory should appear like this:
- glad
- glfw
- gmsh
- libnu
- neutrino

We all like tidy code! For this, we provide an **Uncrustify** (sources: https://github.com/uncrustify/uncrustify) configuration file specific for Neutrino. In order to use it, please first install Uncrustify according to your operating system (e.g. use Homebrew under Mac), then install the VScode's *Uncrustify extension* (https://marketplace.visualstudio.com/items?itemName=LaurentTreguier.uncrustify).\
\
Add the following lines to either the *global* or *project* **settings.json** file:
`"uncrustify.executablePath.linux": "your_path_to_uncrustify",`\
`"editor.defaultFormatter": "LaurentTreguier.uncrustify",`\
`"editor.formatOnSave": true`
\
To edit the *global* settings, on VScode go to the left bar: push the **Extensions** button and select the Uncrustify extension. Then go to **Manage --> Extension Settings** (gear-like icon) and edit the `settings.json` file by clicking one of the links in that section. This will set the Uncrustify code formatter globally in all your VScode projects (but still with per-project custom uncrustify configuration files).\
\
To edit the *project* settings, open `settings.json` file in the `.vscode` you created for Neutrino (the hidden directory inside the `Neutrino` directory) and put the same lines in it. This will set Uncrustify as code formatter (together with the configuration file we provide) only for the Neutrino project.

Congratulations, you have installed Neutrino on Linux within the VScode toolchain!

## Installation: (command shell)
From a system command shell, navigate into your favourite directory and clone the Neutrino project using the command git clone https://github.com/NeutrinoCodes/neutrino.git.

Into the Neutrino's project directory, create a configuration script file called `configure_linux` and edit it by adding the following command lines:\
`cmake -B"./cmake" -H"./" \`\
`-DGLAD_PATH=your_path_to_glad \`\
`-DGLFW_PATH=your_path_to_glfw \`\
`-DGMSH_PATH=your_path_to_gmsh \`\
`-DCL_PATH=your_path_to_opencl \`\
`-DNEUTRINO_PATH=your_path_to_neutrino`\
\
and specify the paths accordingly, where:

*GLAD_PATH* is the path of the root directory of the Glad library: it contains the src and include subdirectories;

*GLFW_PATH* is the path of the root directory of the Glfw library: it contains the include subdirectory;

*GMSH_PATH* is the path of the root directory of the Gmsh library: it contains the include and lib subdirectories;

*CL_PATH* is the path of the root directory of the OpenCL library: it contains the include and lib subdirectories;

*NEUTRINO_PATH* is the path of Neutrino's project folder and should be followed by /libnu, where the library will be installed.

Make the configuration script to be executable (`chmod a+x configure_linux`) and launch it by typing `./configure_linux` at the command prompt. The CMake configuration files will be generated.

Enter the cmake directory and type `make install` (use `make clean` to remove old build files if necessary).

Congratulations, you have installed Neutrino on Linux within the command shell toolchain!