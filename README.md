cc-fpm
======

FastCGI that serves webpage written in C.

Instead of a streaming C interpreter, I am about to compile the code
into dynamically loadable library, whenever the code file changes.

When the code changes, recompile it, disable the running one,
unload it when ready, and then load the new one.

The problem in front is: whether to use external GCC for simplicity,
or to implement a new C compiler for function restriction. At this
very early stage, I am about to take GCC until a rewrite of C compiler
based on LLVM be ready.

For fast deployment, we devided the procedure into two separate parts:
1. Loader as Nginx input filter, that automatically load/update pages;
2. Builder that builds pages.

Both of them will be triggered by inotify[if no better solution].
