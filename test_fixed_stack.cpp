
#include <iostream>
#include "intrnl_ds.h"

int main() {
  constexpr int STACK_SZ = 5;
  auto stk = stack<int>::make_fixed<STACK_SZ>();
  int elems[STACK_SZ]{
    1,
    2,
    3,
    4,
    5};
  stk->push(elems, STACK_SZ);
  std::cout << stk->pop() << ',' << stk->pop() << '\n';
  return 0;
}
