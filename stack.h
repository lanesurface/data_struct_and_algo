#pragma once

#ifndef __QUEUE_H_INCLUDED__
#define __QUEUE_H_INCLUDED__

#include <stdexcept>

/**
 * A first-in last-out container which provides a mechanism for preserving
 * the relative order of elements that are inserted. Adding elements to the
 * queue and then retrieving them at some later point in time ensures that
 * this container provides them in the same order that they were inserted.
 *
 * Use one of the static factory functions, `make_fixed` or `make_resizable`
 * to create an object conforming to this interface.
 */
template <typename T>
class stack {
public:
  virtual ~stack() {}
  virtual void push(const T elem) = 0;
  virtual void push(const T elems[], int len) = 0;
  virtual T pop() = 0;

  template <std::size_t SIZE>
  static stack<T>* make_fixed();
  static stack<T>* make_resizable();
};

template <typename T, std::size_t SIZE>
class fixed_stack : public stack<T> {
  
public:
   
private:
  T elems[SIZE]; 
  std::size_t n{};
};

template <typename T>
class resizable_stack : public stack<T> {
  static const std::size_t DEFAULT_CAP = 10; 
public:
  resizable_stack() : elems(new T[DEFAULT_CAP]),
    n(0),
    max_cap(DEFAULT_CAP) {}
  virtual ~resizable_stack();
  virtual void push(const T elem) override;
  virtual void push(const T elems[], int len) override;
  virtual T pop() override;
private:
  void resize(const std::size_t cap);
  T *elems;
  std::size_t n, max_cap;
};

// TEMPLATE CLASS stack
template <typename T>
template <std::size_t SIZE>
stack<T>* stack<T>::make_fixed() {
  if (SIZE <= 0) throw std::invalid_argument("Size of queue must be > 0");
  else return new fixed_stack<
    T,
    SIZE>{}; 
}

template <typename T>
stack<T>* stack<T>::make_resizable() {
  return new resizable_stack<T>();
}

// TEMPLATE CLASS resizable_stack
template <typename T>
resizable_stack<T>::~resizable_stack() {
  delete[] elems;
}

template <typename T>
void resizable_stack<T>::push(const T elem) {
  if (n == max_cap) resize(max_cap*2); 
  elems[n++] = elem;
}

template <typename T>
void resizable_stack<T>::push(
  const T elems[],
  int len) 
{
  for (std::size_t i = 0; i < len; i++) push(elems[i]); 
}
  
template <typename T>
T resizable_stack<T>::pop() {
  T elem = elems[--n];
  if (n > 0 && n <= max_cap/4) resize(max_cap/2);
  return elem;
} 

template <typename T>
void resizable_stack<T>::resize(const std::size_t cap) {
  T *a = new T[cap];
  for (auto i = 0; i < n; i++) {
    a[i] = elems[i];
  }
  delete[] elems;
  elems = a;
}

#endif // __QUEUE_H_INCLUDED__
