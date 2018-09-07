/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   Copyright (c) 2011-2018 The plumed team
   (see the PEOPLE file at the root of the distribution for a list of names)

   See http://www.plumed.org for more information.

   This file is part of plumed, version 2.

   plumed is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   plumed is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with plumed.  If not, see <http://www.gnu.org/licenses/>.
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/*
  This header might be included more than once in order to provide
  the declarations and the definitions. The guards are thus placed below.
*/

/*
  Here there are a number of cpp macros that can be used to control the behavior.
  Notice that the macros defined by the user are not modified. This is required
  to allow multiple inclusions of the header.

  The macros set here, that is those ending with an underscore, should be undefined at
  the end of this file!
*/

/*
  1: enable C++ wrapper (default)
  0: disable C++ wrapper
*/

#ifdef __PLUMED_WRAPPER_CXX
#define __PLUMED_WRAPPER_CXX_ __PLUMED_WRAPPER_CXX
#else
#define __PLUMED_WRAPPER_CXX_ 1
#endif

/*
  1: invalid construction throws an exception
  0: invalid construction produces an invalid object (default)

  It is set to zero by default for backward compatibility.
*/

#ifdef __PLUMED_WRAPPER_CXX_THROWS
#define __PLUMED_WRAPPER_CXX_THROWS_ __PLUMED_WRAPPER_CXX_THROWS
#else
#define __PLUMED_WRAPPER_CXX_THROWS_ 0
#endif

/*
  If __PLUMED_WRAPPER_CXX_THROWS==1, use this command to throw an exception when construction is invalid.
  By default, throws a std::runtime_error.
*/

#ifdef __PLUMED_WRAPPER_CXX_THROW_CMD
#define __PLUMED_WRAPPER_CXX_THROW_CMD_ __PLUMED_WRAPPER_CXX_THROW_CMD
#else
#define __PLUMED_WRAPPER_CXX_THROW_CMD_ throw ::std::runtime_error(x)
#endif

/*
  1: headers such as cstdlib are included in C++ (default)
  0: headers such as stdlib.h are included in C++
*/

#ifdef __PLUMED_WRAPPER_CXX_STD
#define __PLUMED_WRAPPER_CXX_STD_ __PLUMED_WRAPPER_CXX_STD
#else
#define __PLUMED_WRAPPER_CXX_STD_ 1
#endif

/*
  1: if __PLUMED_WRAPPER_EXTERN==0, it makes the C wrapper functions inline instead of static when using C++.
  0: C wrapper functions are never inline.

  This macro is only useful with __PLUMED_WRAPPER_EXTERN==0. In that case, if __PLUMED_WRAPPER_CXX_INLINE==1,
  the whole interface is declared inline rather than static when compiling with C++.
  As a result, calls to the C interface in different translation units will be merged.

  It is experimental and might produce errors.
*/

#ifdef __PLUMED_WRAPPER_CXX_INLINE
#define __PLUMED_WRAPPER_CXX_INLINE_ __PLUMED_WRAPPER_CXX_INLINE
#else
#define __PLUMED_WRAPPER_CXX_INLINE_ 0
#endif

/*
  1: place C++ wrappers in an anonymous namespace
  0: place C++ wrappers in the PLMD namespace (default)

  It will make PLMD::Plumed a different class (though with the same name)
  in each of the translation units in which `Plumed.h` is included.

  Note: anonymous namespace is experimental and might produce errors.
*/

#ifdef __PLUMED_WRAPPER_CXX_ANONYMOUS_NAMESPACE
#define __PLUMED_WRAPPER_CXX_ANONYMOUS_NAMESPACE_ __PLUMED_WRAPPER_CXX_ANONYMOUS_NAMESPACE
#else
#define __PLUMED_WRAPPER_CXX_ANONYMOUS_NAMESPACE_ 0
#endif

/*
  1: make PLMD::Plumed class polymorphic (default)
  0: make PLMD::Plumed class non-polymorphic
*/

#ifdef __PLUMED_WRAPPER_CXX_POLYMORPHIC
#define __PLUMED_WRAPPER_CXX_POLYMORPHIC_ __PLUMED_WRAPPER_CXX_POLYMORPHIC
#else
#define __PLUMED_WRAPPER_CXX_POLYMORPHIC_ 1
#endif

/*
  1: make the wrapper functions extern (default)
  0: make the wrapper functions static or inline (see also __PLUMED_WRAPPER_CXX_INLINE)

  If set to zero, it disables all functions that only make sense if extern, such as
  Fortran wrappers, global objects, and plumed_kernel_register.

  It can be set to zero to include multiple copies of the wrapper implementation without worrying
  about duplicated symbols.
*/

#ifdef __PLUMED_WRAPPER_EXTERN
#define __PLUMED_WRAPPER_EXTERN_ __PLUMED_WRAPPER_EXTERN
#else
#define __PLUMED_WRAPPER_EXTERN_ 1
#endif

/*
  1: emit plumed_kernel_register function (default)
  0: do not emit plumed_kernel_register function

  This function is only needed to avoid an extra warning when loading old (<=2.4) kernels.
  We might change its default in the future.
*/

#ifdef __PLUMED_WRAPPER_KERNEL_REGISTER
#define __PLUMED_WRAPPER_KERNEL_REGISTER_ __PLUMED_WRAPPER_KERNEL_REGISTER
#else
#define __PLUMED_WRAPPER_KERNEL_REGISTER_ 1
#endif

/*
  1: emit Fortran wrappers (default)
  0: do not emit Fortran wrappers
*/

#ifdef __PLUMED_WRAPPER_FORTRAN
#define __PLUMED_WRAPPER_FORTRAN_ __PLUMED_WRAPPER_FORTRAN
#else
#define __PLUMED_WRAPPER_FORTRAN_ 1
#endif

/*
  1: emit global plumed object (default)
  0: do not emit global plumed object
*/

#ifdef __PLUMED_WRAPPER_GLOBAL
#define __PLUMED_WRAPPER_GLOBAL_ __PLUMED_WRAPPER_GLOBAL
#else
#define __PLUMED_WRAPPER_GLOBAL_ 1
#endif

/*
  1: emit implementation
  0: do not emit implementation

  Allows an implementation to be emitted together with the declarations.

*/

#ifdef __PLUMED_WRAPPER_IMPLEMENTATION
#define __PLUMED_WRAPPER_IMPLEMENTATION_ __PLUMED_WRAPPER_IMPLEMENTATION
#else
#define __PLUMED_WRAPPER_IMPLEMENTATION_ 0
#endif

#if !__PLUMED_WRAPPER_IMPLEMENTATION_ && !__PLUMED_WRAPPER_EXTERN_
#error "If you configure Plumed.h with internal linkage you should emit implementation as well"
#endif

#if __PLUMED_WRAPPER_EXTERN_

#define __PLUMED_WRAPPER_VISIBILITY_ extern

#else

#if __PLUMED_WRAPPER_CXX_INLINE_
#define __PLUMED_WRAPPER_VISIBILITY_ inline
#else
#define __PLUMED_WRAPPER_VISIBILITY_ static
#endif

#undef __PLUMED_WRAPPER_KERNEL_REGISTER_
#define __PLUMED_WRAPPER_KERNEL_REGISTER_ 0
#undef __PLUMED_WRAPPER_FORTRAN_
#define __PLUMED_WRAPPER_FORTRAN_ 0
#undef __PLUMED_WRAPPER_GLOBAL_
#define __PLUMED_WRAPPER_GLOBAL_ 0

#endif

#ifndef __cplusplus
#undef __PLUMED_WRAPPER_CXX_STD_
#define __PLUMED_WRAPPER_CXX_STD_ 0
#endif

#if __PLUMED_WRAPPER_CXX_STD_
#define __PLUMED_WRAPPER_STD ::std::
#else
#define __PLUMED_WRAPPER_STD
#endif

#ifndef __PLUMED_wrapper_Plumed_h
#define __PLUMED_wrapper_Plumed_h

