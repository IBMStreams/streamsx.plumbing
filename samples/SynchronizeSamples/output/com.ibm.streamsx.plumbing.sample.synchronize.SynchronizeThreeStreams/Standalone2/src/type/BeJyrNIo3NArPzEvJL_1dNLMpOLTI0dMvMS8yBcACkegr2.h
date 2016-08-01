// y2_12WindowMarker11FinalMarker


#ifndef BEJYRNIO3NARPZEVJL_1DNLMPOLTI0DMVMS8YBCACKEGR2_H_
#define BEJYRNIO3NARPZEVJL_1DNLMPOLTI0DMVMS8YBCACKEGR2_H_

#include <SPL/Runtime/Type/Enum.h>

#define SELF BeJyrNIo3NArPzEvJL_1dNLMpOLTI0dMvMS8yBcACkegr2

namespace SPL {

class SELF : public Enum
{
public:
   typedef SELF Self;

   static SELF WindowMarker;
   static SELF FinalMarker;
   

   SELF() : Enum(*mappings_) { }
   SELF(uint32_t v) : Enum(*mappings_, v) { }
   SELF(const Self & ot) : Enum(ot) { }
   SELF(const Enum& ot) : Enum(*mappings_) { assignFrom(ot); }
   SELF(const ConstValueHandle & ot) : Enum(ot) { }
   SELF(const std::string & v);
   SELF(const rstring & v);

   virtual Enum * clone() const { return new Self(*this); }

   Self & operator=(const Self & ot) { index_ = ot.index_; return *this; }

   bool operator==(const Self & ot) const { return index_ == ot.index_; }
   bool operator!=(const Self & ot) const { return index_ != ot.index_; }
   bool operator>(const Self & ot) const { return index_ > ot.index_; }
   bool operator>=(const Self & ot) const { return index_ >= ot.index_; }
   bool operator<(const Self & ot) const { return index_ < ot.index_; }
   bool operator<=(const Self & ot) const { return index_ <= ot.index_; }

   bool operator==(const Enum & ot) const { return index_ == ot.getIndex(); }
   bool operator!=(const Enum & ot) const { return index_ != ot.getIndex(); }
   bool operator>(const Enum & ot) const { return index_ > ot.getIndex(); }
   bool operator>=(const Enum & ot) const { return index_ >= ot.getIndex(); }
   bool operator<(const Enum & ot) const { return index_ < ot.getIndex(); }
   bool operator<=(const Enum & ot) const { return index_ <= ot.getIndex(); }

   SELF& operator= (uint32_t v) { index_ = v; return *this; }

private:
   static std::auto_ptr<EnumMappings> mappings_;
   static EnumMappings* initMappings();
};

}  /* namespace SPL */

namespace std { 
    namespace tr1 {
        template<>
        struct hash<SPL::SELF> {
            inline size_t operator()(const SPL::SELF & self) const { return self.hashCode(); }
        };
    }
}

#undef SELF
#endif // BEJYRNIO3NARPZEVJL_1DNLMPOLTI0DMVMS8YBCACKEGR2_H_
