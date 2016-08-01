// t6s15outputDirectorys14outputFilenames9indentions6phraseF5startF8duration


#ifndef BEJWLYUEKGDAMBMA3FWZRU_0QFWQYMAFKS7CHFI3IDQCTSFWJM7BPYWOPJSVXCEONXLBMPDTGOW7ZXBQDQTXCA1J6DV3GBII4CDB_H_
#define BEJWLYUEKGDAMBMA3FWZRU_0QFWQYMAFKS7CHFI3IDQCTSFWJM7BPYWOPJSVXCEONXLBMPDTGOW7ZXBQDQTXCA1J6DV3GBII4CDB_H_

#include <SPL/Runtime/Type/Tuple.h>
#include <SPL/Runtime/Type/PrimitiveType.h>
#include <SPL/Runtime/Type/CollectionType.h>
#include <SPL/Runtime/Serialization/NetworkByteBuffer.h>
#include <SPL/Runtime/Serialization/NativeByteBuffer.h>
#include <SPL/Runtime/Serialization/VirtualByteBuffer.h>



#define SELF BeJwlyUEKgDAMBMA3FWzRu_0QfwQYMaFKS7cHfi3idQctSfWJM7BpywOPJsvxCeonxLbmpdTGoW7ZxBqdQTXCA1j6Dv3gBIi4cDB

namespace SPL {

class SELF : public Tuple
{
public:
    static const bool facade = false;

    typedef SELF Self;
    
    typedef SPL::rstring outputDirectory_type;
    typedef SPL::rstring outputFilename_type;
    typedef SPL::rstring indention_type;
    typedef SPL::rstring phrase_type;
    typedef SPL::float64 start_type;
    typedef SPL::float64 duration_type;

    enum { num_attributes = 6 } ;
    
    SELF() : Tuple(), outputDirectory_(), outputFilename_(), indention_(), phrase_(), start_(), duration_() {}
    SELF(const Self & ot) : Tuple(), outputDirectory_(ot.outputDirectory_), outputFilename_(ot.outputFilename_), indention_(ot.indention_), phrase_(ot.phrase_), start_(ot.start_), duration_(ot.duration_) 
      { constructPayload(ot); }
    SELF(const outputDirectory_type & _outputDirectory, const outputFilename_type & _outputFilename, const indention_type & _indention, const phrase_type & _phrase, const start_type & _start, const duration_type & _duration) : Tuple(), outputDirectory_(_outputDirectory), outputFilename_(_outputFilename), indention_(_indention), phrase_(_phrase), start_(_start), duration_(_duration) { }
    SELF(const Tuple & ot, bool typesafe = true) : Tuple() { assignFrom(ot, typesafe); }
    SELF(const ConstValueHandle & ot) : Tuple() { const Tuple & o = ot; assignFrom(o); }

    virtual ~SELF() {}
    
    outputDirectory_type & get_outputDirectory() { return outputDirectory_; }
    const outputDirectory_type & get_outputDirectory() const { return outputDirectory_; }
    void set_outputDirectory(const outputDirectory_type & _outputDirectory) { outputDirectory_ = _outputDirectory; }
    
    outputFilename_type & get_outputFilename() { return outputFilename_; }
    const outputFilename_type & get_outputFilename() const { return outputFilename_; }
    void set_outputFilename(const outputFilename_type & _outputFilename) { outputFilename_ = _outputFilename; }
    
    indention_type & get_indention() { return indention_; }
    const indention_type & get_indention() const { return indention_; }
    void set_indention(const indention_type & _indention) { indention_ = _indention; }
    
    phrase_type & get_phrase() { return phrase_; }
    const phrase_type & get_phrase() const { return phrase_; }
    void set_phrase(const phrase_type & _phrase) { phrase_ = _phrase; }
    
    start_type & get_start() { return start_; }
    const start_type & get_start() const { return start_; }
    void set_start(const start_type & _start) { start_ = _start; }
    
    duration_type & get_duration() { return duration_; }
    const duration_type & get_duration() const { return duration_; }
    void set_duration(const duration_type & _duration) { duration_ = _duration; }
    
    virtual bool equals(const Tuple & ot) const
    {

        if (typeid(*this) != typeid(ot)) { return false; }
        const SELF & o = static_cast<const SELF &>(ot);
        return (*this == o);

    }

    virtual SELF& clear();

    Tuple* clone() const { return new Self(*this); }
    
    void serialize(VirtualByteBuffer & buf) const
    {
        buf << outputDirectory_ << outputFilename_ << indention_ << phrase_ << start_ << duration_;
    }

    template <class BufferType>
    void serialize(ByteBuffer<BufferType> & buf) const
    {        
        buf << outputDirectory_ << outputFilename_ << indention_ << phrase_ << start_ << duration_;
    } 
    
