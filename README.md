<p>
<img src="/Logos/neutrino_logo.png" width="200" height="200" />
</p>

_A fast and light library for GPU-based computation and interactive data visualization._

[www.neutrino.codes](http://www.neutrino.codes)

© Alessandro LUCANTONIO, Erik ZORZIN - 2018-2019

Requirements
----
- OpenCL-compatible GPU with support for OpenCL-OpenGL interoperability*
- OpenCL v2.2 (runtime/loader + headers)
- OpenGL v4.6 (library + headers)
- GLAD (https://glad.dav1d.de/)
- GLFW v3.3 (https://www.glfw.org/)
- GCC v9.1 [Linux/Mac]
- CMake v3.14.5 [Linux/Mac]
- Make [Linux/Mac]
- Visual Studio 2019 [Windows] (https://visualstudio.microsoft.com/)
- Git v2.21
- Doxygen v1.8.15 (http://www.doxygen.nl/)

\*Only needed to run neutrino in graphical mode; check for the "cl_khr_gl_sharing" extension using
the tool  `clinfo` on Linux.

GCC, CMake and Make can be installed from the package manager of your Linux OS. Under Mac OS, ...

GLAD loader should be generated from its webpage using the following settings: Language = C/C++;
gl = Version 4.6; Profile = Core. Download the zip file containing the code and extract it in a
custom directory, i.e. C:\glad under Windows.

OpenCL runtime/loader are usually part of the GPU drivers.

Compilation
----

### Linux (generic)
1. From the command shell, navigate into your favorite directory and clone neutrino project using
the command `git clone https://github.com/NeutrinoCodes/neutrino.git`.
2. Cd into neutrino's project directory and launch the configuration script in the Code
subdirectory: `./configure`. Cmake configuration files will be generated.
3. Enter the `cmake` directory and type `make` (use  `make clean` to remove build files and
`make run` to launch neutrino demo application after building).
4. Go to `Code/build/linux` under neutrino's project directory and type  `./neutrino` from the
command shell to launch the demo application.

### Windows 10
1. Launch Command Prompt, navigate into your favorite directory and clone neutrino project using
the command `git clone https://github.com/NeutrinoCodes/neutrino.git`
2. Launch Visual Studio 2019 and select neutrino project folder.
3. Project -> CMake settings for neutrino -> Edit JSON; add the string
`"-DGLAD_PATH=C:/path/to/glad -DGLFW_PATH=C:/path/to/glfw -DCL_PATH=C:/path/to/opencl"`
to the parameter `"cmakeCommandArgs"` to specify the paths of GLAD, GLFW, and OpenCL headers
(root directory). Also set the parameter `"buildRoot"` to `"${projectDir}\\build\\windows"`.
_Note: if you installed the NVIDIA GPU Computing Toolkit, `-DCL_PATH` will be something
like `\"C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v9.1/\"`
(notice the trailing and ending slashes, to be used if the path contains spaces)._
4. Build -> Build All.
5. Go to `Code/build/windows` under neutrino's project directory and type  `neutrino` from the
Command Prompt to launch the demo application.

Alternative command line compilation:

1. From the Windows' start menu, launch "Visual Studio 2019" -> "Developer Command Prompt".
2. Cd into your `Neutrino\Code` folder.
3. Launch: `configure_windows.bat`. A new `cmake` folder will be created.
4. Cd into that `cmake` folder.
5. Execute: `devenv /build Release neutrino.sln`. That would compile the code: it will create a
new `Release` folder into the `cmake` folder.
6. Cd into the `Release` folder: a `neutrino.exe` file should be there.
7. Launch it from this command prompt (type: `neutrino`), or double click on its icon from the
Windows' file manager.
