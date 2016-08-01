// eJxtUWFLwzAQ5f5JGX5oUZq2G_1sQRGgHwsSBuh8gWXuugTQJydXZ_1Xpr1zqnki_133r1w7955q_0KWpJLUcV6gKI2GFJL_0pTCLY0adRVbgw8FtykNyzJ_1z4mVTrGxcz3rNHPqPVwlsnx45l5rmGQxMemLelBG0XJy47EIFrDYNMk8OReMrfGd7SRP8iK1qm53Ue_0ZFYxV6tu10WTuj5RG3I1UJEqCNxgQykIROkDTaQ_1pzUDo6zImc3LWE9w4RLDppKvhlMx29X2qTIQ9jjfve9J88QILrhRLGsblf_13FyBiHnA_1BWvZbC0_025dRMMdduD5SK44_1yrH0634Xw9LboyraYwioLrYIg3Sj4BbYiLDm



#include "./NumberStream.h"
using namespace SPL::_Operator;

#include <SPL/Runtime/Function/SPLFunctions.h>
#include <SPL/Runtime/Operator/Port/Punctuation.h>


#define MY_OPERATOR_SCOPE SPL::_Operator
#define MY_BASE_OPERATOR NumberStream_Base
#define MY_OPERATOR NumberStream$OP


// batchSize 1

MY_OPERATOR_SCOPE::MY_OPERATOR::MY_OPERATOR()
: _iterationCount(0)
  
{
    _tuple.clear();
    
        _iters = lit$0;
    
    
    
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::allPortsReady()
{
    createThreads (1);
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::process(uint32_t) 
{
    SPLAPPTRC(L_DEBUG, "Beacon startup...", SPL_OPER_DBG);
    ProcessingElement& pe = getPE();
    
        const double period = lit$1;
    
    
    uint32_t batchSize = 1;
    while(!pe.getShutdownRequested()) {
        
                
                {
                    AutoMutex am (_mutex);
                
                
                    if (_iters != 0) {
                        _iters--;
                
                _tuple.set_i(SPL::int32(::SPL::spl_cast<SPL::int32, SPL::uint64 >::cast(IterationCount()) + lit$2)); 
                submit (_tuple, 0);
                
                    _iterationCount++;
                
                
                
                    if (_iters == 0) {
                        submit(Punctuation::WindowMarker, 0);
                        
                            submit(Punctuation::FinalMarker, 0);
                            goto exit;
                        
                    }
                    }
                
                
                } 
                
	
        
            pe.blockUntilShutdownRequest(period);
        
    }
exit:
    SPLAPPTRC(L_DEBUG, "Beacon exiting...", SPL_OPER_DBG);
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::getCheckpoint(NetworkByteBuffer & opstate)
{
    AutoMutex am (_mutex);
    
    
        opstate.addUInt32(_iters);
    
    
        opstate.addUInt64(_iterationCount);
    
    
        opstate << _tuple;
    
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::restoreCheckpoint(NetworkByteBuffer & opstate)
{
    AutoMutex am (_mutex);
    
    
        _iters = opstate.getUInt32();
    
    
        _iterationCount = opstate.getUInt64();
    
    
        opstate >> _tuple;
    
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::checkpoint(Checkpoint & ckpt)
{
    AutoMutex am(_mutex);

    SPLAPPTRC(L_DEBUG, "Executing checkpoint()", SPL_OPER_DBG);

    
        ckpt << _iters;
    
    
        ckpt << _iterationCount;
        SPLAPPTRC(L_DEBUG, "iterationCount: " << _iterationCount, SPL_OPER_DBG);
    
    
        ckpt << _tuple;
    
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::reset(Checkpoint & ckpt)
{
    AutoMutex am(_mutex);

    
        ckpt >> _iters;
    
    
        ckpt >> _iterationCount;
        SPLAPPTRC(L_DEBUG, "iterationCount: " << _iterationCount, SPL_OPER_DBG);
    
    
        ckpt >> _tuple;
    

    
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::resetToInitialState()
{
    AutoMutex am(_mutex);

    _iterationCount = 0;
    _tuple.clear();
    
        _iters = lit$0;
    

    
    
    return;
}


static SPL::Operator * initer() { return new MY_OPERATOR_SCOPE::MY_OPERATOR(); }
bool MY_BASE_OPERATOR::globalInit_ = MY_BASE_OPERATOR::globalIniter();
bool MY_BASE_OPERATOR::globalIniter() {
    instantiators_.insert(std::make_pair("NumberStream",&initer));
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
    initRTC(*this, lit$1, "lit$1");
    initRTC(*this, lit$2, "lit$2");
    addParameterValue ("iterations", SPL::ConstValueHandle(lit$0));
    addParameterValue ("period", SPL::ConstValueHandle(lit$1));
    (void) getParameters(); // ensure thread safety by initializing here
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


