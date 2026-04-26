#include "StringLinkedList.h"  // Include the header file that declares the StringLinkedList class

void StringLinkedList::removeFront() { // Define the function to remove the first node of the list
  if (head == NULL) return;

  size--;
  StringNode* old = head;  // Store the current head node in a temporary pointer
  head = old->next;  // Update head to point to the second node in the list
  delete old;  // Delete the original head node to free memory
}  

void StringLinkedList::addFront(const String& e) {  
  size++;
  // Define the function to add a new node at the front
  StringNode* v = new StringNode;  // Allocate memory for a new node
  v->elem = e;  // Store the given string element into the new node
  v->next = head;  // Make the new node point to the current head
  head = v;  // Update head to point to the new node
  // if we are adding the FIRST node, then the next pointer inside is NULL
}  

StringLinkedList::~StringLinkedList()  // Define the destructor to clean up all nodes
{ while (!empty()) removeFront(); }  // Repeatedly remove the front node until the list is empty

void StringLinkedList::addLast(const String& e) {
  if (head == NULL) {
    addFront(e); // handles size
    return;
  }

  size++;

  StringNode* current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  StringNode* v = new StringNode;
  v->elem = e;
  v->next = NULL;
  current->next = v;
}

void StringLinkedList::removeCurrent() {
  if (cur == NULL) return;

  size--;

  if (cur == head) {
    removeFront();
    cur = head;
    return;
  }

  StringNode* prev = head;
  while (prev->next != cur) {
    prev = prev->next;
  }

  StringNode* old = cur;
  prev->next = cur->next;
  cur = cur->next;

  delete old;

  if (cur == NULL) cur = head;
}

void StringLinkedList::resetCurrent(){
  cur = head;
}

String StringLinkedList::getCurrent(){
  if (cur == NULL) return "Nothing!";
  return cur->elem;
}

void StringLinkedList::operator++(){
  if (cur == NULL) return;
  // Move forward until reach a NULL node
  if(cur->next != NULL){
    cur = cur->next;
  }else{
    cur=head;
  }
}

void StringLinkedList::addSorted(const String &e) {
  // Case 1: empty list OR should go before head
  if (head == NULL || e < head->elem) {
    addFront(e);
    return;
  }

  StringNode* current = head;

  // Traverse until correct position
  while (current->next != NULL && current->next->elem < e) {
    current = current->next;
  }

  // Insert new node
  StringNode* v = new StringNode;
  v->elem = e;
  v->next = current->next;
  current->next = v;

  size++;  // increment only here
}

int StringLinkedList::getSize(){return size;}