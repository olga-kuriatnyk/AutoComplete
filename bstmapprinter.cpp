#include "bstmap.h"
#include <cmath>
#include <iomanip>
#include <sstream>

using namespace std;

// print a Node in easy to read format
ostream &operator<<(ostream &out, const BSTMap::Node &n) {
  out << "[" << n.data.first << "=" << n.data.second << "]";
  return out;
}

// display BST tree in a human-readable format
// comment out printSideways or printVertical
ostream &operator<<(ostream &out, const BSTMap &bst) {
  BSTMap::printSideways(out, bst.root);
  out << endl;
  // BSTMap::printVertical(out, bst.root);
  return out;
}

/**
 * print tree sideways with root on left
              6
          2
              5
      0
              4
          1
              3
 */
ostream &BSTMap::printSideways(ostream &out, const Node *curr, int level) {
  const static char space = ' ';
  const static int readabilitySpaces = 4;
  if (curr == nullptr) {
    return out;
  }
  printSideways(out, curr->right, ++level);
  out << setfill(space) << setw(level * readabilitySpaces) << space;
  out << *curr << endl;
  printSideways(out, curr->left, level);
  return out;
}

// helper for printVertical
ostream &BSTMap::centeredPrint(ostream &out, int space, const string &str,
                               char fillChar) {
  auto strL = static_cast<int>(str.length());
  int extra = (space - strL) / 2;
  if (extra > 0) {
    out << setfill(fillChar) << setw(extra + strL) << str;
    out << setfill(fillChar) << setw(space - extra - strL) << fillChar;
  } else {
    out << setfill(fillChar) << setw(space) << str;
  }
  return out;
}

/**
 * print tree with the root at top
 *
    _____0______
 __1___      __2___
3     4     5     6
 *
**/
ostream &BSTMap::printTreeLevel(ostream &out, queue<const Node *> &q, int width,
                                int depth, int maxDepth) {
  const static char space = ' ';
  const static char underline = '_';
  int nodes = 0;
  int maxN = pow(2, depth - 1);
  auto spaceForEachItem = static_cast<int>(width * pow(2, maxDepth - 1) / maxN);
  string bigspace = string(static_cast<uint64_t>(spaceForEachItem / 4), space);
  while (nodes++ < maxN) {
    const Node *tp = q.front();
    Node *tpl = nullptr;
    Node *tpr = nullptr;
    q.pop();
    string label = "N";
    if (tp != nullptr) {
      stringstream ss;
      ss << *tp;
      label = ss.str();
      tpl = tp->left;
      tpr = tp->right;
    }
    char filler = depth == maxDepth ? space : underline;
    if (depth == maxDepth) {
      centeredPrint(out, spaceForEachItem, label, filler);
    } else {
      out << bigspace;
      centeredPrint(out, spaceForEachItem / 2, label, filler);
      out << bigspace;
      q.push(tpl);
      q.push(tpr);
    }
  }
  out << endl;
  return out;
}

// helper function for displaying tree sideways, works recursively
ostream &BSTMap::printVertical(ostream &out, Node *curr) {
  const static int width = 6; // must be even
  if (curr == nullptr) {
    return out << "[__]";
  }
  // figure out the maximum depth which determines how wide the tree is
  int maxDepth = getHeight(curr);
  queue<const Node *> q;
  q.push(curr);
  for (int depth = 1; depth <= maxDepth; ++depth) {
    printTreeLevel(out, q, width, depth, maxDepth);
  }
  return out;
}
