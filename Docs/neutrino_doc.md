# Neutrino documentation {#Neutrino_documentation}

# 1. Neutrino in a nutshell {#Neutrino_in_a_nutshell}
*Neutrino* is a C++ software environment for GPU-accelerated parallel computing,
based on the [OpenCL](https://en.wikipedia.org/wiki/OpenCL) and
the [OpenGL](https://en.wikipedia.org/wiki/OpenGL) frameworks.
The aim of Neutrino is to reduce the code overhead, due to the complexity of
the GPU-accelerated paradigm, in order to let the users concentrate on the
implementation of their algorithms.
The architecture of this computational paradigm is based on a parallel execution of routines
running on a OpenCL *client* computing device (e.g. GPU card) and scheduled by a C++ *program* running
on the *host* device carrying the client (e.g. a PC).
The mathematical computation of interest is first prepared on the host device
starting by the `main.cpp` file and then run, by means further code written in so called OpenCL
*kernel* files, on the client.
User-defined variables can be exchanged between the program running on the
host and the kernel running on the client via the OpenCL framework.
The results of the mathematical computation running on the client can be
directly plot in a 3D (also animated) OpenGL *GUI* (Graphical User Interface)
thanks to a modality called OpenCL/GL *interoperability*. The interoperability
allows the data buffers used for the computation within the OpenCL framework and
already allocated on the client to be directly shared with the OpenGL framework
in order to be used for the graphics rendition by the client itself: the advantage
of this is the usage of the fast GPU memory of the client for both computational and
graphics purposes, without using the memory space of the host.

Moreover, the host can also directly render some graphics on the OpenGL GUI via the OpenGL
framework, if necessary.

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
- the high level *user* layer.
- the low level *core* layer.

The user level simply consists of:
- the C++ host program, implemented starting from the `main.cpp` file of their
application.
- the OpenCL client kernels, implemented in one or more `kernel.cl` files.

The core level instead is made of all the necessary C++/OpenGL/OpenCL infrastructure
that makes the user able to concentrate only on the two aforementioned aspects.
More specifically, what it does can be summarised in the following main steps the user
must do in the host implementation of their application:
- a `neutrino` object is instantiated. This serves as a common object, later included in
all others as argument in their initialisation methods, for the exchange of common properties
they need (e.g. common libraries, common macro definitions, common variables, etc...).
- a `window` object is instantiated. It's initialisation sets up the OpenGL framework.
This opens the window where all graphics can be displayed. In case no graphics is needed,
or the available client does not support the OpenCL/GL interoperability modality, this
step can be entirely avoided; of course no graphics plot would be possible in this case, but
the computation can still be performed if at least OpenCL is supported by the client device.
In the latter minimal situation, the output of the computation might be saved on a file for
later analysis.
- an `opencl` object is instantiated. Later on, the initialisation of this object
will be responsible of setting up the OpenCL framework for the computation.
- an array of `queue` objects is instantiated. It has to have at least one element.
The queue is the OpenCL mechanism for scheduling the execution the kernels.
- an array of `kernel` objects is instantiated. It has to have at least one element.
Each kernel contains the routines, written in the OpenCL language, the user developed
in order to solve the mathematical problem of interest.

After their instantiation, these object must be initialised in the same sequence, because
they depend each other in this hierarchy. The number of queues and kernels depends on the
user's application.

# 3. OpenCL/GL GPU-accelerated parallel computing paradigm {#OpenCL_GL_GPU-accelerated_parallel_computing_paradigm}
Modern GPUs are not made of a single, monolithic, processor. Instead they are organised as an
array of multiple identical elementary *compute units*.
OpenCL is a software framework that let the user taking control of all those
compute units within a *parallel computing* paradigm, taking advantage of the
underlying GPU's hardware architecture.
OpenCL abstracts and generalises the particular hardware implementation of each
different type of GPUs by means of its dedicated drivers, making possible
to program different GPUs by a same common programming language.
It is therefore not necessary to know how the hardware architecture is implemented
at a low level inside the GPU: it is sufficient to know there is an *array of
compute units* available to the user. Each of the compute units can be functionally
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

The OpenCL compute units are identified by one or more, usually up to 3
(depending on the available hardware), *global indexes*. Within that maximum number
of available indexes, the user can decide how many indexes use to index the
compute units, therefore changing their corresponding array organisation.
In case the user chooses to use only one index (i), the array becomes a *vector*,
in case of two (i, j) it become a *matrix* and in case of three (i, j, k) it
becomes a *rank-3 tensor* of compute units. The number of indexes chosen to
index the array is called *kernel dimension*, with respect to the OpenCL client
kernel. The total number of cells in the array, besides its indexing organisation,
is called *kernel global size*.

Why it's like this? It comes with the idea of parallelisation.

A parallel program is a software made of serial, time sequential, operations
among a dataset of operands which has been divided among many compute units.
In parallel computation the dataset of operands is split into an array and sent to
the compute units array: the two arrays must have the same indexing organisation.
All compute units run *the same* sequence of operations *concurrently*: the
parallelisation occurs because different compute units compute the same thing on
different data chunks *independently*. By saying "concurrently"
it must be noticed this not necessarily imply the exact *simultaneity*: there
is still the need for some *synchronisation*. The latter requirement comes from
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
there would be a local variable "a_array[N]" and "b_array[N]": this is called
a *1D-kernel* because only one global index is used.
A variable *c* is defined for later use.
The function *barrier(CLK_GLOBAL_MEM_FENCE)* serves as a
synchronisation of this process of instantiation: for reasons depending on both
the OpenCL software and the GPU underlying hardware it might be that this kind of
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

What about the number of element *N*? How big can it be?

It depends on the available GPU. There are big and small OpenCL-compatible
GPUs. In case a given GPU is too small to comply with a big *N*, OpenCL has got
methods to split the computation in sequential time slots: it first fills all
available compute units and performs a first computation, later it continues with
the remaining part of the dataset. This generates a considerable *memory swapping*
overhead and must be taken into account in terms of speed optimisation.
It is always better to make the dataset matching the maximum capacity of
available compute units, at the cost of *padding* the dataset: this approach
remains valid also at a local level inside the OpenCL kernel.

NOTE:
A *2D kernel* would be something that would unwrap a C++ loop like this one:

```
float a[N*M];

for(i = 0; i < N; i++)
{
  for(j = 0; j < M; j++)
  {
    a[j + N*i] = ...some computation...;
  }
}
```

into an OpenCL kernel as follows:

```
__kernel void thekernel(__global float* a_array,
                        int N)
{
  int i = get_global_id(0);
  int j = get_global_id(1);

  float a = a_array[j + N*i];
  barrier(CLK_GLOBAL_MEM_FENCE);

  a = ...some computation...;
  a_array[j + N*i] = a;
  barrier(CLK_GLOBAL_MEM_FENCE);
}
```

Similarly for a *3D kernel*. Notice the usage of one-dimensional arrays (not to
be confused with the OpenCL *kernel dimension* = number of *global indexes*):
OpenCL does not deal with multi-dimensional C++ arrays. For the latter reason,
in an OpenCL kernel all multi-dimensional data have always to be interleaved in a
one-dimensional array.

# 5. Neutrino's OpenCL client-host system {#Neutrino_OpenCL_client_host_system}
Neutrino takes advantage of both host and client devices.
The host is used to prepare the initial dataset (e.g. filling data array, reading data
from a file, etc...) while the client is used for mass computation.
For this to happen, host and client need to talk together: this means they must
share some memory. Memory transfer from the client to the host, and vice-versa,
is always an overkilling task. Modern GPUs have fast and dedicated separate
memory, as opposed to ordinary client PC memory.

@dot
graph client_host_memory
{
  "client (e.g. GPU) memory" -- "host (e.g. PC) memory"
}
@enddot

The best way of managing this memory exchange is to avoid it as much as possible.
In Neutrino, we achieve this as follows:
- data objects can be initialised once by the host. For instance, in case of a
time varying simulation application, the initial data can be prepared at this step (e.g. by
assembling the data arrays, or by loading them from a file). This is done by means of
the several *set* methods of the data objects.
- once this has been done, the data prepared on the host can be loaded on the client
memory by means of the *push* object methods. This also creates, in case the OpenCL/GL
interoperability is supported by the client, a memory share between the OpenCL and the
OpenGL frameworks. This means the OpenGL frame buffer would be directly able to render the
special *point* and *color* data types which have been already allocated on the client
by the push methods and constantly updated by the results of the execution of the OpenCL kernels.
More specifically, if something has to be plot, the user is supposed to implement the kernels
in a ways the point and color data contains such information (e.g. a cloud of points
representing a 3D object, etc...).
- in case the output of the computation is needed elsewhere outside the graphics, it can be
retrieved from the client by the host, and therefore copied in the host's memory, by means of the
*pop* data object methods. This can be used, for instance, in order to save the results on a file.
