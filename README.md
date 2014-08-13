ClangThreadSanitizerTests
=========================

Building threadsanitizer_atomic_int.cpp
=======================================

```bash
$ clang++ -std=c++11 [-stdlib=libc++] [-DUSE_BOOST_ATOMIC] [-DUSE_THREAD] -fsanitize=thread threadsanitizer_atomic_int.cpp
$ ./a.out
```

Building threadsanitizer_shared_ptr.cpp
=======================================

Note that atomic operation on shared_ptr is not implemented in libstdc++, therefore without `-stdlib=libc++` compiler options, `-DUSE_BOOST_ATOMIC` must be specified.

```bash
$ clang++ -std=c++11 -DUSE_BOOST_ATOMIC [-DUSE_THREAD]  -fsanitize=thread threadsanitizer_shared_ptr.cpp
$ ./a.out
```

or

```bash
$ clang++ -std=c++11 -stdlib=libc++ [-DUSE_BOOST_ATOMIC] [-DUSE_THREAD]  -fsanitize=thread threadsanitizer_shared_ptr.cpp
$ ./a.out
```

ThreadSanitizer Results
=======================
https://docs.google.com/spreadsheets/d/1b7prE2xTyetGZY6534N0viKJpUmC11FGKOR38fr0Mes/edit#gid=0
