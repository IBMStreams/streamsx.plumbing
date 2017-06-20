/*
# Licensed Materials - Property of IBM
# Copyright IBM Corp. 2017
*/

#ifndef STREAMS_AGED_MAP_WRAPPERS_H_
#define STREAMS_AGED_MAP_WRAPPERS_H_

#include <SPL/Runtime/Type/SPLType.h>
#include "AgedMap.h"

namespace com {
namespace ibm {
namespace streamsx {
namespace plumbing {
namespace agedmap {

  /// Create an AgedMap
  /// @param expirationTimeMs, the number of milliseconds until a map entry is considered expired
  /// @param dummyKey a dummy key of type T1
  /// @param dummyValue a dummy value of type T2
  /// @return AgedMap handle, or 0 if failure
  template<class T1, class T2>
  SPL::uint64 agedmapCreate(SPL::uint64 expirationTimeMs, const T1 & dummyKey, const T2 & dummyValue)
  {
    return ((SPL::uint64) new AgedMap<T1, T2>(expirationTimeMs));
  }

  /// Release an AgedMap
  /// @param handle the handle of the AgedMap object
  /// @param dummyKey a dummy key of type T1
  /// @param dummyValue a dummy value of type T2
  template<class T1, class T2>
  void agedmapRelease(SPL::uint64 handle, const T1 & dummykey, const T2 & dummyValue)
  {
    delete ((AgedMap<T1, T2>*) handle);
  }

  /// Puts an entry into the AgedMap, constant time
  /// @param handle the handle of the AgedMap object
  /// @param key Map Key
  /// @param value Map Value
  template<class T1, class T2>
  void agedmapPut(SPL::uint64 handle, T1 key, T2 value, uint16_t replayCount)
  {
    ((AgedMap<T1, T2>*) handle)->put(key, value, replayCount);
  }

  /// Retrieves an entry from the AgedMap, constant time
  /// @param handle the handle of the AgedMap object
  /// @param key Map Key
  /// @param value Map Value reference, retrieved value will be written here
  /// @return boolean indicating if the key was found
  template<class T1, class T2>
  SPL::boolean agedmapGet(SPL::uint64 handle, const T1 & key, T2 & value)
  {
    return ((AgedMap<T1, T2>*) handle)->get(key, value);
  }

  /// Erases the entry specified by the Key, getting the value if present, constant time
  /// @param handle the handle of the AgedMap object
  /// @param key Map Key
  /// @param value Map Value reference, retrieved value will be written here
  /// @return boolean indicating if the key was found
  template<class T1, class T2>
  SPL::boolean agedmapErase(SPL::uint64 handle, const T1 & key, T2 & value)
  {
    return ((AgedMap<T1, T2>*) handle)->erase(key, value);
  }

  /// Erases the entry specified by the Key, getting the value if present, constant time
  /// @param the handle of the AgedMap object
  /// @param key Map Key
  /// @param dummyValue a dummy value of type T2
  /// @return boolean indicating if the key was found
  template<class T1, class T2>
  SPL::boolean agedmapErase(SPL::uint64 handle, const T1 & key, const T2 & dummyValue)
  {
    return ((AgedMap<T1, T2>*) handle)->erase(key);
  }

  /// Erases all entries in the AgedMap
  /// @param the handle of the AgedMap object
  /// @param dummyKey a dummy key of type T1
  /// @param dummyValue a dummy value of type T2
  template<class T1, class T2>
  void agedmapClear(SPL::uint64 handle, const T1 & dummyKey, const T2 & dummyValue)
  {
    ((AgedMap<T1, T2>*) handle)->clear();
  }

  /// Causes us to seperate all expired values from active values
  /// Expired values may be retrieved with agedmapGetExpiredEntry
  /// @param the handle of the AgedMap object
  /// @param dummyKey a dummy key of type T1
  /// @param dummyValue a dummy value of type T2
  template<class T1, class T2>
  void agedmapExpire(SPL::uint64 handle, const T1 & dummyKey, const T2 & dummyValue)
  {
    ((AgedMap<T1, T2>*) handle)->expire();
  }

  /// Causes us to renew all expired values, and copy them into an interna list.
  /// Those expired values may be retrieved with agedmapGetExpiredEntry
  /// @param the handle of the AgedMap object
  /// @param firstUnexpiredTimestamp return the earliest timestamp among the un-expired tuples
  /// @param dummyKey a dummy key of type T1
  /// @param dummyValue a dummy value of type T2
  template<class T1, class T2>
  void agedmapRenew(SPL::uint64 handle, SPL::uint64 & firstUnexpiredTimestamp, const T1 & dummyKey, const T2 & dummyValue)
  {
    ((AgedMap<T1, T2>*) handle)->renew(firstUnexpiredTimestamp);
  }

  /// Retrives the first entry from the already expire list
  /// @param the handle of the AgedMap object
  /// @param key the reference for where the key should be written
  /// @param value the reference for where the value should be written
  /// @param replayCount the reference for where the replayCount should be written
  /// @return boolean indicating if there was an entry populated
  template<class T1, class T2>
  SPL::boolean agedmapGetExpiredEntry(SPL::uint64 handle, T1 & key, T2 & value, SPL::uint16 & replayCount)
  {
    return ((AgedMap<T1, T2>*) handle)->getExpiredEntry(key, value, replayCount);
  }

} } } } }

#endif
