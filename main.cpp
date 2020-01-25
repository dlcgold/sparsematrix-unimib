#include <iostream>
#include "sparsematrix.hpp"

typedef sparse_matrix<int> smatrixi;
int main(){
  smatrixi test(0);
  //std::cout << test.get_default_value() << "\n";
  test.add(3, 2, 2);
  test.add(1, 1, 2);
  test.add(5, 0, 1);
  test.add(7, 1, 1);
  test.add(8, 1, 1);
  test.add(90, 830, 10);
  test.add(100, 10, 80);
  test.add(99, 22, 76);
  test.add(1, 10, 20000);
  test.add(1, 30, 20000);
  test.add(54, 1, 4);
  test.add(42, 3, 1);
  test.add(1, 0, 1);
  test.add(67, 20, 0);
  test.add(1, 0, 0);
  test.add(2, 0, 2);
  test.add(3, 0, 0);
  std::cout << "numero elementi: "<<  test.get_size() << "\n";
  std::cout << "numero righe: "<<  test.get_size_row() << "\n";
  std::cout << "numero colonne: "<<  test.get_size_column() << "\n";
  std::cout << "esiste elemento in (830, 10)? " << test.find(830, 10) << "\n";
  std::cout << "esiste elemento in (83, 100)? " << test.find(80, 100) << "\n";

  smatrixi copy(test);
  test.print();
  //test.clear();
  std::cout << "numero elementi after clear: "<<  test.get_size() << "\n";
  std::cout << "print di copy\n";
  copy.print();
  smatrixi::iterator i,ie;
  for(i=test.begin(), ie=test.end(); i!=ie; ++i)
    std::cout << i->value << std::endl;
  // std::cout << i->value << std::endl;
  // std::cout << test<< std::endl;
  return 0;
}
