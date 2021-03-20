// /**
//  * Testing BST - Binary Search Tree functions
//  *
//  * This file has series of tests for BST
//  * Each test is independent and uses assert statements
//  * Test functions are of the form
//  *
//  *      test_netidXX()
//  *
//  * where netid is UW netid and XX is the test number starting from 01
//  *
//  * Test functions can only use the public functions from BST
//  * testBSTAll() is called from main in main.cpp
//  * testBSTAll calls all other functions
//  * @author Multiple
//  * @date ongoing
//  */

#include "bstmap.h"
#include <cassert>
#include <sstream>

using namespace std;

// global value for testing
// NOLINTNEXTLINE
stringstream globalSS;

// need to reset SS before calling this
void printer(const BSTMap::value_type &p) {
  globalSS << "[" << p.first << "=" << p.second << "]";
}

// Testing ==, != and []
void test01() {
  cout << "Starting test01" << endl;
  cout << "* Testing ==, != and []" << endl;
  BSTMap b1;
  auto val = b1["hello"];
  assert(val == 0);
  b1["hello"] = 5;
  val = b1["hello"];
  assert(val == 5);
  b1["world"] = 42;
  b1["alloha"] = 100;
  cout << b1;
  BSTMap b2;
  assert(b1 != b2);
  b2["hello"] = 5;
  b2["world"] = 42;
  b2["alloha"] = 100;
  assert(b1 == b2);
  cout << b2;
  cout << "Ending tes01" << endl;
}

// Testing traversal
void test02() {
  cout << "Starting test02" << endl;
  cout << "* Testing traversal" << endl;
  BSTMap b;
  b["x"] = 10;
  b["f"] = 5;
  b["b"] = 3;
  b["e"] = 4;
  b["z"] = 50;
  cout << b;
  globalSS.str("");
  b.inorder(printer);
  string order = globalSS.str();
  assert(order == "[b=3][e=4][f=5][x=10][z=50]");
  globalSS.str("");
  b.preorder(printer);
  order = globalSS.str();
  assert(order == "[x=10][f=5][b=3][e=4][z=50]");
  globalSS.str("");
  b.postorder(printer);
  order = globalSS.str();
  assert(order == "[e=4][b=3][f=5][z=50][x=10]");
  cout << "Ending test02" << endl;
}

// Testing rebalance
void test03() {
  cout << "Starting test03" << endl;
  cout << "* Testing rebalance" << endl;
  BSTMap b;
  b["1"] = 1;
  b["2"] = 2;
  b["3"] = 3;
  b["4"] = 4;
  b["5"] = 5;
  b["6"] = 6;
  assert(b.height() == 6);
  cout << b << endl;
  b.rebalance();
  assert(b.height() == 3);
  cout << b << endl;
  b.clear();
  assert(b.height() == 0);
  cout << "Ending test03" << endl;
}

// Testing size, contains and count functions
void test04() {
  cout << "Starting test04" << endl;
  cout << "* Testing size, contains and count" << endl;
  BSTMap b;
  assert(b.empty());
  assert(b.contains("x") != true);
  b["x"] = 10;
  b["f"] = 5;
  b["b"] = 3;
  b["z"] = 15;
  assert(b.size() == 4);
  assert(b.contains("x") == true);
  assert(b.count("f") == 1);
  assert(b.contains("z") == true);
  cout << b << endl;
  b.clear();
  assert(b.empty());
  assert(b.contains("x") != true);
  assert(b.count("f") == 0);
  cout << "Ending test04" << endl;
}

// Testing getAll()
void test05() {
  cout << "Starting test05" << endl;
  cout << "* Testing getAll()" << endl;
  BSTMap b;
  b["hello"] = 10;
  b["help"] = 20;
  b["hertz"] = 7;
  b["look"] = 20;
  b["like"] = 30;
  b["lerp"] = 2;
  b["lease"] = 6;
  cout << b << endl;
  auto v = b.getAll("hel");
  assert(v.size() == 2);
  assert(v[0].first == "hello");
  assert(v[0].second == 10);
  assert(v[1].first == "help");
  assert(v[1].second == 20);
  b.rebalance();
  cout << b << endl;
  cout << "Ending test05" << endl;
}

// Testing BSTMap(const vector<value_type> &v)
void test06() {
  cout << "Starting test06" << endl;
  cout << "* Testing BSTMap(const vector<value_type> &v)" << endl;
  BSTMap b;
  b["hello"] = 10;
  b["help"] = 20;
  b["heal"] = 3;
  b["herd"] = 5;
  assert(b.size() == 4);
  auto v = b.getAll("hel");
  assert(v.size() == 2);
  BSTMap d(v);
  cout << d << endl;
  assert(d.size() == 2);
  cout << "Ending test06" << endl;
}

// Testing erase function
void test07() {
  cout << "Starting test07" << endl;
  cout << "* Testing erase function" << endl;
  BSTMap b;
  b["l"] = 0;
  b["a"] = 1;
  b["h"] = 2;
  b["p"] = 1;
  b["m"] = 2;
  b["s"] = 2;
  b["r"] = 3;
  b["t"] = 3;
  assert(b.size() == 8);
  cout << b << endl;
  assert(b.erase("p") == true);
  cout << b << endl;
  assert(b.erase("a") == true);
  assert(b.erase("s") == true);
  assert(b.size() == 5);
  cout << b << endl;
  BSTMap b2;
  assert(b2.erase("a") == false);
  BSTMap b3;
  b3["j"] = 0;
  b3["i"] = 1;
  b3["m"] = 1;
  b3["k"] = 2;
  assert(b3.erase("m") == true);
  cout << "Ending test07" << endl;
}

// Testing Copy constuctor
void test08() {
  cout << "Starting test08" << endl;
  cout << "* Testing Copy constructor" << endl;
  BSTMap b2;
  b2["hello"] = 5;
  b2["world"] = 42;
  b2["alloha"] = 100;
  BSTMap b3(b2);
  cout << b3 << endl;
  assert(b2 == b3);
  BSTMap b4;
  b4["hello"] = 5;
  b4["world"] = 42;
  b4["alloha"] = 1;
  cout << b4 << endl;
  assert(b4 != b3);
  cout << "Ending test08" << endl;
}

// Calling all test functions
void testBSTAll() {
  test01();
  test02();
  test03();
  test04();
  test05();
  test06();
  test07();
  test08();
}