#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <cmath>
#include <iostream>
#include <iterator>
#include <ostream>
#include <climits>

/**
 * @brief tentativo di lavorare su un cella fuori dalle dimensioni, se diciarate
 * 
 * @return eccezione
 */
class IndexOutOfBoundsException: public std::exception {
    virtual const char* what() const throw() {
        return "indice out of bound";
    }
};

/**
 * @brief tentativo di uso di sparse_matrix inesistente
 * 
 * @return eccezione
 */
class NoSparseMatrixException: public std::exception {
    virtual const char* what() const throw() {
        return "passaggio matrice nulla";
    }
};


/**
 * @brief tentativo di cast tra sparse_matrix fallito
 * 
 * @return eccezione
 */
class NoCastSparseMatrixException: public std::exception {
    virtual const char* what() const throw() {
        return "impossibile costruire matrice con cast";
    }
};

class NegativeIndexSparseMatrixException: public std::exception {
    virtual const char* what() const throw() {
        return "indice negativo";
    }
};

class NegativeDimensionSparseMatrixException: public std::exception {
    virtual const char* what() const throw() {
        return "indice negativo";
    }
};
/**
 * @brief Classe sparse_matrix per matrice sparsa
 *
 * @tparam T tipo dei valori della matrice
 */
template <typename T>
class sparse_matrix{
private:

  /**
   * @brief valore di default, scelto dall'utente
   *
   */
  T default_value;

  /**
   * @brief numero massimo di righe, eventualmente scelto dall'utente
   *
   */
  int max_row;
  
  /**
   * @brief numero massimo di colonne, eventualmente scelto dall'utente
   *
   */
  int max_column;

  /**
   * @brief numero di righe
   *
   */
  int size_row;

  /**
   * @brief numero di colonne
   *
   */
  int size_column;

  /**
   * @brief elemento che rappresenta una cella della matrice sparsa
   *
   */
  class node{
  private:
    /**
     * @brief puntatore privato all'elemento successivo
     *
     */
    node *next;
    
  public:
    /**
     * @brief valore contenuto nella cella, modificabile
     *
     */
    T value;

    /**
     * @brief indice di riga, non modificabile 
     *
     */
    const int i;

    /**
     * @brief indice di colonna, non modificabile 
     *
     */
    const int j;
    
    /**
     * @brief costruttore di default dell'elemento
     *
     */
    // node(): next(nullptr){}

    /**
     * @brief costruttore dell'elemento senza elemento successivo
     *
     * @param v valore della cella
     * @param x indice di riga della cella
     * @param y indice di colonna della cella
     */
    node(const T &v, const int x, const int y): next(nullptr), value(v),
						i(x), j(y){}

    /**
     * @brief distruttore del nodo
     *
     */
    ~node(){
      next = nullptr;
    }

    /**
     * @brief si può accedere ai membri privati di sparse_matrix
     *
     */
    friend class sparse_matrix;
  };

  /**
   * @brief puntatore alla testa
   * costruttore
   */
  node *head;

  /**
    * @brief numero totale di elementi inseriti
    *
    */
  int size;

  /**
   * @brief distrugge gli elementi linkati a partire da un elemento
   *
   *
   * @param n elemento a partire dal quale si distrugge
   */
  void recursive_clear(node *n){
    if(n!=nullptr) {
      recursive_clear(n->next);	
      delete n;
      size--;
      n = nullptr;	
    }
  }
public:
  

  /**
   * @brief getter del numero massimo di righe
   *
   * @return massimo numero di righe di sparse_matrix
   */
  int get_max_row() const {
    return max_row;
  }

  /**
   * @brief getter del numero massimo di colonne
   *
   * @return massimo numero di colonne di sparse_matrix
   */
  int get_max_column() const {
    return max_column;
  }

  /**
   * @brief getter dell'elemento di testa
   *
   * @return testa di sparse_matrix
   */
  const node* get_head() const {
    return head;
  }

