#include <string>
#include <vector>

/*
 * Objects of this class represent nodes in the trie
*/

class Node {

 public:
  Node(std::string d) {
    data = d;
    is_word = false;
  }

  // get specific child node
  Node* getChild(std::string n) const {
    for(unsigned int i = 0; i < children.size(); i++) {
      if(n.compare(children[i]->getWord()) == 0) 
	return children[i];
    }
    return NULL;
  }

  // returns true if the word is in the vocabulary
  bool valid_word() const {
    return is_word;
  }

  // set node as a word node
  void set_as_word() {
    is_word = true;
  }

  // return the number of children
  unsigned int numChildren() const {
    return children.size();
  }

  // add a child node
  void addChild(Node* c) {
    children.push_back(c);
    return;
  }

  // returns true if the string can be found among the child nodes
  bool isChild(std::string c) const {
    if(children.size() == 0) 
       return false;
    for(unsigned int i = 0; i < children.size(); i++) {
      if(c.compare(children[i]->getWord()) == 0) 
         return true;
    }
    return false;
  }

  // return the ith child node
  Node* getChild(int i) const {
    return children[i];
  } 

  // return the word data stored
  const std::string& getWord() const {
    return data;
  }
  
 private:
  
  std::string data; // data (word/alphabet) stored 
  std::vector<Node*> children; // list of child nodes 
  bool is_word; // true if the node is a word (not suffix)  

};
