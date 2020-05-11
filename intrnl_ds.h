#pragma once

#ifndef __STACK_H_INCLUDED__
#define __STACK_H_INCLUDED__

#include <stdexcept>

template <typename T>
class stack {
public:
  virtual ~stack() {}
  virtual void push(T elem) = 0;
  virtual void push(const T elems[], std::size_t len) = 0;
  virtual T pop() = 0;

  template <std::size_t SIZE>
  static stack<T>* make_fixed();
  static stack<T>* make_resizable();
};


namespace intrnl_ds {

template <typename T>
struct linked_list {
  T node;
  linked_list *next;
}; 

template <typename T>
using ll = linked_list<T>;

template <typename T, std::size_t SIZE>
class fixed_stack : public stack<T> {
public:
  fixed_stack() : elems(), n(0) {} 
  virtual ~fixed_stack();
  virtual void push(T elem) override;
  virtual void push(const T elems[], std::size_t len) override;
  virtual T pop() override;
private:
  void check_bounds(std::size_t i) const;
  T elems[SIZE]; 
  std::size_t n;
};

template <typename T>
class resizable_stack : public stack<T> {
  static constexpr std::size_t DEFAULT_CAP = 10; 
public:
  resizable_stack() : elems(new T[DEFAULT_CAP]),
    n(0),
    max_cap(DEFAULT_CAP) {}
  virtual ~resizable_stack();
  virtual void push(T elem) override;
  virtual void push(const T elems[], std::size_t len) override;
  virtual T pop() override;
private:
  void resize(std::size_t cap);
  T *elems;
  std::size_t n, max_cap;
};

template <typename T>
class resizable_ll_stack : public stack<T> {
public:

private:
  ll<T> *head; 
  std::size_t n;
};


}
// END NAMESPACE intrnl_ds

// TEMPLATE CLASS stack
template <typename T>
template <std::size_t SIZE>
stack<T>* stack<T>::make_fixed() {
  if (SIZE <= 0) throw std::invalid_argument("Size of stack must be > 0");
  else return new intrnl_ds::fixed_stack<
    T,
    SIZE>{}; 
}

template <typename T>
stack<T>* stack<T>::make_resizable() {
  return new intrnl_ds::resizable_stack<T>{};
}

namespace intrnl_ds {

// TEMPLATE CLASS fixed_stack
template <typename T, std::size_t SIZE>
intrnl_ds::fixed_stack<T,SIZE>::~fixed_stack() {}

template <typename T, std::size_t SIZE>
inline void intrnl_ds::fixed_stack<T,SIZE>::push(T elem) {
  check_bounds(n);
  elems[n++] = elem;
}

template <typename T, std::size_t SIZE>
inline void intrnl_ds::fixed_stack<T,SIZE>::push(
  const T elems[],
  std::size_t len)
{
  for (std::size_t i = 0; i < len; i++) push(elems[i]);  
}

template <typename T, std::size_t SIZE>
inline T intrnl_ds::fixed_stack<T,SIZE>::pop() {
  return elems[--n];
}

template <typename T, std::size_t SIZE>
inline void fixed_stack<T,SIZE>::check_bounds(std::size_t i) const {
  if (i >= n) throw std::out_of_range("Illegal index " + i);
}

// TEMPLATE CLASS resizable_stack
template <typename T>
intrnl_ds::resizable_stack<T>::~resizable_stack() {
  delete[] elems;
}

template <typename T>
void intrnl_ds::resizable_stack<T>::push(T elem) {
  if (n == max_cap) resize(max_cap*2); 
  elems[n++] = elem;
}

template <typename T>
void intrnl_ds::resizable_stack<T>::push(
  const T elems[],
  std::size_t len) 
{
  for (std::size_t i = 0; i < len; i++) push(elems[i]); 
}
  
template <typename T>
T intrnl_ds::resizable_stack<T>::pop() {
  T elem = elems[--n];
  if (n > 0 && n <= max_cap/4) resize(max_cap/2);
  return elem;
} 

template <typename T>
void intrnl_ds::resizable_stack<T>::resize(std::size_t cap) {
  T *a = new T[cap];
  for (auto i = 0; i < n; i++) {
    a[i] = elems[i];
  }
  delete[] elems;
  elems = a;
  max_cap = cap;
}

}
// END NAMESPACE intrnl_ds

template <typename T>
class queue { 
public:
  static queue<T>* make_queue() ;
  ~queue(); 
  void enqueue(T value); 
  T dequeue(); 
private:
  intrnl_ds::ll<T> *head,*tail;
  std::size_t n;
};

// TEMPLATE CLASS queue
template <typename T>
queue<T>* queue<T>::make_queue() {
  return new queue<T>{};
}

template <typename T>
queue<T>::~queue() {
  intrnl_ds::ll<T> *n = head;
  if (!n) return;
  else do {
    auto *tmp = n->next;
    delete n;
    n = tmp; 
  } while (n); 
}

template <typename T>
void queue<T>::enqueue(T value) {
  auto *node = new intrnl_ds::ll<T>{value,nullptr};
  if (tail) tail->next = node;
  else head = node;
  tail = node;
  n++;
}


template <typename T>
T queue<T>::dequeue() {
  intrnl_ds::ll<T> *tmp = head;
  T val = tmp->value;
  head = head->next;
  delete tmp;
  n--;
  return val;
}

#endif // __STACK_H_INCLUDED__
