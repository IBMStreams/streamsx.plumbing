// eJy9Vl1z0zoQHb_1yKwzTB3sosWWnSWoGZpKWQEtSWhKmwEvHseVEYFtGltOkDP8dyfJno9DCzL3Og5XVanfP7p6V0yTsZBSFiG4d5yRLKY4UoJjsZyvPOh0jyGKPIhwbHo4MtIiMlBLoRunGSMIsWqB4aaRulITQSLextyI4RnfQmEEPx346x3MUwZQyhc7qWW6PbhNojOD5bbj99Ob98nQ4HU2H9vj67mN2Y14Ft1dfpu74_1azvvQuQjfwrj86C6_1Npf5Rsbz9cnqfrzQnE8WayiBJ_1_1hZf979uRj_18q_1nnkyH41jtd28vRGep6p6P7Drfk4gzbF0NyefdmfT65Af7FZJp8mMzPTH_06ns4G25E3PPkOl8TiRy2FhU3hQYBCGLsRVGaXE8chDD2D3P4DFM1xcsm4SFbqOJ_1KnPoudU8RgR7FZKvp6nOVyQ_0srt5wIOxlKKa9bmsNlFz5SLF6_0coUu2zTtpRcAlr6Qr0dXi6zdw52JVpHEllPIuvXTktzgx0Hx5KDwNw9CYBEVmBYYBxCNy6EtsyiDAeQAQG93eT1ZXoDmVCGxpKgscCOF8uS1EiGxZJhsY7apxVjhSNY0tCHa2OJaMXKzj1WpsaspuWsEPGWVGIcQ05zTnaUYFI11_19BTgUpJB8yP5_0o7KkzpiL_1ABKCifoq54n5MldAgappNV_1UV2IX6Lqa7_1PnZ7XiT1NZ3aXnmG04ToATGGttoh8Kfh5WkegvW4b_1QPVhmkJCNa3ZurpWIxJB2_1ohA6PlfGPToO29nA9dvviDK15vbrSyrusi8J549RtR_16pTuGtxlrea4zD3S7rSik7oLCG9SVbETaHGcvw6tznYn2027VOqNpuXp4_0y4R_0imFdA40_1TOIp9GPMYqpEICszsomHNsIgESN7UjlN2NZPlPczedVszEDvXTcsXk7Cy6HrlyX4guwEmkUsvmE9IWpb8jLgiaJFmYBZvwGraKruYYpXL43tdtCdhcEOrhO3PlrxIBbajB_1u16P1bgigU5de0ZrWeN0NhQOsO_1e9IAXo1K8BgLy1A_1195AY4LYpstZvx68uAIsoB8Bj0ttq39tHhU7sV18Kg05yGUQ_1ovPmi0hEfwAug83f9wnscdu_0HUJd8hacKVw34Qvhdi1rOPACyK1CpXT8EZTTJafVMp5XUp5OPyg60UV9ypJIIz1d98PChBiF1_0wZYUrwTmb6qeGMM


#include "./Transcript.h"
using namespace SPL::_Operator;

#include <SPL/Runtime/Function/SPLFunctions.h>
#include <SPL/Runtime/Operator/Port/Punctuation.h>


#define MY_OPERATOR_SCOPE SPL::_Operator
#define MY_BASE_OPERATOR Transcript_Base
#define MY_OPERATOR Transcript$OP



