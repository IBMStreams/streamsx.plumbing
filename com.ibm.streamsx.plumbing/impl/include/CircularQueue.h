/* begin_generated_IBM_copyright_prolog                             */
/*                                                                  */
/* This is an automatically generated copyright prolog.             */
/* After initializing,  DO NOT MODIFY OR MOVE                       */
/* **************************************************************** */
/* Licensed Materials - Property of IBM                             */
/* 5724-Y95                                                         */
/* (C) Copyright IBM Corp.  2010, 2012    All Rights Reserved.      */
/* US Government Users Restricted Rights - Use, duplication or      */
/* disclosure restricted by GSA ADP Schedule Contract with          */
/* IBM Corp.                                                        */
/*                                                                  */
/* end_generated_IBM_copyright_prolog                               */
/*! This is a lock-free circular queue for single consumer thread and single
producer thread setups.

Below is an example use:
Producer:

\code
   if(!q.full()) {
     T & x = q.rear();
     writeData(x);
     q.push_back();
   }
\endcode

Consumer:
\code
   if(!q.empty()) {
     T & x = q.front();
     readOrWriteData(x);
     q.pop_front();
   }
\endcode
*/
#ifndef SPL_TOOLKIT_CIRCULAR_QUEUE
#define SPL_TOOLKIT_CIRCULAR_QUEUE

#define compiler_memory_barrier()     asm volatile("" ::: "memory")

#if defined(__i386__) || defined(__x86_64__)
  #define read_memory_barrier()       asm volatile("lfence" ::: "memory")
  #define write_memory_barrier()      asm volatile("sfence" ::: "memory")
  #define full_memory_barrier()       __sync_synchronize();
#elif defined(__PPC__) || defined(__PPC64__)
  #define read_memory_barrier()       asm volatile("isync" ::: "memory")
  #define write_memory_barrier()      asm volatile("lwsync" ::: "memory")
  #define full_memory_barrier()       __sync_synchronize();
#else
   #error "Unsupported architecture, CircularQueue is not designed to work with this"
#endif

template <typename T>
class CircularQueue
{
private:
    struct QueueEntry 
    {
        T data;
    };
public:
    /// Constructor.
    /// @param capacity capacity of the buffer
    CircularQueue(size_t capacity)
        : head_(0), tail_(0), capacity_(capacity+1)
    {
        buffer_ = new QueueEntry[capacity_];
    }

    /// Destructor.
    ~CircularQueue() 
    {
        delete [] buffer_; 
    }

    /// Check if the queue is empty
    /// Return true if the queue is empty
    bool empty() const
    {
        return head_ == tail_;
    }

    /// Get the item at the front of the queue.
    /// @pre !empty()
    /// @return the item at the front of the queue
    T & front()
    {
#if defined(__i386__) || defined(__x86_64__)
        compiler_memory_barrier();
#elif defined(__PPC__) || defined(__PPC64__)
        read_memory_barrier();
#endif
        return buffer_[head_].data;
    }

    /// Pop the item at the front of the queue.
    /// @pre !empty()
    void pop_front()
    {
#if defined(__i386__) || defined(__x86_64__)
        compiler_memory_barrier();
#elif defined(__PPC__) || defined(__PPC64__)
        write_memory_barrier();
#endif
        head_ = inc(head_);
    }

    /// Check if the queue is full
    /// Return true if the queue is full
    bool full() const
    {
        return inc(tail_) == head_;
    }

    /// Get the item at the rear of the queue.
    /// @pre !empty()
    /// @return the item at the front of the queue
    T & rear()
    {
        return buffer_[tail_].data;
    }

    /// Add an item at the end of the queue.
    /// @pre !full()
    void push_back()
    {
#if defined(__i386__) || defined(__x86_64__)
        compiler_memory_barrier();
#elif defined(__PPC__) || defined(__PPC64__)
        write_memory_barrier();
#endif
        tail_ = inc(tail_);
    }

    /// Get the capacity of the queue
    size_t getCapacity() const 
    {
        return capacity_;
    }

    size_t getSize() const
    {
        if (head_ <= tail_) {
            return tail_ - head_;
        }
        else {
            return (capacity_ - head_) + tail_ - 1;
        }
    }

    T & getRawData(size_t i) 
    { 
        return buffer_[i].data; 
    }
private:
    size_t head_;
    size_t tail_;
    QueueEntry * buffer_ __attribute__ ((aligned (256)));
    const size_t capacity_;
    size_t inc(size_t index) const
    {
        return (index + 1) % capacity_;
    }
};

#endif /* SPL_TOOLKIT_CIRCULAR_QUEUE */