/**
\page ReferencePlumedH Reference for interfacing MD codes with PLUMED

  Plumed.h and Plumed.c contain the external plumed interface, which is used to
  integrate it with MD engines. This interface is very general, and is expected
  not to change across plumed versions. Plumed.c also implements a dummy version
  of the interface, so as to allow a code to be fully linked even if the plumed
  library is not available yet. These files could be directly included in the official
  host MD distribution. In this manner, it will be sufficient to link the plumed
  library at link time (on all systems) or directly at runtime (on systems where
  dynamic loading is enabled) to include plumed features.

  Notice that in PLUMED 2.5 this interface has been rewritten in order to allow
  more debugging features and a better behavior in multithread environments.
  The interface is almost perfectly backward compatible, although it implements
  a few additional functions. See more details below.

  Why is Plumed.c written in C and not C++? The reason is that the resulting Plumed.o
  needs to be linked with the host MD code immediately (whereas the rest of plumed
  could be linked a posteriori). Imagine the MD code is written in FORTRAN: when we
  link the Plumed.o file we would like not to need any C++ library linked. In this
  manner, we do not need to know which C++ compiler will be used to compile plumed.
  The C++ library is only linked to the "rest" of plumed, which actually uses it.
  Anyway, Plumed.c is written in such a manner to allow its compilation also in C++
  (C++ is a bit stricter than C) This will
  allow e.g. MD codes written in C++ to just incorporate Plumed.c (maybe renamed into
  Plumed.cpp), without the need of configuring a plain C compiler.

  Plumed interface can be used from C, C++ and FORTRAN. Everything concerning plumed
  is hidden inside a single object type, which is described in C by a structure
  (struct \ref plumed), in C++ by a class (PLMD::Plumed) and in FORTRAN by a
  fixed-length string (CHARACTER(LEN=32)). Obviously C++ can use both struct
  and class interfaces, but the second should be preferred. The reference interface
  is the C one, whereas FORTRAN and C++ interfaces are implemented as wrappers
  around it.

  As of PLUMED 2.5, the interfaces contains a reference counter that allows
  for a better control of plumed initializations and deallocations.
  This is particularly useful for the C++ interface that now
  behaves similarly to a primitive shared pointer and can be thus copied.
  In other languages, to use the reference counter correctly it is sufficient to
  remember the following rule: for any `plumed_create*` call, there should be a corresponding
  `plumed_finalize` call.

  In the C++ interface, all the routines are implemented as methods of PLMD::Plumed.
  In the C and FORTRAN interfaces, all the routines are named plumed_*, to
  avoid potential name clashes. Notice that the entire plumed library
  is implemented in C++, and it is hidden inside the PLMD namespace.

  Handlers to the plumed object can be converted among different representations,
  to allow inter-operability among languages. In C, there are tools to convert
  to/from FORTRAN, whereas in C++ there are tools to convert to/from FORTRAN and C.

  These handlers only contain a pointer to the real structure, so that
  when a plumed object is brought from one language to another,
  it brings a reference to the same environment.

  Moreover, to simplify life in all cases where a single Plumed object is
  required for the entire simulation (which covers many of the practical
  applications with conventional MD codes) it is possible to take advantage
  of a global interface, which is implicitly referring to a unique global instance.
  The global object should still be initialized and finalized properly.
  This global object is obviously not usable in a multithread context.

  The basic method to send a message to plumed is
\verbatim
  (C) plumed_cmd
  (C++) PLMD::Plumed::cmd
  (FORTRAN)  PLUMED_F_CMD
\endverbatim

  To initialize a plumed object, use:
\verbatim
  (C)        plumed_create
  (C++)      (constructor of PLMD::Plumed)
  (FORTRAN)  PLUMED_F_CREATE
\endverbatim

  As of PLUMED 2.5, you can also initialize a plumed object using the following functions,
  that load a specific kernel:
\verbatim
  (C)        plumed_create_dlopen
  (C++)      PLMD::Plumed::dlopen
  (FORTRAN)  PLUMED_F_CREATE_DLOPEN
\endverbatim

  To finalize a plumed object, use
\verbatim
  (C)        plumed_finalize
  (C++)      (destructor of PLMD::Plumed)
  (FORTRAN)  PLUMED_F_FINALIZE
\endverbatim

  To access to the global-object, use
\verbatim
  (C)        plumed_gcreate, plumed_gfinalize, plumed_gcmd
  (C++)      PLMD::Plumed::gcreate, PLMD::Plumed::gfinalize, PLMD::Plumed::gcmd
  (FORTRAN)  PLUMED_F_GCREATE, PLUMED_F_GFINALIZE, PLUMED_F_GCMD
\endverbatim

  To check if the global object has been initialized, use
\verbatim
  (C)        plumed_ginitialized
  (C++)      PLMD::Plumed::ginitialized
  (FORTRAN)  PLUMED_F_GINITIALIZED
\endverbatim

  Notice that when using runtime binding the plumed library might be not available.
  In this case, plumed_create (and plumed_gcreate) will still succeed, but a subsequent
  call to plumed_cmd (or plumed_gcmd) would abort. In order to avoid this
  unpleasant situation you have two options.

  First, you can check if plumed library is available before actually creating an object
  using this function:
\verbatim
  (C)        plumed_installed
  (C++)      PLMD::Plumed::installed
  (FORTRAN)  PLUMED_F_INSTALLED
\endverbatim

  Alternatively, as of PLUMED 2.5, you can interrogate the just created plumed
  object using the following function:
\verbatim
  (C)        plumed_valid
  (C++)      PLMD::Plumed::valid
  (FORTRAN)  PLUMED_F_VALID
\endverbatim

  If you want to create on purpose an invalid Plumed object (useful in C++ to postpone
  the loading of the library) you can use `Plumed p(Plumed::invalid);`.

  To know if the global object is valid instead you should use the following function:
\verbatim
  (C)        plumed_gvalid
  (C++)      PLMD::Plumed::gvalid
  (FORTRAN)  PLUMED_F_GVALID
\endverbatim

  If you use C++ and compile your code with -D__PLUMED_WRAPPER_CXX_THROWS=1,
  an exception will be thrown as soon as you try to construct an invalid object instead.

  To convert handlers between different languages, use
\verbatim
  (C)        plumed_c2f                 (C to FORTRAN)
  (C)        plumed_f2c                 (FORTRAN to C)
  (C++)      Plumed(plumed) constructor (C to C++)
  (C++)      operator plumed() cast     (C++ to C)
  (C++)      Plumed(char*)  constructor (FORTRAN to C++)
  (C++)      toFortran(char*)           (C++ to FORTRAN)
\endverbatim

  As of PLUMED 2.5, we added a reference count. It is in practice possible
  to create multiple `plumed` object that refer to the same environment.
  This is done using the following functions
\verbatim
  (C)        plumed_create_reference(plumed)
  (FORTRAN)  plumed_f_create_reference(char*,char*)
\endverbatim
  In C++ references are managed automatically by constructors and destructor.

  The interface of the FORTRAN functions is very similar to that of the C functions
  and is listed below:

\verbatim
  FORTRAN interface
    SUBROUTINE PLUMED_F_CREATE(p)
      CHARACTER(LEN=32), INTENT(OUT)   :: p
    SUBROUTINE PLUMED_F_CREATE_DLOPEN(p,path)
      CHARACTER(LEN=32), INTENT(OUT)   :: p
      CHARACTER(LEN=*),  INTENT(IN)    :: path
    SUBROUTINE PLUMED_F_CREATE_REFERENCE(p,r)
      CHARACTER(LEN=32), INTENT(OUT)   :: p
      CHARACTER(LEN=32), INTENT(IN)    :: r
    SUBROUTINE PLUMED_F_CREATE_INVALID(p)
      CHARACTER(LEN=32), INTENT(OUT)   :: p
    SUBROUTINE PLUMED_F_CMD(p,key,val)
      CHARACTER(LEN=32), INTENT(IN)    :: p
      CHARACTER(LEN=*),  INTENT(IN)    :: key
      UNSPECIFIED_TYPE,  INTENT(INOUT) :: val(*)
    SUBROUTINE PLUMED_F_FINALIZE(p)
      CHARACTER(LEN=32), INTENT(IN)    :: p
    SUBROUTINE PLUMED_F_INSTALLED(i)
      INTEGER,           INTENT(OUT)   :: i
    SUBROUTINE PLUMED_F_VALID(p,i)
      CHARACTER(LEN=32), INTENT(IN)    :: p
      INTEGER,           INTENT(OUT)   :: i
    SUBROUTINE PLUMED_F_USE_COUNT(p,i)
      CHARACTER(LEN=32), INTENT(IN)    :: p
      INTEGER,           INTENT(OUT)   :: i
    SUBROUTINE PLUMED_F_GLOBAL(p)
      CHARACTER(LEN=32), INTENT(OUT)   :: p
    SUBROUTINE PLUMED_F_GINITIALIZED(i)
      INTEGER,           INTENT(OUT)   :: i
    SUBROUTINE PLUMED_F_GCREATE()
    SUBROUTINE PLUMED_F_GCMD(key,val)
      CHARACTER(LEN=*), INTENT(IN)     :: key
      UNSPECIFIED_TYPE, INTENT(INOUT)  :: val(*)
    SUBROUTINE PLUMED_F_GFINALIZE()
    SUBROUTINE PLUMED_F_GVALID(i)
      INTEGER,           INTENT(OUT)   :: i
\endverbatim

\section ReferencePlumedH-2-5 New in PLUMED 2.5

  The wrappers in PLUMED 2.5 have been completely rewritten with several improvements.
  The interface is almost perfectly backward compatible,
  although a few new functions are introduced (explicitly marked in the documentation).
  As a consequence, if your code uses some of the new functions, you will not be able
  to link it directly with an older PLUMED library (though you will still be able to load
  an older PLUMED library at runtime). In addition, the reference counter changes slightly
  the behavior of the C++ methods used to interoperate with C and FORTRAN.

  An important novelty is that the way the runtime loader is implemented changed drastically.
  Now, the loader is not anymore relying on an initializer function present in the kernel
  to be executed. This will allow the loader to work also if this function is not exported.
  The proper functions from the kernel are indeed searched explicitly now using `dlsym`.

  Some additional features can be enabled using suitable environment variables. In particular:
  - `PLUMED_LOAD_DEBUG` can be set to report more information about the loading process.
  - `PLUMED_LOAD_NAMESPACE` can be set to `LOCAL` to load the PLUMED kernel in a separate
    namespace. The default is global namespace, which is the same behavior of PLUMED <=2.4.
  - `PLUMED_LOAD_DEEPBIND` can be set to load the PLUMED kernel in deepbind mode, thus preferring
    the symbols defined in the library to other symbols with the same name. Only works
    on systems supporting `RTLD_DEEPBIND` and is mostly for debugging purposes.

  Another difference is that the implementation of the wrappers is now completely contained in the `Plumed.h`
  file. You can see that the `Plumed.c` is much simpler now and just includes `Plumed.h`. With a similar
  procedure you could compile the wrappers directly into your code making it unnecessary to link
  the libplumedWrapper.a library. Here's some example cpp macro that can be used to this aim:
  - `-D__PLUMED_WRAPPER_IMPLEMENTATION=1 -D__PLUMED_HAS_DLOPEN` allows to obtain a full implementation of the PLUMED
    interface in the current translation unit. This should be done at most in a single file.
    `-D__PLUMED_HAS_DLOPEN` makes sure PLUMED can be later loaded. This is how `Plumed.o` is produced.
  - `-D__PLUMED_WRAPPER_IMPLEMENTATION=1 -D__PLUMED_STATIC_KERNEL` allows to obtain a full implementation of the PLUMED
    interface in the current translation unit. This should be done at most in a single file. The PLUMED kernel
    should be availabe at link time. This is how `PlumedStatic.o` is produced.
  - `-D__PLUMED_WRAPPER_IMPLEMENTATION=1 -D__PLUMED_HAS_DLOPEN -D__PLUMED_WRAPPER_EXTERN=0` allows to obtain a light
    implementation of the PLUMED interface in the current translation unit. This interface is not exported, so it
    might be repeated in multiple files. As a limitation, it does not contain the PLUMED global instance and
    does not implement the FORTRAN wrappers.

  In addition, the plumed object now implements a reference counter. The number of references can be increased
  by using the function \ref plumed_create_reference() (or by \ref plumed_f_create_reference()), and is decreased by \ref plumed_finalize().
  Consider the following example
\verbatim
  plumed p=plumed_create();
  plumed_cmd(p,"init",NULL);
  plumed q=plumed_create_reference(p);
  plumed_finalize(p);
// at this stage, object q still exists
  plumed_cmd(q,"whatever",NULL);
  plumed_finalize(q);
// now plumed has been really finalized
\endverbatim

  In other words, every \ref plumed_create, \ref plumed_create_dlopen, and \ref plumed_create_reference call must be matched by a \ref plumed_finalize.

  Another difference is that the value of the variable `PLUMED_KERNEL` is read every time a new
  plumed object is instantiated. So, you might even use it to load different plumed versions
  simultaneously, although the preferred way to do this is using the function \ref plumed_create_dlopen.

  Finally, a few functions have been added, namely:
  - Functions to find if a plumed object is valid
    (\ref plumed_valid(), \ref plumed_gvalid(), \ref plumed_f_valid(), \ref plumed_f_gvalid(), \ref PLMD::Plumed::valid(),
     and \ref PLMD::Plumed::gvalid()).
  - Functions to create a plumed object based on the path of a specific kernel
    (\ref plumed_create_dlopen(), \ref plumed_f_create_dlopen(), and \ref PLMD::Plumed::dlopen()).
  - Functions to create a plumed object referencing to another one, implementing a reference counter
    (\ref plumed_create_reference() and \ref plumed_f_create_reference() .

  These functions were not available in PLUMED <=2.4. As a consequence, if you use one of those functions
  you will loose binary compatibility with libplumed.so (or libplumed.dylib on OSX).
  This is going to happen also if you use the C++ operators based on these functions, such as
  the new conversion operators from C and FORTRAN.
  Notice that in any case you will retain compatibility at the level of runtime loading.
  That is, you will always be able to load an older kernel setting the environment variable `PLUMED_KERNEL`.

*/

