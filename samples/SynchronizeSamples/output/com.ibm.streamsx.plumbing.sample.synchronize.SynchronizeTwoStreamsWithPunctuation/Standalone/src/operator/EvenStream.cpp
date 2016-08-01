// eJx9kctuwjAQRTW_1grpOTIhQlV2ARuWRtpKh6q4yYQKW_1Ihsh9T5_0rpQkErVyqsZ3Tm_0c8c2ImI71jg0WVZwgVS3pkIYAglvBIMoip1vMJ7gojMl9QktjyWthqv_0gRT5xI9ySqPD4Fb4Nu_0XlSrXlCT9RpTUkkk_01Y_15a3or9uZpTkZrnralHzfLWfHsbdevK7NY36eJDxDabfL6fdgtpvprmARzgrs7AvRllWW10MyNUwCID1pibJ1BJu0Oj_1Geu0v5ETWilVuu9rFlshFoY_0pVdTBa8R7pd2vHHAOlFRJIoNZGMhc_0m4VucS4IVPYI09Y6LVc8hMYEcMXdDAXzQfrD0cVm7pzh29ZhYfCcLG_00uS7wX7LAwZwuAWGuDudRTCKYsFTY5ITSv1F_1Zw8y4BJwPEAuLgkItkVxhZJA_1QT2WqYH




#include "./EvenStream.h"
using namespace SPL::_Operator;

#include <SPL/Runtime/Function/SPLFunctions.h>
#include <SPL/Runtime/Operator/Port/Punctuation.h>

#include <string>

#define MY_OPERATOR_SCOPE SPL::_Operator
#define MY_BASE_OPERATOR EvenStream_Base
#define MY_OPERATOR EvenStream$OP


#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <signal.h>

#include <streams_boost/iostreams/stream.hpp>
#include <streams_boost/iostreams/filtering_streambuf.hpp>
#include <streams_boost/iostreams/device/file_descriptor.hpp>


#include <SPL/Runtime/Common/ApplicationRuntimeMessage.h>
#include <SPL/Toolkit/IOHelper.h>
#include <SPL/Toolkit/RuntimeException.h>

#include <SPL/Runtime/Operator/OperatorMetrics.h>
#include <SPL/Runtime/Utility/LogTraceMessage.h>

using namespace std;
using namespace streams_boost::iostreams;

#define DEV_NULL "/dev/null"


// defines for error checking conditions
#define CHECK_FAIL      \
    if (failedRead)                                   \
        _numInvalidTuples.incrementValueNoLock()

    #define DO_ERROR(msg)                             \
        do { \
         \
          _numInvalidTuples.incrementValueNoLock();   \
          SPLTRACEMSGANDTHROW(SPLRuntimeFileSourceOperator, L_ERROR, msg, SPL_OPER_DBG);  \
         \
        } while (0)
    #define DO_ERROR_FILESOURCE(msg) DO_ERROR(msg)
    #define CHECK_ERROR(msg)                          \
        if (fs.fail() && !getPE().getShutdownRequested()) \
            DO_ERROR(msg)


string MY_OPERATOR_SCOPE::MY_OPERATOR::makeAbsolute(const string & fileName)
{
    namespace bf = streams_boost::filesystem;
    bf::path file(fileName);
    if (!file.is_absolute()) {
        // getDataDirectory will throw an exception if there is no data directory
        file = getPE().getDataDirectory();
        file /= fileName;
    }
    return file.string();
}


MY_OPERATOR_SCOPE::MY_OPERATOR::MY_OPERATOR()
    : MY_BASE_OPERATOR(), _fd(-1),
         
         
        
        
        
           _firstTime(true),
        
	
	  _fd_src(),
	
	_filt_str(),
	_fs(),
        
        _numFilesOpenedMetric(getContext().getMetrics().getCustomMetricByName("nFilesOpened")),
        _numInvalidTuples(getContext().getMetrics().getCustomMetricByName("nInvalidTuples"))
        
        ,_position(0)
	,_crMutex()
	,_reset(false)
	,_initialized(false)
        
