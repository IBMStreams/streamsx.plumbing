// eJy9Ul1v2jAU1f0nVdUHeEnCqEBF6kMCZSsQFpZWdHupTOIEb47t2Q4k_1fVzAslEP9Y9VXnJPTrnfpxjJaglMUWacIboaBTkLNJcQg8c832Cc8uydSmw7eHZnpb3N_1N04vqe7_1an66dv_0aOzSvar7z6azsNh9CUhfRKvIh0m65k_19ES5_1xrM1K4YY86KxSYT8d1nvh7_0KLzf8eruYez2fg4mu37q3ZLLaOJZ2_1OTgaVc3vJ_06IhlWV7Nl_1c9f_0780m7q7q_1Sh2HFdsyilOgLB8JgMRpJpSVhKQDYW55h25QYZSrGOzsluikLS9A82xiirVAmKFZ2WLJoKzkjTzg8QjHSCBhnuLJBVLbkSGMzr5604ZxixEzZIYJLs4GVYv3Icy1yPSESVy6Wne7Z9fVZvWAXbgohsVLGaBBckcpxIw_0OnU0VNKgDKNFYwjhXmmcLYv4RrSM5zjrs8BGRAAFZPwWAATy7Dhq7D_1iUUMxQhluYsBiz_0qAGEVuJ1F_0C0khqSChHenAJcS5rG1qgOph_1_0MGZOfjtU3vNA2iANpPX83_1Lm_1_1q06hMm5devtOhFRjxM9vfUR7YRnYaT6tqgFNVTTaiV1L8p67hd7om7j_0oyIH6



#ifndef SPL_OPER_INSTANCE_PUNCTUATEDSPEECH1STREAM_H_
#define SPL_OPER_INSTANCE_PUNCTUATEDSPEECH1STREAM_H_

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
#include "../type/BeJyrNIo3S0pNyy9KNU1MK0ktAgAw9gX7.h"

#include <bitset>

#define MY_OPERATOR PunctuatedSpeech1Stream$OP
#define MY_BASE_OPERATOR PunctuatedSpeech1Stream_Base
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
    
    
protected:
    Mutex $svMutex;
    typedef std::bitset<2> OPortBitsetType;
    OPortBitsetType $oportBitset;
    Mutex $fpMutex;
    SPL::rstring param$position$0;
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
   
private:
   Mutex _mutex;
}; 

} // namespace _Operator
} // namespace SPL

#undef MY_OPERATOR_SCOPE
#undef MY_BASE_OPERATOR
#undef MY_OPERATOR
#endif // SPL_OPER_INSTANCE_PUNCTUATEDSPEECH1STREAM_H_

