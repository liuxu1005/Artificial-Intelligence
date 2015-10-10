#include <iostream>
#include <string>
#include "Word.h"
#include <assert.h>
using namespace std;

Word::Word(unsigned int l){
  length = l;
  slots = new char*[l];
  for(unsigned int i = 0; i<l; i++){
    char* p = new char(' ');
    *p = '?';
    slots[i]=p;
  };
}

Word::Word(char* s[], unsigned int l){
  length = l;
  slots = s;
}

Word::~Word(){
  delete[] initial_setting;
  //Already taken care of through Grid
}

void Word::clear(){
  for(unsigned int i = 0; i < length; i++){
    *(slots[i]) = initial_setting[i];
  }
}

void Word::set(string s){  
  for(unsigned int i = 0; i < s.length(); i++){
    *(slots[i]) = s[i];
  }
}

string Word::string_form(){
  string s = "";
  for(unsigned int i = 0; i < length; i++)
    s+=(*slots[i]);
  return s;
}
