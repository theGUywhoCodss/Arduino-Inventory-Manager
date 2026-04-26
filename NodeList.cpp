#include "NodeList.h"

// ---------- Iterator ----------
NodeList::Iterator::Iterator(Node* u) // constructor from Node*
{// when called, an Iterator object will be created
  v = u;
} 

Elem& NodeList::Iterator::operator*() // reference to the element
{
  return v->elem; // v is the Node in Iterator
}

NodeList::Iterator& NodeList::Iterator::operator++() // move to next position
{
  if (v->next == NULL) return *this;
  v = v->next; // the stored node in Iterator becomes the next one

  return *this; // returns a reference to the current Iterator object itself (after it has moved forward).
}

NodeList::Iterator& NodeList::Iterator::operator--() // move to previous position
{
  v = v->prev; // the stored node in Iterator becomes the previous one
  return *this;
}

// ---------- NodeList ----------

NodeList::NodeList() { // constructor
  n = 0;              // initially empty
  header = new Node;  // create sentinels, normally does not store data, not effective node
  trailer = new Node;
  header->next = trailer; // have them point to each other
  trailer->prev = header;

  // (optional but safe) initialize the other links
  header->prev = NULL;
  trailer->next = NULL;
}

NodeList::~NodeList() {
  clear();
  delete header; // Free the memory allocated for the header sentinel node.
  delete trailer; // Free the memory allocated for the trailer sentinel node.
  header = NULL;
  // Set the header pointer to NULL (nullptr in modern C++).
// This avoids a dangling pointer (pointer still pointing to freed memory
// which previously stores the header node).
  trailer = NULL;
}

void NodeList::clear() {
  // remove all real nodes between header and trailer
  while (!empty()) {
    eraseFront();
  }
}

NodeList::Iterator NodeList::begin() const // begin position is first item
{
  return Iterator(header->next); 
  // Create and return an Iterator object.
// The iterator is initialized to point to the FIRST data node.
// header->next skips the header sentinel and points to the first real element.
// This is typically used in begin() to start traversal.
}

NodeList::Iterator NodeList::end() const // end position is just beyond last
{
  return Iterator(trailer);
  // Create and return an Iterator object pointing to the trailer sentinel node.
// The trailer represents the position *after* the last data element.
// This is typically used as end() in a doubly linked list.
// It does NOT point to a real data node, but marks the stopping position for iteration.
}

// insert e before p
void NodeList::insert(const NodeList::Iterator& p, const Elem& e) {
  Node* w = p.v;        // p’s node
  Node* u = w->prev;    // p’s predecessor
  Node* x = new Node;   // new node to insert

  x->elem = e;
  x->next = w;  w->prev = x; // link in x before w
  x->prev = u;  u->next = x; // link in x after u
  n++;
}

void NodeList::insertFront(const Elem& e) // insert at front
{
  insert(begin(), e); // insert before the previous FIRST data node
  //the node that contains e becomes the new fisrt DATA node
}

void NodeList::insertBack(const Elem& e) // insert at rear
{
  insert(end(), e); // insert before trailer, the node that contains e becomes
  // the new last DATA node
}

void NodeList::erase(const Iterator& p) { // remove p
  Node* x = p.v;       // node that p stores, to be removed
  Node* w = x->next;   // successor
  Node* u = x->prev;   // predecessor
  u->next = w;  w->prev = u; // unlink p
  delete x;             // delete this node
  n--;                  // one fewer element
}

void NodeList::eraseFront() // remove first
{
  erase(begin()); //erase FIRST data node
}

void NodeList::eraseBack() // remove last data node
{
  Iterator it = end(); // trailer
  --it;           // equivalent to --end() but avoids temporary issues
  // Iterator it points to last data node now
  erase(it);
}