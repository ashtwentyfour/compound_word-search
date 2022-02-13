#include <queue>
#include <algorithm>
#include "node.h"
#include "word_suffix_pair.h"


class Trie {

 public:

  Trie() {
    root = NULL;
  }

  ~Trie() { // release the dynamically allocated memory
    destroy(root);
  }

  // return a list of concatenated words
  std::list<std::string> concatenatedWords();

  // add a new word to the trie
  void addWord(const std::string& n);
  
  // locate a word or its prefix in the trie
  std::string findWord(const std::string& wrd, const std::string& n);
  
 
 private:

  Node* root; // root node of the trie
  std::queue<WordSuffixPair> wsp; // queue which stores all the word and suffix pairs 

  // add a word to the trie
  void add(Node* r, const std::string& n, int i, std::string w);

  // locate a word/prefix in the trie
  std::string find(Node* r, const std::string& n, int i, std::string w,
		   const std::string& wrd);
 
  // free dynamically allocated memory
  void destroy(Node* r);
 
};
           
         

      
           
         
    
  
   






