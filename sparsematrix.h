#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <cmath>
#include <iostream>
#include <iterator>
#include <cstddef>
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

/**
 * @brief tentativo di lavorare su indici negativi
 * 
 * @return eccezione
 */
class NegativeIndexSparseMatrixException: public std::exception {
  virtual const char* what() const throw() {
    return "indice negativo";
  }
};

/**
 * @brief tentativo di lavorare su dimensioni negative
 * 
 * @return eccezione
 */
class NegativeDimensionSparseMatrixException: public std::exception {
  virtual const char* what() const throw() {
    return "indice negativo";
  }
};

/**
 * @brief tentativo creare nodo fallito
 * 
 * @return eccezione
 */
class  noNodeException: public std::exception {
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
   * @brief bo0leano per dire se la matrice è di dimensoni date dall'utente
   *
   */
  bool dim;
 
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
   * @brief nodo che rappresenta una cella della matrice sparsa
   *
   */
  class node{
  private:
    /**
     * @brief puntatore privato all'elemo successivo
     *
     */
    node *next;
    
    /**
     * @brief struct che definisce l'elemento
     */

    struct element{
      T v;
      const int x;
      const int y;
      element(const T &value, const int i, const int j): v(value), x(i), y(j){}
      ~element(){}
    } *ret;

    /**
     * @brief costruttore di defaul 
     */
    node(): next(nullptr){}
    
    /**
     * @brief costruttore del nodo senza nodo successivo
     *
     * @param v valore della cella
     * @param x indice di riga della cella
     * @param y indice di colonna della cella
     */
    node(const T &v, const int x, const int y): next(nullptr){
      try{
	ret = new element(v, x, y);
      }catch(...){
	throw noNodeException{};
      }
    }
    
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
   * @brief numero totale di nodi inseriti
   *
   */
  int size;

  /**
   * @brief distrugge i nodi a partire da un determinato nodo
   *
   *
   * @param n nodo a partire dal quale si distrugge
   */
  void recursive_clear(node *n){
    if(n!=nullptr) {
      recursive_clear(n->next);
      delete n->ret;
      n->ret = nullptr;
      delete n;
      size--;
      n = nullptr;   
    }
  }
public:

  /**
   * @brief getter del valore di default
   *
   * @return valore di default di sparse_matrix
   */
  const T get_default_value() const {
    return default_value;
  }
  /**
   * @brief getter del tipo di matrice
   *
   * @return true se la matrice è di dimensioni definite dall'utente
   */
  
