#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP
#include <cassert>
#include <cstddef>  //ptrdiff_t
#include <iterator> //std::bidirectional_iterator_tag
#include <iostream>

#include <initializer_list>

template <typename T>
class List;

template <typename T>
struct ListNode {
  T         value = T{};
  ListNode* prev = nullptr;
  ListNode* next = nullptr;
};


//TODO: Implementierung der Methoden des Iterators 
//      (nach Vorlesung STL-1 am 09. Juni) (Aufgabe 3.12)
template <typename T>
struct ListIterator {
  using Self              = ListIterator<T>;
  using value_type        = T;
  using pointer           = T*;
  using reference         = T&;
  using difference_type   = ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;


  /* DESCRIPTION  operator*() */
  T&  operator*()  const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: remaining implementation of derefenciation of 
    //      iterator using operator* (Aufgabe 3.12 - Teil 1)

  } //call *it

  /* DESCRIPTION  operator->() */
  T* operator->() const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: remaining implementation of derefenciation of 
    //      iterator using operator-> (Aufgabe 3.12 - Teil 2)
  }  //call it->method() or it->member


  /* PREINCREMENT, call: ++it, advances one element forward */
  ListIterator<T>& operator++() {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: Implement Postincrement-Operation for Iterator
    //      (Aufgabe 3.12 - Teil 3)
    
  }

  /* POSTINCREMENT (signature distinguishes the iterators), 
                    call:  it++, advances one element forward*/
  ListIterator<T> operator++(int) {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: Implement Postincrement-Operation for Iterator
    //      (Aufgabe 3.12 - Teil 4)

  }


  /* ... */
  bool operator==(ListIterator<T> const& x) const {
    //TODO: Implement Equality-Operation for Iterator
    //      (Aufgabe 3.12 - Teil 5)
    // Iterators should be the same if they refer to the same node
    return false;
  } // call it: == it

  /* ... */
  bool operator!=(ListIterator<T> const& x) const {
    //TODO: Implement Inequality-Operation for Iterator  
    //      (Aufgabe 3.12 - Teil 6)
    // Reuse operator==
    return false;
  } // call it: != it

  /* Advances Iterator */
  ListIterator<T> next() const {
    if (nullptr != node) {
      return ListIterator{node->next};
    } else {
      return ListIterator{nullptr};
    }
  }


  ListNode <T>* node = nullptr;
};



template <typename T>
class List {
  public:

    //friend declarations for testing the members   
    template <typename TEST_TYPE>
    friend size_t get_size(List<TEST_TYPE> const& list_to_test);
    template <typename TEST_TYPE>
    friend ListNode<TEST_TYPE>* get_first_pointer(List<TEST_TYPE> const& list_to_test);
    template <typename TEST_TYPE>
    friend ListNode<TEST_TYPE>* get_last_pointer(List<TEST_TYPE> const& list_to_test);

    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = T const*;
    using reference       = T&;
    using const_reference = T const&;
    using iterator        = ListIterator<T>;

    // not fully implemented yet
    /* list constructor and inilisation list */
    List():
      size_{0},
      first_{nullptr},
      last_{nullptr}{}
    

    // test and implement:
    //TODO: Copy-Konstruktor using Deep-Copy semantics (Aufgabe 3.5)

    // test and implement:
    // TODO: Move-Konstruktor (Aufgabe 3.9)

    //TODO: Initializer-List Konstruktor (3.10 - Teil 1)
    /* ... */
    // test and implement:
    List(std::initializer_list<T> ini_list) {
      //not implemented yet
    }

    // test and implement:
    //TODO: Copy-Konstruktor using Deep-Copy semantics (Aufgabe 3.5)

    /* ... */
    // test and implement:
    //TODO: (unifying) Assignment operator (Aufgabe 3.6)

    /* ... */
    // test and implement:

    bool operator==(List const& rhs)
    {
      //TODO: operator== (Aufgabe 3.8)
    }

    bool operator!=(List const& rhs)
    {
      //TODO: operator!= (Aufgabe 3.8)
      // make use of operator==
    }

    /* ... */
    ~List() {
      //TODO: Implement via clear-Method (Aufgabe 3.4)
    } //can not really be tested

    /* ... */
    ListIterator<T> begin() {
      //TODO: begin-Method returning an Iterator to the 
      //      first element in the List (Aufgabe 3.11)
      return {};
    }

    /* ... */
    ListIterator<T> end() {
      //TODO: end-Method returning an Iterator to element after (!) 
      //      the last element in the List (Aufgabe 3.11)
      return {};
    }

    /* ... */ 
    // test and implement:
    //TODO: clear()-Method (Aufgabe 3.4)


    /* ... */
    //TODO: member function insert (Aufgabe 3.13)

    /* ... */
    //TODO: member function insert (Aufgabe 3.14)

    /* ... */

    //TODO: member function reverse (Aufgabe 3.7 - Teil 1)


    /* inserts an element to the beginning */
    void push_front(T const& element) {
      ListNode<T>* newFront = new ListNode<T>{element};
      if(empty()){
        first_ = newFront;
        last_ = newFront;
        first_->prev = nullptr;
        last_->next = nullptr;
      }
      else{
        first_->prev = newFront;
        newFront->next = first_;
        newFront->prev = nullptr;
        first_ = newFront;
        last_->next = nullptr;
      }
      ++size_;
    }

    /* adds an element to the end  */
    void push_back(T const& element) {
      ListNode<T>* newBack = new ListNode<T>{element};
      if(empty()){
        first_ = newBack;
        last_ = newBack;
        first_->prev = nullptr;
        last_->next = nullptr;
      }
      else{
        last_->next = newBack;
        newBack->prev = last_;
        newBack->next = nullptr;
        last_ = newBack;
        first_->prev = nullptr;
      }
      ++size_;
    }

    /* removes the first element */
    void pop_front() {
      if(empty()) {
        throw "List is empty";
      }
      if(size_ == 1){
        delete first_;
        first_ = nullptr;
        last_ = first_;
      }
      else{
        ListNode<T>* noFront = new ListNode<T>{};
        noFront =first_->next;
        delete first_;
        first_ = noFront;
        noFront->prev = nullptr;
        last_->next = nullptr;
      }
      --size_;
    }

    /* removes the last element */
    void pop_back() {
      if(empty()) {
        throw "List is empty";
      }
      if(size_ == 1){
        delete first_;
        first_ = nullptr;
        last_ = first_;
      }
      else{
        ListNode<T>* noBack = new ListNode<T>{};
        noBack = last_->prev;
        delete last_;
        last_ = noBack;
        noBack->next = nullptr;
        first_->prev = nullptr;
      }
      --size_;
    }

    /* access the first element  */
    T& front() const{
      if(empty()) {
        throw "List is empty";
      }
      return first_->value;
    }

    /* access the last element */
    T& back() const{
      if(empty()) {
        throw "List is empty";
      }
      return last_->value;
    }

    /* checks if the list contains elements */
    bool empty() const {
      return size_== 0;
    };


    /* Returns number of elements in list */
    std::size_t size() const{   
      return size_;
  };


  // list members
  private: 
    std::size_t size_;
    ListNode<T>* first_;
    ListNode<T>* last_;
};

/* ... */
//TODO: Freie Funktion reverse 
//(Aufgabe 3.7 - Teil 2, benutzt Member-Funktion reverse)

/* ... */
//TODO: Freie Funktion operator+ (3.10 - Teil 2)


#endif // # define BUW_LIST_HPP
