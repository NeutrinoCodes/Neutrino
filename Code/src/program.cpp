/// @file

#include "program.hpp"

#define X_MIN           -1.0f
#define Y_MIN           -1.0f
#define X_MAX           1.0f
#define Y_MAX           1.0f
#define SIZE_X          81
#define SIZE_Y          81
#define NUM_POINTS      (SIZE_X*SIZE_Y)
#define DX              (float)((X_MAX-X_MIN)/SIZE_X)
#define DY              (float)((Y_MAX-Y_MIN)/SIZE_Y)
#define DT              0.005

float4* position_old      = new float4(NUM_POINTS);                             // Old position.
float4* velocity_old      = new float4(NUM_POINTS);                             // Old velocity.
float4* acceleration_old  = new float4(NUM_POINTS);                             // Old acceleration.

point4* position          = new point4(NUM_POINTS);                             // Position.
color4* color             = new color4(NUM_POINTS);                             // Particle color.
float4* velocity          = new float4(NUM_POINTS);                             // Velocity.
float4* acceleration      = new float4(NUM_POINTS);                             // Acceleration.

float4* gravity           = new float4(NUM_POINTS);                             // Gravity.
float4* stiffness         = new float4(NUM_POINTS);                             // Stiffness.
float4* resting           = new float4(NUM_POINTS);                             // Resting.
float4* friction          = new float4(NUM_POINTS);                             // Friction.
float4* mass              = new float4(NUM_POINTS);                             // Mass.

int1* index_PC            = new int1(NUM_POINTS);                               // Centre particle.
int1* index_PR            = new int1(NUM_POINTS);                               // Right particle.
int1* index_PU            = new int1(NUM_POINTS);                               // Up particle.
int1* index_PL            = new int1(NUM_POINTS);                               // Left particle.
int1* index_PD            = new int1(NUM_POINTS);                               // Down particle.

float4* freedom           = new float4(NUM_POINTS);                             // Freedom/constrain flag.

text4*  text              = new text4("neutrino!", 1.0f, 1.0f, 1.0f, 1.0f);

float tick;