{
    _numFilesOpenedMetric.setValueNoLock(0);
    _numInvalidTuples.setValueNoLock(0);
    

         
    

}



void MY_OPERATOR_SCOPE::MY_OPERATOR::prepareToShutdown()
{
    if (_fd >= 0) {
        ::close(_fd);
        _fd = -1;
    }
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::initialize()
{
    
        SPLAPPTRC(L_DEBUG, "starting init delay", SPL_OPER_DBG);
        getPE().blockUntilShutdownRequest(lit$0);
        SPLAPPTRC(L_DEBUG, "finished init delay", SPL_OPER_DBG);
    
     
}



void MY_OPERATOR_SCOPE::MY_OPERATOR::punctAndStatus(const string& pathName)
{
  SPLAPPTRC(L_DEBUG, "punctAndStatus", SPL_OPER_DBG);
  

  
      submit (Punctuation::WindowMarker, 0);
  
  
  
}

void MY_OPERATOR_SCOPE::MY_OPERATOR::processOneFile (const string& path)
{
    SPL::BeJwrMXIzKcnMTS02zUlMSs0BACoHAV4 tuple$;
    
    namespace bf = streams_boost::filesystem;
    bf::path absPath(path);
    if (!absPath.is_absolute()) {
        absPath = getPE().getDataDirectory();
        absPath /= path;
    }
    string pathName = absPath.string();
    SPLAPPTRC(L_DEBUG, "Using '" << pathName << "' as the workload file...", SPL_OPER_DBG);

    int fd = ::open (pathName.c_str(), O_RDONLY | O_LARGEFILE);
    if (fd < 0) {
        
        
        SPLLOGMSG(L_ERROR, SPL_APPLICATION_RUNTIME_FAILED_OPEN_INPUT_FILE(pathName, RuntimeUtility::getErrorNoStr()), SPL_OPER_DBG);
        SPLTRACEMSGANDTHROW(SPLRuntimeFileSourceOperator, L_ERROR, SPL_APPLICATION_RUNTIME_FAILED_OPEN_INPUT_FILE(pathName, RuntimeUtility::getErrorNoStr()), SPL_OPER_DBG);
    }
    SPLAPPTRC(L_DEBUG, "File opened.", SPL_OPER_DBG);
    
    
 	_fd_src.reset(new file_descriptor_source(fd, close_handle));
	file_descriptor_source& fd_src = *_fd_src;
    
    _numFilesOpenedMetric.incrementValueNoLock();
    _filt_str.reset(new filtering_streambuf<input>);
    filtering_streambuf<input>& filt_str = *_filt_str;
    
    
    filt_str.push (fd_src);
    
	_fs.reset (new istream(&filt_str));
	istream& fs = *_fs;
    
    fs.imbue(locale::classic());

    _fd = fd;
    _tupleNumber = 0; 





bool failedRead = false;
if (getPE().getShutdownRequested()) SPLAPPTRC(L_DEBUG, "shutdown requested", SPL_OPER_DBG);
while(!getPE().getShutdownRequested()) {
   
  

  


    _tupleNumber++;
  
    if (SPL::safePeek(fs) == EOF) {
      SPLAPPTRC(L_DEBUG, "Break at safePeek(fs) == EOF", SPL_OPER_DBG);
      break;
    }
  

    bool doSubmit = true;
    try {
        
            // ignore comments and empty lines
            fs >> SPL::skipSpaceTabReturnNewLines;
            while (fs.peek() == '#') {
                std::string dummy;
                std::getline (fs, dummy);
                fs >> SPL::skipSpaceTabReturnNewLines;
            }
            
              if (SPL::safePeek(fs)==EOF) break;
            
            failedRead = false;
            



                
                    unsigned char sep;
                
                    SPL::readCSV<SPL::float64,','>(fs, tuple$.get_time());
                    
                        fs >> SPL::skipSpaceTabs;
                         
                            sep = fs.peek();
                            if (sep != ',') {
                                DO_ERROR (SPL_APPLICATION_RUNTIME_FAILED_READ_CHAR (SPL::printableCharacter(','), SPL::printableCharacter(sep), _tupleNumber, "after reading the attribute time"));
                            }
                            fs >> sep;
                        
                    SPL::readCSV<SPL::rstring,','>(fs, tuple$.get_label());
                    
                CHECK_ERROR (SPL_APPLICATION_RUNTIME_FAILED_READ_TUPLE("tuple<float64 time,rstring label>", _tupleNumber));
                CHECK_FAIL;
                
                 
                    // Check that we read a complete line

                    int eolSep = fs.get();
		    if (eolSep == EOF) {
		      
                    }
                    else if (eolSep != '\n' && eolSep != '\r') {
                        
                        DO_ERROR (SPL_APPLICATION_RUNTIME_FAILED_READ_CHAR ("\\n", SPL::printableCharacter(eolSep), _tupleNumber, "after reading the attribute label"));
		    } 
                
            
        



    } catch (const SPLRuntimeException& e) {
        // Add the filename & tuple number
        DO_ERROR_FILESOURCE(
            SPL_APPLICATION_RUNTIME_FILE_SOURCE_SINK_FILENAME_TUPLE(_tupleNumber, pathName, e.getExplanation()));

    } catch (const std::exception& e) {
        DO_ERROR(SPL_APPLICATION_RUNTIME_EXCEPTION(e.what()));
        _numInvalidTuples.incrementValueNoLock();
        doSubmit = false;
    } catch (...) {
        DO_ERROR(SPL_APPLICATION_RUNTIME_UNKNOWN_EXCEPTION);
        _numInvalidTuples.incrementValueNoLock();
        doSubmit = false;
    }
    if (doSubmit) {
      
        submit (tuple$, 0);
        SPLAPPTRC(L_DEBUG, "Submitted tuple " << _tupleNumber, SPL_OPER_DBG);
      
    }
  

}



    punctAndStatus(pathName);


    if (_fd < 0) {
        // We closed it already.  Prevent an error message
        int newFd = ::open (DEV_NULL, O_RDONLY);
        ::dup2 (newFd, _fd);
        ::close(newFd);
    }
    _fd = -1; // no longer using this

    _fs.reset();
    
    _fd_src.reset();
    
    _filt_str.reset();


}


void MY_OPERATOR_SCOPE::MY_OPERATOR::process (Tuple const& tuple, uint32_t port)
{
    AutoPortMutex am(_mutex, *this);
    const SPL::BeJwrMSy2SMvMSc1LzE0FABy3ASS& t = static_cast<const SPL::BeJwrMSy2SMvMSc1LzE0FABy3ASS&>(tuple);
    if (_firstTime) {
        _firstTime = false;
        initialize();
    }


      
    processOneFile (t.get_filename());
}







static SPL::Operator * initer() { return new MY_OPERATOR_SCOPE::MY_OPERATOR(); }
bool MY_BASE_OPERATOR::globalInit_ = MY_BASE_OPERATOR::globalIniter();
bool MY_BASE_OPERATOR::globalIniter() {
    instantiators_.insert(std::make_pair("EvenStream",&initer));
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
    param$format$0 = "csv";
    addParameterValue ("format", SPL::ConstValueHandle(param$format$0));
    addParameterValue ("initDelay", SPL::ConstValueHandle(lit$0));
    (void) getParameters(); // ensure thread safety by initializing here
    $oportBitset = OPortBitsetType(std::string("01"));
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
            bool forward = false;
            {
                AutoPortMutex $apm($fpMutex, *this);
                $oportBitset.reset(port);
                if ($oportBitset.none()) {
                    $oportBitset.set(1);
                    forward=true;
                }
            }
            if(forward)
                submit(punct, 0);
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


