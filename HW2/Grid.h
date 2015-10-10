#include <string>
#include <vector>
#include "Word.h"
using namespace std;

class Grid{
 private:
  void add_word(vector<char*> cw);  
 public:
  //Constructor / Destructor
  Grid(string s, unsigned const int l);
  ~Grid();

  //Structures and Properties
  unsigned int side_length;
  char*** slots;
  vector<Word*> words;

  //Modification
  void clear();
  
  //Printing Functions
  void printGrid();
  void printWords();
};
