#include "autocomplete.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void testAC01() {
  cout << "Starting AC test01" << endl;
  cout << "* Testing basic autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("small.txt");
  auto v = ac.complete("hel");
  assert(v.size() == 2);
  assert(v[0].first == "help");
  assert(v[0].second == 20);
  assert(v[1].first == "hello");
  assert(v[1].second == 10);
  cout << "Ending tesAC01" << endl;
}

void testAC02() {
  cout << "Starting AC test02" << endl;
  cout << "* Testing cities autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("cities.txt");
  auto v = ac.complete("Sea");
  assert(v.size() == 47);
  assert(v[0].first == "Seattle, Washington, United States");
  assert(v[0].second == 608660);
  assert(v[46].first == "Seabeck, Washington, United States");
  assert(v[46].second == 1105);
  cout << "Ending tesAC02" << endl;
}

void testAC03() {
  cout << "Starting AC test03" << endl;
  cout << "* Testing wiktionary autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("wiktionary.txt");
  auto v = ac.complete("here");
  assert(v.size() == 8);
  assert(v[0].first == "here");
  assert(v[0].second == 72982900);
  assert(v[7].first == "herein");
  assert(v[7].second == 394855);
  cout << "Ending tesAC03" << endl;
}

void testAC04() {
  cout << "Starting AC test04" << endl;
  cout << "* Testing cities autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("cities.txt");
  auto v = ac.complete("Seat");
  assert(v.size() == 5);
  assert(v[0].first == "Seattle, Washington, United States");
  assert(v[0].second == 608660);
  assert(v[1].first == "Seaton, South Australia, Australia");
  assert(v[1].second == 9704);
  assert(v[2].first == "Seaton Delaval, United Kingdom");
  assert(v[2].second == 7219);
  assert(v[3].first == "Seaton, United Kingdom");
  assert(v[3].second == 5240);
  assert(v[4].first == "Seat Pleasant, Maryland, United States");
  assert(v[4].second == 4542);
  cout << "Ending tesAC04" << endl;
}

// Calling all test functions
void testACAll() {
  testAC01();
  testAC02();
  testAC03();
  testAC04();
}