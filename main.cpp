#include <iostream>
#include <string>
#include <cassert>
#include "sparsematrix.hpp"


struct point{
  int a;
  int b;
  point(int xx, int yy) : a(xx), b(yy) {}
};



struct positive {
  bool operator()(int a) const {
    return a>0;
  }
};

struct is_defaultf {
  bool operator()(float a) const {
    return a==0.;
  }
};

struct pointxMax {
  bool operator()(point p) const {
    return p.a < p.b;
  }
};
typedef sparse_matrix<int> smatrixi;
typedef sparse_matrix<std::string> smatrixs;
typedef sparse_matrix<point> smatrixp;
typedef sparse_matrix<float> smatrixf;


void test_fondamentali(){
  std::cout << "test matrice float 3x3 (valore default 0)\n";
  smatrixf floatNM(0, 3, 3);
  for(int i = 0; i < floatNM.get_size_row(); i++){
    for(int j = 0; j < floatNM.get_size_column(); j++){
      if(i != j){
        if(j != 0 ){
	  floatNM.add((float)(i+j+7) / (-1 * j * 3), i, j);
	}else{
	  floatNM.add(i + (j * (-1)), i, j);
	}
      }
    }
  }
  // assert(floatNM.get_size_row() == 3);
  // assert(floatNM.get_size_column() == 3);
  // assert(floatNM.get_size_row() == 3);
  // assert(floatNM.get_size_column() == 3);
  std::cout << "\ntest stampa matrice float con accesso mediante operator()\n";
  printdef(floatNM, floatNM.get_size_row(), floatNM.get_size_column());
  
  positive pos;
  int count = evaluate(floatNM, pos);
  std::cout << "\ntest evaluate (numero positivi) matrice float \n";
  assert(count == 2);
  std::cout << count << " = " << 2 << "\n";
  std::cout << "\ntest stampa matrice float con accesso mediante iteratore\n";
  smatrixf::iterator i, ie;
  for(i = floatNM.begin(), ie= floatNM.end(); i!=ie; i++){
    std::cout << i->v << std::endl;
  }
  std::cout << "\ntest cast da matrice float a matrice di interi\n";
  smatrixi interaNM(floatNM);
  std::cout << "\ntest stampa matrice intera con accesso mediante operator()\n";
  printdef(interaNM, interaNM.get_size_row(), interaNM.get_size_column());
  
  count = evaluate(interaNM, pos);
  std::cout << "\ntest evaluate (numero positivi) matrice intera \n";
  assert(count == 2);
  std::cout << count << " = " << 2 << "\n";
  std::cout << "\ntest stampa matrice intera con accesso mediante iteratore\n";
  smatrixi::iterator iu, ieu;
  for(iu = interaNM.begin(), ieu = interaNM.end(); iu!=ieu; iu++){
    std::cout << iu->v << std::endl;
  }
  std::cout << "\ntest assegnamento\n";
  smatrixf floatNM2 = floatNM;
  printdef(floatNM2, floatNM2.get_size_row(), floatNM2.get_size_column());
  std::cout << "\ntest assegnamento con iteratore\n";

  smatrixf::iterator testBegin;
  testBegin = floatNM.begin();
  std::cout << testBegin->v << "\n";
}

void test_vuota(const smatrixi vuota){
  std::cout << "\n\ntest stampa matrice vuota\n";
  std::cout << vuota << std::endl;
  std::cout << "\ntest evaluate matrice vuota\n";
  positive pos;
  int count = evaluate(vuota, pos);
  assert(count == 0);
  std::cout << "valori accettabili: " << count << "\n";
}

void test_point(){
  std::cout << "\ntest stampa matrice di point con iteratore\n";
  smatrixp testp(point(0,0));
 
  std::cout << "\n";
  testp.add(point(1,1), 2, 5);
  testp.add(point(1,2), 1, 2);
  testp.add(point(2,7), 0, 10000);
  testp.add(point(0,0), 1, 5);
  testp.add(point(5,4), 200, 4000);
  
  smatrixp::iterator ip,iep;
   for(ip=testp.begin(), iep=testp.end(); ip!=iep; ip++)
     std::cout << ip->v.a << ", " << ip->v.b << std::endl;
  std::cout << "\ntest stampa matrice di point assegnata\n";
  smatrixp testpp = testp;
  testp.clear();
  for(ip=testpp.begin(), iep=testpp.end(); ip!=iep; ip++)
    std::cout << ip->v.a << ", " << ip->v.b << std::endl;
  pointxMax max;
  int count = evaluate(testpp, max);
  assert(count == 2);
  std::cout << "valori accettabili: " << count << " = 2\n";
  testpp.clear();
}
int main(){
  
  /*test.add(-90, 830, 10);
  test.add(100, 10, 80);
  test.add(99, 22, 76);
  test.add(1, 10, 20000);
  test.add(-1, 30, 20000);
  test.add(54, 1, 4);
  test.add(42, 3, 1);
  test.add(1, 0, 1);
  test.add(-67, 20, 0);
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
  
  
  std::cout << "\nprint di copy\n";
  copy.print();
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
  positive predPos;
  int countPositive = evaluate(test, predPos);
  std::cout << "ho " << countPositive << " numeri positivi\n";
  test.clear();
  std::cout << "numero elementi after clear: "<<  test.get_size() << "\n";*/
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
  /*smatrixf test4(0.);
  test4.add(4.6, 0, 3);
  test4.add(4.4, 4, 3);
  test4.add(76, 67, 3);
  test4.add(3., 0, 375);
  test4.add(5.0, 220, 23);
  test4.print();
  std::cout << test4 << std::endl;
  smatrixf::iterator ip, iep;
  for(ip=test4.begin(), iep=test4.end(); ip!=iep; ip++)
    std::cout << ip->value<< std::endl;
   smatrixi test5(test4);
     std::cout << test5 << std::endl;
  is_defaultf defF;
  std::cout << "ho " << evaluate(test4, defF) << " elementi di default";*/

  test_fondamentali();
  smatrixi costante(0);
  test_vuota(costante);
  test_point();
  return 0;
}
