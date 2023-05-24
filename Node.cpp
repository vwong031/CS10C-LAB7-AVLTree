#include "Node.h"

// Mutators
void Node::setData(string data) {
  this->data = data;
}

// AVLTreeSetChild: https://learn.zybooks.com/zybook/UCRCS010CSpring2021/chapter/7/section/2
void Node::setLeft(Node* node) {
  left = node;
  if (node) {
    node->setParent(this);
  }
  updateHeight();
}

// AVLTreeSetChild: https://learn.zybooks.com/zybook/UCRCS010CSpring2021/chapter/7/section/2
void Node::setRight(Node* node) {
  right = node;
  if (node) {
    node->setParent(this);
  }
  updateHeight();
}

// AVLTreeReplaceChild: https://learn.zybooks.com/zybook/UCRCS010CSpring2021/chapter/7/section/2
void Node::replaceChild(Node *node, Node *replacement) {
  if (left == node) {
    left = replacement;
  }
  else if (right == node) {
    right = replacement;
  }
  if (replacement) {
    replacement->setParent(this);
  }
}

// AVLTreeUpdateHeight: https://learn.zybooks.com/zybook/UCRCS010CSpring2021/chapter/7/section/2
void Node::updateHeight() {
  // Precondition: Each child is already storing its correct height
  int leftHeight, rightHeight, maxChildHeight;
  /*
  ternary operator
  https://learn.zybooks.com/zybook/UCRCS010CSpring2021/chapter/13/section/18?content_resource_id=46785035
  a ? b : c; checks if expression before ? is true
  if a is true, use b
  if a is false, use c
  */
  leftHeight = left ? left->height : -1;
  rightHeight = right ? right->height : -1;
  maxChildHeight = (leftHeight > rightHeight) ? leftHeight : rightHeight;
  
  height =  maxChildHeight + 1;
}

void Node::setParent(Node* node) {
  parent = node;
}


// Accessors
string Node::getData() const {
  return data; 
}

Node* Node::getLeft() const {
  return left; 
}

Node* Node::getRight() const {
  return right;
}

Node* Node::getParent() const {
  return parent; 
}

int Node::getHeight() const {
  return height; 
}

// Comparators
bool Node::operator!=(const Node &node) {
  return !(*this == node);
}

bool Node::operator==(const Node &node) {
  return (node.getData() == data);
}