void setup()
{
  int i;
  int j;
  float x;
  float y;

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////// Preparing arrays... /////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  y = Y_MIN;

  for (j = 0; j < SIZE_Y; j++)
  {
    x = X_MIN;

    for (i = 0; i < SIZE_X; i++)
    {
      position_old->x[i + SIZE_X*j] = x;                                        // Setting "x" initial position_old...
      position_old->y[i + SIZE_X*j] = y;                                        // Setting "y" initial position_old...
      position_old->z[i + SIZE_X*j] = 0.0f;                                     // Setting "z" initial position_old...
      position_old->w[i + SIZE_X*j] = 1.0f;                                     // Setting "w" initial position_old...

      // Setting "x" initial position (Taylor's expansion)...
      position->x[i + SIZE_X*j] = position_old->x[i + SIZE_X*j] +               // position_old +
                                  velocity_old->x[i + SIZE_X*j]*DT +            // velocity_old*dt +
                                  0.5f*acceleration_old->x[i + SIZE_X*j]*DT*DT; // 1/2*acceleration_old*dt^2

      // Setting "y" initial position (Taylor's expansion)...
      position->y[i + SIZE_X*j] = position_old->y[i + SIZE_X*j] +               // position_old +
                                  velocity_old->y[i + SIZE_X*j]*DT +            // velocity_old*dt +
                                  0.5f*acceleration_old->y[i + SIZE_X*j]*DT*DT; // 1/2*acceleration_old*dt^2

      // Setting "z" initial position (Taylor's expansion)...
      position->z[i + SIZE_X*j] = position_old->z[i + SIZE_X*j] +               // position_old +
                                  velocity_old->z[i + SIZE_X*j]*DT +            // velocity_old*dt +
                                  0.5f*acceleration_old->z[i + SIZE_X*j]*DT*DT; // 1/2*acceleration_old*dt^2

      // Setting "w" initial position...
      position->w[i + SIZE_X*j] = 1.0f;

      gravity->x[i + SIZE_X*j] = 0.0f;                                          // Setting "x" gravity...
      gravity->y[i + SIZE_X*j] = 0.0f;                                          // Setting "y" gravity...
      gravity->z[i + SIZE_X*j] = 9.81f;                                         // Setting "z" gravity...
      gravity->w[i + SIZE_X*j] = 1.0f;                                          // Setting "w" gravity...

      stiffness->x[i + SIZE_X*j] = 2000.0f;                                       // Setting "x" stiffness...
      stiffness->y[i + SIZE_X*j] = 2000.0f;                                       // Setting "y" stiffness...
      stiffness->z[i + SIZE_X*j] = 2000.0f;                                       // Setting "z" stiffness...
      stiffness->w[i + SIZE_X*j] = 1.0f;                                        // Setting "w" stiffness...

      resting->x[i + SIZE_X*j] = DX;                                            // Setting "x" resting position...
      resting->y[i + SIZE_X*j] = DX;                                            // Setting "y" resting position...
      resting->z[i + SIZE_X*j] = DX;                                            // Setting "z" resting position...
      resting->w[i + SIZE_X*j] = 1.0f;                                          // Setting "w" resting position...

      friction->x[i + SIZE_X*j] = 200.0f;                                        // Setting "x" friction...
      friction->y[i + SIZE_X*j] = 200.0f;                                        // Setting "y" friction...
      friction->z[i + SIZE_X*j] = 200.0f;                                        // Setting "z" friction...
      friction->w[i + SIZE_X*j] = 1.0f;                                         // Setting "w" friction...

      mass->x[i + SIZE_X*j] = 0.25f;                                             // Setting "x" mass...
      mass->y[i + SIZE_X*j] = 0.25f;                                             // Setting "y" mass...
      mass->z[i + SIZE_X*j] = 0.25f;                                             // Setting "z" mass...
      mass->w[i + SIZE_X*j] = 0.25f;                                             // Setting "w" mass...

      color->r[i + SIZE_X*j] = 1.0f;                                            // Setting "x" initial color...
      color->g[i + SIZE_X*j] = 0.0f;                                            // Setting "y" initial color...
      color->b[i + SIZE_X*j] = 0.0f;                                            // Setting "z" initial color...
      color->a[i + SIZE_X*j] = 1.0f;                                            // Setting "w" initial color...

      x += DX;
    }
    y += DY;
  }

  for (j = 0; j < (SIZE_Y); j++)
  {
    for (i = 0; i < (SIZE_X); i++)
    {
      index_PC->x[i + SIZE_X*j] =  i       + SIZE_X*j;

      freedom->x[i + SIZE_X*j] = 1.0f;
      freedom->y[i + SIZE_X*j] = 1.0f;
      freedom->z[i + SIZE_X*j] = 1.0f;
      freedom->w[i + SIZE_X*j] = 1.0f;

      if ((i != 0) && (i != (SIZE_X - 1)) && (j != 0) && (j != (SIZE_Y - 1)))   // When on bulk:
      {
        index_PR->x[i + SIZE_X*j] = (i + 1)  + SIZE_X*j;
        index_PU->x[i + SIZE_X*j] =  i       + SIZE_X*(j + 1);
        index_PL->x[i + SIZE_X*j] = (i - 1)  + SIZE_X*j;
        index_PD->x[i + SIZE_X*j] =  i       + SIZE_X*(j - 1);
      }

      else                                                                      // When on all borders:
      {
        gravity->x[i + SIZE_X*j] = 0.0f;                                        // Setting "x" gravity...
        gravity->y[i + SIZE_X*j] = 0.0f;                                        // Setting "y" gravity...
        gravity->z[i + SIZE_X*j] = 0.0f;                                        // Setting "z" gravity...
        gravity->w[i + SIZE_X*j] = 1.0f;                                        // Setting "w" gravity...

        freedom->x[i + SIZE_X*j] = 0.0f;
        freedom->y[i + SIZE_X*j] = 0.0f;
        freedom->z[i + SIZE_X*j] = 0.0f;
        freedom->w[i + SIZE_X*j] = 1.0f;
        /*
        stiffness->x[i + SIZE_X*j] = 0.0f;                                      // Setting "x" gravity...
        stiffness->y[i + SIZE_X*j] = 0.0f;                                      // Setting "y" gravity...
        stiffness->z[i + SIZE_X*j] = 0.0f;                                      // Setting "z" gravity...
        stiffness->w[i + SIZE_X*j] = 1.0f;                                      // Setting "w" gravity...

        friction->x[i + SIZE_X*j] = 0.0f;                                       // Setting "x" gravity...
        friction->y[i + SIZE_X*j] = 0.0f;                                       // Setting "y" gravity...
        friction->z[i + SIZE_X*j] = 0.0f;                                       // Setting "z" gravity...
        friction->w[i + SIZE_X*j] = 1.0f;                                       // Setting "w" gravity...
        */
      }

      if ((i == 0) && (j != 0) && (j != (SIZE_Y - 1)))                          // When on left border (excluding extremes):
      {
        index_PR->x[i + SIZE_X*j] = (i + 1)  + SIZE_X*j;
        index_PU->x[i + SIZE_X*j] =  i       + SIZE_X*(j + 1);
        index_PL->x[i + SIZE_X*j] = index_PC->x[i + SIZE_X*j];
        index_PD->x[i + SIZE_X*j] =  i       + SIZE_X*(j - 1);
      }

      if ((i == (SIZE_X - 1)) && (j != 0) && (j != (SIZE_Y - 1)))               // When on right border (excluding extremes):
      {
        index_PR->x[i + SIZE_X*j] = index_PC->x[i + SIZE_X*j];
        index_PU->x[i + SIZE_X*j] =  i       + SIZE_X*(j + 1);
        index_PL->x[i + SIZE_X*j] = (i - 1)  + SIZE_X*j;
        index_PD->x[i + SIZE_X*j] =  i       + SIZE_X*(j - 1);
      }

      if ((j == 0) && (i != 0) && (i != (SIZE_X - 1)))                          // When on low border (excluding extremes):
      {
        index_PR->x[i + SIZE_X*j] = (i + 1)  + SIZE_X*j;
        index_PU->x[i + SIZE_X*j] =  i       + SIZE_X*(j + 1);
        index_PL->x[i + SIZE_X*j] = (i - 1)  + SIZE_X*j;
        index_PD->x[i + SIZE_X*j] = index_PC->x[i + SIZE_X*j];
      }

      if ((j == (SIZE_Y - 1)) && (i != 0) && (i != (SIZE_X - 1)))               // When on high border (excluding extremes):
      {
        index_PR->x[i + SIZE_X*j] = (i + 1)  + SIZE_X*j;
        index_PU->x[i + SIZE_X*j] = index_PC->x[i + SIZE_X*j];
        index_PL->x[i + SIZE_X*j] = (i - 1)  + SIZE_X*j;
        index_PD->x[i + SIZE_X*j] =  i       + SIZE_X*(j - 1);
      }

      if ((i == 0) && (j == 0))                                                 // When on low left corner:
      {
        index_PR->x[i + SIZE_X*j] = (i + 1)  + SIZE_X*j;
        index_PU->x[i + SIZE_X*j] =  i       + SIZE_X*(j + 1);
        index_PL->x[i + SIZE_X*j] = index_PC->x[i + SIZE_X*j];
        index_PD->x[i + SIZE_X*j] = index_PC->x[i + SIZE_X*j];
      }

      if ((i == (SIZE_X - 1)) && (j == 0))                                      // When on low right corner:
      {
        index_PR->x[i + SIZE_X*j] = index_PC->x[i + SIZE_X*j];
        index_PU->x[i + SIZE_X*j] =  i       + SIZE_X*(j + 1);
        index_PL->x[i + SIZE_X*j] = (i - 1)  + SIZE_X*j;
        index_PD->x[i + SIZE_X*j] = index_PC->x[i + SIZE_X*j];
      }

      if ((i == 0) && (j == (SIZE_Y - 1)))                                      // When on high left corner:
      {
        index_PR->x[i + SIZE_X*j] = (i + 1)  + SIZE_X*j;
        index_PU->x[i + SIZE_X*j] = index_PC->x[i + SIZE_X*j];
        index_PL->x[i + SIZE_X*j] = index_PC->x[i + SIZE_X*j];
        index_PD->x[i + SIZE_X*j] = i       + SIZE_X*(j - 1);
      }

      if ((i == (SIZE_X - 1)) && (j == (SIZE_Y - 1)))                           // When on high right corner:
      {
        index_PR->x[i + SIZE_X*j] = index_PC->x[i + SIZE_X*j];
        index_PU->x[i + SIZE_X*j] = index_PC->x[i + SIZE_X*j];
        index_PL->x[i + SIZE_X*j] = (i - 1)  + SIZE_X*j;
        index_PD->x[i + SIZE_X*j] =  i       + SIZE_X*(j - 1);
      }

    }
  }

  tick = 0.0f;                                                                  // Setting initial time tick...

  kernel_size(NUM_POINTS);
  kernel_dimensions(1);
  typeset(text);                                                                // Typesetting "text"...

  set_point4(position, 0);                                                      // Setting kernel argument #0...
  set_color4(color, 1);                                                         // Setting kernel argument #1...
  set_float4(position_old, 2);                                                  // Setting kernel argument #2...
  set_float4(velocity, 3);                                                      // Setting kernel argument #3...
  set_float4(acceleration, 4);                                                  // Setting kernel argument #4...
  set_float4(gravity, 5);                                                       // Setting kernel argument #5...
  set_float4(stiffness, 6);                                                     // Setting kernel argument #6...
  set_float4(resting, 7);                                                       // Setting kernel argument #7...
  set_float4(friction, 8);                                                      // Setting kernel argument #8...
  set_float4(mass, 9);                                                          // Setting kernel argument #9...
  set_int1(index_PC, 10);                                                       // Setting kernel argument #10...
  set_int1(index_PR, 11);                                                       // Setting kernel argument #11...
  set_int1(index_PU, 12);                                                       // Setting kernel argument #12...
  set_int1(index_PL, 13);                                                       // Setting kernel argument #13...
  set_int1(index_PD, 14);                                                       // Setting kernel argument #14...
  set_float4(freedom, 15);
}

