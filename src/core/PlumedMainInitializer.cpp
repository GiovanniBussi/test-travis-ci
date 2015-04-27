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
#include "PlumedMain.h"
#include "tools/Exception.h"
#include <cstdlib>
#if defined __PLUMED_HAS_DLOPEN
#include <dlfcn.h>
#endif

using namespace std;

// !!!!!!!!!!!!!!!!!!!!!!    DANGER   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11
// THE FOLLOWING ARE UTILITIES WHICH ARE NECESSARY FOR DYNAMIC LOADING OF THE PLUMED KERNEL:
// This section should be consistent with the Plumed.h file.
// Since the Plumed.h file may be included in host MD codes, **NEVER** MODIFY THE CODE IN THIS FILE
// unless you know exactly what you are doing

/**
  Container for plumedmain function pointers (create, cmd and finalize).
*/
typedef struct {
  void*(*create)();
  void(*cmd)(void*,const char*,const void*);
  void(*finalize)(void*);
} plumed_plumedmain_function_holder;

/* These functions should be accessible from C, since they might be statically
   used from Plumed.c (for static binding) */

extern "C" void*plumed_plumedmain_create() {
  return new PLMD::PlumedMain;
}

extern "C" void plumed_plumedmain_cmd(void*plumed,const char*key,const void*val) {
  plumed_massert(plumed,"trying to use a plumed object which is not initialized");
  static_cast<PLMD::PlumedMain*>(plumed)->cmd(key,val);
}

extern "C" void plumed_plumedmain_finalize(void*plumed) {
  plumed_massert(plumed,"trying to deallocate a plumed object which is not initialized");
// I think it is not possible to replace this delete with a smart pointer
// since the ownership of this pointer is in a C structure. GB
  delete static_cast<PLMD::PlumedMain*>(plumed);
}

/// This is a static pointer that is searched by the plumed loader, so it should be here.
extern "C" plumed_plumedmain_function_holder plumed_function_pointers = { plumed_plumedmain_create,plumed_plumedmain_cmd,plumed_plumedmain_finalize };

namespace PLMD {

/// Static object which registers Plumed.
/// This is a static object which, during its construction at startup,
/// registers the pointers to plumed_plumedmain_create, plumed_plumedmain_cmd and plumed_plumedmain_finalize
/// to the plumed_kernel_register function.
/// Registration is only required with plumed loader <=2.4, but we do it anyway in order to maintain
/// backward compatibility. Notice that as of plumed 2.5 the plumed_kernel_register is found
/// using dlsym, in order to allow the libplumedKernel library to be loadable also when
/// the plumed_kernel_register symbol is not available.
static class PlumedMainInitializer {
public:
  PlumedMainInitializer() {
#if defined(__PLUMED_HAS_DLOPEN)
    bool debug=std::getenv("PLUMED_LOAD_DEBUG");
    void* handle=dlopen(NULL,RTLD_GLOBAL);
    if(debug) fprintf(stderr,"+++ Registering functions. dlopen handle at %p +++\n",handle);
    typedef plumed_plumedmain_function_holder* (*plumed_kernel_register_type)(const plumed_plumedmain_function_holder*);
    void* func=dlsym(handle,"plumed_kernel_register");
    if(debug) {
      if(func) {
        fprintf(stderr,"+++ plumed_kernel_register found at %p +++\n",func);
      }
      else fprintf(stderr,"+++ plumed_kernel_register not found +++\n");
    }
    plumed_kernel_register_type plumed_kernel_register=(plumed_kernel_register_type)func;
    dlclose(handle);
    plumed_plumedmain_function_holder fh= {plumed_plumedmain_create,plumed_plumedmain_cmd,plumed_plumedmain_finalize};
    if(debug) fprintf(stderr,"+++ Registering functions at %p (%p,%p,%p) +++\n",(void*)&fh,(void*)fh.create,(void*)fh.cmd,(void*)fh.finalize);
    if(plumed_kernel_register) (*plumed_kernel_register)(&fh);
#endif
  }
} RegisterMe;

}


