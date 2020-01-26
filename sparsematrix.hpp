#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <cmath>
#include <iostream>
//#include <iterator>
#include <ostream>

template <typename T>
class sparse_matrix{
private:
  T default_value;
  int size_row;
  int size_column;
  class node{
  private: node *next;
  public:
    T value;
    const unsigned int i;
    const unsigned int j;
    
  

  public:
    node(): next(nullptr){}

    node(const T &v, const int x, const int y): next(nullptr), value(v),
						i(x), j(y){}
						
    node(node *n, const T &v, const int x, const int y): next(n), value(v),
							 i(x), j(y){}

    ~node(){
      next = nullptr;
    }
    friend class sparse_matrix;
  };

  node *head;
  node *tail;
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

  bool find(unsigned int i, unsigned int j) const{
    node *current = head;
    while(current != nullptr){
      if(current->i == i && current->j == j)
	return true;
      current = current->next;
    }
    return false;
  }
  
  void add(const T &v, const unsigned int i, const unsigned int j) {
    node *elem = new node(v, i, j);
    node *temp = head;
    size++;
    unsigned int max_row = 0;
    unsigned int max_column = 0;
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
	  //tail=elem;
	 
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

  T& operator()(unsigned int x, unsigned int y) {
    
    node *current = head;
    T& value = default_value;
    std::cout << value << "\n";
    while(current != nullptr){
     
      if(current->i == x && current->j == y){
       	return current->value;
      }
      
      current = current->next;
    }
    return value;
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

  class iterator{
  private:
    node *element;
    
    friend class sparse_matrix;

    // costruttore per iterare su struttura dati
    iterator(node *n) : element(n) {}
  public:
    // typedef std::forward_iterator_tag iterator_category;
    // typedef node value_type;
    // typedef ptrdiff_t difference_type;
    // typedef node* pointer;
    // typedef node& reference;
    
    //costruttori
    iterator() : element(nullptr) {}
    iterator(const iterator &other) : element(other.element) {}

    // override assegnamento
    iterator& operator=(const iterator &other) {
      element = other.element;
      return *this;
    }

    //distruttore
    ~iterator() {}

     // ovveride accesso
    node& operator*() const{
      
      return element;
      }
    node* operator->() const{
      
      return &*element;
    }
    
    // override post e pre incremento
    node& operator++(int) {
      iterator tmp(*this);
      element = element->next;
      return *element;
    }
    
    node& operator++() {
      // element* res;
      element = element->next;
      return *element;  
    }
    
    // override uguaglianza
    bool operator==(const iterator &other) const {
      return (element->i == other->i && element->j == other->j);
    }
        
    bool operator!=(const iterator &other) const {
      //return (iter->i != other->i && iter->j != other->j);
      return (element != other.element);
    }
    
  
    
  };

  // begin e end
  iterator begin() const {
    return iterator(head);
  }
  iterator end() const {
    return iterator(nullptr);
  }

  
};

// overload << per stampa
template <typename T>
std::ostream &operator<<(std::ostream &os, 
			 const sparse_matrix<T> smatrix) {
	
  typename sparse_matrix<T>::iterator i, ie;
	
  i = smatrix.begin();
  ie = smatrix.end();
  unsigned int prevrow=i->i;
  while(i!=ie) {
    if(i->i != prevrow)
      std::cout << std::endl;
    os << i->value << "\t";
    
    prevrow = i->i;
    ++i;
  }
  
  return os;
  }
#endif
