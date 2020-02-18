<p>
<img src="/Logos/neutrino_logo.png" width="200" height="200" />
</p>

_A fast and light library for GPU-based computation and interactive data visualization._

[www.neutrino.codes](http://www.neutrino.codes)

© Alessandro LUCANTONIO, Erik ZORZIN - 2018-2020

Hardware requirements:
----
- OpenCL-compatible GPU with support for OpenCL-OpenGL.

It is better if the "interoperability" sharing modality exists. By using the tool  `clinfo`, under
Mac check for the `cl_APPLE_gl_sharing` extension, while under Linux or Windows check for the
`cl_khr_gl_sharing` extension.

Software requirements for Mac:
----
- OpenCL v1.2 (runtime/loader + headers) *
- OpenGL v4.6 (library + headers) *
- GLAD (https://glad.dav1d.de/) **
- GLFW v3.3 (https://www.glfw.org/)
- GCC v9.1 ***
- CMake v3.14.5 ***
- Make ***
- Git v2.21 ***
- GraphViz (https://graphviz.org/) ***
- Doxygen v1.8.15 (http://www.doxygen.nl/) ***
- Clinfo (https://github.com/Oblomov/clinfo) ***

\* They should be already present by default in the system.

\** The GLAD loader should be generated from its webpage using the following settings:
- Language = C/C++
- gl = Version 4.6
- Profile = Core

Download the zip file containing the code and extract it in a
custom directory, e.g. `/Users/yourname/glad`.

\*** If not present, they could be installed by using `brew` package manager (https://brew.sh/).

Software requirements for Linux:
----
- OpenCL v1.2 (runtime/loader + headers) *
- OpenGL v4.6 (library + headers) *
- GLAD (https://glad.dav1d.de/) **
- GLFW v3.3 (https://www.glfw.org/)
- GCC v9.1 *
- CMake v3.14.5 *
- Make *
- Git v2.21 *
- GraphViz (https://graphviz.org/) *
- Doxygen v1.8.15 (http://www.doxygen.nl/) *
- Clinfo (https://github.com/Oblomov/clinfo) *

\* If not present, they could be installed by using the system's package manager.

\** The GLAD loader should be generated from its webpage using the following settings:
- Language = C/C++
- gl = Version 4.6
- Profile = Core

Download the zip file containing the code and extract it in a
custom directory, e.g. `˜/glad`.

Software requirements for Windows:
----
- OpenCL v1.2 (runtime/loader + headers) *
- OpenGL v4.6 (library + headers) *
- GLAD (https://glad.dav1d.de/) **
- GLFW v3.3 (https://www.glfw.org/)
- Visual Studio 2019 (https://visualstudio.microsoft.com/) with "Desktop development
with C++ --> C++ CMake tools for Windows" workload.
- Git v2.21 (https://gitforwindows.org/)
- GraphViz (https://graphviz.org/)
- Doxygen v1.8.15 (http://www.doxygen.nl/)
- Clinfo (https://github.com/Oblomov/clinfo)

\* To be installed within the graphics card drivers coming from the manufacturer.

\** The GLAD loader should be generated from its webpage using the following settings:
- Language = C/C++
- gl = Version 4.6
- Profile = Core

Download the zip file containing the code and extract it in a
custom directory, e.g. `C:\Users\yourname\glad`.

Compilation
----

### Mac
1. From the command shell, navigate into your favourite directory and clone the Neutrino project
using the command `git clone https://github.com/NeutrinoCodes/neutrino.git`.
2. Cd into neutrino's project directory and edit the configuration script in the Code
subdirectory: `./configure_mac` by setting your paths. Provide the **absolute** path for the
following variables in the script:
`- DCMAKE_C_COMPILER`
`- DCMAKE_CXX_COMPILER`
`- DGLAD_PATH`
`- DGLFW_PATH`
`- DNEUTRINO_PATH`

You can also set environment variables in your `/Users/yourname/.bash_profile` and use them in the
script.

e.g.

`export CC="/usr/local/bin/gcc-9"`
`export CCX="/usr/local/bin/g++-9"`
`export CPATH="/usr/local/include"`
`export LIBRARY_PATH="/usr/local/lib"`
`export NEUTRINOCODES_PATH="/users/yourname/NeutrinoCodes"`
`export NEUTRINO_PATH=$NEUTRINOCODES_PATH/libnu`
`export GLAD_PATH=$NEUTRINOCODES_PATH/glad`
`export GLFW_PATH=$NEUTRINOCODES_PATH/glfw`

P.S. after setting these variables, remember to exit and re-open the command shell or launch the
shell command `source /Users/yourname/.bash_profile` in order to have them refreshed by the system.
The first four variables are mandatory, because we are using gcc instead of Xcode.

3. Then launch it. The Cmake configuration files will be generated.
4. Enter the `cmake` directory and type `make install` (use `make clean` to remove old build files
  if necessary).

### Linux
1. From the command shell, navigate into your favourite directory and clone neutrino project using
the command `git clone https://github.com/NeutrinoCodes/neutrino.git`.
2. Cd into neutrino's project directory and edit the configuration script in the Code
subdirectory: `./configure_linux` by setting your paths. Provide the **absolute** path for the
following variables in the script:
`- DGLAD_PATH`
`- DGLFW_PATH`
`- DNEUTRINO_PATH`

You can also set environment variables in your `/Users/yourname/.bash_profile` and use them in the
script.

e.g.

`export NEUTRINOCODES_PATH="/users/yourname/NeutrinoCodes"`
`export NEUTRINO_PATH=$NEUTRINOCODES_PATH/libnu`
`export GLAD_PATH=$NEUTRINOCODES_PATH/glad`
`export GLFW_PATH=$NEUTRINOCODES_PATH/glfw`

3. Then launch it. The Cmake configuration files will be generated.
4. Enter the `cmake` directory and type `make install` (use `make clean` to remove old build files
  if necessary).

### Windows
1. Launch Command Prompt, navigate into your favorite directory and clone neutrino project using the command `git clone https://github.com/NeutrinoCodes/neutrino.git`.
2. Launch Visual Studio 2019 and select neutrino project folder.
3. Project -> CMake settings for neutrino -> Edit JSON; add the string `-DGLAD_PATH=C:/path/to/glad` `-DGLFW_PATH=C:/path/to/glfw` `-DCL_PATH=C:/path/to/opencl` to the parameter `cmakeCommandArgs` to specify the paths of GLAD, GLFW, and OpenCL headers (root directory). Also set the parameter `buildRoot` to `${projectDir}\\build\\windows`. Note: if you installed the NVIDIA GPU Computing Toolkit, `-DCL_PATH` will be something like `\"C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v9.1/\"` (notice the trailing and ending slashes, to be used if the path contains spaces).
4. Build -> Build All. The `.lib` file will be placed in the `libnu\lib` folder under the Neutrino project root directory.

### Final considerations
The `libnu` folder would be later used in order to build Neutrino applications. See the "Examples"
repository.

© Alessandro LUCANTONIO, Erik ZORZIN - 2018-2020
