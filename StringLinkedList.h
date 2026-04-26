#ifndef STRINGLINKEDLIST_H  // Begin include guard to prevent multiple inclusion of this header file
#define STRINGLINKEDLIST_H  // Define the macro used for the include guard

#include <Arduino.h>  // Include Arduino core library for String and other Arduino features

class StringNode {  // Define a node class for a singly linked list of strings
private:  
  String elem;  // Store the string element in this node
  StringNode* next;  // Store a pointer to the next node in the list
  friend class StringLinkedList;  // Allow StringLinkedList class to access private members of StringNode
};  // End of StringNode class

class StringLinkedList {  // Define a singly linked list class for strings
public:  
  StringLinkedList()  // Define the constructor for an empty list
    : head(NULL),cur(head) { }  // Initialize the head pointer to NULL indicating an empty list

  ~StringLinkedList();  // Declare the destructor to clean up dynamically allocated nodes

  bool empty() const  // Define a function to check whether the list is empty
  { return head == NULL; }  // Return true if head is NULL meaning no nodes exist

  const String& front() const  // Define a function to access the front element
  { return head->elem; }  // Return a reference to the string stored in the head node
  void operator*(); //Gets currentNode
  void operator++(); // Moves currentNode

  void addFront(const String& e);  
  // Declare a function to insert a new node, that holds a String data, at the front of the list
  void removeCurrent();
  void resetCurrent();
  String getCurrent();
  int getSize();
  void removeFront();
  void addSorted(const String &e);
  void addLast(const String& e);
private:  
  StringNode* head = NULL;  // Store a pointer to the first node in the list
  StringNode* cur = NULL;
  int size = 0;
};  // End of StringLinkedList class

#endif  // End of include guard to prevent multiple inclusion