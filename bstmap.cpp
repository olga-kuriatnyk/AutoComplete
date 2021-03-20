// Olga Kuriatnyk olhak@uw.edu
// 24 Jan 2021

// BST class
// Creates a BST to store values
// Uses Node which holds the data

#include "bstmap.h"
#include <boost/algorithm/string.hpp>
#include <cassert>

using namespace std;

// default constructor
BSTMap::BSTMap() { root = nullptr; }

// copy constructor
BSTMap::BSTMap(const BSTMap &bst) { this->copyTreeHelper(bst.root); }

// given an array of length n
// create a tree to have all items in that array
// with the minimum height (uses same helper as rebalance)
BSTMap::BSTMap(const vector<value_type> &v) {
  int first = 0;
  int last = v.size() - 1;
  root = createTree(v, first, last);
}

// destructor
BSTMap::~BSTMap() { clear(); }

// true if no nodes in BST
bool BSTMap::empty() const { return (root == nullptr); }

// Number of nodes in BST
int BSTMap::size() const { return sizeHelper(this->root); }

// 0 if empty, 1 if only root, otherwise
// height of root is max height of subtrees + 1
int BSTMap::height() const { return getHeight(root); }

// delete all nodes in tree
void BSTMap::clear() {
  if (root == nullptr) {
    return;
  }
  deleteTree(root);
  root = nullptr;
}

// true if item is in BST
bool BSTMap::contains(const key_type &key) const {
  return containsHelper(root, key);
}

// same as contains, but returns 1 or 0
// compatibility with std::map
size_t BSTMap::count(const string &k) const {
  if (containsHelper(root, k)) {
    return 1;
  }
  return 0;
}

// If k matches the key returns a reference to its value
// If k does not match any key, inserts a new element
// with that key and returns a reference to its mapped value.
BSTMap::mapped_type &BSTMap::operator[](const key_type &k) {
  Node *node = search(this->root, k);
  if (node != nullptr) {
    return node->data.second; // return data.second of found node
  }
  value_type item = value_type(k, mapped_type{});
  return insert(item);
}

// inorder traversal: left-root-right
// takes a function that takes a single parameter of type T
void BSTMap::inorder(void visit(const value_type &item)) const {
  inorderHelper(root, visit);
}

// preorder traversal: root-left-right
// takes a function that takes a single parameter of type T
void BSTMap::preorder(void visit(const value_type &item)) const {
  preorderHelper(root, visit);
}

// postorder traversal: left-right-root
// takes a function that takes a single parameter of type T
void BSTMap::postorder(void visit(const value_type &item)) const {
  postorderHelper(root, visit);
}

// balance the BST by saving all nodes to a vector inorder
// and then recreating the BST from the vector
void BSTMap::rebalance() {
  vector<value_type> v;
  saveToVector(root, v);
  int first = 0;
  int last = v.size() - 1;
  deleteTree(root);
  root = createTree(v, first, last);
}

// returns true if item successfully erased
bool BSTMap::erase(const key_type &k) {
  bool flag = false;
  eraseHelper(root, flag, k);
  return flag;
}

// returns a vector of pair objects that match to the key (not sorted)
vector<BSTMap::value_type> BSTMap::getAll(const key_type &k) const {
  vector<value_type> v;
  getAllHelper(v, root, k);
  return v;
}

// trees are equal if they have the same structure
// AND the same item values at all the nodes
bool BSTMap::operator==(const BSTMap &other) const {
  return isMatchingTree(root, other.root);
}

// not == to each other
bool BSTMap::operator!=(const BSTMap &other) const {
  return !isMatchingTree(root, other.root);
}

// height of a Node, nullptr is 0, root is 1, static, no access to 'this'
// helper function to height(), used by printVertical
int BSTMap::getHeight(const Node *n) {
  if (n == nullptr) {
    return 0;
  }
  if (n->left == nullptr && n->right == nullptr) {
    return 1;
  }
  int leftH = getHeight(n->left);
  int rightH = getHeight(n->right);
  if (leftH >= rightH) {
    return leftH + 1;
  }
  return rightH + 1;
}

////////////////////////////////
/////// Helper Functions ///////
////////////////////////////////

// create new node function
BSTMap::Node *BSTMap::createNode(const value_type &item) {
  auto tempNode = new Node();
  tempNode->data = item;
  tempNode->left = nullptr;
  tempNode->right = nullptr;
  return tempNode;
}

// helper function that creates an identical copy of a tree
void BSTMap::copyTreeHelper(Node *nFrom) {
  this->insert(nFrom->data);
  if (nFrom->left != nullptr) {
    copyTreeHelper(nFrom->left);
  }
  if (nFrom->right != nullptr) {
    copyTreeHelper(nFrom->right);
  }
}

// helper function to create BST from the vector
BSTMap::Node *BSTMap::createTree(const vector<value_type> &v, const int &first,
                                 const int &last) {
  if (first > last) {
    return nullptr;
  }
  int mid = (first + last) / 2;
  Node *temp = createNode(v[mid]);
  temp->left = createTree(v, first, mid - 1);
  temp->right = createTree(v, mid + 1, last);
  return temp;
}

// helper recursive deleting of all nodes in the tree
void BSTMap::deleteTree(Node *root) {
  if (root != nullptr) {
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
  }
}

