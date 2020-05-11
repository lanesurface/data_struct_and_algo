
#include <iostream>
#include "intrnl_ds.h"

int main() {
  auto stk = stack<int>::make_resizable();
  int elems[]{1, 2, 3};
  stk->push(elems, 3);
  std::cout << stk->pop() << ',' << stk->pop() << '\n'; 
  return 0;
}