#ifdef __cplusplus
extern "C" {
#endif

/**
  \brief Main plumed object

  This is an object containing a Plumed instance, which should be used in
  the MD engine. It should first be initialized with plumed_create(),
  then it communicates with the MD engine using plumed_cmd(). Finally,
  before the termination, it should be deallocated with plumed_finalize().
  Its interface is very simple and general, and is expected
  not to change across plumed versions. See \ref ReferencePlumedH.
*/
typedef struct {
  /**
    \private
    \brief Void pointer holding the real PlumedMain structure

    To maintain binary compatibility, we should not add members to this structure.
  */
  void*p;
} plumed;

/** \relates plumed
    \brief Constructor

    Constructs a plumed object.

    Notice that if you are linking against libplumedWrapper.a, if you are
    using a code patched in runtime mode, or if you are including the `Plumed.c`
    file directly in your code, this constructor might return an invalid plumed
    object. In particular, this could happen if the `PLUMED_KERNEL` environment
    variable is not set or set incorrectly. In order to detect an incorrect
    plumed object you might use \ref plumed_valid() on the resulting object.
    Alternatively, if you use \ref plumed_cmd() on an invalid plumed object the code will abort.
    Also notice that to avoid memory leaks you should call \ref plumed_finalize()
    to finalize a plumed object even if it is invalid.

    \return The constructed plumed object
*/
__PLUMED_WRAPPER_VISIBILITY_
plumed plumed_create(void);

/** \relates plumed
    \brief Constructor from path. Available as of PLUMED 2.5

    It tries to construct a plumed object loading the kernel located at path.
    Notice that it could leave the resulting object in an invalid state.
    In order to detect an invalid
    plumed object you might use \ref plumed_valid() on the resulting object.
    Alternatively, if you use \ref plumed_cmd() on an invalid plumed object the code will abort.

    Also notice that to avoid memory leaks you should call \ref plumed_finalize()
    to finalize a plumed object even if it is invalid.

    \return The constructed plumed object
*/
__PLUMED_WRAPPER_VISIBILITY_
plumed plumed_create_dlopen(const char*path);

/** \relates plumed
    Create a new reference to an existing object, increasing its reference count.

    Use it to increase by one the reference count of a plumed object.
    The resulting pointer might be identical to the one passed as an
    argument, but the reference count will be incremented by one.
    Notice that you should finalize the resulting object.
\verbatim
  plumed p1;
  plumed p2;
  p1=plumed_create();
  p2=plumed_create_reference(p1);
  plumed_finalize(p1);
// now you can still use p2
  plumed_cmd(p2,"init",NULL);
  plumed_finalize(p2);
// now the underlying object is destroyed.
\endverbatim

    \param p The plumed object that will be referenced to.
*/

__PLUMED_WRAPPER_VISIBILITY_
plumed plumed_create_reference(plumed p);

/** \relates plumed
    \brief Constructor as invalid.

   Can be used to create an object in the same state as if it was returned by
   plumed_create_dlopen with an incorrect path (or plumed_create using runtime binding
   and an incorrect PLUMED_KERNEL).

   Mostly for debug.

    \return The constructed plumed object
*/
__PLUMED_WRAPPER_VISIBILITY_
plumed plumed_create_invalid();

/** \relates plumed
    \brief Tells p to execute a command.

    If the object is not valid, this command will abort.

    \param p The plumed object on which command is acting
    \param key The name of the command to be executed
    \param val The argument. It is declared as const to allow calls like plumed_cmd(p,"A","B"),
               but for some choice of key it can change the content.

    Notice that within PLUMED we use a const_cast to remove any const qualifier from the second
    argument of \ref plumed_cmd.

    In some cases val can be omitted: just pass a NULL pointer (in C++, val is optional and can be omitted,
    or you can equivalently pass NULL or nullptr).
    The set of possible keys is the real API of the plumed library, and will be expanded with time.
    New commands will be added, but backward compatibility will be retained as long as possible.
*/
__PLUMED_WRAPPER_VISIBILITY_
void plumed_cmd(plumed p,const char*key,const void*val);

/** \relates plumed
    \brief Destructor.

    It must be used for any object created using \ref plumed_create(),
    even if the created object is not valid.

    \param p The plumed object to be deallocated
*/
__PLUMED_WRAPPER_VISIBILITY_
void plumed_finalize(plumed p);

/** \relates plumed
    \brief Check if plumed is installed (for runtime binding).

    Notice that this is equivalent to creating a dummy object and check if it is valid.

\verbatim
  // this:
  //int a=plumed_installed();
  // is equivalent to this:

  plumed p=plumed_create();
  int a=plumed_valid(p);
  plumed_finalize(p);

\endverbatim

    This function is mostly provided for compatibility with PLUMED 2.4, where \ref plumed_valid()
    was not available. Using \ref plumed_valid() is now preferred since it creates a single object
    instead of creating a dummy object that is then discarded.

    \return 1 if plumed is installed, 0 otherwise
*/
__PLUMED_WRAPPER_VISIBILITY_
int plumed_installed(void);

/** \relates plumed
    \brief Check if plumed object is valid. Available as of PLUMED 2.5

    It might return false if plumed is not available at runtime.

    \return 1 if plumed is valid, 0 otherwise
*/
__PLUMED_WRAPPER_VISIBILITY_
int plumed_valid(plumed p);

/** \relates plumed
    \brief Returns the number of references to the underlying object. Available as of PLUMED 2.5.
*/
__PLUMED_WRAPPER_VISIBILITY_
int plumed_use_count(plumed p);

#if __PLUMED_WRAPPER_GLOBAL_

/** \relates plumed
    \brief Retrieves an handler to the global structure.

  You can use this if you work on a code that uses the global structure and you want to
  pass to a generic routine an handler to the same structure. E.g.

\verbatim
  plumed p=plumed_global();
  some_routine(p);
\endverbatim
*/
__PLUMED_WRAPPER_VISIBILITY_
plumed plumed_global(void);

/** \relates plumed
    \brief Check if the global interface has been initialized.

    \return 1 if plumed has been initialized, 0 otherwise
*/
__PLUMED_WRAPPER_VISIBILITY_
int plumed_ginitialized(void);

/** \relates plumed
    \brief Constructor for the global interface.

    \note Equivalent to plumed_create(), but initialize the static global plumed object
*/
__PLUMED_WRAPPER_VISIBILITY_
void plumed_gcreate(void);

/** \relates plumed
    \brief Tells to the global interface to execute a command.

    \param key The name of the command to be executed
    \param val The argument. It is declared as const to allow calls like plumed_gcmd("A","B"),
               but for some choice of key it can change the content

    `plumed_gcmd(a,b);` is equivalent to `plumed_cmd(plumed_global(),a,b);`.
*/
__PLUMED_WRAPPER_VISIBILITY_
void plumed_gcmd(const char* key,const void* val);

/** \relates plumed
    \brief Destructor for the global interface.

    `plumed_gfinalize(a,b);` is similar to `plumed_finalize(plumed_global(),a,b);`, but not completely
    equivalent. In particular, plumed_gfinalize() also makes sure that the global object
    is reset to its initial status. After calling it, \ref plumed_ginitialized() will thus return 0.
*/
__PLUMED_WRAPPER_VISIBILITY_
void plumed_gfinalize(void);

/** \relates plumed
    \brief Check if global plumed object is valid. Available as of PLUMED 2.5

    It might return false if plumed is not available at runtime.

    \return 1 if plumed is valid, 0 otherwise.
*/
__PLUMED_WRAPPER_VISIBILITY_
int plumed_gvalid();

#endif

/* routines to convert char handler from/to plumed objects */

/** \related plumed
    \brief Converts a C handler to a FORTRAN handler

    \param p The C handler
    \param c The FORTRAN handler (a char[32])

    This function can be used to convert a plumed object created in C to
    a plumed handler that can be used in FORTRAN. Notice that the reference counter
    is not incremented. In other words, the FORTRAN object will be a weak reference.
    If you later finalize the C handler, the FORTRAN handler will be invalid.
\verbatim
#include <plumed/wrapper/Plumed.h>
int main(int argc,char*argv[]){
  plumed p;
  p=plumed_create();
  char fortran_handler[32];
  plumed_c2f(p,fortran_handler);
  printf("DEBUG: this is a string representation for the plumed handler: %s\n",fortran_handler);
  fortran_routine(fortran_handler);
  plumed_finalize(p);
  return 0;
}
\endverbatim
  Here `fortran_routine` is a routine implemented in FORTRAN that manipulates the
  fortran_handler.
*/
__PLUMED_WRAPPER_VISIBILITY_
void   plumed_c2f(plumed p,char* c);

/** \related plumed
    \brief Converts a FORTRAN handler to a C handler
    \param c The FORTRAN handler (a char[32])
    \return The C handler

    This function can be used to convert a plumed object created in FORTRAN
    to a plumed handler that can be used in C.  Notice that the reference counter
    is not incremented. In other words, the C object will be a weak reference.
    If you later finalize the FORTRAN handler, the C handler will be invalid.
\verbatim
void c_routine(char handler[32]){
  plumed p;
  p=plumed_f2c(handler);
  plumed_cmd(p,"init",NULL);
}
\endverbatim
  Here `c_routine` is a C function that can be called from FORTRAN
  and interact with the provided plumed handler.
*/
__PLUMED_WRAPPER_VISIBILITY_
plumed plumed_f2c(const char* c);

#ifdef __cplusplus
}
#endif

