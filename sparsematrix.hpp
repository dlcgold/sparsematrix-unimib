#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <cmath>
#include <iostream>
#include <iterator>
#include <ostream>

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
  
    node(const T &v, const int x, const int y, node *n): value(v), i(x),
							 j(y), next(n){}

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

  bool find(int i, int j) const{
    node *current = head;
    while(current != nullptr){
      if(current->i == i && current->j == j)
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
      return;
    }else {
      // indice della testa maggiore quindi il nodo diventa la testa
      if((head->i == i && head->j > j) || (head->i > i)) {
	elem->next = head;
	head = elem;
        	  
      }else {
	// nodo iteratore che cicla fino alla fine
	// o fino a che sono sulla stessa riga ma ho trovato un valore
	// di colonna maggiore o sono finito sulla stessa riga
	
	while(temp->next != nullptr &&
	      ((temp->next->i == i && temp->next->j <= j)
	       || (temp->next->i < i))) {
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
	    // avendo sovrascritto cancello elem
	    delete elem;
	  }else {
	    // altrimenti inserisco in mezzo
	    elem->next = temp->next;
	    temp->next = elem;
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
    size_column = max_column;;
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

  //copy constructor from other sparse matrix
  sparse_matrix(const sparse_matrix &other): default_value(other.default_value),
					     size_row(0), size_column(0),
					     head(nullptr), size(0) {
    node *curr = other.head;

    try {
      while(curr != nullptr) {
	add(curr->value, curr->i, curr->j);
	curr = curr->next;
      }		
    }
    catch(...) {
      clear();
      throw;
    }
  }

  // iteratore

  class const_iterator{
  private:
    const node *iter;
    
  public:
    //costruttori
    const_iterator() : iter(nullptr) {}
    const_iterator(const const_iterator &other) : iter(other.iter) {}

    // override assegnamento
    const_iterator& operator=(const const_iterator &other) {
      iter = other.iter;
      return *this;
    }

    //distruttore
    ~const_iterator() {}

    // ovveride accesso
    const T& operator*() const{
      return iter->value;
    }
    const T& operator->() const{
      return &(iter->value);
    }

    // override post e pre incremento
    const_iterator operator++(int) {
      const_iterator tmp(*this);
      iter = iter->next;
      return tmp;
    }
    
    const_iterator& operator++() {
      iter = iter->next;
      return *this;
    }

    // override uguaglianza
    bool operator==(const const_iterator &other) const {
      return (iter == other.iter);
    }
		
    /**
       @brief operator !=
       @return true if not equal
    */
    bool operator!=(const const_iterator &other) const {
      return (iter != other.iter);
    }

  private:
    friend class sparse_matrix;

    // costruttore per iterare su struttura dati
    const_iterator(const node *iter) : iter(iter) {}
  };

  // begin e end
  const_iterator begin() const {
    return const_iterator(head);
  }
  const_iterator end() const {
    return const_iterator(nullptr);
  }
};

// overload << per stampa
template <typename T>
std::ostream &operator<<(std::ostream &os, 
			 const sparse_matrix<T> smatrix) {
	
  typename sparse_matrix<T>::const_iterator i, ie;
	
  i = smatrix.begin();
  ie = smatrix.end();

  while(i!=ie) {
    os << *i << " ";
    
    ++i;
  }

  return os;
}
#endif
