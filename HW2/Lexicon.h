#include <vector>
#include <string>
using namespace std;

class Lexicon{
 public:
  Lexicon(const char* file_name, unsigned int max_length);
  ~Lexicon();
  string get_word(unsigned int i);
  vector<int>* find_matches(string pattern, vector<int>* choices);

  
  vector<string> word_list;
  vector<vector<int> > full_letter_vectors;
  vector<vector<vector<vector<int> > > > index_vectors;  
};
