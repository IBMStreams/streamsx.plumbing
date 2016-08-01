// eJy9UsFO6zAQ1P4JIA7tJWkoaqVKHBpKgUIFJTz1wQW5ySY1cmxjO23C1_0OkTZ4o8OCEfPJoZ3dnZrVkjkJGDBWcsMFgnPHQCAUedOzz4MBxXFNIdH2crFnx5_0wqGQ2n_1nTYHc9f77Knzixezx6mZHwV9MOLmHZpNAtNEM8n074vi_1XN7USv8lMUPL9epDK6Pxfz_1mPuv0Sz_07_0nQ_0_05N1p1E_1_0SHocj31ke2KFHwKg57EBwez0YKG0U5QlUmLeDgbsUKbr2iyTVEa7chJr6mzuSZenCFrqapJKhdoOCh0slOH3FYAtFxBDggmMpNqbMYKm9GrMQgiHh9tuiUii7kpOgeRKZkZkZUYWlUUWrvbd_1sldt3IazXCrU2npZGbilbdr9hoFAQVXBAfRgZ1GobdvgY8qQkxQbmPIIeXkGDSKXiuh_1BdoQZSBmgpjeMUSZqo6mAUrB4tcFp1bw11I92DmZJpPPo_1zKmx_11qVm2zUcvP3Twthe9Y_1I3kzbVdsL7MBpWDbxnVcWW9Elm_1_0XV9a22DfcNAFteBy



#ifndef SPL_OPER_INSTANCE_INDENTEDPUNCTUATEDSPEECH1STREAM_H_
#define SPL_OPER_INSTANCE_INDENTEDPUNCTUATEDSPEECH1STREAM_H_

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

#define MY_OPERATOR IndentedPunctuatedSpeech1Stream$OP
#define MY_BASE_OPERATOR IndentedPunctuatedSpeech1Stream_Base
#define MY_OPERATOR_SCOPE SPL::_Operator

namespace SPL {
namespace _Operator {

class MY_BASE_OPERATOR : public Operator
{
public:
    
    typedef SPL::BeJwlyUEKgDAMBMA3FWzRu_0QfwQYMaFKS7cHfi3idQctSfWJM7BpywOPJsvxCeonxLbmpdTGoW7ZxBqdQTXCA1j6Dv3gBIi4cDB IPort0Type;
    typedef SPL::BeJwlyUEKgDAMBMA3FWzRu_0QfwQYMaFKS7cHfi3idQctSfWJM7BpywOPJsvxCeonxLbmpdTGoW7ZxBqdQTXCA1j6Dv3gBIi4cDB OPort0Type;
    
    MY_BASE_OPERATOR();
    
    ~MY_BASE_OPERATOR();
    
    inline void tupleLogic(Tuple const & tuple, uint32_t port);
    void processRaw(Tuple const & tuple, uint32_t port);
    
    inline void punctLogic(Punctuation const & punct, uint32_t port);
    void processRaw(Punctuation const & punct, uint32_t port);
    void punctPermitProcessRaw(Punctuation const & punct, uint32_t port);
    void punctNoPermitProcessRaw(Punctuation const & punct, uint32_t port);
    
    inline void submit(Tuple & tuple, uint32_t port)
    {
        Operator::submit(tuple, port);
    }
    inline void submit(Punctuation const & punct, uint32_t port)
    {
        Operator::submit(punct, port);
    }
    
    
    
    SPL::rstring lit$0;
    SPL::rstring lit$1;
    
    
protected:
    Mutex $svMutex;
    typedef std::bitset<2> OPortBitsetType;
    OPortBitsetType $oportBitset;
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


class MY_OPERATOR : public MY_BASE_OPERATOR
{
public:
   MY_OPERATOR() {}
  
   void process(Tuple const & tuple, uint32_t port);
   void process(Punctuation const & punct, uint32_t port);
   
}; 

} // namespace _Operator
} // namespace SPL

#undef MY_OPERATOR_SCOPE
#undef MY_BASE_OPERATOR
#undef MY_OPERATOR
#endif // SPL_OPER_INSTANCE_INDENTEDPUNCTUATEDSPEECH1STREAM_H_