    void serialize(NativeByteBuffer & buf) const
    {
        this->serialize<NativeByteBuffer>(buf);
    }

    void serialize(NetworkByteBuffer & buf) const
    {
        this->serialize<NetworkByteBuffer>(buf);
    }
    
    void deserialize(VirtualByteBuffer & buf)
    {
        buf >> outputDirectory_ >> outputFilename_ >> indention_ >> phrase_ >> start_ >> duration_;
    }

    template <class BufferType>
    void deserialize(ByteBuffer<BufferType> & buf)
    {        
        buf >> outputDirectory_ >> outputFilename_ >> indention_ >> phrase_ >> start_ >> duration_;
    } 

    void deserialize(NativeByteBuffer & buf)
    {
        this->deserialize<NativeByteBuffer>(buf);
    }    

    void deserialize(NetworkByteBuffer & buf)
    {
        this->deserialize<NetworkByteBuffer>(buf);
    }    

    void serialize(std::ostream & ostr) const;

    void serializeWithPrecision(std::ostream & ostr) const;

    void deserialize(std::istream & istr, bool withSuffix = false);
    
    void deserializeWithNanAndInfs(std::istream & istr, bool withSuffix = false);
    
    size_t hashCode() const
    {
        size_t s = 17;
        s = 37 * s + std::tr1::hash<outputDirectory_type >()(outputDirectory_);
        s = 37 * s + std::tr1::hash<outputFilename_type >()(outputFilename_);
        s = 37 * s + std::tr1::hash<indention_type >()(indention_);
        s = 37 * s + std::tr1::hash<phrase_type >()(phrase_);
        s = 37 * s + std::tr1::hash<start_type >()(start_);
        s = 37 * s + std::tr1::hash<duration_type >()(duration_);
        return s;
    }
    
    size_t getSerializedSize() const
    {
        size_t size = sizeof(SPL::float64)+sizeof(SPL::float64);
           size += outputDirectory_.getSerializedSize();
   size += outputFilename_.getSerializedSize();
   size += indention_.getSerializedSize();
   size += phrase_.getSerializedSize();

        return size;

    }
    
    uint32_t getNumberOfAttributes() const 
        { return num_attributes; }

    TupleIterator getBeginIterator() 
        { return TupleIterator(*this, 0); }
    
    ConstTupleIterator getBeginIterator() const 
        { return ConstTupleIterator(*this, 0); }

    TupleIterator getEndIterator() 
        { return TupleIterator(*this, num_attributes); }

    ConstTupleIterator getEndIterator() const 
        { return ConstTupleIterator(*this, num_attributes); }
    
    TupleIterator findAttribute(const std::string & attrb)
    {
        std::tr1::unordered_map<std::string, uint32_t>::const_iterator it = mappings_->nameToIndex_.find(attrb);
        if ( it == mappings_->nameToIndex_.end() ) {
            return this->getEndIterator();
        }
        return TupleIterator(*this, it->second);
    }
    
    ConstTupleIterator findAttribute(const std::string & attrb) const
        { return const_cast<Self*>(this)->findAttribute(attrb); }
    
    TupleAttribute getAttribute(uint32_t index)
    {
        if (index >= num_attributes)
            invalidIndex (index, num_attributes);
        return TupleAttribute(mappings_->indexToName_[index], index, *this);
    }
    
    ConstTupleAttribute getAttribute(uint32_t index) const
        { return const_cast<Self*>(this)->getAttribute(index); }

    ValueHandle getAttributeValue(const std::string & attrb)
        { return getAttributeValueRaw(lookupAttributeName(*mappings_, attrb)->second); }


    ConstValueHandle getAttributeValue(const std::string & attrb) const
        { return const_cast<Self*>(this)->getAttributeValue(attrb); }

    ValueHandle getAttributeValue(uint32_t index) 
        { return getAttributeValueRaw(index); }

    ConstValueHandle getAttributeValue(uint32_t index) const
        { return const_cast<Self*>(this)->getAttributeValue(index); }

    Self & operator=(const Self & ot) 
    { 
        outputDirectory_ = ot.outputDirectory_;
        outputFilename_ = ot.outputFilename_;
        indention_ = ot.indention_;
        phrase_ = ot.phrase_;
        start_ = ot.start_;
        duration_ = ot.duration_; 
        assignPayload(ot);
        return *this; 
    }

    Self & operator=(const Tuple & ot) 
    { 
        assignFrom(ot); 
        return *this; 
    }

    void assign(Tuple const & tuple)
    {
        *this = static_cast<SELF const &>(tuple);
    }