#if defined( __cplusplus) && __PLUMED_WRAPPER_CXX_

/* this is to include the NULL pointer */
#if __PLUMED_WRAPPER_CXX_STD_
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#if __PLUMED_WRAPPER_CXX_THROWS_
#include <exception>
#endif

#if __PLUMED_WRAPPER_CXX_ANONYMOUS_NAMESPACE_
namespace {
#endif

/* C++ interface is hidden in PLMD namespace (same as plumed library) */
namespace PLMD {

/**
  C++ wrapper for \ref plumed.

  This class provides a C++ interface to PLUMED.
  It only containts a \ref plumed object, but wraps it with a number of useful methods.
*/

class Plumed {
  /**
    C structure.
  */
  plumed main;
  /**
    Dummy class
  */
  class invalid_t {
  };
public:
  static const invalid_t invalid;
  /**
     Check if plumed is installed (for runtime binding)
     \return true if plumed is installed, false otherwise
     \note Equivalent to plumed_installed() but returns a bool
  */
  static bool installed();
  /**
     Check if Plumed object is valid. Available as of PLUMED 2.5
     Notice that if this header is compiled with -D__PLUMED_WRAPPER_CXX_THROWS=1
     this is guaranteed to be always true.
     \return true if plumed is valid, false otherwise
     \note Equivalent to plumed_valid() but returns a bool
  */
  bool valid() const;
  /**
     Same as \ref valid()

  Allow code such as
  \verbatim
  Plumed p;
  if(!p) raise_error();
  p.cmd("init");
  \endverbatim
  */
  operator bool()const;
  /**
     Returns the number of references to this object.
    note Equivalent to plumed_use_count()
  */
  int use_count() const;
#if __PLUMED_WRAPPER_GLOBAL_
  /**
     Check if global-plumed has been initialized
     \return true if global plumed object (see global()) is initialized (i.e. if gcreate() has been
             called), false otherwise.
     \note Equivalent to plumed_ginitialized() but returns a bool
  */
  static bool ginitialized();
  /**
     Check if global-plumed is valid
     \return true if global plumed object (see global()) is valid.
     \note Equivalent to plumed_gvalid() but returns a bool
  */
  static bool gvalid();
  /**
     Initialize global-plumed.
     \note Equivalent to plumed_gcreate()
  */
  static void gcreate();
  /**
     Send a command to global-plumed
      \param key The name of the command to be executed
      \param val The argument. It is declared as const to allow calls like gcmd("A","B"),
                 but for some choice of key it can change the content
     \note Equivalent to plumed_gcmd()
  */
  static void gcmd(const char* key,const void* val=NULL);
  /**
     Finalize global-plumed
  */
  static void gfinalize();
  /**
     Returns the Plumed global object

     Notice that the object is copied, thus increasing the reference counter of the
     global object. In this manner, the global object will survive after a call to
     \ref gfinalize() if the resulting object is still in scope.

     \return The Plumed global object
  */
  static Plumed global();
#endif
  /**
     Constructor.

    Notice that when using runtime binding the constructed object might be
    invalid. One might check it using the \ref valid() method.
    On the other hand, if code is compiled with -D__PLUMED_WRAPPER_CXX_THROWS=1,
    the constructor will throw an exception if the object is invalid.

    \note Performs the same task a plumed_create()
  */
  Plumed();
  /**
     Clone a Plumed object from a FORTRAN char* handler.

     Notice that if an handler to an invalid plumed object is passed and the code is compiled
     with -D__PLUMED_WRAPPER_CXX_THROWS=1 an exception will be thrown.

     \param c The FORTRAN handler (a char[32]).

     The reference counter for the corresponding object will be increased
     to make sure that the object will be available after plumed_f_finalize is called
     if the created object is still in scope.

  */
// to have maximum portability of this file I do not use the explicit keyword here
// I thus add a suppress command for cppcheck
// cppcheck-suppress noExplicitConstructor
  Plumed(const char*c);
  /**
     Clone a Plumed object from a C plumed structure

     Notice that if a structure containing an invalid plumed object is passed and the code is compiled
     with -D__PLUMED_WRAPPER_CXX_THROWS=1 an exception will be thrown.

     \param p The C plumed structure.

     The reference counter for the corresponding object will be increased
     to make sure that the object will be available after plumed_finalize is called
     if the created object is still in scope.
  */
// to have maximum portability of this file I do not use the explicit keyword here
// I thus add a suppress command for cppcheck
// cppcheck-suppress noExplicitConstructor
  Plumed(plumed p);
  /** Invalid constructor.

    Can be used to initialize an invalid object. It might be useful to postpone
    the initialization of a Plumed object. Consider the following case
  \verbatim
    Plumed p;
    setenv("PLUMED_KERNEL","/path/to/kernel/libplumedKernel.so",1);
    p.cmd("init")
  \endverbatim
    Here the `p` object will be initialized *before* the `PLUMED_KERNEL` env var has been set.
    This can be particularly problematic if `p` is stored in some high level class.
    The following case would do the job
  \verbatim
    Plumed p;
    setenv("PLUMED_KERNEL","/path/to/kernel/libplumedKernel.so",1);
    p=Plumed();
    p.cmd("init")
  \endverbatim
    However, there will be some error reported related to the attempt to load the kernel
    when `p` is initialized. The following solution is the optimal one:
  \verbatim
    Plumed p(Plumed::invalid);
    setenv("PLUMED_KERNEL","/path/to/kernel/libplumedKernel.so",1);
    p=Plumed();
    p.cmd("init")
  \endverbatim
  */
  Plumed(invalid_t);
  /** Copy constructor.

    Takes a reference, incrementing the reference counter of the corresponding object.
  */
  Plumed(const Plumed& p);
  /** Assignment operator.

    Takes a reference,incrementing the reference counter of the corresponding object.
  */
  Plumed&operator=(const Plumed&p);
  /*
    PLUMED 2.4 requires a C++11 compiler.
    Anyway, since Plumed.h file might be redistributed with other codes
    and it should be possible to combine it with earlier PLUMED versions,
    we here explicitly check if C+11 is available before enabling move semantics.
  */
#if __cplusplus > 199711L
  /** Move constructor.
    Only if move semantics is enabled.
  */
  Plumed(Plumed&&);
  /** Move assignment.
    Only if move semantics is enabled.
  */
  Plumed& operator=(Plumed&&);
#endif
  /**
    Create a PLUMED object loading a specific kernel. Available as of PLUMED 2.5.

    It returns an object created with \ref plumed_create_dlopen. The object is owned and
    is then finalized in the destructor. It can be used as follows:
  \verbatim
    PLMD::Plumed p = PLMD::Plumed::dlopen("/path/to/libplumedKernel.so");
  // or, equivalenty:
  //    PLMD::Plumed p(PLMD::Plumed::dlopen("/path/to/libplumedKernel.so"));
    p.cmd("init");
  \endverbatim
    or, equivalently, as
  \verbatim
    auto p = PLMD::Plumed::dlopen("/path/to/libplumedKernel.so");
    p.cmd("init");
  \endverbatim
  */
  static Plumed dlopen(const char* path);

