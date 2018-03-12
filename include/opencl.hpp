#ifndef opencl_hpp
#define opencl_hpp

  #include <stdio.h>
  #include <stdlib.h>

  #ifdef __APPLE__
    #include <OpenCL/opencl.h>
    #include <OpenGL/OpenGL.h>
  #else
    #include <CL/cl.h>
    #include <CL/cl_gl.h>
    #include <GL/gl.h>
  #endif

  // These files are relative to the build/mac or build/linux directory:
  #define KERNEL_FILE             "../../kernel/kernel.txt"
  #define KERNEL_NAME             "the_kernel"
  #define KERNEL_OPTIONS          ""

  extern  char*                   value;
  extern  cl_platform_id*         platforms;
  extern  cl_device_id*           devices;
  extern  cl_context_properties*  properties;
  extern  cl_context              context;
  extern  cl_command_queue        queue;
  extern  cl_program              program;
  extern  cl_kernel               kernel;
  extern  char*                   kernel_source;
  extern  size_t                  size_kernel;
  extern  cl_program              kernel_program;
  extern  size_t                  size_global;
  extern  size_t                  size_local;
  extern  cl_uint                 dimension_kernel;

  cl_uint get_platforms();
  void    get_platform_info(cl_uint index_platform, cl_platform_info name_param);
  cl_uint get_devices(cl_uint index_platform);
  void    get_device_info(cl_uint index_device, cl_device_info name_param);
  void    get_context_properties();
  void    create_context();
  void    create_queue();
  void    read_kernel();
  void    create_program();
  void    build_program();
  void    create_kernel();
  void    create_buffer_from_VBO(GLuint vbo, cl_mem_flags memflags, cl_mem* memory);
  void    get_kernel_workgroup_size(cl_kernel kernel, cl_device_id device_id, size_t* local);
  void    execute_kernel();
  void    acquire_GLObjects(cl_mem* CL_memory_buffer);
  void    enqueue_task(cl_command_queue queue, cl_kernel kernel, cl_event* kernel_event);
  void    wait_for_events(cl_event* kernel_event);
  void    release_GLObjects(cl_mem* CL_memory_buffer);
  void    finish_queue();
  void    release_event(cl_event kernel_event);
  void    release_mem_object(cl_mem CL_memory_buffer);
  void    release_kernel();
  void    release_queue();
  void    release_program();
  void    release_context();

#endif
