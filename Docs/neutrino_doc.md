# OpenCL/GL framework {#openclgl}

# 1. Neutrino in a nutshell {#Neutrino_in_a_nutshell}
*Neutrino* is a C++ software environment for GPU-accelerated parallel computing,
based on the [OpenCL](https://en.wikipedia.org/wiki/OpenCL) and
the [OpenGL](https://en.wikipedia.org/wiki/OpenGL) frameworks.
The aim of Neutrino is to reduce the code overhead, due to the complexity of
the GPU-accelerated paradigm, in order to let the users concentrate on the
implementation of their algorithms.
The mathematical computation of interest is done by means of a single OpenCL
*kernel* defined in the thekernel.cl file and running on the OpenCL *client*
device (GPU). The kernel is invoked by a Neutrino *program* defined by the
program.cpp file and running on the OpenCL *host* device (CPU), where the client
is resident (e.g. a CPU-based PC having a GPU card).
User-defined variables can be exchanged between the program running on the
host and the kernel running on the client via the OpenCL framework.
The results of the mathematical computation running on the client can be
directly rendered in a 3D animated OpenGL *GUI* (Graphical User Interface) via the
OpenCL/GL *interoperability* modality.
The host can also directly render some graphics on the OpenGL GUI via the OpenGL
framework.

@dot
graph neutrino_nutshell
{
  "host program\n(CPU)" -- "client kernel\n(GPU)" [label = " OpenCL"]
  "host program\n(CPU)" -- "OpenGL GUI" [label = " OpenGL"]
  "client kernel\n(GPU)" -- "OpenGL GUI" [label = " OpenCL/GL\ninteroperability"]
  {rank=same; "client kernel\n(GPU)", "OpenGL GUI"}
}
@enddot

# 2. Inside Neutrino {#Inside_Neutrino}
The Neutrino software is divided into two hierarchical layers:
- the high level *user* layer
- the low level *core* layer

The user level consists of:
- the C++ host program, implemented in the program.cpp file, containing:
  - the setup() function
  - the loop() function
  - the terminate() function
- the OpenCL client kernel, implemented in the thekernel.cl file
- the OpenGL *vertex shader*, implemented in the vertex.vert file
- the OpenGL *fragment shader*, implemented in the fragment.frag file

The vertex and fragment shaders are OpenGL programs written in the [GLSL language](https://en.wikipedia.org/wiki/OpenGL_Shading_Language).
Both those OpenGL programs are used by the GPU to render the 3D animated GUI.

The core level consists of all the infrastructure that makes the main() function
able to invoke in sequence the following user level functions:
  - the setup() function, implementing code run only once at the beginning
  of the program.
  - the loop() function, implementing code continuously run in a loop
  - the terminate() function, implementing code run only once at the end of
  the program.

A Neutrino user is not supposed to need to modify the core level functions, if
not in order to extend its basic functionalities, in order to solve their problem of
interest.   

  @dot
  digraph neutrino_layers
  {
    "Neutrino" -> "User layer"
    "Neutrino" -> "Core layer" [style=dotted]
    "User layer" -> "program.cpp", "thekernel.cl", "vertex.vert", "fragment.frag"
    "Core layer" -> "main()" [style=dotted]
    "main()" -> "setup()", "loop()", "terminate()" [style=dotted]
    "program.cpp" -> "setup()"
    "program.cpp" -> "loop()"
    "program.cpp" -> "terminate()"
  }
  @enddot

# 3. OpenCL/GL GPU-accelerated parallel computing paradigm {#OpenCL_GL_GPU-accelerated_parallel_computing_paradigm}
Modern GPUs are not monolithic processors, instead they are organized as an
array of multiple identical elementary *compute units*.
OpenCL is a software framework that let the user taking control of all those
compute units within a *parallel computing* paradigm, taking advantage of the
underlying GPU's hardware architecture.
OpenCL abstracts and generalizes the particular hardware implementation of each
different type of GPUs by means of its dedicated drivers, making possible
to program different GPUs by a same common programming language.
It is therefore not necessary to know how the hardware architecture is implemented
at a low level inside the GPU: it is sufficient to know there is an array of
compute units available to the user. Each of the compute units can be functionally
considered as like as an individual CPU.

@dot
digraph Modern_GPU
{
  graph [label = "Modern GPU architecture:", labelloc = t]
  node [shape = record]
  struct1 [label = "{CPU_1|CPU_1|CPU_3|CPU_4}|
                    {CPU_5|CPU_6|CPU_7|CPU_8}|
                    {CPU_9|CPU_...|CPU_...|CPU_...}|
                    {CPU_...|CPU_...|CPU_...|CPU_N}"]
}
@enddot

The OpenCL compute units are identified by one or more, usually up to 3 and
depending on the available hardware, *global indexes*. Within that maximum number
of available indexes, the user can decide how many indexes use to index the
compute units, therefore changing their corresponding array organization.
In case the user chooses to use only one index (i), the array becomes a *vector*,
in case of two (i, j) it become a *matrix* and in case of three (i, j, k) it
becomes a *rank-3 tensor* of compute units. The number of indexes chosen to
index the array is called *kernel dimension*, with respect to the OpenCL client
kernel. The total number of cells in the array, besides its indexing organization,
is called *kernel global size*.

Why it's like this? It comes with the idea of parallelization.

A parallel program is a software made of serial, time sequential, operations
among a dataset of operands which has been divided among many compute units.
In parallel computation the dataset of operands is split into an array and sent to
the compute units array: the two arrays must have the same indexing organization.
All compute units run *the same* sequence of operations *concurrently*: the
parallelization occurs because different compute units compute the same thing on
different data chunks *independently*. By saying "concurrently"
it must be noticed this not necessarily imply the exact *simultaneity*: there
is still the need for some *synchronization*. The latter requirement comes from
the *memory sharing* among the compute units array.
The choice of the type of indexing reflects type of algorithm that can be
implemented. The goal is to remove serial loops by *unwrapping* them
into a parallel data processing among all available compute units, when
possible. It is not always possible: it depends on the specific problem to be
solved and on the design and implementation of its corresponding computational
algorithm.

# 4. Analysis of an OpenCL code snippet vs its C++ equivalent {#Analysis_of_an_OpenCL_code_snippet_vs_its_CPP_equivalent}
An example showing the previous concepts, hereby written in C++, is the following
one:
```
float a[N];
float b[N];
float c[N];

for (i = 0; i < N; i++)
{
  c[i] = a[i]*b[i];
}
```
This program takes *N-cycles* to be completed on a CPU.

The same program can be rewritten, in OpenCL kernel language, this way:
```
__kernel void thekernel(__global float* a_array,
                        __global float* b_array,
                        __global float* c_array)
{
  int i = get_global_id(0);

  float a = a_array[i];
  float b = b_array[i];
  float c;
  barrier(CLK_GLOBAL_MEM_FENCE);

  c = a + b;
  c_array[i] = c;
  barrier(CLK_GLOBAL_MEM_FENCE);
}
```

The keyword *__kernel* indicates the function *thekernel* is an OpenCL kernel
program. The keyword *__global* means the arrays of float *a_array*, *b_array*
and *c_array* will be indexed to be used as a dataset in conjunction with the
compute units array indexing. An integer variable *i* is defined to be an OpenCL
global index, particularly the global index "0": the first of possible other
kernel dimensions. The *local variables* *a* and *b* have been assigned to a
generic value of their corresponding arrays indexed by *i*: this makes OpenCL
instantiating a specific variable having, respectively, the value of
*a_array[i]* and *b_array[i]* on each corresponding compute unit indexed by the
specific value of the index *i*. In other words, there would be a
"compute unit 1" where there would be a local variable "a_array[1]" and
"b_array[1]", a "compute unit 2" where there would be a local variable
"a_array[2]" and "b_array[2]", ... and so on till the "compute unit N" where
there would be a local variable "a_array[N]" and "b_array[N]": this is said to
be a *1D-kernel*. A variable *c* is defined for later use.
The function *barrier(CLK_GLOBAL_MEM_FENCE)* serves as a synchronization of this
process of instantiation: for reasons depending on both the OpenCL
software and the GPU underlying hardware it might be that this kind of
operation *will not occur exactly simultaneously* on all compute units. There
could be a little *time jitter*, therefore the program *must wait* for all compute
units to complete all the local operations before proceeding with the next steps.
Then the computation *c = a + b* occurs in *on all compute units*: there
is where the parallelism happens, no `for (i = 0; i < N; i++)` loop is involved.
All the results are then retrieved from all compute units and put together from
the local variable *c* to the build the array *c_array[i]*.
The latter operation is also subjected to another time jitter, hence another
*barrier(CLK_GLOBAL_MEM_FENCE)* is issued in order to prevent *memory leakages*.

From an algorithmic point of view, the kernel variables *a_array* and *b_array*
represent the two *input vectors* of the element-wise vector summation
*c_array = a_array + b_array*, while the latter one is the *output vector*
containing the result of that operation.

What about the number of element *N* ? How big can it be?

It depends on the available GPU. There are big and small OpenCL-compatible
GPUs. In case a given GPU is too small to comply with a big *N*, OpenCL has got
methods to split the computation in sequential time slots: it first fills all
available compute units and performs a first computation, later it continues with
the remaining part of the dataset. This generates a considerable *memory swapping*
overhead and must be taken into account in terms of speed optimization.
It is always better to make the dataset matching the maximum capacity of
available compute units, at the cost of *padding* the dataset: this approach
remains valid also at a local level inside the OpenCL kernel.