  /**
     Retrieve the C plumed structure for this object.

     Notice that the resulting plumed structure is a weak reference and
     should NOT be finalized, unless a new reference is explicitly addded
  \verbatim
  Plumed p;
  plumed c=p;
  plumed_finalize(c); // <- this is wrong
  \endverbatim
  \verbatim
  Plumed p;
  plumed c=plumed_create_reference(p);
  plumed_finalize(c); // <- this is right
  \endverbatim
  */
  operator plumed()const;
  /**
     Retrieve a FORTRAN handler for this object
      \param c The FORTRAN handler (a char[32]).
    Notice that the resulting plumed structure is a weak reference and
    should NOT be finalized, unless a new reference is explicitly addded.
  */
  void toFortran(char*c)const;
  /**
     Send a command to this plumed object
      \param key The name of the command to be executed
      \param val The argument. It is declared as const to allow calls like p.cmd("A","B"),
                 but for some choice of key it can change the content
      \note Equivalent to plumed_cmd()
  */
  void cmd(const char*key,const void*val=NULL);
  /**
     Destructor

     It calls \ref plumed_finalize(). Notice that this is done also if the
     constructor failed (that is, if it returned an invalid object). This allows
     declaring Plumed objects also if PLUMED is actually not available, provided
     one does not use the \ref cmd method.

     Destructor is virtual so as to allow correct inheritance from Plumed object.
     To avoid linking problems with g++, I specify "inline" also here (in principle
     it should be enough to specify it down in the definition of the function, but
     for some reason that I do not understand g++ does not inline it properly in that
     case and complains when Plumed.h is included but Plumed.o is not linked. Anyway, the
     way it is done here seems to work properly).
  */
#if __PLUMED_WRAPPER_CXX_POLYMORPHIC_
  inline virtual
#endif
  ~Plumed();
};

/* All methods are inlined so as to avoid the compilation of an extra c++ file */

inline
bool Plumed::installed() {
  return plumed_installed();
}

inline
bool Plumed::valid() const {
  return plumed_valid(main);
}

inline
Plumed::operator bool()const {
  return plumed_valid(main);
}

inline
int Plumed::use_count() const {
  return plumed_use_count(main);
}

inline
Plumed::Plumed():
  main(plumed_create())
{
#if __PLUMED_WRAPPER_CXX_THROWS_
  if(!plumed_valid(main)) {
    plumed_finalize(main);
    __PLUMED_WRAPPER_CXX_THROW_CMD_("Could not initialize a PLUMED object. Check your PLUMED_KERNEL env var.");
  }
#endif
}

inline
Plumed::Plumed(const char*c):
  main(plumed_create_reference(plumed_f2c(c)))
{
#if __PLUMED_WRAPPER_CXX_THROWS_
  if(!plumed_valid(main)) __PLUMED_WRAPPER_CXX_THROW_CMD_("Could not initialize a PLUMED object. Check your PLUMED_KERNEL env var.");
#endif
}

inline
Plumed::Plumed(plumed p):
  main(plumed_create_reference(p))
{
#if __PLUMED_WRAPPER_CXX_THROWS_
  if(!plumed_valid(main)) __PLUMED_WRAPPER_CXX_THROW_CMD_("Could not initialize a PLUMED object. Check your PLUMED_KERNEL env var.");
#endif
}

inline
Plumed::Plumed(invalid_t):
  main(plumed_create_invalid())
{
}

inline
Plumed::Plumed(const Plumed& p):
  main(plumed_create_reference(p.main))
{
}

inline
Plumed& Plumed::operator=(const Plumed&p) {
  if(this != &p) {
    if(main.p) plumed_finalize(main);
    main=plumed_create_reference(p.main);
  }
  return *this;
}

#if __cplusplus > 199711L
inline
Plumed::Plumed(Plumed&& p):
  main(p.main)
{
  p.main.p=nullptr;
}

inline
Plumed& Plumed::operator=(Plumed&& p) {
  if(this != &p) {
    if(main.p) plumed_finalize(main);
    main=p.main;
    p.main.p=nullptr;
  }
  return *this;
}
#endif

inline
Plumed Plumed::dlopen(const char* path) {
  Plumed p(plumed_create_dlopen(path));
  plumed_finalize(p.main); // remove extra reference
#if __PLUMED_WRAPPER_CXX_THROWS_
// throws if the object is not valid.
  if(!p.valid()) __PLUMED_WRAPPER_CXX_THROW_CMD_("Could not initialize a PLUMED object with the given path.");
#endif
  return p;
}

inline
Plumed::operator plumed()const {
  return main;
}

inline
void Plumed::toFortran(char*c)const {
  plumed_c2f(main,c);
}

inline
void Plumed::cmd(const char*key,const void*val) {
  plumed_cmd(main,key,val);
}

inline
Plumed::~Plumed() {
  if(main.p)plumed_finalize(main);
}

#if __PLUMED_WRAPPER_GLOBAL_
inline
bool Plumed::ginitialized() {
  return plumed_ginitialized();
}

inline
bool Plumed::gvalid() {
  return plumed_gvalid();
}

inline
void Plumed::gcreate() {
  plumed_gcreate();
#if __PLUMED_WRAPPER_CXX_THROWS_
  if(!plumed_gvalid()) __PLUMED_WRAPPER_CXX_THROW_CMD_("Could not initialize the global PLUMED object. Check your PLUMED_KERNEL env var.");
#endif
}

inline
void Plumed::gcmd(const char* key,const void* val) {
  plumed_gcmd(key,val);
}

inline
void Plumed::gfinalize() {
  plumed_gfinalize();
}

inline
Plumed Plumed::global() {
  return plumed_global();
}

#endif

}

#if __PLUMED_WRAPPER_CXX_ANONYMOUS_NAMESPACE_
}
#endif

#endif

#endif

#if __PLUMED_WRAPPER_IMPLEMENTATION_
#ifndef __PLUMED_wrapper_Plumed_implementation
#define __PLUMED_wrapper_Plumed_implementation

#ifdef __PLUMED_HAS_DLOPEN
#include <dlfcn.h>
#endif

#if __PLUMED_WRAPPER_CXX_STD_
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <climits>
#else
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
  Function pointer to plumed_create
*/

typedef void*(*plumed_create_pointer)(void);
/**
  Function pointer to plumed_cmd
*/
typedef void(*plumed_cmd_pointer)(void*,const char*,const void*);

/**
  Function pointer to plumed_finalize
*/
typedef void(*plumed_finalize_pointer)(void*);

/**
   Holder for plumedmain function pointers.
*/
typedef struct {
  plumed_create_pointer create;
  plumed_cmd_pointer cmd;
  plumed_finalize_pointer finalize;
} plumed_plumedmain_function_holder;

/**
   Holder for plumed symbol table.
*/
typedef struct {
  int version;
  plumed_plumedmain_function_holder functions;
} plumed_symbol_table_type;

/**
  Historically (PLUMED<=2.4) register for plumedmain function pointers.
  As of PLUMED>=2.5, this function does not do anything except for reporting the attempt to register
  something. It always returns NULL. The function should be here anyway to allow an incomplete
  libplumedKernel (<=2.4), expecting this function to be present, to be loaded correctly.
*/
#if __PLUMED_WRAPPER_KERNEL_REGISTER_
/* Since it is only called from outside, it must be hardcoded to be extern */
extern plumed_plumedmain_function_holder* plumed_kernel_register(const plumed_plumedmain_function_holder*);
#endif

