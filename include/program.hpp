#ifndef program_hpp
#define program_hpp

#include <stdio.h>
#include <stdlib.h>
#include "opengl.hpp"
#include "opencl.hpp"
#include "data.hpp"
#include "interop.hpp"

#define NEAR_Z_CLIP 0.1f
#define FAR_Z_CLIP 100.0f
#define FOV 60.0f
#define LINE_WIDTH 3

void load();
void setup();
void loop();
void terminate();

#endif
