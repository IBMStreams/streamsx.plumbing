// eJztVE1P4zAQ1fwVtAe45BO1Um8NpQuFailhVeCC3MRNvYrtrD1pE379uiFpaWmX3Qs9gCIfMnrPnnlvZiLJLTbhlkZFCdeFlaU5nzCRWLoU0UxJwZ5ppxOuf8AFx3wuHFmWjWVG7YAOFmn58_1wq6XWHwbDr98fPt_1mTM5ouRg9D0r8K29HFlPksHkUYTseDYTvIysWPm4GeF2dUiuJ6wrP47rsctx_0L4Hc8urs_167q_1Wr25nwSX7DTqBdbsqHo0ZfjNgfDmutOZppJg6xQA7Jnk1K5LiOncThjabyqyNeFZSrX9qpiwDsUECQgpqAMeIOO0i6jYJEeqwd98zgGWSWWysBKKTxqJwuMTWOF3g93_1AXt7wMu8_0iRCqYwQG8xGl_1MiU1RrJoXJepXoC_1YjXAIGquoOgBbIHLMce0zRZcolKOOIsaGO91lKBeF0FWYipgKXqTeRbKaIXgMqQaApOc4VqdBrDWqpP0e5XtMsn6PcZTvLg7Tz_1lLdZgybwOZq2KKZUd6jzT_1d07DMNW_01fOeGFcGQt2R_1h_1mCNrRNe9ztBbR7Ke6Y0b_1yGvzxiV8te88ceZCh_1jL9gKZ7tekfvdq_0TD_0c6X8AA6d3Al
/*
 * Copyright (C) 2013, 2016 International Business Machines Corporation. 
 * All Rights Reserved.
 */


#include <sys/time.h>
#include <time.h>
#include <float.h>
#include <SPL/Runtime/Utility/BackoffSpinner.h>


// DEBUG: inputPort[0] type is tuple<rstring outputDirectory,rstring outputFilename,rstring indention,rstring phrase,float64 start,float64 duration>
// DEBUG: outputPort[0] type is tuple<rstring outputDirectory,rstring outputFilename,rstring indention,rstring phrase,float64 start,float64 duration>
// DEBUG: inputPort[1] type is tuple<rstring outputDirectory,rstring outputFilename,rstring indention,rstring phrase,float64 start,float64 duration>
// DEBUG: outputPort[1] type is tuple<rstring outputDirectory,rstring outputFilename,rstring indention,rstring phrase,float64 start,float64 duration>
// DEBUG: inputPort[2] type is tuple<rstring outputDirectory,rstring outputFilename,rstring indention,rstring phrase,float64 start,float64 duration>
// DEBUG: outputPort[2] type is tuple<rstring outputDirectory,rstring outputFilename,rstring indention,rstring phrase,float64 start,float64 duration>
// DEBUG: timeFactor is 'lit$0'




#include "./SynchronizedSpeech1Stream.h"
using namespace SPL::_Operator;

#include <SPL/Runtime/Function/SPLFunctions.h>
#include <SPL/Runtime/Operator/Port/Punctuation.h>

#include <string>

#define MY_OPERATOR_SCOPE SPL::_Operator
#define MY_BASE_OPERATOR SynchronizedSpeech1Stream_Base
#define MY_OPERATOR SynchronizedSpeech1Stream$OP



// Constructor
MY_OPERATOR_SCOPE::MY_OPERATOR::MY_OPERATOR()
{
    SPLLOG(L_TRACE, "entering com.ibm.streamsx.plumbing.synchronize::Synchronize constructor", "Synchronize");


    if (lit$0 < 0) THROW (SPLRuntimeOperator, "Sorry, 'timeFactor' parameter must be greater than zero");


    // initialize all state variables

    previousSubmitTime = 0;
    previousTupleTimestamp = 0;

    for (int i=0; i < 3; i++) {
    	nextTimestamp[i] = 0;
	stopCount[i] = 0;
	clearCount[i] = 0;
    }

   SPLLOG(L_TRACE, "leaving com.ibm.streamsx.plumbing.synchronize::Synchronize constructor", "Synchronize");
}