/* Utility to convert function pointers to pointers, just for the sake of printing them */
#define __PLUMED_CONVERT_FPTR(ptr,fptr) { ptr=NULL; __PLUMED_WRAPPER_STD memcpy(&ptr,&fptr,(sizeof(fptr)>sizeof(ptr)?sizeof(ptr):sizeof(fptr))); }

#define __PLUMED_GETENV __PLUMED_WRAPPER_STD getenv
#define __PLUMED_FPRINTF __PLUMED_WRAPPER_STD fprintf
#define __PLUMED_MALLOC __PLUMED_WRAPPER_STD malloc
#define __PLUMED_FREE __PLUMED_WRAPPER_STD free

#if __PLUMED_WRAPPER_KERNEL_REGISTER_
plumed_plumedmain_function_holder* plumed_kernel_register(const plumed_plumedmain_function_holder* f) {
  void* tmpptr;
  if(f) {
    if(__PLUMED_GETENV("PLUMED_LOAD_DEBUG")) {
      __PLUMED_FPRINTF(stderr,"+++ Ignoring registration at %p (",(void*)f);
      __PLUMED_CONVERT_FPTR(tmpptr,f->create);
      __PLUMED_FPRINTF(stderr,"%p,",tmpptr);
      __PLUMED_CONVERT_FPTR(tmpptr,f->cmd);
      __PLUMED_FPRINTF(stderr,"%p,",tmpptr);
      __PLUMED_CONVERT_FPTR(tmpptr,f->finalize);
      __PLUMED_FPRINTF(stderr,"%p) +++\n",tmpptr);
    }
  }
  return NULL;
}
#endif

#if defined( __PLUMED_HAS_DLOPEN)
/**
Try to dlopen a path with a given mode.
If the dlopen command fails, it tries to strip the `Kernel` part of the name.

This function is declared static (internal linkage) so that it is not visible from outside.
It is first declared then defined to make sure it is a regular C static function.
*/

static void* plumed_attempt_dlopen(const char*path,int mode);
static void* plumed_attempt_dlopen(const char*path,int mode) {
  char* pathcopy;
  void* p;
  char* pc;
  size_t strlenpath;
  pathcopy=NULL;
  p=NULL;
  pc=NULL;
  strlenpath=0;
  dlerror();
  p=dlopen(path,mode);
  if(!p) {
    /*
      Something went wrong. We try to remove "Kernel" string from the PLUMED_KERNEL variable
      and load directly the shared library. Notice that this particular path is only expected
      to be necessary when using PLUMED<=2.4 and the symbols in the main executable are
      not visible. All the other cases (either PLUMED>=2.5 or symbols in the main executable visible)
      should work correctly without entering here.
    */
    __PLUMED_FPRINTF(stderr,"+++ An error occurred. Message from dlopen(): %s +++\n",dlerror());
    strlenpath=__PLUMED_WRAPPER_STD strlen(path);
    pathcopy=(char*) __PLUMED_MALLOC(strlenpath+1);
    __PLUMED_WRAPPER_STD strncpy(pathcopy,path,strlenpath+1);
    pc=pathcopy+strlenpath-6;
    while(pc>=pathcopy && __PLUMED_WRAPPER_STD memcmp(pc,"Kernel",6)) pc--;
    if(pc>=pathcopy) {
      __PLUMED_WRAPPER_STD memmove(pc, pc+6, __PLUMED_WRAPPER_STD strlen(pc)-5);
      __PLUMED_FPRINTF(stderr,"+++ This error is expected if you are trying to load a kernel <=2.4");
      __PLUMED_FPRINTF(stderr,"+++ Trying %s +++\n",pathcopy);
      p=dlopen(pathcopy,mode);
      if(!p) __PLUMED_FPRINTF(stderr,"+++ An error occurred. Message from dlopen(): %s +++\n",dlerror());
    }
    __PLUMED_FREE(pathcopy);
  }
  return p;
}

/**
  Utility to search for a function.
  Notice that it uses tmpptr and debug. Only to be used within plumed_search_symbols
*/
#define __PLUMED_SEARCH_FUNCTION(func,name) \
  if(!func) { \
    tmpptr=dlsym(p,name); \
    if(tmpptr) { \
      *(void **)(&func)=tmpptr; \
      if(debug) __PLUMED_FPRINTF(stderr,"+++ %s found at %p +++\n",name,tmpptr); \
    } else { \
      if(debug) __PLUMED_FPRINTF(stderr,"+++ Function %s not found\n",name); \
    } \
  }

/**
Search symbolds in a dlopened library.

This function is declared static (internal linkage) so that it is not visible from outside.
It is first declared then defined to make sure it is a regular C static function.
*/
static void plumed_search_symbols(void* p, plumed_plumedmain_function_holder* f,plumed_symbol_table_type** table);
static void plumed_search_symbols(void* p, plumed_plumedmain_function_holder* f,plumed_symbol_table_type** table) {
  plumed_plumedmain_function_holder functions;
  plumed_symbol_table_type* table_ptr;
  void* tmpptr;
  char* debug;
  functions.create=NULL;
  functions.cmd=NULL;
  functions.finalize=NULL;
  table_ptr=NULL;
  tmpptr=NULL;
  /*
    Notice that as of PLUMED 2.5 we ignore self registrations.
    Pointers are searched in the form of a single pointer to a structure, which
    is the standard way in PLUMED 2.5, as well as using alternative names used in
    PLUMED 2.0 to 2.4 (e.g. plumedmain_create) and in some intermediate versions between
    PLUMED 2.4 and 2.5 (e.g. plumed_plumedmain_create). The last chance is probably
    unnecessary and might be removed at some point.
  */
  debug=__PLUMED_GETENV("PLUMED_LOAD_DEBUG");
  table_ptr=(plumed_symbol_table_type*) dlsym(p,"plumed_symbol_table");
  if(table_ptr) functions=table_ptr->functions;
  if(debug) {
    if(table_ptr) {
      __PLUMED_FPRINTF(stderr,"+++ plumed_symbol_table version %i found at %p +++\n",table_ptr->version,(void*)table_ptr);
      __PLUMED_FPRINTF(stderr,"+++ plumed_function_pointers found at %p (",(void*)&table_ptr->functions);
      __PLUMED_CONVERT_FPTR(tmpptr,functions.create);
      __PLUMED_FPRINTF(stderr,"%p,",tmpptr);
      __PLUMED_CONVERT_FPTR(tmpptr,functions.cmd);
      __PLUMED_FPRINTF(stderr,"%p,",tmpptr);
      __PLUMED_CONVERT_FPTR(tmpptr,functions.finalize);
      __PLUMED_FPRINTF(stderr,"%p) +++\n",tmpptr);
    } else {
      __PLUMED_FPRINTF(stderr,"+++ plumed_symbol_table (available in PLUMED>=2.5) not found, perhaps kernel is older +++\n");
    }
  }
  /* only searches if they were not found already */
  __PLUMED_SEARCH_FUNCTION(functions.create,"plumedmain_create");
  __PLUMED_SEARCH_FUNCTION(functions.create,"plumed_plumedmain_create");
  __PLUMED_SEARCH_FUNCTION(functions.cmd,"plumedmain_cmd");
  __PLUMED_SEARCH_FUNCTION(functions.cmd,"plumed_plumedmain_cmd");
  __PLUMED_SEARCH_FUNCTION(functions.finalize,"plumedmain_finalize");
  __PLUMED_SEARCH_FUNCTION(functions.finalize,"plumed_plumedmain_finalize");
  if(functions.create && functions.cmd && functions.finalize) {
    if(debug) __PLUMED_FPRINTF(stderr,"+++ PLUMED was loaded correctly +++\n");
    *f=functions;
    if(table) *table=table_ptr;
  } else {
    if(!functions.create) __PLUMED_FPRINTF(stderr,"+++ Pointer to (plumed_)plumedmain_create not found +++\n");
    if(!functions.cmd) __PLUMED_FPRINTF(stderr,"+++ Pointer to (plumed_)plumedmain_cmd not found +++\n");
    if(!functions.finalize) __PLUMED_FPRINTF(stderr,"+++ Pointer to (plumed_)plumedmain_finalize not found +++\n");
    f->create=NULL;
    f->cmd=NULL;
    f->finalize=NULL;
    if(table) *table=NULL;
  }
}

#endif

