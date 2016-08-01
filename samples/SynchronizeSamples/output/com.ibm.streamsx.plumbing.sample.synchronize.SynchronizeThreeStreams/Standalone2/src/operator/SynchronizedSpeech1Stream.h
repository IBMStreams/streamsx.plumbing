// eJztVE1P4zAQ1fwVtAe45BO1Um8NpQuFailhVeCC3MRNvYrtrD1pE379uiFpaWmX3Qs9gCIfMnrPnnlvZiLJLTbhlkZFCdeFlaU5nzCRWLoU0UxJwZ5ppxOuf8AFx3wuHFmWjWVG7YAOFmn58_1wq6XWHwbDr98fPt_1mTM5ouRg9D0r8K29HFlPksHkUYTseDYTvIysWPm4GeF2dUiuJ6wrP47rsctx_0L4Hc8urs_167q_1Wr25nwSX7DTqBdbsqHo0ZfjNgfDmutOZppJg6xQA7Jnk1K5LiOncThjabyqyNeFZSrX9qpiwDsUECQgpqAMeIOO0i6jYJEeqwd98zgGWSWWysBKKTxqJwuMTWOF3g93_1AXt7wMu8_0iRCqYwQG8xGl_1MiU1RrJoXJepXoC_1YjXAIGquoOgBbIHLMce0zRZcolKOOIsaGO91lKBeF0FWYipgKXqTeRbKaIXgMqQaApOc4VqdBrDWqpP0e5XtMsn6PcZTvLg7Tz_1lLdZgybwOZq2KKZUd6jzT_1d07DMNW_01fOeGFcGQt2R_1h_1mCNrRNe9ztBbR7Ke6Y0b_1yGvzxiV8te88ceZCh_1jL9gKZ7tekfvdq_0TD_0c6X8AA6d3Al
/*
 * Copyright (C) 2013, 2016 International Business Machines Corporation. 
 * All Rights Reserved.
 */





#ifndef SPL_OPER_INSTANCE_SYNCHRONIZEDSPEECH1STREAM_H_
#define SPL_OPER_INSTANCE_SYNCHRONIZEDSPEECH1STREAM_H_

#include <SPL/Runtime/Operator/Operator.h>
#include <SPL/Runtime/Operator/ParameterValue.h>
#include <SPL/Runtime/Operator/OperatorContext.h>
#include <SPL/Runtime/Operator/OperatorMetrics.h>
#include <SPL/Runtime/Operator/Port/AutoPortMutex.h>
#include <SPL/Runtime/Operator/State/StateHandler.h>
#include <SPL/Runtime/ProcessingElement/PE.h>
#include <SPL/Runtime/Type/SPLType.h>
#include <SPL/Runtime/Utility/CV.h>
using namespace UTILS_NAMESPACE;

#include "../type/BeJwlyUEKgDAMBMA3FWzRu_0QfwQYMaFKS7cHfi3idQctSfWJM7BpywOPJsvxCeonxLbmpdTGoW7ZxBqdQTXCA1j6Dv3gBIi4cDB.h"

#include <bitset>
#include <vector>

#define MY_OPERATOR SynchronizedSpeech1Stream$OP
#define MY_BASE_OPERATOR SynchronizedSpeech1Stream_Base
#define MY_OPERATOR_SCOPE SPL::_Operator

namespace SPL {
namespace _Operator {

class MY_BASE_OPERATOR : public Operator
{
public:
    
    typedef SPL::BeJwlyUEKgDAMBMA3FWzRu_0QfwQYMaFKS7cHfi3idQctSfWJM7BpywOPJsvxCeonxLbmpdTGoW7ZxBqdQTXCA1j6Dv3gBIi4cDB IPort0Type;
    typedef SPL::BeJwlyUEKgDAMBMA3FWzRu_0QfwQYMaFKS7cHfi3idQctSfWJM7BpywOPJsvxCeonxLbmpdTGoW7ZxBqdQTXCA1j6Dv3gBIi4cDB IPort1Type;
    typedef SPL::BeJwlyUEKgDAMBMA3FWzRu_0QfwQYMaFKS7cHfi3idQctSfWJM7BpywOPJsvxCeonxLbmpdTGoW7ZxBqdQTXCA1j6Dv3gBIi4cDB IPort2Type;
    typedef SPL::BeJwlyUEKgDAMBMA3FWzRu_0QfwQYMaFKS7cHfi3idQctSfWJM7BpywOPJsvxCeonxLbmpdTGoW7ZxBqdQTXCA1j6Dv3gBIi4cDB OPort0Type;
    typedef SPL::BeJwlyUEKgDAMBMA3FWzRu_0QfwQYMaFKS7cHfi3idQctSfWJM7BpywOPJsvxCeonxLbmpdTGoW7ZxBqdQTXCA1j6Dv3gBIi4cDB OPort1Type;
    typedef SPL::BeJwlyUEKgDAMBMA3FWzRu_0QfwQYMaFKS7cHfi3idQctSfWJM7BpywOPJsvxCeonxLbmpdTGoW7ZxBqdQTXCA1j6Dv3gBIi4cDB OPort2Type;
    