// Destructor
MY_OPERATOR_SCOPE::MY_OPERATOR::~MY_OPERATOR() 
{
}


// Notify port readiness
void MY_OPERATOR_SCOPE::MY_OPERATOR::allPortsReady() 
{
}


// Notify pending shutdown
void MY_OPERATOR_SCOPE::MY_OPERATOR::prepareToShutdown() 
{
	cvStopped.broadcast();
	cvCleared.broadcast();
}


// Processing for source and threaded operators   
void MY_OPERATOR_SCOPE::MY_OPERATOR::process(uint32_t idx)
{
}


// Tuple processing for mutating ports 
void MY_OPERATOR_SCOPE::MY_OPERATOR::process(Tuple & tuple, uint32_t port)
{
}


// get the current time, as a 'double', in seconds since the Unix epoch, with microsecond accuracy
double theTimeRightNow()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
}


// determine whether or not this port is next in line to submit its tuple
bool MY_OPERATOR_SCOPE::MY_OPERATOR::itsOurTurn(uint32_t ourPort)
{
    uint32_t nextPort = -1;
    double oldestTimestamp = DBL_MAX;
    for (int i=0; i < 3; i++) {
      if ( stopCount[i] != stopCount[ourPort] ) continue;
      if ( nextTimestamp[i] == 0 ) return false;
      if ( nextTimestamp[i] >= oldestTimestamp ) continue;
      nextPort = i;
      oldestTimestamp = nextTimestamp[i];
    }
    if (nextPort == -1) SPLLOG(L_ERROR, "all input ports stopped", "Synchronize");

    return (ourPort==nextPort);
}


// Tuple processing for non-mutating ports
void MY_OPERATOR_SCOPE::MY_OPERATOR::process(Tuple const & tuple, uint32_t port)
{
    SPLLOG(L_TRACE, "entering com.ibm.streamsx.plumbing.synchronize::Synchronize process(," << port << "), tuple=" << tuple, "Synchronize");

    // get the value of the timestamp attribute from the tuple received by this input port
    switch(port) {
case 0: { const IPort0Type& iport$0 = tuple; nextTimestamp[0] = static_cast<double>(iport$0.get_start()); } break;
case 1: { const IPort1Type& iport$1 = tuple; nextTimestamp[1] = static_cast<double>(iport$1.get_start()); } break;
case 2: { const IPort2Type& iport$2 = tuple; nextTimestamp[2] = static_cast<double>(iport$2.get_start()); } break;
 
    }
    SPLLOG(L_TRACE, "next timestamp for port " << port << " is " << nextTimestamp[port], "Synchronize");

    // wait (in a spin loop) until this port's tuple is next in time sequence
    BackoffSpinner spinner;
    SPLLOG(L_TRACE, "port " << port << " waiting for its turn", "Synchronize");
    while( !getPE().getShutdownRequested() && !itsOurTurn(port) ) spinner.wait();


    // wait a bit longer until its time to replay this port's tuple
    if (lit$0 > 0) {
       const double delay = previousTupleTimestamp ? ( nextTimestamp[port] - previousTupleTimestamp ) / lit$0 : 0;
       const double theTimeToSubmit = previousSubmitTime + delay; // note that 'previousSubmitTime' will be zero on first tuple
       SPLLOG(L_TRACE, "port " << port << " taking its turn, waiting " << delay << " seconds", "Synchronize");
       while ( !getPE().getShutdownRequested() && theTimeRightNow() < theTimeToSubmit ) spinner.wait();
    }


    // advance the shared timestamp
    if (previousTupleTimestamp < nextTimestamp[port]) previousTupleTimestamp = nextTimestamp[port];

    // forward the tuple downstream, and remember when we sent it
    SPLLOG(L_TRACE, "port " << port << " submitting tuple=" << tuple, "Synchronize");
    previousSubmitTime = theTimeRightNow();

    // submit the current tuple now
    submit(tuple, port);

    // this port needs to receive another tuple before any port can proceed
    nextTimestamp[port] = 0;

    SPLLOG(L_TRACE, "leaving com.ibm.streamsx.plumbing.synchronize::Synchronize process(," << port << "), tuple=" << tuple, "Synchronize");
}