/*
  Returns the global pointers, either those available at link time or those
  found in the library loaded at PLUMED_KERNEL env var.
  If plumed_symbol_table_ptr is not NULL, it is used to return a pointer to the symbol table
  (if available).
  Notice that problems can be detected checking if the functions have a NULL ptr.
  On the other hand, the symbol table pointer might be NULL just because the plumed version is <=2.4.
  If handle is not NULL, it is used to return a dlopen handle that should be subsequently dlclosed.
*/
static plumed_plumedmain_function_holder plumed_retrieve_functions(plumed_symbol_table_type** plumed_symbol_table_ptr,void** handle);
static plumed_plumedmain_function_holder plumed_retrieve_functions(plumed_symbol_table_type** plumed_symbol_table_ptr,void** handle) {
#if defined(__PLUMED_STATIC_KERNEL)
  /* Real interface */
  /* These functions are defined in the plumedKernel library */
  /* They should always be extern, disregarding __PLUMED_WRAPPER_VISIBILITY */
  extern void*plumed_plumedmain_create(void);
  extern void plumed_plumedmain_cmd(void*,const char*,const void*);
  extern void plumed_plumedmain_finalize(void*);
  extern plumed_symbol_table_type plumed_symbol_table;
  /*
    When __PLUMED_STATIC_KERNEL is defined, the function holder is initialized
    to statically bound plumed_plumedmain_create, plumed_plumedmain_cmd, plumed_plumedmain_finalize and
    cannot be changed. This saves from mis-set values for PLUMED_KERNEL.
  */
  plumed_plumedmain_function_holder g= {&plumed_plumedmain_create,&plumed_plumedmain_cmd,&plumed_plumedmain_finalize};
  if(plumed_symbol_table_ptr) *plumed_symbol_table_ptr=&plumed_symbol_table;
  if(handle) *handle=NULL;
  return g;
#elif ! defined(__PLUMED_HAS_DLOPEN)
  /*
    When dlopen is not available, we hard code them to NULL
  */
  plumed_plumedmain_function_holder g= {NULL,NULL,NULL};
  if(plumed_symbol_table_ptr) *plumed_symbol_table_ptr=NULL;
  if(handle) *handle=NULL;
  return g;
#else
  /*
    On the other hand, for runtime binding, we use dlsym to find the relevant functions.
  */
  plumed_plumedmain_function_holder g;
  /* search is done once and only once */
  const char* path;
  void* p;
  char* debug;
  int dlopenmode;
  g.create=NULL;
  g.cmd=NULL;
  g.finalize=NULL;
  path=__PLUMED_GETENV("PLUMED_KERNEL");
  p=NULL;
  debug=__PLUMED_GETENV("PLUMED_LOAD_DEBUG");
  dlopenmode=0;
  if(plumed_symbol_table_ptr) *plumed_symbol_table_ptr=NULL;
  if(handle) *handle=NULL;
#ifdef __PLUMED_DEFAULT_KERNEL
  /*
    This variable allows a default path for the kernel to be hardcoded.
    Can be useful for hardcoding the predefined plumed location
    still allowing the user to override this choice setting PLUMED_KERNEL.
    The path should be chosen at compile time adding e.g.
    -D__PLUMED_DEFAULT_KERNEL=/opt/local/lib/libplumed.dylib
  */
  /* This is required to add quotes */
#define PLUMED_QUOTE_DIRECT(name) #name
#define PLUMED_QUOTE(macro) PLUMED_QUOTE_DIRECT(macro)
  if(! (path && (*path) )) path=PLUMED_QUOTE(__PLUMED_DEFAULT_KERNEL);
#endif
  if(path && (*path)) {
    fprintf(stderr,"+++ Loading the PLUMED kernel runtime +++\n");
    fprintf(stderr,"+++ PLUMED_KERNEL=\"%s\" +++\n",path);
    if(__PLUMED_GETENV("PLUMED_LOAD_NAMESPACE") && !__PLUMED_WRAPPER_STD strcmp(__PLUMED_GETENV("PLUMED_LOAD_NAMESPACE"),"LOCAL")) {
      dlopenmode=RTLD_NOW|RTLD_LOCAL;
      if(debug) __PLUMED_FPRINTF(stderr,"+++ Loading with mode RTLD_NOW|RTLD_LOCAL +++\n");
    } else {
      dlopenmode=RTLD_NOW|RTLD_GLOBAL;
      if(debug) __PLUMED_FPRINTF(stderr,"+++ Loading with mode RTLD_NOW|RTLD_GLOBAL +++\n");
    }
#ifdef RTLD_DEEPBIND
    if(__PLUMED_GETENV("PLUMED_LOAD_DEEPBIND")) {
      dlopenmode=dlopenmode|RTLD_DEEPBIND;
      if(debug) __PLUMED_FPRINTF(stderr,"+++ Loading with mode RTLD_DEEPBIND +++\n");
    }
#endif
    p=plumed_attempt_dlopen(path,dlopenmode);
    if(p) plumed_search_symbols(p,&g,plumed_symbol_table_ptr);
  }
  if(handle) *handle=p;
  return g;
#endif
}

/**
  Implementation.
  Small object used to store pointers directly into the plumed object defined in Plumed.h.
  This allows avoiding the extra function call to plumed_retrieve_functions at every cmd,
  at the cost of an extra indirection.
*/
typedef struct {
  int refcount;
  void* dlhandle;
  int nodlclose;
  plumed_plumedmain_function_holder functions;
  plumed_symbol_table_type* table;
  void* p;
} plumed_implementation;

static plumed_implementation* plumed_malloc_pimpl();

static plumed_implementation* plumed_malloc_pimpl() {
  plumed_implementation* pimpl;
  /* allocate space for implementation object. this is free-ed in plumed_finalize(). */
  pimpl=(plumed_implementation*) __PLUMED_MALLOC(sizeof(plumed_implementation));
  if(!pimpl) {
    __PLUMED_FPRINTF(stderr,"+++ Allocation error +++\n");
    __PLUMED_WRAPPER_STD exit(1);
  }
  pimpl->refcount=1;
  pimpl->dlhandle=NULL;
  pimpl->nodlclose=0;
  pimpl->functions.create=NULL;
  pimpl->functions.cmd=NULL;
  pimpl->functions.finalize=NULL;
  pimpl->table=NULL;
  pimpl->p=NULL;
  return pimpl;
}

/* C wrappers: */

plumed plumed_create(void) {
  /* returned object */
  plumed p;
  /* pointer to implementation */
  plumed_implementation* pimpl;
  /* allocate space for implementation object. this is free-ed in plumed_finalize(). */
  pimpl=plumed_malloc_pimpl();
  /* store pointers in pimpl */
  pimpl->functions=plumed_retrieve_functions(&pimpl->table,&pimpl->dlhandle);
  /* note if handle should not be dlclosed */
  /* Notice that PLUMED_LOAD_NODLCLOSE only affects the kernel linked from PLUMED_KERNEL
     and is not used in plumed_create_dlopen() */
  pimpl->nodlclose=__PLUMED_GETENV("PLUMED_LOAD_NODLCLOSE")!=NULL;
  /* in case of failure, return */
  /* the resulting object should be plumed_finalized, though you cannot use plumed_cmd */
  if(!pimpl->functions.create) {
    /* store pimpl in returned object */
    p.p=pimpl;
    return p;
  }
  assert(pimpl->functions.cmd);
  assert(pimpl->functions.finalize);
  /* obtain object */
  pimpl->p=(*(pimpl->functions.create))();
  assert(pimpl->p);
  /* store pimpl in returned object */
  p.p=pimpl;
  return p;
}

plumed plumed_create_dlopen(const char*path) {
  /* returned object */
  plumed p;
  /* pointer to implementation */
  plumed_implementation* pimpl;
  int dlopenmode;
  /* allocate space for implementation object. this is free-ed in plumed_finalize(). */
  pimpl=plumed_malloc_pimpl();
#ifdef __PLUMED_HAS_DLOPEN
  dlopenmode=RTLD_NOW|RTLD_LOCAL;
#ifdef RTLD_DEEPBIND
  dlopenmode=dlopenmode|RTLD_DEEPBIND;
#endif
  if(path) pimpl->dlhandle=plumed_attempt_dlopen(path,dlopenmode);
  if(pimpl->dlhandle) plumed_search_symbols(pimpl->dlhandle,&pimpl->functions,&pimpl->table);
#endif
  if(!pimpl->functions.create) {
    p.p=pimpl;
    return p;
  }
  assert(pimpl->functions.cmd);
  assert(pimpl->functions.finalize);
  /* obtain object */
  pimpl->p=(*(pimpl->functions.create))();
  assert(pimpl->p);
  /* store pimpl in returned object */
  p.p=pimpl;
  return p;
}

plumed plumed_create_reference(plumed p) {
  plumed_implementation* pimpl;
  /* obtain pimpl */
  pimpl=(plumed_implementation*) p.p;
  assert(pimpl);
  /* increase reference count */
  pimpl->refcount++;
  return p;
}

plumed plumed_create_invalid() {
  plumed p;
  plumed_implementation* pimpl;
  pimpl=plumed_malloc_pimpl();
  assert(pimpl);
  p.p=pimpl;
  return p;
}


void plumed_cmd(plumed p,const char*key,const void*val) {
  plumed_implementation* pimpl;
  /* obtain pimpl */
  pimpl=(plumed_implementation*) p.p;
  assert(pimpl);
  if(!pimpl->p) {
    __PLUMED_FPRINTF(stderr,"+++ ERROR: you are trying to use plumed, but it is not available +++\n");
    __PLUMED_FPRINTF(stderr,"+++ Check your PLUMED_KERNEL environment variable +++\n");
    __PLUMED_WRAPPER_STD exit(1);
  }
  assert(pimpl->functions.create);
  assert(pimpl->functions.cmd);
  assert(pimpl->functions.finalize);
  /* execute */
  (*(pimpl->functions.cmd))(pimpl->p,key,val);
}

