#ifndef program_hpp
#define program_hpp

#define GLM_ENABLE_EXPERIMENTAL

#include <stdio.h>
#include <stdlib.h>
#include "opengl.hpp"
#include "opencl.hpp"
#include "data.hpp"
#include "interop.hpp"

void setup();
void loop();
void terminate();

#endif