  bool get_dim() const {
    return dim;
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
   * @brief getter del numero di elemi
   *
   */
  int get_size() const {
    return size;
  }
  
  /**
   * @brief costruttore di default della matrice di dimensioni indefinite
   *
   * @param dvalue valore di default obbligatorio
   */
  sparse_matrix(T dvalue): default_value(dvalue), dim(false),
			   size_row(INT_MAX),
			   size_column(INT_MAX),
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
    default_value(dvalue), dim(true), size_row(row),
    size_column(column), head(nullptr), size(0){
    
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
      std::swap(dim, tmp.dim);
      std::swap(size_row, tmp.size_row);
      std::swap(size_column, tmp.size_column);
    }
    return *this;
  }

  
  /**
   * @brief aggiunta di un elemo e calcolo righe e colonne attuali
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
    // se la matrice è di dimensioni definite controllo di essere
    // nelle dimensioni definite dall'utente (usando l'implicazione logica)
    if(!dim || ((i < size_row) && (j < size_column))){
      node *elem;
      try{
	elem = new node(v, i, j);
      }catch(...){
	throw noNodeException{};
      }
      // parto iterando dalla testa per capire dove inserie il nuovo nodo
      node *temp = head;
      // di base aumento di 1 la size in quanto sto inserendo un nodo
      // ci sarà un -1 in caso di cambio di nodo
      size++;
      if(head == nullptr){
	head = elem;
      }else {
	// indice della testa maggiore quindi il nodo diventa la testa
	if((head->ret->x == i && head->ret->y > j) || (head->ret->x > i)) {
	  elem->next = head;
	  head = elem;
        	  
	}else {
	  // nodo iteratore che cicla fino alla fine
	  // o fino a che sono sulla stessa riga ma ho trovato un valore
	  // di colonna maggiore o sono finito sulla stessa riga
	
	  while(temp->next != nullptr &&
		((temp->next->ret->x == i && temp->next->ret->y <= j)
		 || (temp->next->ret->x < i))) {
	    temp = temp->next;
	  }

	  // se sono arrivato alla fine aggiungo il valore alla fine
	  // o se l'ultimo valore è identico tengo l'ultimo valore aggiunto
	  if(temp->next == nullptr) {
	    if(elem->ret->x == temp->ret->x && elem->ret->y == temp->ret->y) {
	      temp->ret->v = elem->ret->v;
	      size--;
	      // avendo sovrascritto cancello elem e la struct con i valori
	      delete elem->ret;
	      elem->ret = nullptr;
	      delete elem;
	      elem = nullptr;
	    }else{
	      elem->next = nullptr;
	      temp->next = elem;
	    }
	  }else {
	    // aggiungo il valore in mezzo
	    // se sono uguali tengo l'ultimo valore aggiunto
	    if(elem->ret->x == temp->ret->x && elem->ret->y == temp->ret->y) {
	      temp->ret->v = elem->ret->v;
	      size--;
	      // avendo sovrascritto cancello elem e la struct con i valori
	      delete elem->ret;
	      elem->ret = nullptr;      
	      delete elem;
	      elem = nullptr;
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
    // conto massima riga e colonna se non definite dall'utente
    if(!dim){
      int max_row_current = 0;
      int max_column_current = 0;
      node *iter = head;
      while(iter != nullptr){
	if(iter->ret->x > max_row_current)
	  max_row_current = iter->ret->x;
	if(iter->ret->y > max_column_current)
	  max_column_current = iter->ret->y;
	iter = iter->next;
      }
      size_row = max_row_current;
      size_column = max_column_current;
    }
    
  }

  /**
   * @brief stampa lineare dei nodi
   *
   */
  void print() const{
    node *current = head;
    while(current != nullptr){
      std::cout << current->ret->v << " in (" << current->ret->x << ", " << current->ret->y
		<<")\n";
      current = current->next;
      
    }
  }
  
  /**
   * @brief overload dell'operatore () per accedere al nodo di posizone (x,y)
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
    if((x < size_row) && (y < size_column)){
      node *current = head;
      T& value = default_value;

      // come per la add avanzo fino alle condizioni di arresto
      while(current->next != nullptr &&
	    ((current->next->ret->x == x && current->next->ret->y <= y)
	     || (current->next->ret->x < x))) {
	
	current = current->next;
      }
      // se mi sono fermato sul nodo corrispondente alle coordinate richieste
      // ne resituisco il valore, altrimenti resituisco il valore di default
      if(current->ret->x == x && current->ret->y == y){
	return current->ret->v;
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
    //delete head->ret;
    head = nullptr;
    
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
					     dim(other.dim),
					     size_row(other.size_row),
					     size_column(other.size_column),
					     head(nullptr), size(0) {
    node *curr = other.head;

    // eseguo una copia nodo per nodo
    try {
      while(curr != nullptr) {
	add(curr->ret->v, curr->ret->x, curr->ret->y);
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
    node *elem;
    friend class sparse_matrix;
    // costruttore per iterare su struttura dati
    iterator(node *n) : elem(n) {}
    
  public:
    typedef std::forward_iterator_tag iterator_category;
    typedef typename node::element value_type;
    typedef ptrdiff_t difference_type;
    typedef typename node::element* pointer;
    typedef typename node::element& reference;
    
    //costruttori
    iterator() : elem(nullptr) {}
    iterator(const iterator &other) : elem(other.elem) {}

    // override assegnamento
    iterator& operator=(const iterator &other) {
      elem = other.elem;
      
      return *this;
    }

    //distruttore
    ~iterator() {}

    // ovveride accesso
    reference operator*() const{
      //elem ret = elem(elem->value, elem->i, elem->j);
      return *elem->ret;
      
    }

    pointer operator->() const{
      
      return (elem->ret);
    }
 
    // override post e pre incremento
    iterator operator++(int) {
      iterator tmp(*this);
      elem = elem->next;
      return tmp;
    }
    
    iterator operator++() {
      elem = elem->next;
      return *this;  
    }

    // override uguaglianza
    bool operator==(const iterator &other) const {
      return (elem->ret->x == other->ret->x && elem->ret->y == other->ret->y);
    }
        
    bool operator!=(const iterator &other) const {
      return (elem != other.elem);
    }

  };

  /**
   * @brief iteratore costante (in lettura) per sparse_matrix
   */

