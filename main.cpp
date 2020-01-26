#include <iostream>
#include <string>
#include "sparsematrix.hpp"
struct point{
  int a;
  int b;
  point(int xx, int yy) : a(xx), b(yy) {}
};
typedef sparse_matrix<int> smatrixi;
typedef sparse_matrix<std::string> smatrixs;
typedef sparse_matrix<point> smatrixp;

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
  test.add(83, 830, 9);
  std::cout << "numero elementi: "<<  test.get_size() << "\n";
  std::cout << "numero righe: "<<  test.get_size_row() << "\n";
  std::cout << "numero colonne: "<<  test.get_size_column() << "\n";
  std::cout << "esiste elemento in (830, 10)? " << test.find(830, 10) << "\n";
  std::cout << "esiste elemento in (83, 100)? " << test.find(80, 100) << "\n";

  smatrixi copy(test);
  test.print();
  //test.clear();
  
  std::cout << "print di copy\n";
  //copy.print();
  std::cout << std::endl;
  smatrixi::iterator i,ie;
  for(i=test.begin(), ie=test.end(); i!=ie; i++)
    std::cout << i->value << std::endl;
  std::cout << std::endl;
  std::cout << test << std::endl;
  std::cout << std::endl;
  std::cout << "test ()\n";
 
  std::cout << test(1, 2) << " " << test(45, 42) << "\n";
  test.print();
  test.clear();
  std::cout << "numero elementi after clear: "<<  test.get_size() << "\n";
  /*
  for(i=copy.begin(), ie=copy.end(); i!=ie; i++)
    i->value += 1;
  for(i=copy.begin(), ie=copy.end(); i!=ie; i++)
    std::cout << i->value << " ("<< i->i <<", " << i->j<< ")"<< std::endl;
  std::cout << copy << std::endl;
  std::cout << std::endl;
  smatrixs test2("default");
  test2.add("ciao", 2, 2);
  test2.add("come", 1, 2);
  test2.add("sta", 0, 1);
  test2.add("andando", 1, 5);
  test2.add("la vita", 1, 1);
  smatrixs::iterator is,ies;
  for(is=test2.begin(), ies=test2.end(); is!=ies; is++)
    std::cout << is->value << std::endl;
  test2.clear();
  std::cout << std::endl;
  smatrixp test3(point(0,0));
  test3.add(point(1,1), 2, 2);
  test3.add(point(1,2), 1, 2);
  test3.add(point(2,7), 0, 1);
  test3.add(point(0,0), 1, 5);
  test3.add(point(5,4), 200, 4000);
  smatrixp::iterator ip,iep;
  for(ip=test3.begin(), iep=test3.end(); ip!=iep; ip++)
    std::cout << ip->value.a << ", " << ip->value.b << std::endl;
  test3.clear();*/
  return 0;
}
