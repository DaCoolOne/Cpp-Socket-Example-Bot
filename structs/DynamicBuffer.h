

#ifndef STRUCTS_DYNAMIC_BUFFER_H
#define STRUCTS_DYNAMIC_BUFFER_H

#include <cstdint>

namespace rlbot {

template <class T>
class DynamicBuffer
{
  private:
    T* m_buffer;
    uint16_t m_max_size;

    // Disallow copying of Dynamic buffers.
    // DynamicBuffer& operator=(const DynamicBuffer & source);
    // DynamicBuffer(DynamicBuffer & source);

  public:
    DynamicBuffer();
    ~DynamicBuffer();

    bool resize(uint16_t size);
    bool upscale(uint16_t size);
    T* get() const { return m_buffer; };
};

}

#include "DynamicBuffer.hpp"

#endif

