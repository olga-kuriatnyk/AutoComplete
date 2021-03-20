#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

#include "bstmap.h"


using namespace std;

class Autocomplete {
public:
  Autocomplete() = default;

  // reads the file and stores all objects in BST
  // after all items are in the tree calls rebalance()
  void readFile(const string &fileName);
  
  //returns sorted by value vector of all strings that start with a given prefix
  vector<BSTMap::value_type> complete(const string &prefix) const;

private:
  // BST of phrases and their frequency
  BSTMap phrases;

  // sorter
  bool static sortByWeight(BSTMap::value_type &a, BSTMap::value_type &b);
};

#endif // AUTOCOMPLETE_H
