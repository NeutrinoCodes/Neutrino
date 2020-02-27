<p>
<img src="/Logos/neutrino_logo.png" width="200" height="200" />
</p>

_A fast and light library for GPU-based computation and interactive data visualization._

[www.neutrino.codes](http://www.neutrino.codes)

© Alessandro LUCANTONIO, Erik ZORZIN - 2018-2020

Hardware requirements:
----
- OpenCL-compatible GPU.

For interactive visualization, it is better if the _OpenCL-OpenGL interoperability_ mode is supported. Using the tool  `clinfo` (https://github.com/Oblomov/clinfo) check for the `cl_APPLE_gl_sharing` extension under MacOS, while under Linux or Windows check for the
`cl_khr_gl_sharing` extension.

Software requirements:
----
- OpenCL v1.2 (runtime/loader + headers) *
- OpenGL v4.6 (library + headers) *
- git v2.21 ***
- GLAD (https://glad.dav1d.de/) **
- GLFW v3.3 (https://www.glfw.org/)
- gcc v9.1 (**Linux/MacOS only**)
- cMake v3.14.5 (**Linux/MacOS only**)
- make (**Linux/MacOS only**)
- Visual Studio 2019 (https://visualstudio.microsoft.com/) with "Desktop development
with C++ --> C++ CMake tools for Windows" workload (**Windows only**).
- GraphViz (https://graphviz.org/) ***
- Doxygen v1.8.15 (http://www.doxygen.nl/) ***

\* They should be already present by default in the system. Under Linux, if not present, they can be installed by using the system's package manager.

\** The GLAD loader should be generated from its webpage using the following settings:
- Language = C/C++
- gl = Version 4.6
- Profile = Core

Download the zip file containing the code and extract it in a
custom directory.

\*** On MacOS they can be installed by using `brew` package manager (https://brew.sh/).

Compilation
----

### Linux/MacOS
1. From the command shell, navigate into your favourite directory and clone the Neutrino project
using the command `git clone https://github.com/NeutrinoCodes/neutrino.git`.
2. Cd into Neutrino's project directory and create a configuration script called `configure` in the Code subdirectory. Edit this file by adding the following command line: `cmake -B"./cmake" -H"./" -DGLAD_PATH=/path/to/glad/root -DGLFW_PATH=/path/to/GLFW/root/ -DNEUTRINO_PATH=/path/to/neutrino/libnu` and specify the paths accordingly. In particular, `DNEUTRINO_PATH` is the path of Neutrino's project folder and should be followed by `/libnu`, where the library will be installed.
On **MacOS** you also need to set the variables `DCMAKE_C_COMPILER` and `DCMAKE_CXX_COMPILER`, because we are using gcc instead of Xcode.
3. Make the configuration script executable and launch it by typing `./configure` at the command prompt. The CMake configuration files will be generated.
4. Enter the `cmake` directory and type `make install` (use `make clean` to remove old build files
  if necessary).

### Windows
1. Launch Command Prompt, navigate into your favorite directory and clone the Neutrino project using the command `git clone https://github.com/NeutrinoCodes/neutrino.git`.
2. Launch Visual Studio 2019 and select neutrino project folder.
3. Project -> CMake settings for neutrino -> Edit JSON; add the string `-DGLAD_PATH=C:/path/to/glad` `-DGLFW_PATH=C:/path/to/glfw` `-DCL_PATH=C:/path/to/opencl` to the parameter `cmakeCommandArgs` to specify the paths of GLAD, GLFW, and OpenCL headers (root directory). Also set the parameter `buildRoot` to `${projectDir}\\build\\windows`. Note: if you installed the NVIDIA GPU Computing Toolkit, `-DCL_PATH` will be something like `\"C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v9.1/\"` (notice the trailing and ending slashes, to be used if the path contains spaces).
4. Build -> Build All. The `.lib` file will be placed in the `libnu\lib` folder under the Neutrino project root directory.

Final considerations
---
See the "Examples" repository for codes demonstrating the use of the library.

© Alessandro LUCANTONIO, Erik ZORZIN - 2018-2020
