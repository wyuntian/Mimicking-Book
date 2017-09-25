#ifndef __TREAP
#define __TREAP
#include <string>
#include <cstdlib>
#include <string>

struct TreapNode {
  std::string key;
  int value;
  int priority;
  TreapNode* left;
  TreapNode* right;
  // you can add a constructor
};

class Treap {
  TreapNode *root;
   // TreapNode *curr=root;
  // add more helper functions here
  
 public:
  Treap() { // constructor
    srand(time(0));
     //root=NULL;
    // your code here
  }

  void insert(const std::string& key, int value);

  int find(const std::string& key);
  // return value for the key if found
  // if not found returns -1

};

#endif
