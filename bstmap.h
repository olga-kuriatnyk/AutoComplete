// Olga Kuriatnyk olhak@uw.edu
// 24 Jan 2021

// BST class
// Creates a BST to store values
// Uses Node which holds the data
// Uses templates to store any type of data
// binarysearchtreee.cpp file is included at the bottom of the .h file
// binarysearchtreee.cpp is part of the template, cannot be compiled separately

#ifndef BSTMAP_H
#define BSTMAP_H

#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

class BSTMap {

  // display BST tree in a human-readable format
  // comment out printSideways or printVertical
  friend ostream &operator<<(ostream &out, const BSTMap &bst);

public:
  using key_type = string;
  using mapped_type = uint64_t;
  using value_type = pair<key_type, mapped_type>;

  // constructor, empty tree
  BSTMap();

  // copy constructor
  BSTMap(const BSTMap &bst);

  // given an array of length n
  // create a tree to have all items in that array
  // with the minimum height (uses same helper as rebalance)
  explicit BSTMap(const vector<value_type> &v);

  // destructor
  virtual ~BSTMap();

  // move not allowed
  BSTMap(BSTMap &&other) = delete;

  // assignment not allowed
   BSTMap &operator=(const BSTMap &other) = delete;
  
  // move assignment not allowed
  BSTMap &operator=(BSTMap &&other) = delete;

  // true if no nodes in BST
  bool empty() const;

  // Number of nodes in BST
  int size() const;

  // 0 if empty, 1 if only root, otherwise
  // height of root is max height of subtrees + 1
  int height() const;

  // delete all nodes in tree
  void clear();

  // true if item is in BST
  bool contains(const key_type &key) const;

  // same as contains, but returns 1 or 0
  // compatibility with std::map
  size_t count(const key_type &k) const;

  // If k matches the key returns a reference to its value
  // If k does not match any key, inserts a new element
  // with that key and returns a reference to its mapped value.
  mapped_type &operator[](const key_type &k);

  // inorder traversal: left-root-right
  // takes a function that takes a single parameter of type T
  void inorder(void visit(const value_type &item)) const;

  // preorder traversal: root-left-right
  void preorder(void visit(const value_type &item)) const;

  // postorder traversal: left-right-root
  void postorder(void visit(const value_type &item)) const;

  // balance the BST by saving all nodes to a vector inorder
  // and then recreating the BST from the vector
  void rebalance();

  // returns true if item successfully erased - BONUS
  bool erase(const key_type &k);

  //returns a vector of pair objects that match to the key (not sorted)
  vector<value_type> getAll(const key_type &k) const;

  // trees are equal if they have the same structure
  // AND the same item values at all the nodes
  bool operator==(const BSTMap &other) const;

  // not == to each other
  bool operator!=(const BSTMap &other) const;

private:
  // Node for BST
  struct Node {
    // key-value pair
    value_type data;
    // children
    struct Node *left = nullptr;
    struct Node *right = nullptr;
  };

  // refer to data type "struct Node" as Node
  using Node = struct Node;

  // print Node
  friend ostream &operator<<(ostream &out, const Node &n);

  // root of the tree
  Node *root{nullptr};

  // print tree sideways with root on left
  static ostream &printSideways(ostream &out, const Node *curr, int level = 0);

  // helper for printVertical
  static ostream &centeredPrint(ostream &out, int space, const string &str,
                                char fillChar = ' ');

  // print tree with the root at top
  static ostream &printTreeLevel(ostream &out, queue<const Node *> &q,
                                 int width, int depth, int maxDepth);

  // helper function for displaying tree sideways, works recursively
  static ostream &printVertical(ostream &out, Node *curr);

  // height of a Node, nullptr is 0, root is 1, static, no access to 'this'
  // helper function to height(), used by printVertical
  static int getHeight(const Node *n);


  ////////////////////////////////
  /////// Helper Functions ///////
  ////////////////////////////////

  // create new node function
  Node* createNode(const value_type &item);

  // helper function that creates an identival copy of a tree
  void copyTreeHelper(Node *nFrom); 

  // helper function to create BST from the vector
  Node* createTree(const vector<value_type> &v, const int &first, const int &last);

  // recursive deleting of all nodes in the tree
  void deleteTree(Node *root);

  // helper function for counting number of nodes in BST
  int sizeHelper(Node *root) const;

  // helper function accepts node and key, returns true if item is in BST
  bool containsHelper(Node *n, const key_type &key) const;

  // helper function to search a given key in a given BST
  Node* search(Node *root, const key_type &k) const;

  // insert fanction that inserts the element if no such item exists
  // return the mapped_type of the item that was inserted
  mapped_type& insert(const value_type &item);

  // recursive insert helper function that return the Node
  // of the item that was inserted
  Node* recursiveInsert(Node *curr, const value_type &item);

  // inorder helper traversal: left-root-right
  // takes, a node and a function that takes a single parameter of type T
  void inorderHelper(Node *n, void visit(const value_type &item)) const;

  // preorder helper traversal: root-left-right
  // takes a node and a function that takes a single parameter of type T
  void preorderHelper(Node *n, void visit(const value_type &item)) const;

  //  postorder helper traversal: left-right-root
  // takes a node and a function that takes a single parameter of type T
  void postorderHelper(Node *n, void visit(const value_type &item)) const;

  // save all nodes from BST to a vector inorder
  void saveToVector(Node *n, vector<value_type> &v);

  // erase helper function
  // acepts BST root and a key, delets the key and returns the new root
  // flag is true when delete was successful
  Node* eraseHelper(Node *n, bool &flag, const key_type &k);

  // return the node with minimum key value found in a non-empty BST
  Node* minValNode(Node *n);

  // recursive helper function that finds objects that march to the key 
  // adds them to a vector of pair objects 
  void getAllHelper(vector<value_type> &v, Node *n, const key_type &k) const;

  // recursive helper function for == and != operators
  // return true if trees are equals
  bool isMatchingTree(Node *n, Node *nOther) const;
};

#endif // BSTMAP_H
