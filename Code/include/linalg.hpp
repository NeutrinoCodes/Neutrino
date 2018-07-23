#ifndef linalg_hpp
#define linalg_hpp

  #include <math.h>

  class vector
  {
    private:

    public:
      vector();
      ~vector();

      float  x;
      float  y;
      float  z;
  };

  class quaternion
  {
  private:

  public:
    quaternion();
    ~quaternion();

    float  a;
    float  b;
    float  c;
    float  d;
  };

  class matrix
  {
  private:

  public:
    matrix();
    ~matrix();

    float  a_11;
    float  a_12;
    float  a_13;

    float  a_21;
    float  a_22;
    float  a_23;

    float  a_31;
    float  a_32;
    float  a_33;
  };


  float   dot(vector a, vector b);
  float   magnitude(vector a);
  vector  normalize(vector a);
  float   angle(vector a, vector b);
  vector  cross(vector a, vector b);
  matrix  rotate(quaternion q);
  
#endif
