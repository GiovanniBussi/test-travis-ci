# include the machine dependent configuration
ifneq ($(MAKECMDGOALS),clean)
  -include ../Makefile.conf
endif

.PHONY: all clean install

plumed_compiled := $(wildcard ../src/lib/plumed)

ifeq ($(strip $(plumed_compiled)),)

all:
	@echo You must compile plumed before building the cython interface

else

ifdef python_bin

unexport CXX
unexport CC
unexport CFLAGS
unexport CXXFLAGS

all:
	@echo Building python interface for PLUMED 
	plumed_program_name=plumed \
          plumed_include_dir=../src/wrapper \
          plumed_default_kernel="$$PWD/../src/lib/libplumedKernel.$(SOEXT)" \
          $(python_bin) setup.py build_ext -i

else

all:
	@echo Python support was not configure
endif

endif

pip:
	cp ../src/wrapper/Plumed.h .
	cp ../VERSION .

clean:
	rm -fr *.so plumed.cpp build Plumed.h VERSION
