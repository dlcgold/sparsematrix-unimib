#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <cmath>
template <typename T>
class sparse_matrix{
private:
  T default_value;
  int size_row;
  int size_column;
  struct node{
    T value;
    int i;
    int j;
    
    node *next;

    
    node(): next(nullptr){}

    node(const T &v, const int x, const int y): value(v), i(x), j(y),
						next(nullptr){}
  
   
    //node(const T &v, node *n): value(v), next(n){}
    
  };

  node *head;
  unsigned int size;

  float concat(int a, int b) { 
    float len = floor(log10(b) + 1);
    float corr = pow(10, len);
    return a + b / corr;
  } 
public:

  sparse_matrix(T dvalue): default_value(dvalue), size(0), head(nullptr),
			   size_row(0), size_column(0){};
  

  const T get_default_value() const {
    return default_value;
  }
  
  int get_size_column() const {
    return size_column;
  }

  int get_size_row() const {
    return size_row;
  }

  
  unsigned int get_size() const {
    return size;
  }

  void add(const T &v, const int i, const int j) {
    node *elem = new node(v, i, j);
    node *temp = new node();
    if(head == nullptr){
      head = elem;
      size++;
    }else {
      // indice della testa maggiore quindi il nodo diventa la testa
      if((head->i == i && head->j > j) || (head->i > i)) {
	elem->next = head;
	head = elem;
	size++;
      }else {
	// nodo iteratore che cicla fino alla fine
	// o fino a che sono sulla stessa riga ma ho trovato un valore
	// di colonna maggiore o sono finito sulla stessa riga
	temp = head;
	while(temp->next != nullptr &&
	      ((temp->next->i == i && temp->next->j <= j)
	       || (temp->next->i <= i))) {
	  temp = temp->next;
	}
	// se sono arrivato alla fine aggiungo il valore alla fine
	if(temp->next == nullptr) {
	  elem->next = nullptr;
	  temp->next = elem;
	  size++;
	}else {
	  // aggiungo il valore in mezzo
	  // se sono uguali tengo l'ultimo valore aggiunto
	  if(elem->i == temp->i && elem->j == temp->j) {
	    temp->value = elem->value;
	  }else {
	    // altrimenti inserisco in mezzo
	    elem->next = temp->next;
	    temp->next = elem;
	    size++;
	  }
	}
      }
    }
    
  }

  void print(){
    node *current = head;
    while(current != nullptr){
      std::cout << current->value << " in (" << current->i << ", " << current->j
		<<")\n";
      current = current->next;
	
    }
  }
  
};


#endif
