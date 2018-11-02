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

    public:
      cl_command_queue  queue_id;                                               // OpenCL queue.
      cl_context        context_id;                                             // OpenCL context.
      cl_device_id      device_id;                                              // OpenCL device id.

            queue();
      void  init(neutrino* loc_neutrino);
            ~queue();
  };

#endif
