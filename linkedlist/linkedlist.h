/*
 * LinkedList.h
 * Partial example of a linked list
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <iostream>
#include <cstddef>

using namespace std;

template<typename Element_Type>

class LinkedList {

public:

    // default constructor
    LinkedList() { num_items = 0; head = tail = NULL; }

    // makes a copy of otherList
    LinkedList(const LinkedList &otherList)
        {
            num_items = 0; head = tail = NULL;
            Node *otherNode = otherList.head;
            while (otherNode != NULL) {
                insert(otherNode->data);
                otherNode = otherNode->next;
            }
        }

    // destructor, deallocates node storage
    ~LinkedList()
        { clear(); }

    // insert element at the end of the list
    void insert(Element_Type element)
    {
        // implementation of insert member function
    }

    bool remove(Element_Type element)
    {
        // implementation of remove member function
    }

    // clear out the list, deallocating node storage
    void clear()
    {
        Node *next = head;
        while (next != NULL) {
            next = head->next;
            delete head;
            head = next;
        }
        head = tail = NULL;
        num_items = 0;
    }

    // other public member functions
    // ...
    // ...
    // ...
    
private:
        struct Node {
            Element_Type data;
            Node* next;
        Node(const Element_Type& the_data, Node* next_val = NULL) :
            data(the_data), next(next_val) {}
        };
        Node *head;
        Node *tail;
        int num_items;  //Number of items in the list

};

#endif