// helper function for counting number of nodes in BST
int BSTMap::sizeHelper(Node *root) const {
  if (root == nullptr) {
    return 0;
  }
  return (sizeHelper(root->left) + 1 + sizeHelper(root->right));
}

// helper function accepts node and key, returns true if item is in BST
bool BSTMap::containsHelper(Node *n, const key_type &key) const {
  if (n == nullptr) {
    return false;
  }
  if (key == n->data.first) {
    return true;
  }
  if (key < n->data.first) {
    return containsHelper(n->left, key);
  }
  return containsHelper(n->right, key);
}

// helper function to search a given key in a given BST
BSTMap::Node *BSTMap::search(Node *root, const key_type &k) const {
  if (root == nullptr || root->data.first == k) {
    return root;
  }
  if (root->data.first < k) { // key if greater than root's key
    return search(root->right, k);
  }
  return search(root->left, k);
}

// insert fanction that inserts the element if no such key exists
// return the mapped_type of the item that was inserted
BSTMap::mapped_type &BSTMap::insert(const value_type &item) {
  if (root == nullptr) {
    root = createNode(item);
    return root->data.second;
  }
  Node *curr = recursiveInsert(root, item);
  return curr->data.second;
}

// recursive insert helper function that return the Node
// of the item that was inserted
BSTMap::Node *BSTMap::recursiveInsert(Node *curr, const value_type &item) {
  if (curr->data < item) {
    if (curr->right == nullptr) {
      Node *insertNode = createNode(item);
      curr->right = insertNode;
      curr = curr->right;
    } else {
      return recursiveInsert(curr->right, item);
    }
  } else if (curr->data > item) {
    if (curr->left == nullptr) {
      Node *insertNode = createNode(item);
      curr->left = insertNode;
      curr = curr->left;
    } else {
      return recursiveInsert(curr->left, item);
    }
  }
  return curr;
}

// inorder helper traversal: left-root-right
// takes a node and a function that takes a single parameter of type T
void BSTMap::inorderHelper(Node *n, void visit(const value_type &item)) const {
  if (n == nullptr) {
    return;
  }
  inorderHelper(n->left, visit);
  visit(n->data);
  inorderHelper(n->right, visit);
}

// preorder helper traversal: root-left-right
// takes a node and a function that takes a single parameter of type T
void BSTMap::preorderHelper(Node *n, void visit(const value_type &item)) const {
  if (n == nullptr) {
    return;
  }
  visit(n->data);
  preorderHelper(n->left, visit);
  preorderHelper(n->right, visit);
}

//  postorder helper traversal: left-right-root
// takes a node and a function that takes a single parameter of type T
void BSTMap::postorderHelper(Node *n,
                             void visit(const value_type &item)) const {
  if (n == nullptr) {
    return;
  }
  postorderHelper(n->left, visit);
  postorderHelper(n->right, visit);
  visit(n->data);
}

// save all nodes from BST to a vector inorder
void BSTMap::saveToVector(Node *n, vector<value_type> &v) {
  if (n == nullptr) {
    return;
  }
  saveToVector(n->left, v);
  v.push_back(n->data);
  saveToVector(n->right, v);
}

// erase helper function
// acepts BST root and a key, delets the key and returns the new root
// flag is true when delete was successful
BSTMap::Node *BSTMap::eraseHelper(Node *n, bool &flag, const key_type &k) {
  if (n == nullptr) {
    return n;
  }
  if (k < n->data.first) {
    n->left = eraseHelper(n->left, flag, k);
  } else if (k > n->data.first) {
    n->right = eraseHelper(n->right, flag, k);
  } else {
    // node with only one child or no child
    if (n->left == nullptr) {
      Node *temp = n->right;
      delete n;
      flag = true;
      return temp;
    }
    if (n->right == nullptr) {
      Node *temp = n->left;
      delete n;
      flag = true;
      return temp;
    }
    // node with both children
    Node *temp = minValNode(n->right);
    n->data = temp->data;
    n->right = eraseHelper(n->right, flag, temp->data.first);
  }
  return n;
}

// return the node with minimum key value found in a non-empty BST
BSTMap::Node *BSTMap::minValNode(Node *n) {
  Node *curr = n;
  while (curr->left != nullptr) {
    curr = curr->left;
  }
  return curr;
}

// recursive helper function that finds objects that march to the key
// adds them to a vector of pair objects
void BSTMap::getAllHelper(vector<value_type> &v, Node *n,
                          const key_type &k) const {
  if (n == nullptr) {
    return;
  }
  if (!boost::algorithm::starts_with(n->data.first, k)) {
    if (n->data.first < k) {
      getAllHelper(v, n->right, k);
    } else {
      getAllHelper(v, n->left, k);
    }
  } else {
    v.push_back(n->data);
    getAllHelper(v, n->right, k);
    getAllHelper(v, n->left, k);
  }
}

// recursive helper function for == and != operators
// return true if trees are equals
bool BSTMap::isMatchingTree(Node *n, Node *nOther) const {
  if (n == nullptr && nOther == nullptr) {
    return true;
  }
  if (n == nullptr || nOther == nullptr) {
    return false;
  }
  if (n->data != nOther->data) {
    return false;
  }
  return isMatchingTree(n->left, nOther->left) &&
         isMatchingTree(n->right, nOther->right);
}