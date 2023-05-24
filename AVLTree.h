#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std; 

#include "Node.h"

#ifndef AVLTREE_H
#define AVLTREE_H

class AVLTree {
  public:
    AVLTree();
    void insert(const string&);
    int balanceFactor(Node*);
    void printBalanceFactors();
    void visualizeTree(const string&);
  private:  
    Node *root; 
    void rotate(Node*);
    void rotateLeft(Node*); 
    void rotateRight(Node*); 
    void printBalanceFactors(Node*); 
    void visualizeTree(ofstream&, Node*); 
    Node* searchForParent(const string &);
    // void updateHeight(Node*); // See Node class
    // bool setChild(Node*, string, Node*); // TODO: check if parameters are correct
    // void replaceChild(Node*); // TODO: check if parameters are correct
};

#endif
