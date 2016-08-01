// eJy9Vl1z0zoQHb_1yKwzTB3sosWWnSWoGZpKWQEtSWhKmwEvHseVEYFtGltOkDP8dyfJno9DCzL3Og5XVanfP7p6V0yTsZBSFiG4d5yRLKY4UoJjsZyvPOh0jyGKPIhwbHo4MtIiMlBLoRunGSMIsWqB4aaRulITQSLextyI4RnfQmEEPx346x3MUwZQyhc7qWW6PbhNojOD5bbj99Ob98nQ4HU2H9vj67mN2Y14Ft1dfpu74_1azvvQuQjfwrj86C6_1Npf5Rsbz9cnqfrzQnE8WayiBJ_1_1hZf979uRj_18q_1nnkyH41jtd28vRGep6p6P7Drfk4gzbF0NyefdmfT65Af7FZJp8mMzPTH_06ns4G25E3PPkOl8TiRy2FhU3hQYBCGLsRVGaXE8chDD2D3P4DFM1xcsm4SFbqOJ_1KnPoudU8RgR7FZKvp6nOVyQ_0srt5wIOxlKKa9bmsNlFz5SLF6_0coUu2zTtpRcAlr6Qr0dXi6zdw52JVpHEllPIuvXTktzgx0Hx5KDwNw9CYBEVmBYYBxCNy6EtsyiDAeQAQG93eT1ZXoDmVCGxpKgscCOF8uS1EiGxZJhsY7apxVjhSNY0tCHa2OJaMXKzj1WpsaspuWsEPGWVGIcQ05zTnaUYFI11_19BTgUpJB8yP5_0o7KkzpiL_1ABKCifoq54n5MldAgappNV_1UV2IX6Lqa7_1PnZ7XiT1NZ3aXnmG04ToATGGttoh8Kfh5WkegvW4b_1QPVhmkJCNa3ZurpWIxJB2_1ohA6PlfGPToO29nA9dvviDK15vbrSyrusi8J549RtR_16pTuGtxlrea4zD3S7rSik7oLCG9SVbETaHGcvw6tznYn2027VOqNpuXp4_0y4R_0imFdA40_1TOIp9GPMYqpEICszsomHNsIgESN7UjlN2NZPlPczedVszEDvXTcsXk7Cy6HrlyX4guwEmkUsvmE9IWpb8jLgiaJFmYBZvwGraKruYYpXL43tdtCdhcEOrhO3PlrxIBbajB_1u16P1bgigU5de0ZrWeN0NhQOsO_1e9IAXo1K8BgLy1A_1195AY4LYpstZvx68uAIsoB8Bj0ttq39tHhU7sV18Kg05yGUQ_1ovPmi0hEfwAug83f9wnscdu_0HUJd8hacKVw34Qvhdi1rOPACyK1CpXT8EZTTJafVMp5XUp5OPyg60UV9ypJIIz1d98PChBiF1_0wZYUrwTmb6qeGMM


#ifndef SPL_OPER_INSTANCE_TRANSCRIPT_H_
#define SPL_OPER_INSTANCE_TRANSCRIPT_H_

#include <SPL/Runtime/Serialization/NetworkByteBuffer.h>
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

#include "../function/com/ibm/streamsx/plumbing/sample/synchronize/SecondsToTimestamp.h"
#include "../type/BeJwlyUEKgDAMBMA3FWzRu_0QfwQYMaFKS7cHfi3idQctSfWJM7BpywOPJsvxCeonxLbmpdTGoW7ZxBqdQTXCA1j6Dv3gBIi4cDB.h"
#include "../type/BeJyrNIo3NArPzEvJL_1dNLMpOLTI0dMvMS8yBcACkegr2.h"


#define MY_OPERATOR Transcript$OP
#define MY_BASE_OPERATOR Transcript_Base
#define MY_OPERATOR_SCOPE SPL::_Operator

namespace SPL {
namespace _Operator {

class MY_BASE_OPERATOR : public Operator
{
public:
    
    typedef SPL::BeJwlyUEKgDAMBMA3FWzRu_0QfwQYMaFKS7cHfi3idQctSfWJM7BpywOPJsvxCeonxLbmpdTGoW7ZxBqdQTXCA1j6Dv3gBIi4cDB IPort0Type;
    
    MY_BASE_OPERATOR();
    
    ~MY_BASE_OPERATOR();
    
    inline void tupleLogic(Tuple const & tuple, uint32_t port);
    void processRaw(Tuple const & tuple, uint32_t port);
    
    inline void punctLogic(Punctuation const & punct, uint32_t port);
    void processRaw(Punctuation const & punct, uint32_t port);
    void punctPermitProcessRaw(Punctuation const & punct, uint32_t port);
    void punctNoPermitProcessRaw(Punctuation const & punct, uint32_t port);
    
    
    
    SPL::int32 lit$0;
    SPL::uint64 lit$1;
    SPL::rstring lit$2;
    SPL::int32 lit$3;
    SPL::rstring lit$4;
    SPL::rstring lit$5;
    SPL::rstring lit$6;
    SPL::uint32 lit$7;
    SPL::int32 lit$8;
    SPL::rstring lit$9;
    SPL::uint32 lit$10;
    SPL::uint32 lit$11;
    SPL::boolean lit$12;
    SPL::rstring lit$13;
    SPL::rstring lit$14;
    SPL::rstring lit$15;
    SPL::int32 lit$16;
    SPL::rstring lit$17;
    SPL::rstring lit$18;
    SPL::rstring lit$19;
    SPL::uint32 lit$20;
    SPL::int32 lit$21;
    SPL::uint64 lit$22;
    SPL::rstring lit$23;
    SPL::rstring lit$24;
    SPL::uint64 lit$25;
    
    SPL::rstring state$filename;
    SPL::uint64 state$file;
    
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
{
public:
   MY_OPERATOR() {}
   
       void getCheckpoint(NetworkByteBuffer & opstate) { checkpointStateVariables(opstate); }
       void restoreCheckpoint(NetworkByteBuffer & opstate) { restoreStateVariables(opstate); }
   
   
}; 

} // namespace _Operator
} // namespace SPL

#undef MY_OPERATOR_SCOPE
#undef MY_BASE_OPERATOR
#undef MY_OPERATOR
#endif // SPL_OPER_INSTANCE_TRANSCRIPT_H_

