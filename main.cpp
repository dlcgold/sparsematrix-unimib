#include <iostream>
#include <string>
#include <cassert>
#include "sparsematrix.h"


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
  assert(floatNM.get_size_row() == 3);
  assert(floatNM.get_size_column() == 3);
  assert(floatNM.get_size_row() == 3);
  assert(floatNM.get_size_column() == 3);
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
  testp.add(point(2,4), 1, 2);
  testp.add(point(5,4), 200, 4000);
  testp.add(point(1,0), 1, 5);
  assert(testp.get_size()==5);
  assert(testp.get_size_row()==200);
  assert(testp.get_size_column()==10000);  
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

void test_duplicati(){
  std::cout << "\ntest inserimento duplicati\n";
  smatrixi testM(0);
  testM.add(1, 0, 0);
  testM.add(2, 1, 2);
  testM.add(5, 0, 0);
  testM.add(2, 1, 2);

  testM.add(4, 0, 0);
  testM.add(5, 0, 0);
  testM.print();
  assert(testM.get_size() == 2);
  std::cout << "test duplicati superato\n";
  testM.clear();
}
int main(){
  test_fondamentali();
  smatrixi costante(0);
  test_vuota(costante);
  test_point();
  test_duplicati();
  return 0;
}