    MY_BASE_OPERATOR();
    
    ~MY_BASE_OPERATOR();
    
    inline void tupleLogic(Tuple const & tuple, uint32_t port);
    void processRaw(Tuple const & tuple, uint32_t port);
    
    inline void punctLogic(Punctuation const & punct, uint32_t port);
    void processRaw(Punctuation const & punct, uint32_t port);
    void punctPermitProcessRaw(Punctuation const & punct, uint32_t port);
    void punctNoPermitProcessRaw(Punctuation const & punct, uint32_t port);
    
    
    
    SPL::float64 lit$0;
    
    
protected:
    Mutex $svMutex;
    typedef std::bitset<4> OPortBitsetType;
    std::vector<OPortBitsetType> $oportBitset;
    Mutex $fpMutex;
    void checkpointStateVariables(NetworkByteBuffer & opstate) const;
    void restoreStateVariables(NetworkByteBuffer & opstate);
    void checkpointStateVariables(Checkpoint & ckpt);
    void resetStateVariables(Checkpoint & ckpt);
    void resetStateVariablesToInitialState();
    bool hasStateVariables() const;
    void resetToInitialStateRaw();
    void checkpointRaw(Checkpoint & ckpt);
    void resetRaw(Checkpoint & ckpt);
private:
    static bool globalInit_;
    static bool globalIniter();
    ParameterMapType paramValues_;
    ParameterMapType& getParameters() { return paramValues_;}
    void addParameterValue(std::string const & param, ConstValueHandle const& value)
    {
        ParameterMapType::iterator it = paramValues_.find(param);
        if (it == paramValues_.end())
            it = paramValues_.insert (std::make_pair (param, ParameterValueListType())).first;
        it->second.push_back(&ParameterValue::create(value));
    }
    void addParameterValue(std::string const & param)
    {
        ParameterMapType::iterator it = paramValues_.find(param);
        if (it == paramValues_.end())
            it = paramValues_.insert (std::make_pair (param, ParameterValueListType())).first;
        it->second.push_back(&ParameterValue::create());
    }
};


#include <vector>

#include <SPL/Runtime/Utility/Mutex.h>
#include <SPL/Runtime/Utility/CV.h>


class MY_OPERATOR : public MY_BASE_OPERATOR 
{
public:
  // Constructor
  MY_OPERATOR();

  // Destructor
  virtual ~MY_OPERATOR(); 

  // Notify port readiness
  void allPortsReady(); 

  // Notify pending shutdown
  void prepareToShutdown(); 

  // Processing for source and threaded operators   
  void process(uint32_t idx);
    
  // Tuple processing for mutating ports 
  void process(Tuple & tuple, uint32_t port);
    
  // Tuple processing for non-mutating ports
  void process(Tuple const & tuple, uint32_t port);

  // Punctuation processing
  void process(Punctuation const & punct, uint32_t port);

private:

  // for synchronizing tuples
  volatile double previousSubmitTime; // clock time, shared by all ports
  volatile double previousTupleTimestamp; // tuple time, shared by all ports
  volatile double nextTimestamp[3]; // tuple time, per port

  // for synchronizing threads at punctuation
  uint32_t stopCount[3];
  SPL::Mutex mutexStopped; 
  SPL::CV cvStopped; 
  
  // for synchronizing threads after punctuation
  uint32_t clearCount[3];
  SPL::Mutex mutexCleared; 
  SPL::CV cvCleared; 
  
  // private functions
  bool itsOurTurn(uint32_t ourPort);
  bool allCaughtUp(uint32_t* counters, uint32_t port);

}; 


} // namespace _Operator
} // namespace SPL

#undef MY_OPERATOR_SCOPE
#undef MY_BASE_OPERATOR
#undef MY_OPERATOR
#endif // SPL_OPER_INSTANCE_SYNCHRONIZEDSPEECH1STREAM_H_


