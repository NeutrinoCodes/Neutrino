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

# Hardware requirements
- GPU having the **OpenCL-OpenGL interoperability mode** (`cl_khr_gl_sharing` extension available: it can be verified by running Clinfo).

This can be verified by installing and using the `clinfo` command line tool. The tool can be obtained via the Linux package manager (which ont depends on the Linux distribution you have) or for both Linux and Windows by downloading it from: https://github.com/Oblomov/clinfo. After its installation, on a command terminal window do:\
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
Please **verify the presence** of the `cl_khr_gl_sharing` extension. Some **old GPU** models **do not have it**: those ones **would not work** with Neutrino.

# Installation
## Foreword
On Linux many (possibly all) of the following requirements can be obtained directly by installing them from its own available **package manager**, according to the distribution of Linux you have installed on your PC. Alternatively, they can be downloaded (also cloned via GIT, if they are Github repositories) from the suggested links.

On Windows, since there is no package manager, you should follow this alternative only.

## 1. Install GIT
It is used for downloading/cloning other Neutrino dependencies. Moreover, it is very useful also for organizing your own projects as well.
Go to: https://git-scm.com and download/install it wherever it suggests you.

## 2. Install Neutrino

From a **command shell** create a *NeutrinoCodes* directory, then navigate into it and clone the Neutrino project using the command:\
`git clone https://github.com/NeutrinoCodes/neutrino.git`

This will create the following directory structure:\
`NeutrinoCodes`\
` └───neutrino`


## 2. Install the OpenGL/CL video drivers
Please refere to the **manufacturer** of your **video card**. What you need is: 
- OpenCL (runtime/loader + headers)
- OpenGL (library + headers)
  
e.g. if you have an Nvidia card, go to their webpage and download their SDK. 

Do this on Windows. On Linux you can search the package manager as well.
Download/install it wherever it suggests you, but **take note of its location for later!**

e.g. on Windows, if you have an Nvidia card, it can be something like this: 
`C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v10.1`

Notice the path **must** be specificed with *double backslashes*, in order to correctly manage the possibility of space characters in the them.
Also notice that `your_path_to_OpenCL` might be something like this (it depends on your GPU's graphics drivers):\

## 3. Install the GLAD loader
This library is for loading the OpenGL context. Goto: https://glad.dav1d.de/
 and **generate the loader from its webpage** using the following settings:
- Language = C/C++
- gl = Version 4.6 (or higher)
- Profile = Core

After having generated it, **download the zip file** containing the code and extract it in: `glad` inside `NeutrinoCodes`.

At this point you should have this directory structure:\
`NeutrinoCodes`\
` ├───glad`\
` └───neutrino`


This other library is for creating an OpenGL window:
- GLFW (https://www.glfw.org/)



- GMSH (https://gmsh.info/) **
- IMGUI (https://github.com/ocornut/imgui)
- IMPLOT (https://github.com/epezent/implot)
- GCC (https://gcc.gnu.org) **if using Linux**
- Visual Studio (https://visualstudio.microsoft.com/) **if using Windows**
- CMake (https://cmake.org)
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