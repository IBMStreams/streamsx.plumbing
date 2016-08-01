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

SPL_TYPES = build/type/BeJyrNIo3NArPzEvJL_1dNLMpOLTI0dMvMS8yBcACkegr2.o \
            build/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.o \
            build/type/BeJwlyUEKgDAMBMA3FWzRu_0QfwQYMaFKS7cHfi3idQctSfWJM7BpywOPJsvxCeonxLbmpdTGoW7ZxBqdQTXCA1j6Dv3gBIi4cDB.o \
            build/type/BeJyrNIo3S0pNyy9KNU1MK0ktAgAw9gX7.o 
SPL_FUNCTIONS = build/function/com/ibm/streamsx/plumbing/sample/synchronize/SecondsToTimestamp.o 
SPL_OPERATORS = build/operator/Speech1Stream.o \
                build/operator/PunctuatedSpeech1Stream.o \
                build/operator/IndentedPunctuatedSpeech1Stream.o \
                build/operator/SynchronizedSpeech1Stream.o \
                build/operator/Transcript.o 
SPL_PE_OBJS = build/pe/BeJwzNvTMS0nNK0lNCSjNSy4pTQSyggtSU5MzDINLilITc_0ONjHHJGBqjqTQNrsxLzijKz8uswlBrEFKUmFecXJRZUBIPACSzCw0.o 
SPL_PE_BINS = bin/com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeThreeStreams-a.dpe 

SPL_ADL_FILE = com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeThreeStreams.adl

SPL_OUTPUT_DIR_ROOT = $(shell printf '%q' '/home/streamsdev/git/streamsx.plumbing/samples/SynchronizeSamples/output/com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeThreeStreams')
SPL_OUTPUT_DIR = $(shell printf '%q' 'Standalone2')

.PHONY: distclean clean all types functions operators pes svar bundle toolkits standalone sablink

all: bin types functions operators pes svar standalone bundle sablink

