#include <string>
#include <vector>
using namespace std;

class Word{
public:
  Word(unsigned int l);
  Word(char* s[], unsigned int l);
  ~Word();
  unsigned int length;
  char** slots;
  char* initial_setting;

  string string_form();
  void set(string s);  
  void clear();
};