  class const_iterator{
  private:
    const node *elem;
    
    friend class sparse_matrix;

    // costruttore per iterare su struttura dati
    const_iterator(node *n) : elem(n) {}
  public:
    typedef std::forward_iterator_tag iterator_category;
    typedef typename node::element value_type;
    typedef ptrdiff_t difference_type;
    typedef const typename node::element* pointer;
    typedef const typename node::element& reference;

    //costruttori
    const_iterator() : elem(nullptr) {}
    const_iterator(const const_iterator &other) : elem(other.elem) {}

    // override assegnamento
    const_iterator& operator=(const const_iterator &other) {
      elem = other.elem;
      return *this;
    }

    //distruttore
    ~const_iterator() {}

    // ovveride accesso
    reference operator*() const{
      return elem->ret;
    }
    pointer operator->() const{
      return &*elem->ret;
    }
    
    // override post e pre incremento
    const_iterator operator++(int) {
      iterator tmp(*this);
      elem = elem->next;
      return tmp;
    }
    
    const_iterator operator++() {
      elem = elem->next;
      return *this;  
    }
    
    // override uguaglianza e diversità
    bool operator==(const const_iterator &other) const {
      return (elem->ret->x == other->ret->x && elem->ret->y == other->ret->y);
    }
        
    bool operator!=(const const_iterator &other) const {
      return elem != other.elem;
    }

    friend class iterator;
    
    // Uguaglianza e diversità con iterator
    bool operator==(const iterator &other) const {
      return elem == other.elem;
    }
    bool operator!=(const iterator &other) const {
      return  elem != other.elem;
    }

    // Costruttore di conversione iterator -> const_iterator
    const_iterator(const iterator &other) : elem(other.elem) {
    }

    // Assegnamento di un iterator ad un const_iterator
    const_iterator &operator=(const iterator &other) {
      elem = other.elem;
      return *this;
    }

  };
  
  /**
   * @brief iteratore all'inizio della sparse_matrix
   *
   * @return iteratore alla head
   */
  iterator begin() {
    return iterator(head);
  }

  /**
   * @brief iteratore alla fine della sparse_matrix
   *
   * @return nullptr 
   */
  iterator end() {
    return iterator(nullptr);
  }
  
  /**
   * @brief iteratore costante alla testa della sparse_matrix
   * 
   * @return iteratore alla head
   */
  const_iterator begin() const {
    return const_iterator(head);
  }

  /**
   * @brief iteratore costante alla fine della sparse_matrix
   *
   * @return nullptr 
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
    default_value(static_cast<T>(other.get_default_value())), dim(other.get_dim()),
    size_row(other.get_size_row()), size_column(other.get_size_column()),
    head(nullptr), size(0) {

    // mi muovo con gli iteratori nella matrice sparsa passata in ingresso
    // effettuo la add alla nuova matrice sparsa con cast del valore
    typename sparse_matrix<Q>::const_iterator i, ie;
    i = other.begin();
    ie = other.end();
    try {
      while(i != ie) {
	add(static_cast<T>(i->v), i->x, i->y);
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
    throw NegativeIndexSparseMatrixException();
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
  // evito overflow se provo a stampare su una matrice nulla
  if(smatrix.get_size() == 0)
    return os;
  // mi salvo il numero di riga per andare a capo
  int prevrow = i->x;
  
  while(i!=ie) {
    if(i->x != prevrow)
      std::cout << std::endl;
    os << i->v << "\t";
    prevrow = i->x;
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
  if(smatrix.get_size() == 0) return count;
  i = smatrix.begin();
  ie = smatrix.end();
	
  while(i!=ie) {
    if(pred(i->v)) {
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
