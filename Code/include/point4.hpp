/// @file

#ifndef point4_hpp
#define point4_hpp

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// "POINT4" CLASS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class point4
  {
    private:
      const char*       get_error(cl_int loc_error);
      GLfloat*          data;
      cl_context        context;                                                // OpenCL context.

    public:



      GLfloat*          x;
      GLfloat*          y;
      GLfloat*          z;
      GLfloat*          w;

      int               size;
      GLuint            vao;
      GLuint            vbo;
      cl_mem            buffer;

                        point4();

      void              init  (
                                cl_context loc_opencl_context,
                                int loc_data_number
                              );

      void              set   (
                                kernel* loc_kernel,
                                int loc_kernel_arg
                              );

      void              push  (
                                queue* loc_queue,
                                kernel* loc_kernel,
                                int loc_kernel_arg
                              );

      void              pop   (
                                queue* loc_queue,
                                kernel* loc_kernel,
                                int loc_kernel_arg
                              );

                        ~point4();
  };

#endif
