# NEUTRINO LIBRARY

<p align="center">
<img src="./Logos/neutrino_logo.png" width="200" height="200" />
</p>

*A fast and light library for GPU-based computation and interactive data visualization.*

[www.neutrino.codes](https://www.neutrino.codes)

# Overview
Neutrino is a C++ library that facilitates writing parallel code running on GPU hardware combining the power of the OpenCL computational framework with the OpenGL graphics language (see https://www.neutrino.codes).

Neutrino can be successfully installed and used on Linux (see: [Linux installation](./Installation/Linux/installation_linux.md)), Mac (see: [Mac installation](./Installation/Mac/installation_mac.md)) or Windows (see: [Windows installation](./Installation/Windows/installation_windows.md)).

# Hardware requirements
- GPU having the **OpenCL-OpenGL interoperability mode** (`cl_khr_gl_sharing` extension under Linux or Windows, `cl_APPLE_gl_sharing` extension under Mac).

# Software requirements
- Clinfo (https://github.com/Oblomov/clinfo)
- OpenCL (runtime/loader + headers)
- OpenGL (library + headers)
- GIT (https://git-scm.com)
- GLAD (https://glad.dav1d.de/)
- GLFW (https://www.glfw.org/)
- GMSH (https://gmsh.info/)
- GCC (https://gcc.gnu.org)
- CMake (https://cmake.org)
- GraphViz (https://graphviz.org/)
- Doxygen (https://www.doxygen.nl/)

## Examples
In order to test the installation of Neutrino and to start experimenting with it, please go to the *Examples* repository: https://github.com/NeutrinoCodes/Examples.

© Alessandro LUCANTONIO, Erik ZORZIN - 2018-2020