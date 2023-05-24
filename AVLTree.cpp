// Collaborated with: Valerie Wong, Kira Hammond, zyBooks

/* Compile command:
   g++ AVLTree.cpp Node.cpp main.cpp -Wall -Werror -o a.out
   */

#include "AVLTree.h"

AVLTree::AVLTree() {
  root = 0;
}

void AVLTree::insert(const string &word) {
  Node *parent = 0;
  Node *node = new Node(word);
  
  parent = searchForParent(word);
  if (root == 0) {
    // insert at root
    // cout << "Inserting at root" << endl;
    root = node;
  }
  else if (parent == 0) {
    // Node already in tree
    return;
  }
  else if (word < parent->getData()) {
    // insert as left leaf
    // cout << "Inserting as left leaf" << endl;
    parent->setLeft(node);
  }
  else {
    // insert as right leaf
    // cout << "Inserting as right leaf" << endl;
    parent->setRight(node);
  }
  node->setParent(parent);

  visualizeTree("BeforeRotation.dot");
  while (node) {
    // cout << endl << "Rebalancing " << node->getData() << endl;
    rotate(node);
    // cout << "Moving from " << node->getData() << " to parent" << endl;
    node = node->getParent();
  }
  visualizeTree("AfterRotation.dot");
  
  // cout << "Finished inserting" << endl;
}

Node* AVLTree::searchForParent(const string &word) {
  Node *curr = 0;
  Node *parent = 0;
  
  if (root == 0) {
    // insert at root
    return 0;
  }
  else {
    curr = root;
    // while curr is not null
    while (curr != 0) {
      // if word < curr, look to left subtree
      if (word < curr->getData()) {
        // if left subtree is null, insert here
        if (curr->getLeft() == 0) {
          // found parent for node
          parent = curr;
          break;
        }
        else {
          // if left subtree is not null, traverse left
          curr = curr->getLeft();
        }
      }
      else if (word > curr->getData()) {
        // if word > curr, look right subtree
        if (curr->getRight() == 0) {
          // found parent for node
          parent = curr;
          break;
        }
        else {
          // else traverse right 
          curr = curr->getRight();
        }
      }
      else {
        // Node already in tree
        parent = 0;
        break;
      }
    }
  }
  
  return parent;
}

// AVLTreeGetBalance: https://learn.zybooks.com/zybook/UCRCS010CSpring2021/chapter/7/section/2
int AVLTree::balanceFactor(Node* node) {
  // Precondition: Each child is already storing its correct height
  int leftHeight = -1;
  int rightHeight = -1; 

  if (!node) {
    // cout << "node doesn't exist... returning 0" << endl; 
    return 0; 
  }
  // cout << "finding balance factor of " << node->getData() << endl;
  
  if (node->getLeft()) {
    leftHeight = node->getLeft()->getHeight(); 
  }

  if (node->getRight()) {
    rightHeight = node->getRight()->getHeight();
  }
 

  return leftHeight - rightHeight;
}

void AVLTree::printBalanceFactors() {
  printBalanceFactors(root);
  cout << endl;
}

void AVLTree::printBalanceFactors(Node *node) {
  if (!node) {
    return;
  }
  printBalanceFactors(node->getLeft());
  cout << node->getData() << "(" << balanceFactor(node) << "), ";
  printBalanceFactors(node->getRight());
}

// AVLTreeRebalance: https://learn.zybooks.com/zybook/UCRCS010CSpring2021/chapter/7/section/2
void AVLTree::rotate(Node* node) {
  // Precondition: Each child is already storing its correct height
  // cout << "----rotate function----" << endl; 
  // cout << "updating height..." << endl;
  node->updateHeight();
  int nodeBF = balanceFactor(node);
  // cout << "Found node's balance factor" << endl;
  int rightBF = balanceFactor(node->getRight());
  // cout << "Found right child's balance factor" << endl;
  int leftBF = balanceFactor(node->getLeft());
  // cout << "Found left child's balance factor" << endl;
  
  // cout << "Done finding balance factors" << endl;
  if (nodeBF == -2) {
    // cout << "node's BF = -2" << endl;
    if (rightBF == 1) {
      // cout << "right child's BF = 1" << endl; 
      // double rotation case
      rotateRight(node->getRight());
    }
    rotateLeft(node);
  } 
  else if (nodeBF == 2) {
    // cout << "node's BF = 2" << endl;
    if (leftBF == -1) {
      // cout << "left child's BF = -1" << endl;
      // double rotation case
      rotateLeft(node->getLeft());
    }
    rotateRight(node);
  }

  // cout << "Done rotating" << endl;

}

void AVLTree::rotateLeft(Node *node) {
  Node *rightChild = node->getRight();
  Node *rightLeftChild = rightChild->getLeft(); 
  Node *parent = node->getParent(); 

  if (parent != 0) {
    // rotate internal node left
    parent->replaceChild(node, rightChild);
  }
  else {
    // rotate root left
    root = rightChild; 
    root->setParent(0);
  }
  rightChild->setLeft(node);
  node->setRight(rightLeftChild);
}

// AVLTreeRotateRight: https://learn.zybooks.com/zybook/UCRCS010CSpring2021/chapter/7/section/2
void AVLTree::rotateRight(Node *node) {
  Node *leftChild = node->getLeft();
  Node *leftRightChild = leftChild->getRight();
  Node *parent = node->getParent();

  if (parent != 0) {
    // rotate internal node right
    parent->replaceChild(node, leftChild);
  } else {
    // rotate root right
    root = leftChild;
    root->setParent(0);
  }
  leftChild->setRight(node);
  node->setLeft(leftRightChild);
}

void AVLTree::visualizeTree(const string &outputFilename)
{
  ofstream outFS(outputFilename.c_str());
  if (!outFS.is_open())
  {
    cout << "Error" << endl;
    return;
  }
  outFS << "digraph G {" << endl;
  visualizeTree(outFS, root);
  outFS << "}";
  outFS.close();
  string jpgFilename = outputFilename.substr(0, outputFilename.size() - 4) + ".jpg";
  string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
  system(command.c_str());
}

void AVLTree::visualizeTree(ofstream &outFS, Node *n)
{
  if (n)
  {
    if (n->getLeft())
    {
      visualizeTree(outFS, n->getLeft());
      outFS << n->getData() << " -> " << n->getLeft()->getData() << ";" << endl;
    }

    if (n->getRight())
    {
      visualizeTree(outFS, n->getRight());
      outFS << n->getData() << " -> " << n->getRight()->getData() << ";" << endl;
    }
  }
}
