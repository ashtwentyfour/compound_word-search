#include <algorithm>
#include <queue>
#include <list> 
#include "trie.h"




/* get the concatenated words */
std::list<std::string> Trie::concatenatedWords() {
  // list of words to be returned
  std::list<std::string> c_words;
  // analyze all the word - suffix pairs
  while(!wsp.empty()) {
    // pop the first pair
    WordSuffixPair p = wsp.front();
    wsp.pop();
    // get the suffix/word from the trie
    std::string suffix(findWord(p.getWord(), p.getSuffix()));
    // if the word or the suffix were found
    if(suffix != "") {
      // if the suffix was found (suffix itself is a word)
      if(p.getSuffix().compare(suffix) == 0 && suffix.size() > 1) {
        // add the word - suffix pair to the queue
	c_words.push_back(p.getWord());
      }
      // form a new suffix from the remaining alphabets
      else if(suffix.size() < p.getSuffix().size()) {
	std::string new_suffix = (p.getSuffix()).substr(suffix.size(),
                 p.getSuffix().size() - suffix.size());
        // add the new pair to the queue for the same word
	WordSuffixPair q(p.getWord(), new_suffix);
	wsp.push(q);
      }
    }
  }

  return c_words;

}




/* add a word to the trie */
void Trie::addWord(const std::string& n) {
  // if the trie is empty
  if(root == NULL)
    root = new Node("r$$t");
  int i = 0;
  std::string s(1,n[0]);
  std::string w("");
  // call the add function
  add(root, n, i, w);

}




/* search for a word or return a prefix of the word */
std::string Trie::findWord(const std::string& wrd, 
                 const std::string& n) {
  int i = 0;
  std::string w("");
  // call the find function
  return find(root, n, i, w, wrd);

}




/* add a word and its prefixes to the trie */
void Trie::add(Node* r, const std::string& n, int i, std::string w) {

  if(i < n.size()) {
    // next character 
    std::string t(1,n[i]);  
    // if the prefix is a child node 
    if(r->isChild(w) && w.size() < n.size() && w.size() > 1) {

      Node* c = r->getChild(w);
      // confirm that the child c is a valid word
      if(c->valid_word()) {

	std::string word(w);
	std::string suffix("");
        // get the respective suffix
	suffix = n.substr(i,n.size() - i);
        // form a word-suffix pair
	WordSuffixPair wp(n , suffix);
        // add pair to the queue
	wsp.push(wp);
        // new child node for the suffix
	Node* suffix_child = new Node(suffix);
	r->addChild(suffix_child);
        // node for the original word (child of the suffix node)
	std::string orig_word = word + suffix;
	Node* the_word = new Node(orig_word);
	the_word->set_as_word();
	suffix_child->addChild(the_word);
        // if the next character is a child node
	if(r->isChild(t)) {
	  Node* temp = r->getChild(t);
	  w += n[i];
	  i++;
	  add(temp, n, i, w);
	}
	// if not continue addition     
	else { 
	  Node* c = new Node(t);
	  r->addChild(c);
	  w += n[i];
	  i++;
	  add(c, n, i, w);
	}
      }
    }
    // if the prefix is a child node
    else if(r->isChild(w) && w.size() == 1 && !r->isChild(t)) {
      Node* child = new Node(t);
      r->addChild(child);
      w += n[i];
      i++;
      add(child, n, i, w);
    }
    // if neither the prefix nor the next character are child nodes
    else if(!r->isChild(w) && !r->isChild(t)) {
      Node* child = new Node(t);
      r->addChild(child);
      w += n[i];
      i++;
      add(child, n, i, w);
    }
    // if the next character after the current prefix is a child
    else if((!r->isChild(w) && r->isChild(t)) || 
           (r->isChild(w) && r->isChild(t))) {
      Node* child = r->getChild(t);
      w += n[i];
      i++;
      add(child, n, i, w);
    }          
  }
  // if the word has been found 
  else if(i == n.size()) {
    Node* child = new Node(w);
    r->addChild(child);
    child->set_as_word();
    return;
  }

}




/* locate a word or prefix in the trie */
std::string Trie::find(Node* r, const std::string& n, int i, std::string w,
                 const std::string& wrd) {

  // if the word has been found
  if(i == n.size()) {
    if(r->isChild(w) && w.size() > 1)
      return w;
    else
      return "";
  }
  
  std::string s(1, n[i]); // next character
  // if the itself word is a child node or continues as a new branch  
  if((r->isChild(s) && !r->isChild(w)) || 
     (r->isChild(s) && r->isChild(w))) {
    
    Node* temp = r->getChild(s);
    // if part of the word is not a child node
    if(!r->isChild(w)) {
      // continue iterating through the characters
      w += n[i];
      i++;
      return find(temp, n, i, w, wrd);
    }
    // if part of the word is a child node
    else {
      // check for multiple prefix matches
      std::string suff = find(temp, n, i + 1, w + n[i], wrd);
      if(suff.compare("") == 0 && w.size() > 1)
	return w;
      else {
	std::string word(wrd);
	std::string temp("");
	for(unsigned int i = w.size(); i < n.size() && w.size() > 1; i++)
	  temp += n[i];
        // add the other pair to the queue
	WordSuffixPair p(word, temp);
	wsp.push(p);
	return suff;
      }
    }
  }
  // if the word prefix is a child node 
  else if(r->isChild(w) && !r->isChild(s) && w.size() > 1) {
    return w;
  }
  // check whether the suffix is a child node
  else {
    for(unsigned int k = 0; k < r->numChildren(); k++) {
      if(n.compare(w + r->getChild(k)->getWord()) == 0 && w.size() > 1)
	return w;
    }
    return "";
  }
}




/* free dynamically allocated memory */
void Trie::destroy(Node* r) {

  // root is null
  if(r == NULL)
    return;
  // if the node has child nodes
  if(r->numChildren() > 0) {
    // delete child nodes
    unsigned int x = r->numChildren();
    Node* temp = NULL;
    for(unsigned int i = 0; i < x; i++) {
      temp = r->getChild(i);
      destroy(temp);
      temp = NULL;
    }
  }
  // free current node
  delete r;
  r = NULL;
  return;

}
