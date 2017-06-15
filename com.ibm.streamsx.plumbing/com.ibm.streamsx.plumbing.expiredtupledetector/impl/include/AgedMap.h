/*
# Licensed Materials - Property of IBM
# Copyright IBM Corp. 2017
*/

#ifndef STREAMS_AGED_MAP
#define STREAMS_AGED_MAP

#include <list>
#include <tr1/unordered_map>
#include <cstddef>
#include <inttypes.h>
#include <sys/time.h>
#include <iostream>
#include <SPL/Runtime/Type/List.h>

using namespace std;

namespace com {
namespace ibm {
namespace streamsx {
namespace plumbing {
namespace agedmap {

  template<typename K, typename V>
  class AgedMap
  {
  public:

    typedef std::pair<const K, V> value_type;
    typedef std::list< value_type > value_type_list;

    AgedMap(uint64_t expirationTimeMs) : expirationTimeMs_(expirationTimeMs)
    {

    }

    /// Constant time normal case
    /// Linear time if re-hashing occurs
    /// Inserts the key and value with the current time
    void put(K key, V value, uint16_t replayCount)
    {
      Data newItem;
      newItem.timestamp = getCurrentTime();
      newItem.expireTime = expirationTimeMs_;
      newItem.key = key;
      newItem.value = value;
      newItem.replayCount = replayCount;

      DataListIter listIter = timeOrderedList_.insert(timeOrderedList_.end(), newItem);

      lookupMap_.insert(std::make_pair(key,listIter));
    }

    /// Constant time
    /// Returns boolean indicate if the get was successful
    /// Sets the value if the get was successful
    bool get(const K & key, V & value) const
    {
      LookupMapIter iter = lookupMap_.find(key);
      if(iter != lookupMap_.end())
      {
        value = iter->second;
        return true;
      }
      return false;
    }

    /// Constant time
    /// Returns boolean indicate if the key was found in the map.
    bool find(const K & key) const
    {
      LookupMapIter iter = lookupMap_.find(key);
      if(iter != lookupMap_.end())
      {
        return true;
      }
      return false;
    }

    /// Constant time
    /// Returns boolean indicate if the erase was successful
    /// Sets the value if the erase was successful
    bool erase(const K & key, V & value)
    {
      LookupMapIter iter = lookupMap_.find(key);
      if(iter != lookupMap_.end())
      {
        timeOrderedList_.erase(iter->second);
        value = iter->second->value;
        lookupMap_.erase(iter);
        return true;
      }
      return false;
    }

    bool erase(const K & key)
    {
      LookupMapIter iter = lookupMap_.find(key);
      if(iter != lookupMap_.end())
      {
        timeOrderedList_.erase(iter->second);
        lookupMap_.erase(iter);
        return true;
      }
      return false;
    }

    bool eraseIfExists(const K & key)
    {
    	return(erase(key));
    }

    /// Constant Time
    /// Removes all keys and values
    void clear()
    {
      lookupMap_.clear();
      timeOrderedList_.clear();
      expiredValues_.clear();
    }


    /// Linear Time
    /// Moves all expired entries to the expired list
    void expire()
    {
      uint64_t currentTime = getCurrentTime();
      DataListIter iter = timeOrderedList_.begin();
      while(iter != timeOrderedList_.end())
      {
        Data entry = *iter;
        uint64_t expiredTime = currentTime - entry.expireTime;
        if(entry.timestamp < expiredTime)
        {
          expiredValues_.push_back(entry);
          lookupMap_.erase(entry.key);
          iter = timeOrderedList_.erase(iter);
        }
        else
        {
          break;
        }
      }
    }

    /// Linear Time
    /// Copy all expired entries to the expired list.
    /// After that, delete the expired entries from the lookup map as well as the timeOrderedList.
    /// firstUnexpiredTimestamp returns the earliest timestamp among the un-expired messages
    void expire(uint64_t & firstUnexpiredTimestamp)
    {
      uint64_t currentTime = getCurrentTime();
      firstUnexpiredTimestamp = currentTime;

      DataListIter iter = timeOrderedList_.begin();
      while(iter != timeOrderedList_.end())
      {
    	uint64_t expiredTime = currentTime - iter->expireTime;
        if(iter->timestamp < expiredTime)
        {
          expiredValues_.push_back(*iter);
          lookupMap_.erase(iter->key);
          iter = timeOrderedList_.erase(iter);
        }
        else
        {
          firstUnexpiredTimestamp = iter->timestamp;
          return;
        }
      }
    }

