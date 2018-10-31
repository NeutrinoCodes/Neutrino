/// @file

#ifndef color4_hpp
#define color4_hpp

  #include "neutrino.hpp"

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// "COLOR4" CLASS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class color4
  {
    private:
      const char*     get_error(cl_int loc_error);
      int             err;
      unsigned int    i;
      GLfloat*        data;
      cl_context      context;                                                // OpenCL context.

    public:
      GLfloat*        r;
      GLfloat*        g;
      GLfloat*        b;
      GLfloat*        a;

      int             size;
      GLuint          vao;
      GLuint          vbo;
      cl_mem          buffer;

                      color4();
      void            init(int num_data);
      void            set(kernel* k, int kernel_arg);
      void            push(queue* q, kernel* k, int kernel_arg);
      void            pop(queue* q, kernel* k, int kernel_arg);
                      ~color4();
  };

#endif