void loop()
{
  push_point4(&position->buffer, 0);                                            // Pushing kernel argument #0...
  push_color4(&color->buffer, 1);                                               // Pushing kernel argument #1...
  push_float4(&position_old->buffer, 2);                                        // Pushing kernel argument #2...
  push_float4(&velocity->buffer, 3);                                            // Pushing kernel argument #3...
  push_float4(&acceleration->buffer, 4);                                        // Pushing kernel argument #4...
  push_float4(&gravity->buffer, 5);                                             // Pushing kernel argument #5...
  push_float4(&stiffness->buffer, 6);                                           // Pushing kernel argument #6...
  push_float4(&resting->buffer, 7);                                             // Pushing kernel argument #7...
  push_float4(&friction->buffer, 8);                                            // Pushing kernel argument #8...
  push_float4(&mass->buffer, 9);                                                // Pushing kernel argument #9...
  push_int1(&index_PC->buffer, 10);                                             // Pushing kernel argument #10...
  push_int1(&index_PR->buffer, 11);                                             // Pushing kernel argument #11...
  push_int1(&index_PU->buffer, 12);                                             // Pushing kernel argument #12...
  push_int1(&index_PL->buffer, 13);                                             // Pushing kernel argument #13...
  push_int1(&index_PD->buffer, 14);                                             // Pushing kernel argument #14...
  push_float4(&freedom->buffer, 15);

  execute_kernel();

  pop_point4(&position->buffer, 0);                                             // Pushing kernel argument #0...
  pop_color4(&color->buffer, 1);                                                // Pushing kernel argument #1...
  pop_float4(&position_old->buffer, 2);                                         // Pushing kernel argument #2...
  pop_float4(&velocity->buffer, 3);                                             // Pushing kernel argument #3...
  pop_float4(&acceleration->buffer, 4);                                         // Pushing kernel argument #4...
  pop_float4(&gravity->buffer, 5);                                              // Pushing kernel argument #5...
  pop_float4(&stiffness->buffer, 6);                                            // Pushing kernel argument #6...
  pop_float4(&resting->buffer, 7);                                              // Pushing kernel argument #7...
  pop_float4(&friction->buffer, 8);                                             // Pushing kernel argument #8...
  pop_float4(&mass->buffer, 9);                                                 // Pushing kernel argument #9...
  pop_int1(&index_PC->buffer, 10);                                              // Pushing kernel argument #10...
  pop_int1(&index_PR->buffer, 11);                                              // Pushing kernel argument #11...
  pop_int1(&index_PU->buffer, 12);                                              // Pushing kernel argument #12...
  pop_int1(&index_PL->buffer, 13);                                              // Pushing kernel argument #13...
  pop_int1(&index_PD->buffer, 14);                                              // Pushing kernel argument #14...
  pop_float4(&freedom->buffer, 15);

  plot(position, color, STYLE_POINT);
  //print(text);
}

void terminate()
{
  delete position;
  delete color;
  delete velocity;
  delete acceleration;
  delete position_old;
  delete velocity_old;
  delete acceleration_old;
  delete gravity;
  delete stiffness;
  delete resting;
  delete friction;
  delete mass;
  delete index_PC;
  delete index_PD;
  delete index_PL;
  delete index_PR;
  delete index_PU;
  delete text;

  printf("All done!\n");
}