    bool operator==(const Self & ot) const 
    {  
       return ( 
                outputDirectory_ == ot.outputDirectory_ && 
                outputFilename_ == ot.outputFilename_ && 
                indention_ == ot.indention_ && 
                phrase_ == ot.phrase_ && 
                start_ == ot.start_ && 
                duration_ == ot.duration_  
              ); 
    }
    bool operator==(const Tuple & ot) const { return equals(ot); }

    bool operator!=(const Self & ot) const { return !(*this == ot); }
    bool operator!=(const Tuple & ot) const { return !(*this == ot); }


    void swap(SELF & ot) 
    { 
        std::swap(outputDirectory_, ot.outputDirectory_);
        std::swap(outputFilename_, ot.outputFilename_);
        std::swap(indention_, ot.indention_);
        std::swap(phrase_, ot.phrase_);
        std::swap(start_, ot.start_);
        std::swap(duration_, ot.duration_);
      std::swap(payload_, ot.payload_);
    }

    void reset()
    { 
        *this = SELF(); 
    }

    void normalizeBoundedSetsAndMaps(); 

    const std::string & getAttributeName(uint32_t index) const
    {
        if (index >= num_attributes)
            invalidIndex (index, num_attributes);
        return mappings_->indexToName_[index];
    }

    const std::tr1::unordered_map<std::string, uint32_t> & getAttributeNames() const 
        { return mappings_->nameToIndex_; }

protected:

    ValueHandle getAttributeValueRaw(const uint32_t index)
    {
        if (index >= num_attributes)
            invalidIndex(index, num_attributes);
        const TypeOffset & t = mappings_->indexToTypeOffset_[index];
        return ValueHandle((char*)this + t.getOffset(), t.getMetaType(), &t.getTypeId());
    }

private:
    
    outputDirectory_type outputDirectory_;
    outputFilename_type outputFilename_;
    indention_type indention_;
    phrase_type phrase_;
    start_type start_;
    duration_type duration_;

    static std::auto_ptr<TupleMappings> mappings_;
    static TupleMappings* initMappings();
};

inline VirtualByteBuffer & operator>>(VirtualByteBuffer & sbuf, SELF & tuple) 
    { tuple.deserialize(sbuf); return sbuf; }
inline VirtualByteBuffer & operator<<(VirtualByteBuffer & sbuf, SELF const & tuple) 
    { tuple.serialize(sbuf); return sbuf; }

template <class BufferType>
inline ByteBuffer<BufferType> & operator>>(ByteBuffer<BufferType> & sbuf, SELF & tuple) 
    { tuple.deserialize(sbuf); return sbuf; }
template <class BufferType>
inline ByteBuffer<BufferType> & operator<<(ByteBuffer<BufferType> & sbuf, SELF const & tuple) 
    { tuple.serialize(sbuf); return sbuf; }

inline NetworkByteBuffer & operator>>(NetworkByteBuffer & sbuf, SELF & tuple) 
    { tuple.deserialize(sbuf); return sbuf; }
inline NetworkByteBuffer & operator<<(NetworkByteBuffer & sbuf, SELF const & tuple) 
    { tuple.serialize(sbuf); return sbuf; }

inline NativeByteBuffer & operator>>(NativeByteBuffer & sbuf, SELF & tuple) 
    { tuple.deserialize(sbuf); return sbuf; }
inline NativeByteBuffer & operator<<(NativeByteBuffer & sbuf, SELF const & tuple) 
    { tuple.serialize(sbuf); return sbuf; }

template<>
inline std::ostream & serializeWithPrecision(std::ostream & ostr, SELF const & tuple) 
    { tuple.serializeWithPrecision(ostr); return ostr; }
inline std::ostream & operator<<(std::ostream & ostr, SELF const & tuple) 
    { tuple.serialize(ostr); return ostr; }
inline std::istream & operator>>(std::istream & istr, SELF & tuple) 
    { tuple.deserialize(istr); return istr; }
template<>
inline void deserializeWithSuffix(std::istream & istr, SELF  & tuple) 
{ tuple.deserialize(istr,true);  }
inline void deserializeWithNanAndInfs(std::istream & istr, SELF  & tuple, bool withSuffix = false) 
{ tuple.deserializeWithNanAndInfs(istr,withSuffix);  }



}  // namespace SPL

namespace std
{
    inline void swap(SPL::SELF & a, SPL::SELF & b)
    {
        a.swap(b);
    }
};

namespace std { 
    namespace tr1 {
        template <>
        struct hash<SPL::SELF> {
            inline size_t operator()(const SPL::SELF & self) const 
                { return self.hashCode(); }
        };
    }
}

#undef SELF
#endif // BEJWLYUEKGDAMBMA3FWZRU_0QFWQYMAFKS7CHFI3IDQCTSFWJM7BPYWOPJSVXCEONXLBMPDTGOW7ZXBQDQTXCA1J6DV3GBII4CDB_H_ 



