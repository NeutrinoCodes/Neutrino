/// @file

#ifndef queue_hpp
#define queue_hpp

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// "QUEUE" CLASS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class queue
  {
    private:

    public:
      cl_command_queue  queue_id;                                               // OpenCL queue.
      cl_context        context_id;                                             // OpenCL context.
      cl_device_id      device_id;                                              // OpenCL device id.

            queue();
      void  init(opencl* loc_opencl_context);
            ~queue();
  };

#endif
