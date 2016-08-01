// eJxtUWFLwzAQ5f5JGX5oUZq2G_1sQRGgHwsSBuh8gWXuugTQJydXZ_1Xpr1zqnki_133r1w7955q_0KWpJLUcV6gKI2GFJL_0pTCLY0adRVbgw8FtykNyzJ_1z4mVTrGxcz3rNHPqPVwlsnx45l5rmGQxMemLelBG0XJy47EIFrDYNMk8OReMrfGd7SRP8iK1qm53Ue_0ZFYxV6tu10WTuj5RG3I1UJEqCNxgQykIROkDTaQ_1pzUDo6zImc3LWE9w4RLDppKvhlMx29X2qTIQ9jjfve9J88QILrhRLGsblf_13FyBiHnA_1BWvZbC0_025dRMMdduD5SK44_1yrH0634Xw9LboyraYwioLrYIg3Sj4BbYiLDm

#include <SPL/Runtime/Utility/Mutex.h>

#ifndef SPL_OPER_INSTANCE_NUMBERSTREAM_H_
#define SPL_OPER_INSTANCE_NUMBERSTREAM_H_

#include <SPL/Runtime/Operator/State/StateHandler.h>
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

#include "../type/BeJwrMcw0zAQABRMBCp.h"


#define MY_OPERATOR NumberStream$OP
#define MY_BASE_OPERATOR NumberStream_Base
#define MY_OPERATOR_SCOPE SPL::_Operator

namespace SPL {
namespace _Operator {

class MY_BASE_OPERATOR : public Operator
{
public:
    
    typedef SPL::BeJwrMcw0zAQABRMBCp OPort0Type;
    
    MY_BASE_OPERATOR();
    
    ~MY_BASE_OPERATOR();
    
    
    
    
    SPL::int32 lit$0;
    SPL::float64 lit$1;
    SPL::int32 lit$2;
    
    
protected:
    Mutex $svMutex;
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



class MY_OPERATOR : public MY_BASE_OPERATOR
  , public StateHandler
{
public:
   MY_OPERATOR();
  
   void allPortsReady();
   void process(uint32_t index);
   virtual void getCheckpoint(NetworkByteBuffer & opstate);
   virtual void restoreCheckpoint(NetworkByteBuffer & opstate);

   virtual void checkpoint(Checkpoint & ckpt);
   virtual void reset(Checkpoint & ckpt);
   virtual void resetToInitialState();

private:
   SPL::BeJwrMcw0zAQABRMBCp _tuple;
   SPL::uint32 _iters;
   Mutex _mutex;
   uint64_t _iterationCount;
   uint64_t IterationCount() const { return _iterationCount;}

   
}; 

} // namespace _Operator
} // namespace SPL

#undef MY_OPERATOR_SCOPE
#undef MY_BASE_OPERATOR
#undef MY_OPERATOR
#endif // SPL_OPER_INSTANCE_NUMBERSTREAM_H_