   /**
   * @brief getter del valore di default
   *
   * @return valore di default di sparse_matrix
   */
  const T get_default_value() const {
    return default_value;
  }

  /**
   * @brief getter del numero di righe
   *
   * @return numero di righe di sparse_matrix
   */
  int get_size_row() const {
    return size_row;
  }
  
  /**
   * @brief getter del numero di colonne
   *
   * @return numero di colonne di sparse_matrix
   */
  int get_size_column() const {
    return size_column;
  }

  /**
   * @brief getter del numero di elementi
   *
   */
  int get_size() const {
    return size;
  }
  
  /**
   * @brief costruttore della matrice di dimensioni indefinite
   *
   * @param dvalue valore di default obbligatorio
   */
  sparse_matrix(T dvalue): default_value(dvalue), max_row(INT_MAX),
			   max_column(INT_MAX), size_row(0), size_column(0),
			   head(nullptr), size(0){};


  /**
   * @brief costruttore della matrice di dimensioni definite
   *
   * @param dvalue valore di default obbligatorio
   * @param row numero di righe
   * @param column numero di colonne
   *
   * @throw NegativeDimensionSparseMatrixException() per dimensioni negative
   */
  sparse_matrix(T dvalue, int row, int column):
    default_value(dvalue), max_row(row), max_column(column), size_row(0),
    size_column(0), head(nullptr), size(0){
    if(row < 0 || column < 0)
      NegativeDimensionSparseMatrixException();
  };
  

  /**
   * @brief overload dell'operatore di assegnamento
   *
   * @param other altra sparse_matrix per l'assegnamento
   * @return sparse_matrix
   */
  sparse_matrix &operator=(const sparse_matrix &other) {

    /**
     * @brief se le sparse_matrix sono diverse inverto gli attributi delle due
     */
    if(this != &other) {
      sparse_matrix tmp(other);
      std::swap(head, tmp.head);
      std::swap(size, tmp.size);
      std::swap(default_value, tmp.default_value);
      std::swap(max_row, tmp.max_row);
      std::swap(max_column, tmp.max_column);
      std::swap(size_row, tmp.size_row);
      std::swap(size_column, tmp.size_column);
    }
    return *this;
  }

  /*bool find(unsigned int i, unsigned int j) const{
    node *current = head;
    while(current != nullptr){
      if(current->i == i && current->j == j)
	return true;
      current = current->next;
    }
    return false;
  }*/
  
