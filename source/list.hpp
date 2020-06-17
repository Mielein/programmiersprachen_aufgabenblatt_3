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

    /* list constructor and inilisation list */
    List():
      size_{0},
      first_{nullptr},
      last_{nullptr}{}
    

    /* copy constructer using Deep-Copy semantic */
    List(List<T> const& l):
      size_{0},
      first_{nullptr},
      last_{nullptr}{
      ListNode<T>* tmp = l.first_;
      while(tmp != nullptr){
        push_back(tmp->value);
        tmp = tmp->next;    
      }
    }

    // test and implement:
    // TODO: Move-Konstruktor (Aufgabe 3.9)

    //TODO: Initializer-List Konstruktor (3.10 - Teil 1)
    /* ... */
    // test and implement:
    List(std::initializer_list<T> ini_list) {
      //not implemented yet
    }

    /* assigns values to the container  */
    //memberfunction page 11 vorlesung 7
    List<T>& operator=(List<T> rhs){
      swap(rhs);
      return *this;
    }

    /* checks if the contents of lhs and rhs are equal */
    bool operator==(List const& rhs){
      if(size_ == rhs.size_){
        auto tmp{first_};
        auto tmp_r{rhs.first_};
        while(nullptr != tmp){
          if(tmp->value != tmp_r->value){
            return false;
          }
          tmp = (*tmp).next;
          tmp_r = (*tmp_r).next;
        } 
        return true;      
      }
      else{
       return false;  
      }
    }

    bool operator!=(List const& rhs){
      return !(*this == rhs);
    }

    /* called when the lifetime of an object ends
     purpose  is to free  resources that object may have acquired during its lifetime. */
    ~List() {
      clear();
    }

    /* begin-Method returning an Iterator to the 
       first element in the List */
    ListIterator<T> begin() {
      auto begin = first_;
      return {begin};
    }

    /* end-Method returning an Iterator to element after 
       the last element in the List */
    ListIterator<T> end() {
      auto end = nullptr;
      return {end};
    }

    /* clears the contents */ 
    void clear(){
      while(!empty()){
        pop_front();
      }
    }

    /* ... */
    //TODO: member function insert (Aufgabe 3.13)

    /* ... */
    //TODO: member function insert (Aufgabe 3.14)

    /* changes the sequence of the list */
    void reverse(){
      if(size_ <  2){
        return;
      }
      else{
        std::swap(first_,last_);  
        ListNode<T>* tmp = first_;
        std::swap(tmp->next,tmp->prev);
        while(tmp->next != nullptr){
          tmp = tmp->next;
          std::swap(tmp->next,tmp->prev);
        }    
      }
    }  


    /* inserts an element to the beginning */
    void push_front(T const& element) {
      ListNode<T>* newFront = new ListNode<T>{element};
      if(empty()){
        first_ = newFront;
        last_ = newFront;
      }
      else{
        first_->prev = newFront;
        newFront->next = first_;
        first_ = newFront;
      }
      ++size_;
    }

    /* adds an element to the end  */
    void push_back(T const& element) {
      ListNode<T>* newBack = new ListNode<T>{element};
      if(empty()){
        first_ = newBack;
        last_ = newBack;
      }
      else{
        last_->next = newBack;
        newBack->prev = last_;
        last_ = newBack;
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
        auto noFront = first_->next;
        delete first_;
        first_ = noFront;
        noFront->prev = nullptr;
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
        auto noBack = last_->prev;
        delete last_;
        last_ = noBack;
        noBack->next = nullptr;
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

    /* inisilation of swap for the unifying assignment operator */
    void swap(List<T>& rhs){
      std::swap(first_,rhs.first_);
      std::swap(last_, rhs.last_);
    } 

  // list members
  private: 
    std::size_t size_;
    ListNode<T>* first_;
    ListNode<T>* last_;
};

/* changes the sequence of the list */
template<typename T> 
List<T> reverse(List<T> const& list){
  auto tmp{list};
  tmp.reverse();
  return tmp;
}


/* ... */
//TODO: Freie Funktion operator+ (3.10 - Teil 2)


#endif // # define BUW_LIST_HPP
