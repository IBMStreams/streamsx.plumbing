# begin_generated_IBM_copyright_prolog                             
#                                                                  
# This is an automatically generated copyright prolog.             
# After initializing,  DO NOT MODIFY OR MOVE                       
# **************************************************************** 
# THIS SAMPLE CODE IS PROVIDED ON AN "AS IS" BASIS. IBM MAKES NO   
# REPRESENTATIONS OR WARRANTIES, EXPRESS OR IMPLIED, CONCERNING    
# USE OF THE SAMPLE CODE, OR THE COMPLETENESS OR ACCURACY OF THE   
# SAMPLE CODE. IBM DOES NOT WARRANT UNINTERRUPTED OR ERROR-FREE    
# OPERATION OF THIS SAMPLE CODE. IBM IS NOT RESPONSIBLE FOR THE    
# RESULTS OBTAINED FROM THE USE OF THE SAMPLE CODE OR ANY PORTION  
# OF THIS SAMPLE CODE.                                             
#                                                                  
# LIMITATION OF LIABILITY. IN NO EVENT WILL IBM BE LIABLE TO ANY   
# PARTY FOR ANY DIRECT, INDIRECT, SPECIAL OR OTHER CONSEQUENTIAL   
# DAMAGES FOR ANY USE OF THIS SAMPLE CODE, THE USE OF CODE FROM    
# THIS [ SAMPLE PACKAGE,] INCLUDING, WITHOUT LIMITATION, ANY LOST  
# PROFITS, BUSINESS INTERRUPTION, LOSS OF PROGRAMS OR OTHER DATA   
# ON YOUR INFORMATION HANDLING SYSTEM OR OTHERWISE.                
#                                                                  
# (C) Copyright IBM Corp. 2017  All Rights reserved.         
#                                                                  
# end_generated_IBM_copyright_prolog                               

# Note: Before compiling this application, you must first
# make the toolkit from the streamsx.plumbing directory via
# this command: ant all

# User must complete this line on her/his own to point to the correct
# location of the plumbing toolkit directory.
PLUMBING_TOOLKIT_HOME ?= $(STREAMS_INSTALL)/toolkits

# If the user wants to specify the location of the
# plumbing toolkit directory outside of this make file,
# (s)he can always set the STREAMS_SPLPATH environment variable
# and point it to a specific version of the plumbing toolkit directory.
# e-g: export STREAMS_SPLPATH=/tmp/mydir/streamsx.plumbing
# This environment variable  will take precedence over the value specified 
# in the previous make statement.
ifndef STREAMS_SPLPATH
   SPLC_FLAGS ?= -a -z -t $(PLUMBING_TOOLKIT_HOME)
else
   SPLC_FLAGS ?= -a -z 
endif

SPLC = $(STREAMS_INSTALL)/bin/sc
SPL_CMD_ARGS ?= --data-directory=./data 
SPL_MAIN_COMPOSITE = expiredtupledetector.test::ExpiredTupleDetectorTest

all: distributed

distributed:
	$(SPLC) $(SPLC_FLAGS) -M $(SPL_MAIN_COMPOSITE) $(SPL_CMD_ARGS) --output-directory=./output/expiredtupledetector.test.ExpiredTupleDetectorTest/Distributed

clean: 
	$(SPLC) $(SPLC_FLAGS) -C -M $(SPL_MAIN_COMPOSITE)
	rm -rf output
