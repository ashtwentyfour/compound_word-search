#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <cstdlib>
#include <algorithm>
#include "trie.h"

// used in sorting a list of words by length 
bool compare_length(std::string& x, std::string& y) {
  return x.size() > y.size();
}


int main(int argc , char* argv[]) {

  // two command line arguments
  if(argc != 3) {
    std::cerr<<"Incorrect number of input arguments"<<std::endl;
    exit(1);
  }

  // .txt list of words
  std::ifstream file(argv[1]); 
  if(!file) {
    std::cerr<<"Unable to find/input file";
    exit(1);
  }
  
  // if flag > 0 print output to file
  int flag = atoi(argv[2]);
  // read in each word
  std::string line;
  // trie data structure used to store words and prefixes
  Trie words;
  // read each word and add it to the trie
  while(file >> line) {
    words.addWord(line);
  }
  file.close();
  
  // return the list of required words  
  std::list<std::string> wrds = words.concatenatedWords(); 
  // if no concatenated words exist  
  if(wrds.size() == 0) {
    std::cout<<"no concatenated words found"<<std::endl;
    exit(0);
  } 
  wrds.sort();
  wrds.unique();
  // sort them in descending order of their length
  wrds.sort(compare_length);
  // print the longest and second longest words
  std::list<std::string>::iterator it = wrds.begin();
  std::cout<<"longest concatenated word = "<<*it<<std::endl;
  if(wrds.size() > 1) {
    it++;
    std::cout<<"second longest concatenated word = "<<*it<<std::endl;
  }
  // output the number of words
  std::cout<<"no. of concatenated words = "<<wrds.size()<<std::endl;
  // if an output file is required (flag > 0)
  if(flag > 0) {
    std::ofstream output("concatenated_words.txt");
    for(it = wrds.begin(); it != wrds.end(); it++) 
       output<<*it<<std::endl;
    output.close();
  }

  return 0;

}
