// y2_6before5after


#include "BeJyrNIo3S0pNyy9KNU1MK0ktAgAw9gX7.h"

#define SELF BeJyrNIo3S0pNyy9KNU1MK0ktAgAw9gX7

using namespace SPL;

std::auto_ptr<EnumMappings> SELF::mappings_(SELF::initMappings());


SELF SELF::before(0);
SELF SELF::after(1);

SELF::SELF(const std::string & v)
: Enum(*mappings_)
{
    // initialize from a string value
    this->Enum::operator=(v);
}

SELF::SELF(const rstring & v)
: Enum(*mappings_)
{
    // initialize from a string value
    this->Enum::operator=(v);
}


EnumMappings* SELF::initMappings()
{
   EnumMappings* em = new EnumMappings();
   // initialize the mappings 
   {
      std::string s("before");
      em->nameToIndex_.insert(std::make_pair(s, 0));
      em->indexToName_.push_back(s);
   }
   
   {
      std::string s("after");
      em->nameToIndex_.insert(std::make_pair(s, 1));
      em->indexToName_.push_back(s);
   }
   
   return em;
}
