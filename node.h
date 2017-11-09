#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <stdlib.h>

using namespace std;

template <class t>
class node{
private:
  t info;
  node<t> *next;
  node<t> *previous;
public:
  node(t n){ info = n; next = previous = NULL;}
  node(){next = previous = NULL;}
  void setInfo(t n){info = n;}
  void setNext(node<t>* p){next = p;}
  void setPrevious(node<t>* p){previous = p;}
  t getInfo(){return info;}
  node<t>* getnext(){return next;}
  node<t>* getPrevious(){return previous;}
};

#endif
