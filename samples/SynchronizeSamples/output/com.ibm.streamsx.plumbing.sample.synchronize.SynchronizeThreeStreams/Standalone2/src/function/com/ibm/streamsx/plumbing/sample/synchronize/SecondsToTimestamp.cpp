#include "SPL/Runtime/Function/SPLFunctions.h"
#include "./SecondsToTimestamp.h"
namespace com { namespace ibm { namespace streamsx { namespace plumbing { namespace sample { namespace synchronize { 
SPL::rstring SecondsToTimestamp (const SPL::float64& elapsed)
{
    const SPL::int32 id$hours = ::SPL::spl_cast<SPL::int32, SPL::float64 >::cast((elapsed / SPL::float64(3600.0)));
    const SPL::int32 id$minutes = ::SPL::spl_cast<SPL::int32, SPL::float64 >::cast(((elapsed - (::SPL::spl_cast<SPL::float64, SPL::int32 >::cast(id$hours) * SPL::float64(3600.0))) / SPL::float64(60.0)));
    const SPL::int32 id$seconds = ::SPL::spl_cast<SPL::int32, SPL::float64 >::cast(::SPL::Functions::Math::fmod(elapsed, SPL::float64(60.0)));
    const SPL::int32 id$milliseconds = ::SPL::spl_cast<SPL::int32, SPL::float64 >::cast((::SPL::Functions::Math::fmod(elapsed, SPL::float64(1.0)) * SPL::float64(1000.0)));
    return (((((((::SPL::spl_cast<SPL::rstring, SPL::int32 >::cast(id$minutes) + SPL::rstring(":")) + ((id$seconds < SPL::int32(10)) ? SPL::rstring("0") : SPL::rstring(""))) + ::SPL::spl_cast<SPL::rstring, SPL::int32 >::cast(id$seconds)) + SPL::rstring(".")) + ((id$milliseconds < SPL::int32(100)) ? SPL::rstring("0") : SPL::rstring(""))) + ((id$milliseconds < SPL::int32(10)) ? SPL::rstring("0") : SPL::rstring(""))) + ::SPL::spl_cast<SPL::rstring, SPL::int32 >::cast(id$milliseconds));
}
} } } } } } 
