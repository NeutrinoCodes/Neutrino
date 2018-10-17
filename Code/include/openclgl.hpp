/// @file

#ifndef openclgl_hpp
#define openclgl_hpp


  const char* get_error(cl_int error);
  cl_uint     get_platforms();
  void        get_platform_info(cl_uint index_platform, cl_platform_info name_param);
  cl_uint     get_devices(cl_uint index_platform);
  void        get_device_info(cl_uint index_device, cl_device_info name_param);
  void        init_opencl_context();
  void        release_opencl_context();

  void        typeset(text4* text);
  //void        load_kernel(kernel* k);
  //void        init_opencl_kernel(kernel* k);
  void        get_kernel_workgroup_size(kernel* k, cl_device_id device_id, size_t* local);
  void        execute_kernel(kernel* k);

  void        wait_for_event(kernel* k);
  void        release_event(kernel* k);

  void        release_queue();

#endif
