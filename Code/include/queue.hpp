/// @file

#ifndef queue_hpp
#define queue_hpp

  #include "neutrino.hpp"

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// "QUEUE" CLASS ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  class queue
  {
    private:
      neutrino*           baseline;                                             // Neutrino baseline.

      // OpenCL error get function:
      const char*         get_error     (
                                          cl_int      loc_error                 // Error code.
                                        );

      // OpenCL error check function:
      void                check_error   (
                                          cl_int      loc_error                 // Error code.
                                        );

    public:
      cl_command_queue  queue_id;                                               // OpenCL queue.
      cl_context        context_id;                                             // OpenCL context.
      cl_device_id      device_id;                                              // OpenCL device id.

            queue();
      void  init(neutrino* loc_baseline);
            ~queue();
  };

#endif
