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

SPL_TYPES = build/type/BeJwrMXIzKcnMTS02zUlMSs0BACoHAV4.o \
            build/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.o 
SPL_FUNCTIONS = 
SPL_OPERATORS = build/operator/EvenStream.o \
                build/operator/SynchronizedEvenStream.o \
                build/operator/SynchronizedSink.o 
SPL_PE_OBJS = build/pe/BeJwzNHAtS80LLilKTcyNNzIKrsxLzijKz8usSk1BkjA0Q5YIzszLjgcAaLwVDT.o 
SPL_PE_BINS = bin/com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeTwoStreams-a.dpe 

SPL_ADL_FILE = com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeTwoStreams.adl

SPL_OUTPUT_DIR_ROOT = $(shell printf '%q' '/home/streamsdev/git/streamsx.plumbing/samples/SynchronizeSamples/output/com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeTwoStreams')
SPL_OUTPUT_DIR = $(shell printf '%q' 'Standalone1')

.PHONY: distclean clean all types functions operators pes svar bundle toolkits standalone sablink

all: bin types functions operators pes svar standalone bundle sablink

distclean clean:
	@rm -fr bin/* build/type build/function build/operator build/pe build/svar build/bundle build/standalone com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeTwoStreams.sab

bin:
	@mkdir -m 775 bin

types: $(SPL_TYPES)

build/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.o: \
	    src/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.h \
	    src/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.cpp \
	    build/cppOptions \
	    | build/type
	@echo ' [CXX-type] enum{csv,txt,bin,block,line}'
	@$(CXX) -o $@ -c $(SPL_CXXFLAGS) src/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.cpp

build/type/BeJwrMXIzKcnMTS02zUlMSs0BACoHAV4.o: \
	    src/type/BeJwrMXIzKcnMTS02zUlMSs0BACoHAV4.h \
	    src/type/BeJwrMXIzKcnMTS02zUlMSs0BACoHAV4.cpp \
	    build/cppOptions \
	    | build/type
	@echo ' [CXX-type] tuple<float64 time,rstring label>'
	@$(CXX) -o $@ -c $(SPL_CXXFLAGS) src/type/BeJwrMXIzKcnMTS02zUlMSs0BACoHAV4.cpp

build/type:
	-@mkdir -m 775 build/type

operators: $(SPL_OPERATORS)

-include build/operator/EvenStream.d
build/operator/EvenStream.o: \
	    src/operator/EvenStream.h \
	    src/operator/EvenStream.cpp\
	    build/dep/operator/EvenStream.dep \
	    src/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.h \
	    src/type/BeJwrMXIzKcnMTS02zUlMSs0BACoHAV4.h  \
	    build/cppOptions \
	    | build/operator
	@echo ' [CXX-operator] EvenStream'
	@$(CXX) -o $@ -MD -I /home/streamsdev/InfoSphere_Streams/4.1.1.0/toolkits/spl/impl/nl/include -I /home/streamsdev/InfoSphere_Streams/4.1.1.0/toolkits/spl/impl/include -DSPLJAVAFUNCTION_ADL_FILENAME=\"com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeTwoStreams.adl\" -c $(SPL_CXXFLAGS) src/operator/EvenStream.cpp

-include build/operator/SynchronizedEvenStream.d
build/operator/SynchronizedEvenStream.o: \
	    src/operator/SynchronizedEvenStream.h \
	    src/operator/SynchronizedEvenStream.cpp\
	    build/dep/operator/SynchronizedEvenStream.dep  \
	    build/cppOptions \
	    | build/operator
	@echo ' [CXX-operator] SynchronizedEvenStream'
	@$(CXX) -o $@ -MD -I /home/streamsdev/git/streamsx.plumbing/com.ibm.streamsx.plumbing/impl/nl/include -DSPLJAVAFUNCTION_ADL_FILENAME=\"com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeTwoStreams.adl\" -c $(SPL_CXXFLAGS) src/operator/SynchronizedEvenStream.cpp

-include build/operator/SynchronizedSink.d
build/operator/SynchronizedSink.o: \
	    src/operator/SynchronizedSink.h \
	    src/operator/SynchronizedSink.cpp\
	    build/dep/operator/SynchronizedSink.dep \
	    src/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.h \
	    src/type/BeJwrMXIzKcnMTS02zUlMSs0BACoHAV4.h  \
	    build/cppOptions \
	    | build/operator
	@echo ' [CXX-operator] SynchronizedSink'
	@$(CXX) -o $@ -MD -I /home/streamsdev/InfoSphere_Streams/4.1.1.0/toolkits/spl/impl/nl/include -I /home/streamsdev/InfoSphere_Streams/4.1.1.0/toolkits/spl/impl/include -DSPLJAVAFUNCTION_ADL_FILENAME=\"com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeTwoStreams.adl\" -c $(SPL_CXXFLAGS) src/operator/SynchronizedSink.cpp

build/operator:
	-@mkdir -m 775 -p build/operator

functions: $(SPL_FUNCTIONS)

pes: $(SPL_PE_BINS)

build/pe/BeJwzNHAtS80LLilKTcyNNzIKrsxLzijKz8usSk1BkjA0Q5YIzszLjgcAaLwVDT.o: \
	    src/pe/BeJwzNHAtS80LLilKTcyNNzIKrsxLzijKz8usSk1BkjA0Q5YIzszLjgcAaLwVDT.h \
	    src/pe/BeJwzNHAtS80LLilKTcyNNzIKrsxLzijKz8usSk1BkjA0Q5YIzszLjgcAaLwVDT.cpp  \
	    build/cppOptions \
	    | build/pe
	@echo ' [CXX-pe] pe com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeTwoStreams-a'
	@$(CXX) -o $@ -c $(SPL_CXXFLAGS) src/pe/BeJwzNHAtS80LLilKTcyNNzIKrsxLzijKz8usSk1BkjA0Q5YIzszLjgcAaLwVDT.cpp

PEcom.ibm.streamsx.plumbing.sample.synchronize.SynchronizeTwoStreams-a = \
	    build/pe/BeJwzNHAtS80LLilKTcyNNzIKrsxLzijKz8usSk1BkjA0Q5YIzszLjgcAaLwVDT.o \
	    build/operator/EvenStream.o \
	    build/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.o \
	    build/type/BeJwrMXIzKcnMTS02zUlMSs0BACoHAV4.o \
	    build/operator/SynchronizedEvenStream.o \
	    build/operator/SynchronizedSink.o 

bin/com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeTwoStreams-a.dpe: \
	$(PEcom.ibm.streamsx.plumbing.sample.synchronize.SynchronizeTwoStreams-a) \
	build/dep/com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeTwoStreams-a.dep \
	build/ldOptions
	@echo ' [LD-pe] pe com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeTwoStreams-a'
	@$(CXX) $(SPL_CXXFLAGS) -o bin/com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeTwoStreams-a.dpe -fPIC -shared $(PEcom.ibm.streamsx.plumbing.sample.synchronize.SynchronizeTwoStreams-a) -lstreams-stdtk-runtime -lstreams_boost_iostreams -lstreams_boost_filesystem -lstreams_boost_system -lstreams-stdtk-runtime -lstreams_boost_iostreams -lstreams_boost_filesystem -lstreams_boost_system $(SPL_LDFLAGS)

build/pe:
	-@mkdir -m 775 build/pe

standalone: bin/standalone.exe

build/standalone/standalone.o: \
	    src/standalone/standalone.h \
	    src/standalone/standalone.cpp  \
	    build/cppOptions \
	    | build/standalone
	@echo ' [CXX-standalone] standalone'
	@$(CXX) -o $@ -c $(SPL_CXXFLAGS) src/standalone/standalone.cpp

bin/standalone.exe: build/standalone/standalone.o build/ldOptions
	@echo ' [LD-standalone] standalone'
	@$(CXX) $(SPL_CXXFLAGS) -o bin/standalone.exe build/standalone/standalone.o $(PE_STAND_LIB)
	@echo ' [LN-standalone] standalone '
	@ln -sf standalone bin/com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeTwoStreams
build/standalone:
	-@mkdir -m 775 build/standalone

sablink:

	@ln -sf ../com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeTwoStreams.sab bin/sab

bundle: com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeTwoStreams.sab

-include /home/streamsdev/git/streamsx.plumbing/samples/SynchronizeSamples/output/com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeTwoStreams/Standalone1/build/dep/com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeTwoStreams.sab.d
com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeTwoStreams.sab: $(SPL_PE_BINS) $(SPL_ADL_FILE) bin/standalone.exe
	@echo ' [Bundle] com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeTwoStreams.sab'
	@$(SPL_BUNDLE_BUILDER) $(SPL_OUTPUT_DIR_ROOT) $(SPL_OUTPUT_DIR) $(SPL_ADL_FILE) com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeTwoStreams.sab true