void plumed_finalize(plumed p) {
  plumed_implementation* pimpl;
  /* obtain pimpl */
  pimpl=(plumed_implementation*) p.p;
  assert(pimpl);
  /* decrease reference count */
  pimpl->refcount--;
  if(pimpl->refcount>0) return;
  /* to allow finalizing an invalid plumed object, we only call
     finalize if the object is valid */
  if(pimpl->p) {
    assert(pimpl->functions.create);
    assert(pimpl->functions.cmd);
    assert(pimpl->functions.finalize);
    /* finalize */
    (*(pimpl->functions.finalize))(pimpl->p);
  }
#ifdef __PLUMED_HAS_DLOPEN
  /* dlclose library */
  if(pimpl->dlhandle && !pimpl->nodlclose) dlclose(pimpl->dlhandle);
#endif
  /* free pimpl space */
  __PLUMED_FREE(pimpl);
  /* reset to null */
  p.p=NULL;
}

int plumed_valid(plumed p) {
  plumed_implementation* pimpl;
  /* obtain pimpl */
  pimpl=(plumed_implementation*) p.p;
  assert(pimpl);
  if(pimpl->p) return 1;
  else return 0;
}

int plumed_use_count(plumed p) {
  plumed_implementation* pimpl;
  /* obtain pimpl */
  pimpl=(plumed_implementation*) p.p;
  assert(pimpl);
  return pimpl->refcount;
}

int plumed_installed(void) {
  plumed p;
  int result;
  p=plumed_create();
  result=plumed_valid(p);
  plumed_finalize(p);
  return result;
}

#if __PLUMED_WRAPPER_GLOBAL_

/* we declare a Plumed_g_main object here, in such a way that it is always available */

static plumed plumed_gmain= {NULL};

plumed plumed_global(void) {
  return plumed_gmain;
}

void plumed_gcreate(void) {
  /* should be created once */
  assert(plumed_gmain.p==NULL);
  plumed_gmain=plumed_create();
}

void plumed_gcmd(const char*key,const void*val) {
  plumed_cmd(plumed_gmain,key,val);
}

void plumed_gfinalize(void) {
  plumed_finalize(plumed_gmain);
  plumed_gmain.p=NULL;
}

int plumed_ginitialized(void) {
  if(plumed_gmain.p) return 1;
  else        return 0;
}

int plumed_gvalid() {
  assert(plumed_gmain.p);
  return plumed_valid(plumed_gmain);
}

#endif

void plumed_c2f(plumed p,char*c) {
  unsigned i;
  unsigned char* cc;
  /*
    Convert the address stored in p.p into a proper FORTRAN string
    made of only ASCII characters. For this to work, the two following
    assertions should be satisfied:
  */
  assert(CHAR_BIT<=12);
  assert(sizeof(p.p)<=16);

  assert(c);
  cc=(unsigned char*)&p.p;
  for(i=0; i<sizeof(p.p); i++) {
    /*
      characters will range between '0' (ASCII 48) and 'o' (ASCII 111=48+63)
    */
    c[2*i]=cc[i]/64+48;
    c[2*i+1]=cc[i]%64+48;
  }
  for(; i<16; i++) {
    c[2*i]=' ';
    c[2*i+1]=' ';
  }
}

plumed plumed_f2c(const char*c) {
  plumed p;
  unsigned i;
  unsigned char* cc;

  assert(CHAR_BIT<=12);
  assert(sizeof(p.p)<=16);

  assert(c);
  cc=(unsigned char*)&p.p;
  for(i=0; i<sizeof(p.p); i++) {
    /*
      perform the reversed transform
    */
    cc[i]=(c[2*i]-48)*64 + (c[2*i+1]-48);
  }
  for(; i<16; i++) {
    assert(c[2*i]==' ');
    assert(c[2*i+1]==' ');
  }
  return p;
}


#if __PLUMED_WRAPPER_FORTRAN_

/*
  Fortran wrappers
  These are just like the global C wrappers. They are
  just defined here and not declared since they
  should not be used from c/c++ anyway.

  We use a macro that does the following:
  - declare a static function named NAME_static
  - declare a number of functions named NAME_ etc, with all possible
    fortran mangling schemes (zero, one, or two underscores, lower and upper case)
  - define the NAME_static function.

  The static function is used basically as an inline function in a C-compatible manner.
*/

#define __PLUMED_IMPLEMENT_FORTRAN(lower,upper,arg1,arg2) \
  static void lower ## _static arg1; \
  extern void lower      arg1 {lower ## _static arg2;} \
  extern void lower ##_  arg1 {lower ## _static arg2;} \
  extern void lower ##__ arg1 {lower ## _static arg2;} \
  extern void upper      arg1 {lower ## _static arg2;} \
  extern void upper ##_  arg1 {lower ## _static arg2;} \
  extern void upper ##__ arg1 {lower ## _static arg2;} \
  static void lower ## _static arg1

__PLUMED_IMPLEMENT_FORTRAN(plumed_f_create,PLUMED_F_CREATE,(char*c),(c)) {
  plumed p;
  p=plumed_create();
  plumed_c2f(p,c);
}

__PLUMED_IMPLEMENT_FORTRAN(plumed_f_create_dlopen,PLUMED_F_CREATE_DLOPEN,(char*c,char*path),(c,path)) {
  plumed p;
  p=plumed_create_dlopen(path);
  plumed_c2f(p,c);
}

__PLUMED_IMPLEMENT_FORTRAN(plumed_f_create_reference,PLUMED_F_CREATE_REFERENCE,(char* c,char*r),(c,r)) {
  plumed p,q;
  p=plumed_f2c(r);
  q=plumed_create_reference(p);
  plumed_c2f(q,c);
}

__PLUMED_IMPLEMENT_FORTRAN(plumed_f_create_invalid,PLUMED_F_CREATE_INVALID,(char* c),(c)) {
  plumed p;
  p=plumed_create_invalid();
  plumed_c2f(p,c);
}

__PLUMED_IMPLEMENT_FORTRAN(plumed_f_cmd,PLUMED_F_CMD,(char*c,char*key,void*val),(c,key,val)) {
  plumed p;
  p=plumed_f2c(c);
  plumed_cmd(p,key,val);
}

__PLUMED_IMPLEMENT_FORTRAN(plumed_f_finalize,PLUMED_F_FINALIZE,(char*c),(c)) {
  plumed p;
  p=plumed_f2c(c);
  plumed_finalize(p);
}

__PLUMED_IMPLEMENT_FORTRAN(plumed_f_installed,PLUMED_F_INSTALLED,(int*i),(i)) {
  assert(i);
  *i=plumed_installed();
}

/* New in PLUMED 2.5 */
__PLUMED_IMPLEMENT_FORTRAN(plumed_f_valid,PLUMED_F_VALID,(char*c,int*i),(c,i)) {
  plumed p;
  assert(i);
  p=plumed_f2c(c);
  *i=plumed_valid(p);
}

__PLUMED_IMPLEMENT_FORTRAN(plumed_f_use_count,PLUMED_F_USE_COUNT,(char*c,int*i),(c,i)) {
  plumed p;
  assert(i);
  p=plumed_f2c(c);
  *i=plumed_use_count(p);
}

#if __PLUMED_WRAPPER_GLOBAL_

__PLUMED_IMPLEMENT_FORTRAN(plumed_f_global,PLUMED_F_GLOBAL,(char*c),(c)) {
  plumed_c2f(plumed_gmain,c);
}

__PLUMED_IMPLEMENT_FORTRAN(plumed_f_ginitialized,PLUMED_F_GINITIALIZED,(int*i),(i)) {
  assert(i);
  *i=plumed_ginitialized();
}

__PLUMED_IMPLEMENT_FORTRAN(plumed_f_gcreate,PLUMED_F_GCREATE,(void),()) {
  plumed_gcreate();
}

__PLUMED_IMPLEMENT_FORTRAN(plumed_f_gcmd,PLUMED_F_GCMD,(char*key,void*val),(key,val)) {
  plumed_gcmd(key,val);
}

__PLUMED_IMPLEMENT_FORTRAN(plumed_f_gfinalize,PLUMED_F_GFINALIZE,(void),()) {
  plumed_gfinalize();
}

/* New in PLUMED 2.5 */
__PLUMED_IMPLEMENT_FORTRAN(plumed_f_gvalid,PLUMED_F_GVALID,(int*i),(i)) {
  assert(i);
  *i=plumed_gvalid();
}
#endif

#endif /* __PLUMED_WRAPPER_FORTRAN_ */

#ifdef __cplusplus
}
#endif

#endif

#endif

#undef __PLUMED_WRAPPER_CXX_
#undef __PLUMED_WRAPPER_CXX_THROWS_
#undef __PLUMED_WRAPPER_CXX_THROW_CMD_
#undef __PLUMED_WRAPPER_CXX_STD_
#undef __PLUMED_WRAPPER_CXX_INLINE_
#undef __PLUMED_WRAPPER_CXX_ANONYMOUS_NAMESPACE_
#undef __PLUMED_WRAPPER_CXX_POLYMORPHIC_
#undef __PLUMED_WRAPPER_EXTERN_
#undef __PLUMED_WRAPPER_KERNEL_REGISTER_
#undef __PLUMED_WRAPPER_FORTRAN_
#undef __PLUMED_WRAPPER_GLOBAL_
#undef __PLUMED_WRAPPER_IMPLEMENTATION_