    /// Linear Time
    /// Copy all expired entries to the expired list.
    /// After that, delete the expired entries from the lookup map as well as the timeOrderedList.
    /// This is an overloaded method that takes a boolean argument to decide whether to loop
    /// through all the elements in the time ordered list or only upto the point where a non-expired
    /// entry is found. This method is useful for a situation when the user configured this
    /// operator for expireTime overriding during the normal course of the application's life.
    void expire(bool checkAllListElements)
    {
      uint64_t currentTime = getCurrentTime();
// If you want to measure the looping time, adjust the following
// preprocessor directive with the correct name.
#define PRINT_STATS_XYZ
#ifdef PRINT_STATS
      cout << "Loop start time=" << currentTime << endl;
      size_t sizeOfList = timeOrderedList_.size();
#endif
      DataListIter iter = timeOrderedList_.begin();
      // In the tests done using the Streams QSE virtual machine, it took
      // 23 milliseconds to iterate through a timeOrderedList with a
      // size of 100K elements via the code block below.
      while(iter != timeOrderedList_.end())
      {
        Data entry = *iter;
        uint64_t expiredTime = currentTime - entry.expireTime;
        if(entry.timestamp < expiredTime)
        {
          expiredValues_.push_back(entry);
          lookupMap_.erase(entry.key);
          iter = timeOrderedList_.erase(iter);
        }
        else
        {
          if (checkAllListElements == true) {
        	  // Continue checking all the remaining list elements.
        	  // Go to the next element.
        	  ++iter;
        	  continue;
          } else {
        	  // This element has not expired yet.
        	  // Caller doesn't want us to check the remaining list elements.
        	  // Stop looping now.
        	  break;
          }
        }
      }

#ifdef PRINT_STATS
      uint64_t loopEndTime = getCurrentTime();
      cout << "Loop end time=" << loopEndTime << ", Looping time=" <<
    	(loopEndTime-currentTime) << ", List size=" << sizeOfList << endl;
#endif
    }

    /// Linear Time
    /// Copy all expired entries to the expired list, and renew them
    /// firstUnexpiredTimestamp returns the earliest timestamp among the un-expired messages
    void renew(uint64_t & firstUnexpiredTimestamp)
    {
      uint64_t currentTime = getCurrentTime();
      uint64_t expiredTime = currentTime - expirationTimeMs_;
      firstUnexpiredTimestamp = currentTime;

      DataListIter iter = timeOrderedList_.begin();
      while(iter != timeOrderedList_.end())
      {
        if(iter->timestamp < expiredTime)
        {
          // increase replay count
          iter->replayCount += 1;
          expiredValues_.push_back(*iter);
          // renew timestamp
          iter->timestamp = currentTime;
          ++iter;
        }
        else
        {
          firstUnexpiredTimestamp = iter->timestamp;
          // move all renewed items to the end of the list
          if (iter != timeOrderedList_.begin()) {
            timeOrderedList_.splice(timeOrderedList_.end(), timeOrderedList_, timeOrderedList_.begin(), iter);
          }
          return;
        }
      }
    }

    /// Constant Time
    /// Writes first expired entry into key and value
    /// Returns boolean indicating if there were any entries
    bool getExpiredEntry(K & key, V & value, uint16_t & replayCount)
    {
      if(expiredValues_.empty())
      {
        return false;
      }
      else
      {
        key = expiredValues_.front().key;
        value = expiredValues_.front().value;
        replayCount = expiredValues_.front().replayCount;
        expiredValues_.pop_front();
        return true;
      }
    }

    /// Populates the caller provided list with the current
    /// items stored in the agedMap data structure.
    /// Returns boolean indicating if there were any entries
    bool getTimeOrderedListOfItems(SPL::list<V> & timeOrderedListOfItems)
    {
      if(timeOrderedList_.empty())
      {
        return false;
      }
      else
      {
          DataListIter iter = timeOrderedList_.begin();
          while(iter != timeOrderedList_.end())
          {
        	timeOrderedListOfItems.pushBack(iter->value);
        	++iter;
          }

          return true;
      }
    }

    /// Gets current milliseconds since epoch
    static uint64_t getCurrentTime()
    {
      struct timeval tp;
      ::gettimeofday(&tp, NULL);
      return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
    }

    /// Sets the new expireTime value.
    void setExpireTime(uint64_t expireTime) {
    	expirationTimeMs_ = expireTime;
    }

  private:

    uint64_t expirationTimeMs_;

    /// Struct to hold the key and a timestamp
    /// This allows us to have a nice type to put in the
    /// dequeue for the expiration thread to use
    typedef struct {
      K key;
      V value;
      uint64_t timestamp;
      uint64_t expireTime;
      uint16_t replayCount;
    } Data;

    typedef std::list<Data> DataList;
    typedef typename std::list<Data>::iterator DataListIter;
    DataList timeOrderedList_;

    typedef std::tr1::unordered_map<K, DataListIter> LookupMap;
    typedef typename LookupMap::iterator LookupMapIter;
    LookupMap lookupMap_;

    DataList expiredValues_;
  };
} } } } }

#endif // STREAMS_AGED_MAP
