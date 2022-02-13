#include <string>

/* 
 * Objects of this class represent a word 
 * and one of its suffixes
*/

class WordSuffixPair {

 public:
   
  WordSuffixPair(std::string w, std::string s) { // w -> word, s -> suffix
    word = w;
    suffix = s;
  }

  const std::string& getWord() const { // returns the word
    return word;
  }

  const std::string& getSuffix() const { // returns the suffix
    return suffix;
  }

 private:
   
  std::string word; // word
  std::string suffix; // suffix

};
