#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include "Grid.h"
#include <string.h>
using namespace std;

Grid::Grid(string s, unsigned const int l){
  //cout<<s<<"\n"<<s.length()<<endl;
  side_length = l;
  //init set of rows in grid
  slots = new char**[l];
  for(unsigned int row=0; row<l; row++){    
    //init new row in grid
    slots[row]=new char*[l];
    vector<char*>curr_word(0);
    for(unsigned int col=0; col<l; col++){
      char* c = new char(' ');
      //cout<<"row "<<row<<" col "<<col;
      //cout<<((l*row)+col)<<" :: "<<(s.length()-1)<<endl;
      assert(((unsigned)(l*row)+col) <= s.length()-1);
      assert(s[(l*row)+col] != 0);
      
      *c = s[(l*row)+col];
      slots[row][col] = c;
      
      if(*c != '_')
       	curr_word.push_back(c);      
      if(!curr_word.empty() && (*c == '_' || col==(l-1))){
        add_word(curr_word);
        curr_word.clear();
      }
      
    }
  }

  for(unsigned int col=0; col<l; col++){    
    vector<char*>curr_word(0);
    for(unsigned int row=0; row<l; row++){
      char* c = slots[row][col];
      
      if(*c != '_')
       	curr_word.push_back(c);      
      if(!curr_word.empty() && (*c == '_' || row==(l-1))){
        add_word(curr_word);
        curr_word.clear();
      }
      
    }
  }    
}

void Grid::add_word(vector<char*> cw){
  Word* w = new Word(cw.size());
  w->initial_setting = new char[cw.size()];
  for(unsigned int i = 0; i < cw.size(); i++){
    delete w->slots[i];
    w->slots[i] = cw[i];
    w->initial_setting[i]=*(cw[i]);
  }
  words.push_back(w);    
}

void Grid::printWords(){
  for(unsigned int i = 0; i <words.size(); i++)
    cout<<i<<". "<<(words.at(i))->string_form()<<endl;
}

void Grid::clear(){
  for (unsigned int i=0; i<words.size();i++)
    (words.at(i))->clear();  
}

void Grid::printGrid(){
  cout<<"--------------------"<<endl;
  for(unsigned int row = 0; row < side_length; row++){
    for(unsigned int col = 0; col < side_length; col++)
      cout<<*(slots[row][col])<<" ";    
    cout<<endl;
  }
  cout<<"--------------------"<<endl;
}

Grid::~Grid(){
  for(unsigned int row = 0; row < side_length; row++){
    for(unsigned int col = 0; col < side_length; col++)
      delete slots[row][col];    
    delete[] slots[row];
  }
  delete[] slots;  
  for(unsigned int i = 0; i < words.size(); i++){
    delete[] words[i]->slots;
    delete words[i];
  }
}
