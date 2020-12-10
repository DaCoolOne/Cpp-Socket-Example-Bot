

#ifndef STRUCTS_DYNAMIC_BUFFER_HPP
#define STRUCTS_DYNAMIC_BUFFER_HPP

#include "DynamicBuffer.h"

using namespace rlbot;

template <class T>
DynamicBuffer<T>::DynamicBuffer()
{
  m_max_size = 256;
  m_buffer = new T[m_max_size];
}

template <class T>
bool DynamicBuffer<T>::resize(uint16_t size)
{
  bool do_resize = size != m_max_size;
  // bool do_resize = size > m_max_size;
  if(do_resize)
  {
    delete[] m_buffer;
    m_max_size = size;
    m_buffer = new T[m_max_size];
    return true;
  }
  return false;
}

template <class T>
bool DynamicBuffer<T>::upscale(uint16_t size)
{
  // bool do_resize = size != m_max_size;
  bool do_resize = size > m_max_size;
  if(do_resize)
  {
    delete[] m_buffer;
    m_max_size = size;
    m_buffer = new T[m_max_size];
    return true;
  }
  return false;
}

template <class T>
DynamicBuffer<T>::~DynamicBuffer()
{
  delete[] m_buffer;
}

#endif
