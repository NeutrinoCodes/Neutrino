# Windows installation

## Overview
Neutrino is a C++ library that facilitates writing parallel code running on GPU hardware combining the power of the OpenCL computational framework with the OpenGL graphics language (see https://www.neutrino.codes).

Neutrino can be successfully installed and used on Windows by using the **Visual Studio** IDE or **VScode** editor toolchain.



## Software requirements:
- OpenCL (runtime/loader + headers), coming along the installation of the graphics drivers.
- OpenGL (library + headers), coming along the installation of the graphics drivers.
- GIT (https://git-scm.com)
- GLAD (https://glad.dav1d.de/) *
- GLFW (https://www.glfw.org/)
- GMSH (https://gmsh.info/)
- IMGUI (https://github.com/ocornut/imgui)
- IMPLOT (https://github.com/epezent/implot)
- Visual Studio (https://visualstudio.microsoft.com/) **
- CMake (https://cmake.org) **
- GraphViz (https://graphviz.org/)
- Doxygen (https://www.doxygen.nl/)
- DS4Windows (https://ryochan7.github.io/ds4windows-site/) optional for Windows, in case you want to use the PS4 Dual Shock gamepad (not required others for HID compliant gamepads).

\* The GLAD loader should be generated from its webpage using the following settings:
- Language = C/C++
- gl = Version 4.6 (or higher)
- Profile = Core

After having generated it, download the zip file containing the code and extract it in a custom directory (see *Installation*).

\** When using the **VScode editor**, please follow the instructions (https://code.visualstudio.com/docs/cpp/config-msvc) in order to install it and verify the installation of Visual Studio, as well as the instructions (https://code.visualstudio.com/docs/cpp/cmake-linux, there are no specific instructions for Windows) to verify the installation of Cmake and to install the Cmake Tools extension for VSCode. If using only the **Visual Studio** IDE instead of the VScode editor, please install also the Cmake Tools extension for Visual Studio.

**IMPORTANT NOTE FOR GMSH INSTALLATION ON WINDOWS**: GMSH is used in Neutrino as an API library. Under a Windows purely native environment (which is the case of Windows + the Visual Studio compiler) there is a limitation (see https://gitlab.onelab.info/gmsh/gmsh/-/issues/894) and because of this the GMSH API can used only as an external DLL. In order to install it on Windows, please download the GMSH's *Software Development Kit (SDK) for Windows* (64-bit or 32-bit, according to your operating system) and follow this procedure:
- after having downloaded the GMSH's SDK `.zip` file, extract it and copy the `gmsh` directory into the `NeutrinoCodes` directory.
- go to the `include` directory in the `gmsh` directory and rename the `gmsh.h` file `gmsh.h_original`.
- in the same directory, rename the `gmsh.h_cwrap` file to `gmsh.h`.
- go to the `lib` directory in the `gmsh` directory and copy che GMSH DLL file into `C.\Windows\System32`.

This should make the GMSH's API working on Windows.

We assume Neutrino is going to be installed in a directory named *NeutrinoCodes* containing the following subdirectories:
- glad
- glfw
- gmsh
- imgui
- implot

From the command shell (either VScode's or system's), navigate into *NeutrinoCodes* and create a `libnu` directory using the command:\
`mkdir libnu`\
\
This will create the `libnu` directory.

From the command shell (either VScode's or system's), navigate into *NeutrinoCodes* and clone the Neutrino project using the command:\
`git clone https://github.com/NeutrinoCodes/neutrino.git` \
\
This will create the `neutrino` directory. Now we offer two alternative methods for continuing the installation.

## Installation: 1st method - VScode toolchain
Go to the `neutrino` directory and create a `.vscode` hidden directory:\
`mkdir .vscode`\
\
and create a new file `settings.json` in it, then fill it with the following information:\
`{`\
&nbsp;&nbsp;`"cmake.configureSettings":`\
&nbsp;&nbsp;`{`\
&nbsp;&nbsp;&nbsp;&nbsp;`"GLAD_PATH": "your_path_to_NeutrinoCodes\\glad",`\
&nbsp;&nbsp;&nbsp;&nbsp;`"GLFW_PATH": "your_path_to_NeutrinoCodes\\glfw",`\
&nbsp;&nbsp;&nbsp;&nbsp;`"GMSH_PATH": "your_path_to_NeutrinoCodes\\gmsh",`\
&nbsp;&nbsp;&nbsp;&nbsp;`"CL_PATH": "your_path_to_OpenCL",`\
&nbsp;&nbsp;&nbsp;&nbsp;`"IMGUI_PATH": "your_path_to_NeutrinoCodes\\imgui",`\
&nbsp;&nbsp;&nbsp;&nbsp;`"IMPLOT_PATH": "your_path_to_NeutrinoCodes\\implot",`\
&nbsp;&nbsp;&nbsp;&nbsp;`"NEUTRINO_PATH": "your_path_to_NeutrinoCodes\\libnu"`\
&nbsp;&nbsp;`}`\
`}`\
\
and save it.

Then in VScode, open a folder from the file menu and select NeutrinoCodes. Go to the left bar and locate the **CMake** button (it comes after the installation of the CMake Tools extension for VScode) and push it: a CMake panel will open, push the **Configure All Projects** button on it.

Go to the bottom bar and locate:
- the **Build variant** button: verify it has been selected to **[Release]**.
- the **Active kit** button: verify it has been selected according to your system's characteristics. e.g. **[Visual Studio Community 2019 Release - amd64]**.
- the **Target** button: verify it has been selected to **[install]**.
- the **Build** button: push it in order to build the Neutrino project.

## Installation: 2nd method - Visual Studio toolchain
Go to the `neutrino` directory and edit the `CMakeSettings.json` file in it, then fill it with the following information:\
`{`\
&nbsp;&nbsp;`"configurations": [`\
&nbsp;&nbsp;&nbsp;&nbsp;`{`\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`"name": "x64-Release",`\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`"generator": "Ninja",`\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`"configurationType": "Release",`\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`"buildRoot": "${projectDir}\\build\\cmake\\${name}",`\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`"installRoot": "${projectDir}\\out\\install\\${name}",`\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`"cmakeCommandArgs": "-DGLAD_PATH=\"your_path_to_NeutrinoCodes\\glad\" -DGLFW_PATH=\"your_path_to_NeutrinoCodes\\glfw\" -DGMSH_PATH=\"your_path_to_NeutrinoCodes\\gmsh\" -DCL_PATH=\"your_path_to_OpenCL\\opencl\" -DIMGUI_PATH=\"your_path_to_NeutrinoCodes\\imgui" -DIMPLOT_PATH=\"your_path_to_NeutrinoCodes\\implot" -DNEUTRINO_PATH=\"your_path_to_NeutrinoCodes\\libnu\"",`\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`"buildCommandArgs": "",`\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`"ctestCommandArgs": "",`\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`"inheritEnvironments": [ "msvc_x64_x64" ],`\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`"variables": [`\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`{`\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`"name": "CMAKE_INSTALL_PREFIX",`\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`"value": "E:/BookHouseBoys/ezor/NeutrinoCodes/libnu",`\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`"type": "PATH"`\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`}`\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`]`\
&nbsp;&nbsp;&nbsp;&nbsp;`}`\
&nbsp;&nbsp;`]`\
`}`\
\
and save it.

Then in Visual Studio, open a folder from the file menu and select NeutrinoCodes. Visual Studio will invoke Cmake. After it finished configuring the project, go to the Build menu and push the **Build** button. Once the Neutrino library has been built, it has to be installed: to do so, go to the Build menu and push the **Install** button.

Alternatively, the same file can edited in Visual Studio by right-clicking the CMakeLists.txt file in the Solution Explorer - Folder View and then selecting the **CMake Settings for 'project_name'** button. This will open the CMake Settings editor. The string to be edited, containing all user's paths, is the one in the **CMake command arguments** text field.

## Post installation notes

Notice all paths **must** be specificed with *double backslashes*, in order to correctly manage the possibility of space characters in the them.
Also notice that `your_path_to_OpenCL` might be something like this (it depends on your GPU's graphics drivers):\
`C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v10.1`\
\
At this point, Neutrino is configured for your system and the NeutrinoCodes directory should appear like this:
- glad
- glfw
- gmsh
- imgui
- implot
- libnu
- neutrino

We all like tidy code! For this, we provide an **Uncrustify** (sources: https://github.com/uncrustify/uncrustify) configuration file specific for Neutrino. In order to use it, please first install Uncrustify according to your operating system (e.g. use Homebrew under Mac), then install the VScode's *Uncrustify extension* (https://marketplace.visualstudio.com/items?itemName=LaurentTreguier.uncrustify).\
\
Add the following lines to either the *global* or *project* **settings.json** file:
`"uncrustify.executablePath.windows": "your_path_to_uncrustify",`\
`"editor.defaultFormatter": "LaurentTreguier.uncrustify",`\
`"editor.formatOnSave": true`\
\
To edit the *global* settings, on VScode go to the left bar: push the **Extensions** button and select the Uncrustify extension. Then go to **Manage --> Extension Settings** (gear-like icon) and edit the `settings.json` file by clicking one of the links in that section. This will set the Uncrustify code formatter globally in all your VScode projects (but still with per-project custom uncrustify configuration files).\
\
To edit the *project* settings, open `settings.json` file in the `.vscode` you created for Neutrino (the hidden directory inside the `Neutrino` directory) and put the same lines in it. This will set Uncrustify as code formatter (together with the configuration file we provide) only for the Neutrino project.

Congratulations, you have installed Neutrino on Windows!