  /**
   * @brief aggiunta di un elemento e calcolo righe e colonne attuali
   * 
   * @param v valore da aggiungere
   * @param i indice di riga della cella in cui aggiungere il valore
   * @param j indice di colonna della cella in cui aggiungere il valore
   *
   * @throw IndexOutOfBoundsException() cella fuori dalla matrice
   * @throw NegativeIndexSparseMatrixException() indici negativi
   */
  void add(const T &v, const int i, const int j) {
    if(i < 0 || j < 0)
      throw  NegativeIndexSparseMatrixException();
    if((i < max_row) && (j < max_column)){
      
      node *elem = new node(v, i, j);
      node *temp = head;
      size++;
      if(head == nullptr){
	head = elem;
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
	    if(elem->i == temp->i && elem->j == temp->j) {
	      temp->value = elem->value;
	      size--;
	      // avendo sovrascritto cancello elem
	      delete elem;
	    }else{
	      elem->next = nullptr;
	      temp->next = elem;
	    }
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
    }else{
      throw IndexOutOfBoundsException();
    }
    // conto massima riga e colonna
    int max_row_current = 0;
    int max_column_current = 0;
    node *iter = head;
    while(iter != nullptr){
      if(iter->i > max_row_current)
	max_row_current = iter->i;
      if(iter->j > max_column_current)
	max_column_current = iter->j;
      iter = iter->next;
    }
    size_row = max_row_current;
    size_column = max_column_current;
    return;
    
  }

  /**
   * @brief stampa lineare degli elementi
   *
   */
  void print(){
    node *current = head;
    while(current != nullptr){
      std::cout << current->value << " in (" << current->i << ", " << current->j
		<<")\n";
      current = current->next;
      
    }
  }
  
  /**
   * @brief overload dell'operatore () per accedere all'elemento
   *
   * @param x indice di riga della cella voluta
   * @param y indice di colonna della cella voluta
   *
   * @return valore di default se cella non trovata
   * @return valore della cella richiesta
   *
   * @throw IndexOutOfBoundsException() cella fuori dalla matrice
   * @throw NegativeIndexSparseMatrixException() indici negativi
   */
  const T& operator()(int x, int y) {
    if(x < 0 || y < 0)
      throw  NegativeIndexSparseMatrixException();
    if((x < max_row) && (y < max_column)){
      node *current = head;
      T& value = default_value;

      // come per la add avanzo fino a che non ho problemi
      while(current->next != nullptr &&
	    ((current->next->i == x && current->next->j <= y)
	     || (current->next->i < x))) {
	
	current = current->next;
      }
      if(current->i == x && current->j == y){
	return current->value;
      }else{
	return value;
      }
    }else{
      throw IndexOutOfBoundsException();
    }
  }

  /**
   * @brief distrugge la sparse_matrix a partire dalla testa della matrice
   *
   */
  void clear(){
    recursive_clear(head);
    head = nullptr;
    return;
  }

  /**
   * @brief distruttore della sparse_matrix
   *
   */
  ~sparse_matrix(){
    clear();
  }

  /**
   * @brief costruttore copia
   *
   * @param other altra sparse_matrix
   *
   * @throw NoSparseMatrixException() eccezione matrice inesistente
   */
  sparse_matrix(const sparse_matrix &other): default_value(other.default_value),
					     max_row(other.max_row),
					     max_column(other.max_column),
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
      throw NoSparseMatrixException();
    }
  }

 
  
  /**
   * @brief iteratore (in lettura e scrittura) per sparse_matrix
   */
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

    /**
     * @brief iteratore costante (in lettura) per sparse_matrix
   */

  class const_iterator{
  private:
    const node *element;
    
    friend class sparse_matrix;

    // costruttore per iterare su struttura dati
    const_iterator(node *n) : element(n) {}
  public:
    // typedef std::forward_iterator_tag iterator_category;
    // typedef node value_type;
    // typedef ptrdiff_t difference_type;
    // typedef node* pointer;
    // typedef node& reference;
    
    //costruttori
    const_iterator() : element(nullptr) {}
    const_iterator(const const_iterator &other) : element(other.element) {}

    // override assegnamento
    const_iterator& operator=(const const_iterator &other) {
      element = other.element;
      return *this;
    }

    //distruttore
    ~const_iterator() {}

    // ovveride accesso
    const node& operator*() const{
      
      return element;
    }
    const node* operator->() const{
      
      return &*element;
    }
    
    // override post e pre incremento
    const node& operator++(int) {
      iterator tmp(*this);
      element = element->next;
      return *element;
    }
    
    const node& operator++() {
      // element* res;
      element = element->next;
      return *element;  
    }
    
    // override uguaglianza
    bool operator==(const const_iterator &other) const {
      return (element->i == other->i && element->j == other->j);
    }
        
    bool operator!=(const const_iterator &other) const {
      //return (iter->i != other->i && iter->j != other->j);
      return element != other.element;
    }

    friend class iterator;
    // Uguaglianza
    bool operator==(const iterator &other) const {
      return element == other.element;
    }

    // Diversita'
    bool operator!=(const iterator &other) const {
      return  element != other.element;
    }

    // Costruttore di conversione iterator -> const_iterator
    const_iterator(const iterator &other) : element(other.element) {
    }

    // Assegnamento di un iterator ad un const_iterator
    const_iterator &operator=(const iterator &other) {
      element = other.element;
      return *this;
    }

  };
  
  /**
   * @brief iteratore alla testa della sparse_matrix
   */
  iterator begin() {
    return iterator(head);
  }

   /**
   * @brief iteratore alla fine della sparse_matrix
   */
  iterator end() {
    return iterator(nullptr);
  }
  
  /**
   * @brief iteratore costante alla testa della sparse_matrix
   */
  const_iterator begin() const {
    return const_iterator(head);
  }

   /**
   * @brief iteratore costante alla fine della sparse_matrix
   */
  const_iterator end() const {
    return const_iterator(nullptr);
  }
  
  /**
   * @brief costruttore copia con cast
   *
   * @tparam Q tipo della matrice per cast Q->T
   *
   * @param other altra sparse_matrix ti tipo Q
   *
   * @throw NoCastSparseMatrixException() eccezione cast fallito
   */
  template <typename Q>
  sparse_matrix(const sparse_matrix<Q> &other):
    default_value(static_cast<T>(other.get_default_value())),
    max_row(other.get_max_row()), max_column(other.get_max_column()),
    size_row(0), size_column(0),
    head(nullptr), size(0) {
    
    typename sparse_matrix<Q>::const_iterator i, ie;
    i = other.begin();
    ie = other.end();
    try {
      while(i != ie) {
	add(static_cast<T>(i->value), i->i, i->j);
	++i;
      }		
    }
    catch(...) {
      clear();
      throw NoCastSparseMatrixException();
    }
  }
  
};

