.PHONY: all clean 

SPLC_FLAGS = -a
SPLC = $(STREAMS_INSTALL)/bin/sc

SPL_CMD_ARGS ?= -t ../../../com.ibm.streamsx.plumbing
SPL_MAIN_COMPOSITE = BadMeasure

all: standalone

standalone:
	$(SPLC) $(SPLC_FLAGS) -z -T -M $(SPL_MAIN_COMPOSITE) $(SPL_CMD_ARGS)

distributed:
	$(SPLC) $(SPLC_FLAGS) -z -M $(SPL_MAIN_COMPOSITE) $(SPL_CMD_ARGS)

clean: 
	$(SPLC) $(SPLC_FLAGS) -C -M $(SPL_MAIN_COMPOSITE)

