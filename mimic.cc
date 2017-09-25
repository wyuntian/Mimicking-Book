#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "treap.h"

using namespace std;

// Replace all characters except letters (A-Z,a-z) in line with ' ',
// except keep '-' or '\'' if they are between letters.
void lowercaseWords(string & line) {
  for( string::iterator it = line.begin(); it != line.end(); ++it ) {
    if( !isalpha(*it) ) {
      if( (*it != '-' && *it != '\'') ||
	  it == line.begin() || it+1 == line.end() ||
	  !isalpha(*(it-1)) || !isalpha(*(it+1)) ) {
	*it = ' ';
      }
    } else {
      *it = tolower(*it);
    }
  }
}

int Treap::find(const std::string& key){

  TreapNode *curr=root;
  while(curr){
        if(key==curr->key){
            return curr->value;
        }else if(key<curr->key){
            curr=curr->left;
        }else{
            curr=curr->right;
        }
    }
    return -1;

}

void rotateRight(TreapNode *& a){
    TreapNode * b = a->left;
    a->left=b->right;
    b->right=a;
    a=b;
}

void rotateLeft(TreapNode *& a){
    TreapNode * b = a->right;
    a->right = b->left;
    b->left = a;
    a=b;
}

void insertNode(TreapNode *& troot, TreapNode *& i){
    if(troot==NULL){
        troot = i;
    }else{
        if(i->key<troot->key){
            insertNode(troot->left,i);
            if(troot->left->priority < troot->priority){

                    rotateRight(troot);
            }
        }else{
            insertNode(troot->right, i);
            if(troot->right->priority < troot->priority){

                    rotateLeft(troot);
            }
        }
    }
}

void Treap::insert(const std::string& key, int value){

  TreapNode * iNode = new TreapNode;
  iNode->key = key;
  iNode->value = value;
  iNode->priority = rand()%1000;
  iNode->left = NULL;
  iNode->right = NULL;

    insertNode(root,iNode);

}

int main(int argc, char *argv[]) {
  if( argc < 2 || argc > 3 ) {
    cerr << "Usage: " << argv[0] << " n book.txt" << endl;
    exit(1);
  }

  int n = atoi(argv[1]);

    Treap * myTreap = new Treap;
    int r = 0;
    int getRank = 0;
    vector<string> words; // word[r] is the r-th word
    vector<int> all_word_ranks; //ranks of all words in the text
    vector<vector<int>> follower_ranks; //followers_ranks[r] is a vector of ranks of followers of word[r]
  
  ifstream fin;
  fin.open(argv[2]);
  if( !fin.is_open() ) {
    cerr << "Unable to open " << argv[1] << endl;
    exit(2);
  }
  string line;
  string word;
  while( !fin.eof() ) {
    getline(fin,line);
    lowercaseWords(line);
    istringstream iss(line, istringstream::in);
    while( iss >> word ) {
        if(myTreap->find(word)==-1) {
            if (r == 0) {
                vector<int> newVec;
                follower_ranks.push_back(newVec);
                all_word_ranks.push_back(r);
                myTreap->insert(word, r);
                words.push_back(word);
                r++;
            } else {
                vector<int> newVec;
                int allSize = (int)all_word_ranks.size();

                int lastWordRank = all_word_ranks[allSize - 1];
                follower_ranks[lastWordRank].push_back(r);
                follower_ranks.push_back(newVec);
                all_word_ranks.push_back(r);
                myTreap->insert(word, r);
                words.push_back(word);
                r++;
            }
        }else{
            getRank = myTreap->find(word);
            int allSize = (int)all_word_ranks.size();
            int lastWordRank = all_word_ranks[allSize - 1];
            follower_ranks[lastWordRank].push_back(getRank);
            all_word_ranks.push_back(getRank);
        }
    }
  }
  fin.close();



    if(n==0) {
        for (int i = 0; i < follower_ranks.size(); i++) {
            std::cout << words[i] << ":";
            for (int j = 0; j < follower_ranks[i].size(); j++) {
                std::cout << words[follower_ranks[i][j]] + " ";
            }
            std::cout << std::endl;
        }
    }else{
    vector<int> A = all_word_ranks;            //set A to be the vector of all word ranks
    for (int k = 0; k < n; k++) {     //repeat size() times
        int i = int(rand() % A.size());  //choose a random index i into A
        std::cout << words[A[i]] + " ";     //A=follower_ranks[A[i]];
        if (follower_ranks[A[i]].size() != 0) {
            A = follower_ranks[A[i]];    //set A to be the vector followers[A[i]]
        } else {
            A = all_word_ranks;          //set A to be all word ranks;
        }
    }
        std::cout<<std::endl;
}
  return 0;
}