/**
   * @brief costruttore copia con cast
   *
   * @tparam Q tipo della matrice per cast Q->T
   *
   * @param other altra sparse_matrix con valori di tipo Q
   *
   * @throw NoCastSparseMatrixException() eccezione cast fallito
   * @throw NegativeIndexSparseMatrixException() indici negativi   
   */
template <typename T>
void printdef(sparse_matrix<T> smatrix, int n, int m){
  if(n < 0 || m < 0)
    NegativeIndexSparseMatrixException();
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      std::cout << smatrix(i, j) << " ";
    }
    std::cout << std::endl;
  }
}

/**
 * @brief overload operatore di stream << per sparse_matrix
 * 
 * @tparam T tipo della sparse_matrix
 * @param os stream
 * @param smatrix sparse_matrix con valori di tipo T
 * @return puntatore allo stream
 */
template <typename T>
std::ostream &operator<<(std::ostream &os, 
			 const sparse_matrix<T> &smatrix) {
	
  typename sparse_matrix<T>::const_iterator i, ie;
	
  i = smatrix.begin();
  ie = smatrix.end();
  // evito overflow se provo a stampare il nulla
  if(smatrix.get_head()==nullptr)
    return os;
  int prevrow=i->i;
  while(i!=ie) {
    if(i->i != prevrow)
      std::cout << std::endl;
    os << i->value << "\t";
    
    prevrow = i->i;
    ++i;
  }
  
  return os;
}

/**
 * @brief conteggio valori della sparse_matrix che rispettano un predicato
 * 
 * @tparam T tipo della sparse_matrix
 * @param P tipo funtore da verificare
 * @param smatrix sparse_matrix con valori di tipo T
 * @param pred funtore
 * @return conteggio dei valori che rispettano il predicato
 */
template <typename T, typename P>
int evaluate(const sparse_matrix<T> &smatrix, P pred) {

  typename sparse_matrix<T>::const_iterator i, ie;
  int count = 0;
  if(smatrix.get_head()==nullptr) return count;
  i = smatrix.begin();
  ie = smatrix.end();
	
  while(i!=ie) {
    if(pred(i->value)) {
      count++;
    }
    ++i;
  }
  // calcolo le celle di default
  // se pred(default) = true sommo quel numero al mio count
  int totalDefault = (smatrix.get_size_row() * smatrix.get_size_column())
    - smatrix.get_size();
  if(pred(smatrix.get_default_value()))
    count += totalDefault;
  return count;
}
#endif
