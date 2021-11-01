# NEUTRINO LIBRARY

<p align="center">
<img src="./Logos/neutrino_logo.png" width="200" height="200" />
</p>

*A fast and light library for GPU-based computation and interactive data visualization.*

[www.neutrino.codes](https://www.neutrino.codes)

© Alessandro LUCANTONIO, Erik ZORZIN - 2018-2021

# Overview
Neutrino is a C++ library that facilitates writing parallel code running on GPU hardware combining the power of the OpenCL computational framework with the OpenGL graphics language (see https://www.neutrino.codes).

Neutrino can be installed on Linux (see: [Linux installation](./Installation/Linux/installation_linux.md)) or Windows (see: [Windows installation](./Installation/Windows/installation_windows.md)).

# Hardware requirements
- GPU having the **OpenCL-OpenGL interoperability mode** (`cl_khr_gl_sharing` extension available: it can be verified by running Clinfo).

# Software requirements
- Clinfo (https://github.com/Oblomov/clinfo)
- OpenCL (runtime/loader + headers)
- OpenGL (library + headers)
- GIT (https://git-scm.com)
- GLAD (https://glad.dav1d.de/)
- GLFW (https://www.glfw.org/)
- GMSH (https://gmsh.info/)
- IMGUI (https://github.com/ocornut/imgui)
- GCC (https://gcc.gnu.org) if using Linux
- Visual Studio (https://visualstudio.microsoft.com/) is using Windows
- CMake (https://cmake.org)
- GraphViz (https://graphviz.org/)
- Doxygen (https://www.doxygen.nl/)
- DS4Windows (https://ryochan7.github.io/ds4windows-site/) optional for Windows, in case you want to use the PS4 Dual Shock gamepad (not required others for HID compliant gamepads).

## Examples
Neutrino-based example applications che be found at the *Examples* repository: https://github.com/NeutrinoCodes/Examples.

© Alessandro LUCANTONIO, Erik ZORZIN - 2018-2021