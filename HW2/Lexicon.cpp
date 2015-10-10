#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <assert.h>
#include "Lexicon.h"
using namespace std;

Lexicon::Lexicon(const char* file_name, unsigned int max_length){
  word_list = vector<string>(1000000);
  full_letter_vectors = vector<vector<int> >(max_length+1, vector<int>() );
  
  for(unsigned int i = 0; i < max_length+1; i++){
    vector<vector<vector<int> > > n_letter_words;    
    for(unsigned int j = 0; j < i; j++){
      vector<vector<int> > nth_letter_array(26, vector<int>() );      
      n_letter_words.push_back(nth_letter_array);      
    }
    index_vectors.push_back(n_letter_words);
  }
  
  ifstream inFile(file_name);
  if ( !inFile ) {
    cerr << "Cannot open " << file_name << "\n";
    exit( 1 );
  }
  
  string next = "";
  int word_list_index = 0;
  while(inFile >> next && next.length()<=max_length){
    word_list[word_list_index]=next;
    for(unsigned int letter = 0; letter < next.length(); letter++){
      assert(0<=next.length()&&next.length()<=index_vectors.size());
      assert(0<=letter && letter<=index_vectors[next.length()].size());
      assert(0<=((unsigned)next[letter]-'A') && "It's very likely you have lowercase or non-alphanumeric characters in your dictionary!");
      assert(((unsigned)next[letter]-'A')<=index_vectors[next.length()][letter].size()  && "It's very likely you have lowercase or non-alphanumeric characters in your dictionary!");
      assert(0<=next.length() && next.length()<=full_letter_vectors.size());
      
      
      index_vectors[next.length()][letter][next[letter]-'A'].push_back(word_list_index);
    }
    full_letter_vectors[next.length()].push_back(word_list_index);    
    word_list_index++;
  }
}

Lexicon::~Lexicon(){
}

string Lexicon::get_word(unsigned int i){
  if(i<=word_list.size())
    return word_list[i];
  else return "";
}

vector<int>* intersection(vector<int>* s1, vector<int>* s2){
  vector<int>* s3 = new vector<int>();
  set_intersection(s1->begin(), s1->end(),
                   s2->begin(), s2->end(),
                   back_inserter(*s3));
  return s3;
}

vector<int>* difference(vector<int>* s1, vector<int>* s2){
  vector<int>* s3 = new vector<int>();
  set_difference(s1->begin(), s1->end(),
                 s2->begin(), s2->end(),
                 back_inserter(*s3));
  return s3;
}


// void vector_copy(vector<int> s1, vector<int> s2){
//   for(unsigned int i = 0; i < s1.size(); i++)
//     s2.push_back(s1[i]);
// }


vector<int>* Lexicon::find_matches(string pattern, vector<int>* choices){
  // if(!choices->empty()){
  //   for(unsigned int i = 0; i < choices->size(); i++)
  //     cout<<choices->at(i)<<"---"<<get_word(choices->at(i))<<endl;
  //   cout<<"==========="<<endl;
  // }
  
  vector<int>* matches = new vector<int>();
  bool started = false;
  unsigned int pattlength = pattern.length();
  for(unsigned int letter = 0; letter < pattlength; letter++){
    if(pattern[letter] != '?'){
      if(!started){        
        assert(0<=pattlength && pattlength<=index_vectors.size());
        assert(0<=letter && letter<=index_vectors[pattlength].size());
        assert(0<=((unsigned)pattern[letter]-'A') &&
               ((unsigned)pattern[letter]-'A')<=index_vectors[pattlength][letter].size());
        
        vector<int> raw_matches = index_vectors[pattlength][letter][pattern[letter]-'A'];        
        for(unsigned int i = 0; i < raw_matches.size(); i++)
          matches->push_back(raw_matches[i]);

        started = true;
      }else{
        vector<int>* new_matches = intersection(matches,&(index_vectors[pattlength][letter][pattern[letter]-'A']));
        delete matches;
        matches = new_matches;
      }
    }
  }
  if(!started){
    vector<int> raw_matches = full_letter_vectors[pattlength];
    for(unsigned int i = 0; i < raw_matches.size(); i++)
      matches->push_back(raw_matches[i]);
  }
  //vector<int>* sorted_matches = new vector<int>(*matches);
  vector<int>* sorted_choices = new vector<int>(*choices);
  //sort(sorted_matches->begin(),sorted_matches->end());
  sort(sorted_choices->begin(),sorted_choices->end());
  //assert(equal(sorted_matches->begin(), sorted_matches->end(), matches->begin()));
  //assert(equal(sorted_choices->begin(), sorted_choices->end(), choices->begin()));
  vector<int>* result = difference(matches,sorted_choices);
  //assert(intersection(result,sorted_choices)->empty());
  //delete sorted_matches;
  delete sorted_choices;
  delete matches;
  return result;
}