std::string printCounts(uint32_t* counters) {

   std::stringstream buffer;
   buffer << "[";
   for (int i=0; i < 3; i++) { buffer << (i==0 ? "" : ",") << counters[i]; }
   buffer << "]";
   return buffer.str();
}


// determine whether or not all ports have caught up to this port at a checkpoint
bool MY_OPERATOR_SCOPE::MY_OPERATOR::allCaughtUp(uint32_t* counters, uint32_t port)
{
    for (int i=0; i < 3; i++) { if (  counters[i]<counters[port] ) return false; }
    return true;
}


// Punctuation processing
void MY_OPERATOR_SCOPE::MY_OPERATOR::process(Punctuation const & punct, uint32_t port)
{
    SPLLOG(L_TRACE, "entering com.ibm.streamsx.plumbing.synchronize::Synchronize process(" << punct << ", " << port << ")", "Synchronize");
    
    {
	AutoMutex am(mutexStopped);
	stopCount[port]++;
	SPLLOG(L_DEBUG, "port " << port << " stopped at " << punct << " " << stopCount[port] << ", others at p=" << printCounts(stopCount), "Synchronize");
	while ( !getPE().getShutdownRequested() && !allCaughtUp(stopCount, port) ) cvStopped.wait(mutexStopped);
	cvStopped.broadcast();
    }

    submit(punct, port);
    previousSubmitTime = 0; 
    previousTupleTimestamp = 0;
    nextTimestamp[port] = 0;

    {
	AutoMutex am(mutexCleared);
	clearCount[port]++;
	SPLLOG(L_TRACE, "port " << port << " cleared at " << punct << " " << clearCount[port] << ", others at c=" << printCounts(clearCount), "Synchronize");
	while ( !getPE().getShutdownRequested() && !allCaughtUp(clearCount, port) ) cvCleared.wait(mutexCleared);
	cvCleared.broadcast();
    }

    SPLLOG(L_DEBUG, "port " << port << " resuming after " << punct << " " << stopCount[port] << ", others at p=" << printCounts(stopCount) << ", c=" << printCounts(clearCount), "Synchronize");
    SPLLOG(L_TRACE, "leaving com.ibm.streamsx.plumbing.synchronize::Synchronize process(" << punct << ", " << port << ")", "Synchronize");
}


static SPL::Operator * initer() { return new MY_OPERATOR_SCOPE::MY_OPERATOR(); }
bool MY_BASE_OPERATOR::globalInit_ = MY_BASE_OPERATOR::globalIniter();
bool MY_BASE_OPERATOR::globalIniter() {
    instantiators_.insert(std::make_pair("SynchronizedSpeech1Stream",&initer));
    return true;
}

template<class T> static void initRTC (SPL::Operator& o, T& v, const char * n) {
    SPL::ValueHandle vh = v;
    o.getContext().getRuntimeConstantValue(vh, n);
}

MY_BASE_OPERATOR::MY_BASE_OPERATOR()
 : Operator() {
    PE & pe = PE::instance();
    uint32_t index = getIndex();
    initRTC(*this, lit$0, "lit$0");
    addParameterValue ("timeAttributes");
    addParameterValue ("timeAttributes");
    addParameterValue ("timeAttributes");
    addParameterValue ("timeFactor", SPL::ConstValueHandle(lit$0));
    (void) getParameters(); // ensure thread safety by initializing here
    $oportBitset.push_back(OPortBitsetType(std::string("0111")));
    $oportBitset.push_back(OPortBitsetType(std::string("0111")));
    $oportBitset.push_back(OPortBitsetType(std::string("0111")));
}
MY_BASE_OPERATOR::~MY_BASE_OPERATOR()
{
    for (ParameterMapType::const_iterator it = paramValues_.begin(); it != paramValues_.end(); it++) {
        const ParameterValueListType& pvl = it->second;
        for (ParameterValueListType::const_iterator it2 = pvl.begin(); it2 != pvl.end(); it2++) {
            delete *it2;
        }
    }
}

