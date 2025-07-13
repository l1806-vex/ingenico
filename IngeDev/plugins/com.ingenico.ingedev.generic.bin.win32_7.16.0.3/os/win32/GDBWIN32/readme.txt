This is GDB from the MingW distribution.

We must use this one instead of Cygwin GDB, because Cygwin GDB
is not able to set a breakpoint using the file's full path, if the file
has been compiled with its relative path, and if the current drive is
different from the file's drive.

