// eJy9kktLw0AUhbl_1pbhoNzNJKC6ya0XxFRCi4k4m6TUZmEeYmWqbX_08kJrWJASmIZJXLOfd_05zC5loRnklhnkEm7I5XYyoyrgti9ykujFa8xjtPvHwgh8F8IM0Ko21dI13j7YZKXm_1ouV8ljGkT1k0hSG6xXF_1p69bwk5aw1CO7OAkgf7uP4TWjmzpcAQEstkXbnN_1hOC_07oDxpqmawEWnoEknajDXMMlFYYQASOS1w5Z3i2dWj9YHAuAF5p4ylIge610c4XcJBPa8NpbTO4YrnTxicbGPugl7vKoLVcK49xuPyl_1a0y4GDamqHLBP12wTIUYHxDvhZ_1q4P827UNrz6Zd7QyHBcz2f44T_0fpB0NPK54vovY5hR3iKdn_1F_1ET2s4JAH
/*
 * Copyright (C) 2013, 2016 International Business Machines Corporation. 
 * All Rights Reserved.
 */





#ifndef SPL_OPER_INSTANCE_SYNCHRONIZEDEVENSTREAM_H_
#define SPL_OPER_INSTANCE_SYNCHRONIZEDEVENSTREAM_H_

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

#include "../type/BeJwrMXIzKcnMTS02zUlMSs0BACoHAV4.h"

#include <bitset>
#include <vector>

#define MY_OPERATOR SynchronizedEvenStream$OP
#define MY_BASE_OPERATOR SynchronizedEvenStream_Base
#define MY_OPERATOR_SCOPE SPL::_Operator

namespace SPL {
namespace _Operator {

class MY_BASE_OPERATOR : public Operator
{
public:
    
    typedef SPL::BeJwrMXIzKcnMTS02zUlMSs0BACoHAV4 IPort0Type;
    typedef SPL::BeJwrMXIzKcnMTS02zUlMSs0BACoHAV4 IPort1Type;
    typedef SPL::BeJwrMXIzKcnMTS02zUlMSs0BACoHAV4 OPort0Type;
    typedef SPL::BeJwrMXIzKcnMTS02zUlMSs0BACoHAV4 OPort1Type;
    
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
    typedef std::bitset<3> OPortBitsetType;
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
  volatile double nextTimestamp[2]; // tuple time, per port

  // for synchronizing threads at punctuation
  uint32_t stopCount[2];
  SPL::Mutex mutexStopped; 
  SPL::CV cvStopped; 
  
  // for synchronizing threads after punctuation
  uint32_t clearCount[2];
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
#endif // SPL_OPER_INSTANCE_SYNCHRONIZEDEVENSTREAM_H_