void MY_BASE_OPERATOR::tupleLogic(Tuple const & tuple, uint32_t port) {
    switch(port) {
    }
}


void MY_BASE_OPERATOR::processRaw(Tuple const & tuple, uint32_t port) {
    tupleLogic (tuple, port);
    static_cast<MY_OPERATOR_SCOPE::MY_OPERATOR*>(this)->MY_OPERATOR::process(tuple, port);
}


void MY_BASE_OPERATOR::punctLogic(Punctuation const & punct, uint32_t port) {
}

void MY_BASE_OPERATOR::punctPermitProcessRaw(Punctuation const & punct, uint32_t port) {
    {
        punctNoPermitProcessRaw(punct, port);
    }
}

void MY_BASE_OPERATOR::punctNoPermitProcessRaw(Punctuation const & punct, uint32_t port) {
    switch(punct) {
    case Punctuation::WindowMarker:
        punctLogic(punct, port);
        process(punct, port);
        break;
    case Punctuation::FinalMarker:
        punctLogic(punct, port);
        
        if (punct == Punctuation::FinalMarker) {
            process(punct, port);
            for (uint32_t i = 0; i < 3; ++i) {
                bool forward = false;
                {
                    AutoPortMutex $apm($fpMutex, *this);
                    $oportBitset[i].reset(port);
                    if ($oportBitset[i].none()) {
                        $oportBitset[i].set(3);
                        forward=true;
                    }
                }
                if(forward)
                    submit(punct, i);
            }
            return;
        }
        process(punct, port);
        break;
    case Punctuation::DrainMarker:
    case Punctuation::ResetMarker:
    case Punctuation::ResumeMarker:
        break;
    case Punctuation::SwitchMarker:
        break;
    default:
        break;
    }
}

void MY_BASE_OPERATOR::processRaw(Punctuation const & punct, uint32_t port) {
    switch(port) {
    case 0:
        punctNoPermitProcessRaw(punct, port);
        break;
    case 1:
        punctNoPermitProcessRaw(punct, port);
        break;
    case 2:
        punctNoPermitProcessRaw(punct, port);
        break;
    }
}



void MY_BASE_OPERATOR::checkpointStateVariables(NetworkByteBuffer & opstate) const {
}

void MY_BASE_OPERATOR::restoreStateVariables(NetworkByteBuffer & opstate) {
}

void MY_BASE_OPERATOR::checkpointStateVariables(Checkpoint & ckpt) {
}

void MY_BASE_OPERATOR::resetStateVariables(Checkpoint & ckpt) {
}

void MY_BASE_OPERATOR::resetStateVariablesToInitialState() {
}

bool MY_BASE_OPERATOR::hasStateVariables() const {
    return false;
}

void MY_BASE_OPERATOR::resetToInitialStateRaw() {
    AutoMutex $apm($svMutex);
    StateHandler *sh = getContext().getStateHandler();
    if (sh != NULL) {
        sh->resetToInitialState();
    }
    resetStateVariablesToInitialState();
}

void MY_BASE_OPERATOR::checkpointRaw(Checkpoint & ckpt) {
    AutoMutex $apm($svMutex);
    StateHandler *sh = getContext().getStateHandler();
    if (sh != NULL) {
        sh->checkpoint(ckpt);
    }
    checkpointStateVariables(ckpt);
}

void MY_BASE_OPERATOR::resetRaw(Checkpoint & ckpt) {
    AutoMutex $apm($svMutex);
    StateHandler *sh = getContext().getStateHandler();
    if (sh != NULL) {
        sh->reset(ckpt);
    }
    resetStateVariables(ckpt);
}


