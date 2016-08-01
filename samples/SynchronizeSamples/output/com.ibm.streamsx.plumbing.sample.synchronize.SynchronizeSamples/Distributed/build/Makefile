# NOTE: This makefile is designed to be run from one level up in the directory
# hierarchy compared to where it resides. For instance, if this makefile is
# located at 'output/build/Makefile', then it can be launched as:
# 'make -f build/Makefile' from the 'output' directory.

SHELL=/bin/bash
ifeq ($(CXX),)
  CXX=g++
endif
PKGCONFIG := /home/streamsdev/InfoSphere_Streams/4.1.1.0/bin/dst-pe-pkg-config.sh
SPL_BUNDLE_BUILDER := /home/streamsdev/InfoSphere_Streams/4.1.1.0/system/impl/bin/spl-bundle-builder
PE_INCLUDE := $(shell $(PKGCONFIG) --cflags dst-spl-pe-install)
PE_LIB := $(shell $(PKGCONFIG) --libs dst-spl-pe-install)
PE_STAND_LIB := $(shell $(PKGCONFIG) --libs dst-spl-pe-install-standalone)
SPL_CXXFLAGS = -Wall -Wno-unused -Wno-sign-compare
SPL_CXXFLAGS += -D_REENTRANT -fPIC -finline-functions -fmessage-length=0
SPL_CXXFLAGS += $(PE_INCLUDE) -O3 -DNDEBUG  -std=gnu++98 
SPL_LDFLAGS = $(PE_LIB)

SPL_TYPES = 
SPL_FUNCTIONS = 
SPL_OPERATORS = 
SPL_PE_OBJS = 
SPL_PE_BINS = 

SPL_ADL_FILE = com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeSamples.adl

SPL_OUTPUT_DIR_ROOT = $(shell printf '%q' '/home/streamsdev/git/streamsx.plumbing/samples/SynchronizeSamples/output/com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeSamples')
SPL_OUTPUT_DIR = $(shell printf '%q' 'Distributed')

.PHONY: distclean clean all types functions operators pes svar bundle toolkits standalone sablink

all: bin types functions operators pes svar standalone bundle sablink

distclean clean:
	@rm -fr bin/* build/type build/function build/operator build/pe build/svar build/bundle build/standalone com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeSamples.sab

bin:
	@mkdir -m 775 bin

types: $(SPL_TYPES)

build/type:
	-@mkdir -m 775 build/type

operators: $(SPL_OPERATORS)

functions: $(SPL_FUNCTIONS)

pes: $(SPL_PE_BINS)

build/pe:
	-@mkdir -m 775 build/pe

standalone: 
	@rm -f bin/standalone.exe
	@rm -f bin/com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeSamples
	@rm -f bin/sab
	@rm -f bin/standalone

sablink:

	@rm -f bin/sab

bundle: com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeSamples.sab

-include /home/streamsdev/git/streamsx.plumbing/samples/SynchronizeSamples/output/com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeSamples/Distributed/build/dep/com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeSamples.sab.d
com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeSamples.sab: $(SPL_PE_BINS) $(SPL_ADL_FILE)
	@echo ' [Bundle] com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeSamples.sab'
	@$(SPL_BUNDLE_BUILDER) $(SPL_OUTPUT_DIR_ROOT) $(SPL_OUTPUT_DIR) $(SPL_ADL_FILE) com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeSamples.sab false

