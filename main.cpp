#include <iostream>
#include "sparsematrix.hpp"
#include <vector>
typedef sparse_matrix<int> smatrixi;
int main(){
  smatrixi test(0);
  std::cout << test.get_default_value() << "\n";
  test.add(3, 2, 2);
  test.add(1, 1, 2);
  test.add(5, 0, 1);
  test.add(7, 1, 1);
  test.add(8, 1, 1);
  test.add(100, 10, 80);
  test.add(99, 99, 76);
  test.add(1, 10, 20000);
  std::cout << test.get_size() << "\n";
  test.print();
}
