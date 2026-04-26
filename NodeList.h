#ifndef NODELIST_H
#define NODELIST_H

#include <Arduino.h>

typedef String Elem; // list base element type

struct Node { // a node of the list
  Elem elem;   // element value
  Node* prev;  // previous in list
  Node* next;  // next in list
};

class NodeList { // node-based list
public:
  class Iterator { // an iterator for the list
  public:
    // short member functions defined in class 
    bool operator==(const Iterator& p) const { return v == p.v; } // compare positions
    // v: node in this Iterator; p.v node stored in Iterator p
    bool operator!=(const Iterator& p) const { return v != p.v; }

    // long ones defined outside
    Elem& operator*();                // reference to the element
    Iterator& operator++();           // move to next position
    Iterator& operator--();           // move to previous position

    friend class NodeList;            // give NodeList access

  private:
    Node* v;                          // pointer to the node
    Iterator(Node* u);                // create from node, declare only, no obj. created
    // Constructor, private, only friend class NodeList and Iterator class itself can use it
  }; // end of Iterator class 

public:
  NodeList();                         // default constructor
  ~NodeList();                        // housekeeping (needed to free memory on Arduino)

  // short member functions defined in class
  int size() const { return n; }      // list size
  bool empty() const { return (n == 0); } // is the list empty?

  // long ones defined outside
  Iterator begin() const;             // beginning position
  Iterator end() const;               // (just beyond) last position
  void insertFront(const Elem& e);    // insert at front
  void insertBack(const Elem& e);     // insert at rear
  void insert(const Iterator& p, const Elem& e); // insert e before p
  void eraseFront();                  // remove first
  void eraseBack();                   // remove last
  void erase(const Iterator& p);      // remove p

  // housekeeping functions omitted. . .
  // (We add clear() internally via destructor to avoid memory leak.)

private: // data members
  int n;            // number of items
  Node* header;     // head-of-list sentinel, mark beginning of list
  Node* trailer;    // tail-of-list sentinel, mark end of list

  void clear();     // remove all nodes (helper for destructor)
};

#endif