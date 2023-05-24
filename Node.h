#include <iostream>
using namespace std; 

#ifndef NODE_H
#define NODE_H

class Node {
  private:
    string data;
    Node* left;
    Node* right; 
    Node* parent; 
    int height; 
  public:
    // Constructor
    // Node() : data(""), left(0), right(0), parent(0), height(0) {}
    Node(string data) : data(data), left(0), right(0), parent(0), height(0) {}
    // Mutators
    void setData(string); 
    void setLeft(Node*);
    void setRight(Node*);
    void setParent(Node*);
    void replaceChild(Node*, Node*);
    void updateHeight();
    // Accessors
    string getData() const;  
    Node* getLeft() const;
    Node* getRight() const; 
    Node* getParent() const; 
    int getHeight() const; 
    // Comparators
    bool operator!=(const Node&);
    bool operator==(const Node&);
};

#endif
