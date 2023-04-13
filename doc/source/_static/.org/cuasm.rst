=====
CUASM
=====

    :Author: John Thingstad
    :Date: ""2023-04-13"



1 cuasm
-------

cuasm is a program that translates SASL assembly to machine code.

1.1 PTX and SASS
~~~~~~~~~~~~~~~~

NVIDIA has a virtual machine language called PTX. ptxas is a assembler
that translates this byte-code format to machine-code on load after
performing some optimizations. This make the code architecture
independent. It does, however, means it might miss some opportunities for
hardware specific optimizations.

The hardware specific language is called SASS. SASS is short for
Source and ASSembly.

Anyhow to generate SASL use nvcc with -cuobj option then use  cudisasm to
view the assembly instructions. You can also generate SASL from ptxas.

1.2 libelf
~~~~~~~~~~

libelf are a set of utilities for reading, writing and studying ELF
files. ELF stands for Executable Link Format and is the Linux link format.
In addition to ELF format we need DWARF. DWARF stands for Debugging
With Arbitrary Record and is the way Linux embeds debug information
into executables and libraries.
Of particular use for us is libelf.so and libelf.h

1.3 CuAssembler
~~~~~~~~~~~~~~~

CuAssembler is a python tool for assembling to SASL.
On git hub at `https://github.com/cloudcores/CuAssembler <https://github.com/cloudcores/CuAssembler>`_


Documentation at `https://sourceware.org/elfutils/ <https://sourceware.org/elfutils/>`_
