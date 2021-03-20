#include "autocomplete.h"
#include "bstmap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void testBSTAll();

// reads the file and stores all objects in BST
// after all items are in the tree calls rebalance()
void Autocomplete::readFile(const string &fileName) {
  ifstream ifs(fileName);
  string readValue;
  int lines;
  getline(ifs, readValue);
  istringstream parseLine(readValue);
  parseLine >> lines;
  for (int i = 0; i < lines; i++) {
    getline(ifs, readValue, '\t');
    istringstream parseValue(readValue);
    int value;
    parseValue >> value;
    string key;
    getline(ifs, key, '\n');
    phrases[key] = value;
  }
  ifs.close();
  phrases.rebalance();
}

// sorter
bool Autocomplete::sortByWeight(BSTMap::value_type &a, BSTMap::value_type &b) {
  return a.second > b.second;
}

// returns sorted by value vector of all strings that start with a given prefix
vector<BSTMap::value_type>
Autocomplete::complete(const BSTMap::key_type &prefix) const {
  vector<BSTMap::value_type> v = phrases.getAll(prefix);
  sort(v.begin(), v.end(), sortByWeight);
  return v;
}