distclean clean:
	@rm -fr bin/* build/type build/function build/operator build/pe build/svar build/bundle build/standalone com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeThreeStreams.sab

bin:
	@mkdir -m 775 bin

types: $(SPL_TYPES)

build/type/BeJyrNIo3NArPzEvJL_1dNLMpOLTI0dMvMS8yBcACkegr2.o: \
	    src/type/BeJyrNIo3NArPzEvJL_1dNLMpOLTI0dMvMS8yBcACkegr2.h \
	    src/type/BeJyrNIo3NArPzEvJL_1dNLMpOLTI0dMvMS8yBcACkegr2.cpp \
	    build/cppOptions \
	    | build/type
	@echo ' [CXX-type] enum{WindowMarker,FinalMarker}'
	@$(CXX) -o $@ -c $(SPL_CXXFLAGS) src/type/BeJyrNIo3NArPzEvJL_1dNLMpOLTI0dMvMS8yBcACkegr2.cpp

build/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.o: \
	    src/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.h \
	    src/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.cpp \
	    build/cppOptions \
	    | build/type
	@echo ' [CXX-type] enum{csv,txt,bin,block,line}'
	@$(CXX) -o $@ -c $(SPL_CXXFLAGS) src/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.cpp

build/type/BeJyrNIo3S0pNyy9KNU1MK0ktAgAw9gX7.o: \
	    src/type/BeJyrNIo3S0pNyy9KNU1MK0ktAgAw9gX7.h \
	    src/type/BeJyrNIo3S0pNyy9KNU1MK0ktAgAw9gX7.cpp \
	    build/cppOptions \
	    | build/type
	@echo ' [CXX-type] enum{before,after}'
	@$(CXX) -o $@ -c $(SPL_CXXFLAGS) src/type/BeJyrNIo3S0pNyy9KNU1MK0ktAgAw9gX7.cpp

build/type/BeJwlyUEKgDAMBMA3FWzRu_0QfwQYMaFKS7cHfi3idQctSfWJM7BpywOPJsvxCeonxLbmpdTGoW7ZxBqdQTXCA1j6Dv3gBIi4cDB.o: \
	    src/type/BeJwlyUEKgDAMBMA3FWzRu_0QfwQYMaFKS7cHfi3idQctSfWJM7BpywOPJsvxCeonxLbmpdTGoW7ZxBqdQTXCA1j6Dv3gBIi4cDB.h \
	    src/type/BeJwlyUEKgDAMBMA3FWzRu_0QfwQYMaFKS7cHfi3idQctSfWJM7BpywOPJsvxCeonxLbmpdTGoW7ZxBqdQTXCA1j6Dv3gBIi4cDB.cpp \
	    build/cppOptions \
	    | build/type
	@echo ' [CXX-type] tuple<rstring outputDirectory,rstring outputFilename,rstr...rt,float64 duration>'
	@$(CXX) -o $@ -c $(SPL_CXXFLAGS) src/type/BeJwlyUEKgDAMBMA3FWzRu_0QfwQYMaFKS7cHfi3idQctSfWJM7BpywOPJsvxCeonxLbmpdTGoW7ZxBqdQTXCA1j6Dv3gBIi4cDB.cpp

build/type:
	-@mkdir -m 775 build/type

operators: $(SPL_OPERATORS)

-include build/operator/Speech1Stream.d
build/operator/Speech1Stream.o: \
	    src/operator/Speech1Stream.h \
	    src/operator/Speech1Stream.cpp\
	    build/dep/operator/Speech1Stream.dep \
	    src/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.h  \
	    build/cppOptions \
	    | build/operator
	@echo ' [CXX-operator] Speech1Stream'
	@$(CXX) -o $@ -MD -I /home/streamsdev/InfoSphere_Streams/4.1.1.0/toolkits/spl/impl/nl/include -I /home/streamsdev/InfoSphere_Streams/4.1.1.0/toolkits/spl/impl/include -DSPLJAVAFUNCTION_ADL_FILENAME=\"com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeThreeStreams.adl\" -c $(SPL_CXXFLAGS) src/operator/Speech1Stream.cpp

-include build/operator/PunctuatedSpeech1Stream.d
build/operator/PunctuatedSpeech1Stream.o: \
	    src/operator/PunctuatedSpeech1Stream.h \
	    src/operator/PunctuatedSpeech1Stream.cpp\
	    build/dep/operator/PunctuatedSpeech1Stream.dep \
	    src/type/BeJyrNIo3S0pNyy9KNU1MK0ktAgAw9gX7.h \
	    src/type/BeJwlyUEKgDAMBMA3FWzRu_0QfwQYMaFKS7cHfi3idQctSfWJM7BpywOPJsvxCeonxLbmpdTGoW7ZxBqdQTXCA1j6Dv3gBIi4cDB.h  \
	    build/cppOptions \
	    | build/operator
	@echo ' [CXX-operator] PunctuatedSpeech1Stream'
	@$(CXX) -o $@ -MD -I /home/streamsdev/InfoSphere_Streams/4.1.1.0/toolkits/spl/impl/nl/include -DSPLJAVAFUNCTION_ADL_FILENAME=\"com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeThreeStreams.adl\" -c $(SPL_CXXFLAGS) src/operator/PunctuatedSpeech1Stream.cpp

-include build/operator/IndentedPunctuatedSpeech1Stream.d
build/operator/IndentedPunctuatedSpeech1Stream.o: \
	    src/operator/IndentedPunctuatedSpeech1Stream.h \
	    src/operator/IndentedPunctuatedSpeech1Stream.cpp\
	    build/dep/operator/IndentedPunctuatedSpeech1Stream.dep  \
	    build/cppOptions \
	    | build/operator
	@echo ' [CXX-operator] IndentedPunctuatedSpeech1Stream'
	@$(CXX) -o $@ -MD -I /home/streamsdev/InfoSphere_Streams/4.1.1.0/toolkits/spl/impl/nl/include -DSPLJAVAFUNCTION_ADL_FILENAME=\"com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeThreeStreams.adl\" -c $(SPL_CXXFLAGS) src/operator/IndentedPunctuatedSpeech1Stream.cpp

-include build/operator/SynchronizedSpeech1Stream.d
build/operator/SynchronizedSpeech1Stream.o: \
	    src/operator/SynchronizedSpeech1Stream.h \
	    src/operator/SynchronizedSpeech1Stream.cpp\
	    build/dep/operator/SynchronizedSpeech1Stream.dep  \
	    build/cppOptions \
	    | build/operator
	@echo ' [CXX-operator] SynchronizedSpeech1Stream'
	@$(CXX) -o $@ -MD -I /home/streamsdev/git/streamsx.plumbing/com.ibm.streamsx.plumbing/impl/nl/include -DSPLJAVAFUNCTION_ADL_FILENAME=\"com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeThreeStreams.adl\" -c $(SPL_CXXFLAGS) src/operator/SynchronizedSpeech1Stream.cpp

-include build/operator/Transcript.d
build/operator/Transcript.o: \
	    src/operator/Transcript.h \
	    src/operator/Transcript.cpp\
	    build/dep/operator/Transcript.dep \
	    src/type/BeJyrNIo3NArPzEvJL_1dNLMpOLTI0dMvMS8yBcACkegr2.h \
	    src/function/com/ibm/streamsx/plumbing/sample/synchronize/SecondsToTimestamp.h  \
	    build/cppOptions \
	    | build/operator
	@echo ' [CXX-operator] Transcript'
	@$(CXX) -o $@ -MD -I /home/streamsdev/InfoSphere_Streams/4.1.1.0/toolkits/spl/impl/nl/include -DSPLJAVAFUNCTION_ADL_FILENAME=\"com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeThreeStreams.adl\" -c $(SPL_CXXFLAGS) src/operator/Transcript.cpp

build/operator:
	-@mkdir -m 775 -p build/operator

functions: $(SPL_FUNCTIONS)

-include build/function/com/ibm/streamsx/plumbing/sample/synchronize/SecondsToTimestamp.d
build/function/com/ibm/streamsx/plumbing/sample/synchronize/SecondsToTimestamp.o: \
	    src/function/com/ibm/streamsx/plumbing/sample/synchronize/SecondsToTimestamp.h \
	    src/function/com/ibm/streamsx/plumbing/sample/synchronize/SecondsToTimestamp.cpp\
	    build/dep/function/com/ibm/streamsx/plumbing/sample/synchronize/SecondsToTimestamp.dep \
	    build/cppOptions \
	    | build/function/com/ibm/streamsx/plumbing/sample/synchronize
	@echo ' [CXX-function] com.ibm.streamsx.plumbing.sample.synchronize::SecondsToTimestamp'
	@$(CXX) -o $@ -c -MD -DSPLJAVAFUNCTION_ADL_FILENAME=\"com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeThreeStreams.adl\" $(SPL_CXXFLAGS) src/function/com/ibm/streamsx/plumbing/sample/synchronize/SecondsToTimestamp.cpp

build/function/com/ibm/streamsx/plumbing/sample/synchronize:
	-@mkdir -m 775 -p build/function/com/ibm/streamsx/plumbing/sample/synchronize

pes: $(SPL_PE_BINS)

build/pe/BeJwzNvTMS0nNK0lNCSjNSy4pTQSyggtSU5MzDINLilITc_0ONjHHJGBqjqTQNrsxLzijKz8uswlBrEFKUmFecXJRZUBIPACSzCw0.o: \
	    src/pe/BeJwzNvTMS0nNK0lNCSjNSy4pTQSyggtSU5MzDINLilITc_0ONjHHJGBqjqTQNrsxLzijKz8uswlBrEFKUmFecXJRZUBIPACSzCw0.h \
	    src/pe/BeJwzNvTMS0nNK0lNCSjNSy4pTQSyggtSU5MzDINLilITc_0ONjHHJGBqjqTQNrsxLzijKz8uswlBrEFKUmFecXJRZUBIPACSzCw0.cpp  \
	    build/cppOptions \
	    | build/pe
	@echo ' [CXX-pe] pe com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeThreeStreams-a'
	@$(CXX) -o $@ -c $(SPL_CXXFLAGS) src/pe/BeJwzNvTMS0nNK0lNCSjNSy4pTQSyggtSU5MzDINLilITc_0ONjHHJGBqjqTQNrsxLzijKz8uswlBrEFKUmFecXJRZUBIPACSzCw0.cpp

PEcom.ibm.streamsx.plumbing.sample.synchronize.SynchronizeThreeStreams-a = \
	    build/pe/BeJwzNvTMS0nNK0lNCSjNSy4pTQSyggtSU5MzDINLilITc_0ONjHHJGBqjqTQNrsxLzijKz8uswlBrEFKUmFecXJRZUBIPACSzCw0.o \
	    build/operator/Speech1Stream.o \
	    build/type/BeJwlyUEKgDAMBMA3FWzRu_0QfwQYMaFKS7cHfi3idQctSfWJM7BpywOPJsvxCeonxLbmpdTGoW7ZxBqdQTXCA1j6Dv3gBIi4cDB.o \
	    build/type/BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.o \
	    build/operator/PunctuatedSpeech1Stream.o \
	    build/type/BeJyrNIo3S0pNyy9KNU1MK0ktAgAw9gX7.o \
	    build/operator/IndentedPunctuatedSpeech1Stream.o \
	    build/operator/SynchronizedSpeech1Stream.o \
	    build/operator/Transcript.o \
	    build/function/com/ibm/streamsx/plumbing/sample/synchronize/SecondsToTimestamp.o \
	    build/type/BeJyrNIo3NArPzEvJL_1dNLMpOLTI0dMvMS8yBcACkegr2.o 

bin/com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeThreeStreams-a.dpe: \
	$(PEcom.ibm.streamsx.plumbing.sample.synchronize.SynchronizeThreeStreams-a) \
	build/dep/com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeThreeStreams-a.dep \
	build/ldOptions
	@echo ' [LD-pe] pe com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeThreeStreams-a'
	@$(CXX) $(SPL_CXXFLAGS) -o bin/com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeThreeStreams-a.dpe -fPIC -shared $(PEcom.ibm.streamsx.plumbing.sample.synchronize.SynchronizeThreeStreams-a) -lstreams-stdtk-runtime -lstreams_boost_iostreams -lstreams_boost_filesystem -lstreams_boost_system $(SPL_LDFLAGS)

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
	@ln -sf standalone bin/com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeThreeStreams
build/standalone:
	-@mkdir -m 775 build/standalone

sablink:

	@ln -sf ../com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeThreeStreams.sab bin/sab

bundle: com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeThreeStreams.sab

-include /home/streamsdev/git/streamsx.plumbing/samples/SynchronizeSamples/output/com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeThreeStreams/Standalone2/build/dep/com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeThreeStreams.sab.d
com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeThreeStreams.sab: $(SPL_PE_BINS) $(SPL_ADL_FILE) bin/standalone.exe
	@echo ' [Bundle] com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeThreeStreams.sab'
	@$(SPL_BUNDLE_BUILDER) $(SPL_OUTPUT_DIR_ROOT) $(SPL_OUTPUT_DIR) $(SPL_ADL_FILE) com.ibm.streamsx.plumbing.sample.synchronize.SynchronizeThreeStreams.sab true

