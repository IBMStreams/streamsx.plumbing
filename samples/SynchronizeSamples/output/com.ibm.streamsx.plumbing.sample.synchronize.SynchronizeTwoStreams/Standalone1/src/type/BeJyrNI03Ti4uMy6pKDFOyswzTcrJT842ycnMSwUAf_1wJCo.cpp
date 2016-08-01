// y5_3csv3txt3bin5block4line


#include "BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo.h"

#define SELF BeJyrNI03Ti4uMy6pKDFOyswzTcrJT842ycnMSwUAf_1wJCo

using namespace SPL;

std::auto_ptr<EnumMappings> SELF::mappings_(SELF::initMappings());


SELF SELF::csv(0);
SELF SELF::txt(1);
SELF SELF::bin(2);
SELF SELF::block(3);
SELF SELF::line(4);

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
      std::string s("csv");
      em->nameToIndex_.insert(std::make_pair(s, 0));
      em->indexToName_.push_back(s);
   }
   
   {
      std::string s("txt");
      em->nameToIndex_.insert(std::make_pair(s, 1));
      em->indexToName_.push_back(s);
   }
   
   {
      std::string s("bin");
      em->nameToIndex_.insert(std::make_pair(s, 2));
      em->indexToName_.push_back(s);
   }
   
   {
      std::string s("block");
      em->nameToIndex_.insert(std::make_pair(s, 3));
      em->indexToName_.push_back(s);
   }
   
   {
      std::string s("line");
      em->nameToIndex_.insert(std::make_pair(s, 4));
      em->indexToName_.push_back(s);
   }
   
   return em;
}