static SPL::Operator * initer() { return new MY_OPERATOR_SCOPE::MY_OPERATOR(); }
bool MY_BASE_OPERATOR::globalInit_ = MY_BASE_OPERATOR::globalIniter();
bool MY_BASE_OPERATOR::globalIniter() {
    instantiators_.insert(std::make_pair("Transcript",&initer));
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
    initRTC(*this, lit$3, "lit$3");
    initRTC(*this, lit$4, "lit$4");
    initRTC(*this, lit$5, "lit$5");
    initRTC(*this, lit$6, "lit$6");
    initRTC(*this, lit$7, "lit$7");
    initRTC(*this, lit$8, "lit$8");
    initRTC(*this, lit$9, "lit$9");
    initRTC(*this, lit$10, "lit$10");
    initRTC(*this, lit$11, "lit$11");
    initRTC(*this, lit$12, "lit$12");
    initRTC(*this, lit$13, "lit$13");
    initRTC(*this, lit$14, "lit$14");
    initRTC(*this, lit$15, "lit$15");
    initRTC(*this, lit$16, "lit$16");
    initRTC(*this, lit$17, "lit$17");
    initRTC(*this, lit$18, "lit$18");
    initRTC(*this, lit$19, "lit$19");
    initRTC(*this, lit$20, "lit$20");
    initRTC(*this, lit$21, "lit$21");
    initRTC(*this, lit$22, "lit$22");
    initRTC(*this, lit$23, "lit$23");
    initRTC(*this, lit$24, "lit$24");
    initRTC(*this, lit$25, "lit$25");
    state$filename = (::SPL::Functions::Utility::dataDirectory() + lit$24);
    SPLAPPTRC(L_DEBUG, "Variable: state$filename Value: " << state$filename,SPL_OPER_DBG);
    state$file = lit$25;
    SPLAPPTRC(L_DEBUG, "Variable: state$file Value: " << state$file,SPL_OPER_DBG);
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

void MY_BASE_OPERATOR::tupleLogic(Tuple const & tuple, uint32_t port) {
    IPort0Type const & iport$0 = static_cast<IPort0Type const  &>(tuple);
    AutoPortMutex $apm($svMutex, *this);
    
{
    SPL::int32 id$error = lit$0;
    if ((state$file == lit$1)) 
        {
            state$file = ::SPL::Functions::File::fopen(state$filename, lit$2, id$error);
            ::SPL::Functions::Utility::Assert((SPL::boolean)(id$error == lit$3), (((lit$5 + state$filename) + lit$4) + ::SPL::Functions::Utility::strerror(id$error)), lit$6, lit$7);
        }
    if ((::SPL::Functions::String::length(iport$0.get_phrase()) > lit$8)) 
        {
            const SPL::rstring id$timeline = (((((iport$0.get_indention() + lit$14) + ::com::ibm::streamsx::plumbing::sample::synchronize::SecondsToTimestamp(iport$0.get_start())) + lit$13) + ::SPL::Functions::Utility::formatNumber(iport$0.get_duration(), lit$10, lit$11, (SPL::boolean)lit$12)) + lit$9);
            const SPL::rstring id$textline = ((iport$0.get_indention() + iport$0.get_phrase()) + lit$15);
            ::SPL::Functions::File::fwriteString((id$timeline + id$textline), state$file, id$error);
            ::SPL::Functions::Utility::Assert((SPL::boolean)(id$error == lit$16), (((lit$18 + state$filename) + lit$17) + ::SPL::Functions::Utility::strerror(id$error)), lit$19, lit$20);
        }
}

}


void MY_BASE_OPERATOR::processRaw(Tuple const & tuple, uint32_t port) {
    tupleLogic (tuple, port);
    static_cast<MY_OPERATOR_SCOPE::MY_OPERATOR*>(this)->MY_OPERATOR::process(tuple, port);
}


void MY_BASE_OPERATOR::punctLogic(Punctuation const & punct, uint32_t port) {
    AutoPortMutex $apm($svMutex, *this);
    
{
    SPL::int32 id$error = lit$21;
    if ((state$file != lit$22)) 
        {
            ::SPL::Functions::File::fwriteString(lit$23, state$file, id$error);
            if ((SPL::BeJyrNIo3NArPzEvJL_1dNLMpOLTI0dMvMS8yBcACkegr2(punct-1) == SPL::BeJyrNIo3NArPzEvJL_1dNLMpOLTI0dMvMS8yBcACkegr2::FinalMarker)) 
                {
                    ::SPL::Functions::File::fclose(state$file, id$error);
                }
        }
}

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
    }
}



void MY_BASE_OPERATOR::checkpointStateVariables(NetworkByteBuffer & opstate) const {
    opstate << state$filename;
    opstate << state$file;
}

void MY_BASE_OPERATOR::restoreStateVariables(NetworkByteBuffer & opstate) {
    opstate >> state$filename;
    opstate >> state$file;
}

void MY_BASE_OPERATOR::checkpointStateVariables(Checkpoint & ckpt) {
    ckpt << state$filename;
    ckpt << state$file;
}

void MY_BASE_OPERATOR::resetStateVariables(Checkpoint & ckpt) {
    ckpt >> state$filename;
    ckpt >> state$file;
}

void MY_BASE_OPERATOR::resetStateVariablesToInitialState() {
    state$filename = (::SPL::Functions::Utility::dataDirectory() + lit$24);
    SPLAPPTRC(L_DEBUG, "Variable: state$filename Value: " << state$filename,SPL_OPER_DBG);
    state$file = lit$25;
    SPLAPPTRC(L_DEBUG, "Variable: state$file Value: " << state$file,SPL_OPER_DBG);
}

bool MY_BASE_OPERATOR::hasStateVariables() const {
    return true;
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



