# NEUTRINO LIBRARY

<p align="center">
<img src="./Logos/neutrino_logo.png" width="200" height="200" />
</p>

*A fast and light library for GPU-based computation and interactive data visualization.*

[www.neutrino.codes](https://www.neutrino.codes)

© Alessandro LUCANTONIO, Erik ZORZIN - 2018-2022

# Overview
Neutrino is a C++ library that facilitates writing parallel code running on GPU hardware combining the power of the OpenCL computational framework with the OpenGL graphics language (see https://www.neutrino.codes).

Neutrino can be installed on **Linux** and **Windows**.

**On Linux** the following requirements can be fulfilled directly by installing software packages from its own **package manager**, according to the distribution of Linux you have installed on your PC. Alternatively, they can be downloaded (also cloned via GIT, if they are Github repositories) from the suggested links.

**On Windows**, since there is no package manager, you should follow this latter alternative only.

Neutrino requires a GPU having the **OpenCL-OpenGL interoperability mode**.

This can be verified by installing and using the `clinfo` command line tool. The tool can be obtained from: https://github.com/Oblomov/clinfo. After its installation, on a command terminal window do:\
`clinfo`\
\
In the **text output** (it can be long!) there should be a section regarding your GPU, similar to this one:\
...\
`Name:                                          GeForce GTX 1060 6GB`\
`Vendor:                                        NVIDIA Corporation`\
`Driver version:                                451.67`\
`Profile:                                       FULL_PROFILE`\
`Version:                                       OpenCL 1.2 CUDA`\
`Extensions:                                    cl_khr_global_int32_base_atomics cl_khr_global_int32_extended_atomics cl_khr_local_int32_base_atomics cl_khr_local_int32_extended_atomics cl_khr_fp64 cl_khr_byte_addressable_store cl_khr_icd cl_khr_gl_sharing cl_nv_compiler_options cl_nv_device_attribute_query cl_nv_pragma_unroll cl_nv_d3d10_sharing cl_khr_d3d10_sharing cl_nv_d3d11_sharing cl_nv_copy_opts cl_nv_create_buffer cl_khr_int64_base_atomics cl_khr_int64_extended_atomics`\
...\
\
Please **verify the presence** of the `cl_khr_gl_sharing` extension. Some **old GPU** models **do not have it**: those ones **would not work** with Neutrino.

# Installation

## 1. Install C++
It is used for compiling Neutrino and all its Examples.\
On Linux, install GCC: https://gcc.gnu.org and Cmake: https://cmake.org.\
On Windows, install Visual Studio: https://visualstudio.microsoft.com/ with the **C++ CMake tools for Windows** by selecting it from the **Desktop development with C++** workload during the installation.

## 2. Install GIT
It is used for downloading/cloning Neutrino and some of its dependencies. Moreover, it is very useful also for organizing your own projects as well.
Go to: https://git-scm.com and install it wherever it suggests you.

## 3. Install OpenGL and OpenCL
Please refer to the **manufacturer** of your **video card**. What you need is: 
- OpenCL (runtime/loader + headers)
- OpenGL (library + headers)
  
e.g. On Windows, if you have an Nvidia card go to their webpage and download their SDK. Then install it wherever it suggests you, it can be something like this:\
`C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v10.1`

**Take note of this path**, later on we will refer to it as: `your_path_to_OpenCL`.

Since now, notice all those kind of paths will be specificed with **double backslashes**, in order to correctly manage the possibility of space characters in the them.

## 4. Install Neutrino

, then navigate into it and clone the Neutrino project using the command:\
`git clone https://github.com/NeutrinoCodes/neutrino.git`

This will create the following directory structure:\
`NeutrinoCodes`\
` └───neutrino`

## 5. Install GLAD
This library is for loading pointers to OpenGL functions at runtime, core as well as extensions.\
Goto: https://glad.dav1d.de/
 and **generate the loader from its webpage** using the following settings:
- Language = C/C++
- gl = Version 4.6 (or higher)
- Profile = Core

After having generated it, **download the zip file** containing the code.
On your PC, create a `NeutrinoCodes` directory, then create a `glad` directory in it and extract the zip file you have downloaded.

At this point you should have this directory structure:\
`NeutrinoCodes`\
` └───glad`

## 6. Install GLFW
This library is for creating an OpenGL window. Download it from: https://www.glfw.org/ and copy it to a `glfw` directory you have to create in the `NeutrinoCodes` parent directory.

At this point you should have this directory structure:\
`NeutrinoCodes`\
` ├───glad`\
` └───glfw`

## 7. Install GMSH
This software: https://gmsh.info/ is for the creation and the manipulation of 1D, 2D and 3D meshes: this is a useful tool in order to define the connectivity of the cellular automata in Neutrino. Install it in a `gmsh` directory you have to create in the `NeutrinoCodes` parent directory.

**IMPORTANT NOTE FOR GMSH INSTALLATION ON WINDOWS**: GMSH is used in Neutrino as an API library. Under a Windows purely native environment (which is the case of Windows + the Visual Studio compiler) there is a limitation (see https://gitlab.onelab.info/gmsh/gmsh/-/issues/894) and because of this the GMSH API can used only as an external DLL. In order to install it on Windows, please download the GMSH's *Software Development Kit (SDK) for Windows* (64-bit or 32-bit, according to your operating system) and follow this procedure:
- after having downloaded the GMSH's SDK `.zip` file, extract it and copy the `gmsh` directory into the `NeutrinoCodes` directory.
- go to the `include` directory in the `gmsh` directory and rename the `gmsh.h` file `gmsh.h_original`.
- in the same directory, rename the `gmsh.h_cwrap` file to `gmsh.h`.
- go to the `lib` directory in the `gmsh` directory and copy che GMSH DLL file into `C.\Windows\System32`.

This should make the GMSH's API working on Windows.

At this point you should have this directory structure:\
`NeutrinoCodes`\
` ├───glad`\
` ├───glfw`\
` └───gmsh`

- IMGUI (https://github.com/ocornut/imgui)
- IMPLOT (https://github.com/epezent/implot)

- GraphViz (https://graphviz.org/)
- Doxygen (https://www.doxygen.nl/)
- DS4Windows (https://ryochan7.github.io/ds4windows-site/) optional for Windows, in case you want to use the PS4 Dual Shock gamepad (not required others for HID compliant gamepads, but anyway recommended in case Windows gets crazy because of multiple HID instances: https://ds4-windows.com/drivers/).

\* The GLAD loader should be generated from its webpage using the following settings:
- Language = C/C++
- gl = Version 4.6 (or higher)
- Profile = Core

After having generated it, download the zip file containing the code and extract it in a custom directory (see OS-specific installation notes ([Linux installation](./Installation/Linux/installation_linux.md), [Windows installation](./Installation/Windows/installation_windows.md)).

\** See OS-specific installation notes ([Linux installation](./Installation/Linux/installation_linux.md), [Windows installation](./Installation/Windows/installation_windows.md)).

In case you develop under both Windows and Linux, you might also consider using VScode: https://code.visualstudio.com/. This gives you the same developing environment under both systems.
Please, see the specific installation instructions
([Linux installation](./Installation/Linux/installation_linux.md), [Windows installation](./Installation/Windows/installation_windows.md)).

## Examples
Neutrino-based example applications che be found, **together with their installation instructions as well**, at the *Examples* repository: https://github.com/NeutrinoCodes/Examples.

© Alessandro LUCANTONIO, Erik ZORZIN - 2018-2022