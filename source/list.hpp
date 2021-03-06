#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP
#include <cassert>
#include <cstddef>  //ptrdiff_t
#include <iterator> //std::bidirectional_iterator_tag
#include <iostream>
#include <vector>
#include <initializer_list>

template <typename T>
class List;

template <typename T>
struct ListNode {
  T         value = T{};
  ListNode* prev = nullptr;
  ListNode* next = nullptr;
};


template <typename T>
struct ListIterator {
  using Self              = ListIterator<T>;
  using value_type        = T;
  using pointer           = T*;
  using reference         = T&;
  using difference_type   = ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;


  /* derefenciation of iterator using operator* */
  T&  operator*()  const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }
    return node->value;

  } //call *it

  /* derefenciation of iterator using operator-> */
  T* operator->() const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }
    return &node->value;
  }


  /* PREINCREMENT, call: ++it, advances one element forward */
  ListIterator<T>& operator++() {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }
    else{
      node = node->next;
      return *this;
    }
  }

  /* POSTINCREMENT (signature distinguishes the iterators), 
                    call:  it++, advances one element forward*/
  ListIterator<T> operator++(int) {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }
    else{
      auto tmp = *this;
      ++(*this);
      return tmp;
    }
  }


  /* Equality-Operation for Iterator 
    should be true if it is equal*/
  bool operator==(ListIterator<T> const& x) const {
    return node == x.node;
  } // call it: == it

  /* Equality-Operation for Iterator
   should be false if it is equal*/
  bool operator!=(ListIterator<T> const& x) const {
    return !(node == x.node);
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

    /* move constructer */
    List(List&& rhs):
      size_(rhs.size_),
      first_(rhs.first_),
      last_(rhs.last_){
        rhs.size_ = 0;
        rhs.first_ = nullptr;
        rhs.last_ = nullptr;
      }

    /* object of type std::initializer_list<T> 
    is a lightweight proxy object that provides access to 
    array of objects of type const T */
    List(std::initializer_list<T> ini_list):
      size_{0},
      first_{nullptr},
      last_{nullptr} {
      List<int> list{};
      for(T element : ini_list){
        push_back(element);
      }
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
    ListIterator<T> begin() const{
      return ListIterator<T>{first_};
    }

    /* end-Method returning an Iterator to element after 
       the last element in the List */
    ListIterator<T> end() const{
      return ListIterator<T>{nullptr};
    }

    /* clears the contents */ 
    void clear(){
      while(!empty()){
        pop_front();
      }
    }

    /* inserts node at a names position */
    ListIterator<T> insert(ListIterator<T> const& pos, T const& element){
      if(pos.node == nullptr && pos != end()){
        throw "Iterator does not point to valid node";
      }
      else if(pos == begin()){
        push_front(element);
        return begin();
      }
      else if (pos == end()){
        push_back(element);
        return end();
      }
      else{
        ListNode<T>* node_at_pos = new ListNode<T>{element, pos.node->prev, pos.node};
        pos.node->prev->next = node_at_pos;
        pos.node->prev = node_at_pos;
        ++size_;
        return ListIterator<T>{node_at_pos};
      } 
    }

    /* erases node at named position */
    ListIterator<T> erase(ListIterator<T> const& pos){
      if(empty()){
        throw "List is empty :(";
      }
      else if(pos == begin()){
        pop_front();
        return begin();
      }
      else if(pos == end()){
        pop_back();
        return end();
      }
      else{
        auto tmp = pos.node->next;
        pos.node->prev->next = tmp;
        pos.node->prev = tmp->prev;
        delete pos.node;

        --size_;
        return ListIterator<T>{tmp};
      }
      
    }

  

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

/* objects of list are copied into empty vector*/
template < typename T >
bool has_same_content(List<T> const& list ,std::vector<T> const& vec){
  std::vector<T> copy_vec{};
  std::copy(list.begin(), list.end(), std::back_inserter(copy_vec));
  if(vec != copy_vec){
    return false;
  }
  return true;
}

/* combines two lists into one */
template<typename T>
List<T> operator+(List<T>& list1, List<T>& list2){
  List<T> list{};
  for(T element : list1){
    list.push_back(element);
  }
  for(T element : list2){
    list.push_back(element);
  }
  return list;
}


#endif // # define BUW_LIST_HPP
