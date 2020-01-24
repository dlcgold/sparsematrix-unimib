#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <cmath>
#include <iostream>

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
  
   
    ~node(){
      next = nullptr;
    }    
  };

  node *head;
  unsigned int size;

  

  void recursive_clear(node *n){
    if(n!=nullptr) {
      recursive_clear(n->next);	
      delete n;
      size--;
      n = nullptr;	
    }
  }
public:

  sparse_matrix(T dvalue): default_value(dvalue),size_row(0), size_column(0),
			   head(nullptr), size(0){};
  

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

  sparse_matrix &operator=(const sparse_matrix &other) {
    
    if(this != &other) {
      sparse_matrix tmp(other);
      std::swap(head,tmp.head);
      std::swap(size,tmp.size);
    }
    return *this;
  }

  bool find(const T &v) const{
    node *current = head;
    while(current != nullptr){
      if(current->value == v)
	return true;
      current = current->next;
    }
    return false;
  }
  
  void add(const T &v, const int i, const int j) {
    node *elem = new node(v, i, j);
    node *temp = head;
    size++;
    int max_row = 0;
    int max_column = 0;
    if(head == nullptr){
      head = elem;
      //size++;
      elem = nullptr;
      delete elem;
      return;
    }else {
      // indice della testa maggiore quindi il nodo diventa la testa
      if((head->i == i && head->j > j) || (head->i > i)) {
	elem->next = head;
	head = elem;
	elem = nullptr;
	//size++;	  
      }else {
	// nodo iteratore che cicla fino alla fine
	// o fino a che sono sulla stessa riga ma ho trovato un valore
	// di colonna maggiore o sono finito sulla stessa riga
	
	while(temp->next != nullptr &&
	      ((temp->next->i == i && temp->next->j <= j)
	       || (temp->next->i <= i))) {
	  temp = temp->next;
	}

	// se sono arrivato alla fine aggiungo il valore alla fine
	if(temp->next == nullptr) {
	  elem->next = nullptr;
	  temp->next = elem;
	 
	  //size++;
	}else {
	  // aggiungo il valore in mezzo
	  // se sono uguali tengo l'ultimo valore aggiunto
	  if(elem->i == temp->i && elem->j == temp->j) {
	    temp->value = elem->value;
	    size--;
	  }else {
	    // altrimenti inserisco in mezzo
	    elem->next = temp->next;
	    temp->next = elem;
	    
	    //size++;
	  }
	}
	
      }
    }
    // conto massima riga e colonna
    node *iter = head;
    while(iter != nullptr){
      if(iter->i > max_row)
	max_row = iter->i;
      if(iter->j > max_column)
	max_column = iter->j;
      iter = iter->next;
    }
    size_row = max_row;
    size_column = max_column;
    iter = nullptr;
    temp=nullptr;
    
    elem = nullptr;
    return;
    
  }

  void print(){
    node *current = head;
    while(current != nullptr){
      std::cout << current->value << " in (" << current->i << ", " << current->j
		<<")\n";
      current = current->next;
      
    }
  }

  void clear(){
    recursive_clear(head);
    head = nullptr;
    return;
  }
  
  ~sparse_matrix(){
    clear();
  }
};


#endif
