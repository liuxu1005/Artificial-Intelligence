/*
  BFS/DFS
  search.cpp
  Purpose: performs best and depth first search on a provided graph file

  @author Tom Williams
  @version 1.0 8/14/2015
 */


#include <assert.h>
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

/*
  Use Me!
  =======
  A Node in this graph representation consists of:
  1. data: the string data contained in that node
  2. edges: a vector of pointers to nodes that node is connected to.
*/
struct Node{
  string data;
  vector<Node*> *edges;
};  

/*
  Use Me!
  =======
  A Graph in this graph representation consists of:
  1. nodes: a vector of nodes contained in the graph.
*/
struct Graph{
  vector<Node*> *nodes;
};

/*
  Fill me in!
  ===========
  Purpose: perform a Breadth-First Search (BFS) for a Node* with particular data
  Argument: graph -- a Graph* as defined above
  Argument: query -- the string data of the node we are searching for
  Argument: root_index -- the index of the Node* in graph->nodes at which to start the search
  Returns: A deque* of Node*s visited during the search.
  Side effects: None
 */
deque<Node*>* bfs(Graph* graph, string query, unsigned int root_index){
  deque<Node*> *visited = new deque<Node*>();
  deque<Node*> *process = new deque<Node*>();
  vector<Node*> *track = new vector<Node*>();

  Node *n = graph->nodes->at(root_index);
  if(!n->data.compare(query)) {
        visited->push_back(n); 
        delete process;
        delete track;
        return visited;
      }
  process->push_back(n);
  track->push_back(n); 

  while(!process->empty()) {  
    n = process->front();
    process->pop_front();
    visited->push_back(n);
    int size = n->edges->size();
    int i, j;

    
    for(i = 0; i < size; i++) {       
      if(!n->edges->at(i)->data.compare(query)) {
        visited->push_back(n->edges->at(i)); 
        delete process;
        delete track;
        return visited;
      }
      bool processed = false;
      int t_size = track->size();
      for(j = 0; j < t_size; j++) {
        if (track->at(j) == n->edges->at(i)) {
          processed = true;
          break;
        }
      }
      if(!processed) {    
        process->push_back(n->edges->at(i));
        track->push_back(n->edges->at(i));
      }
    }
  }
  
  if (visited->back()->data.compare(query))
     visited->clear();
  delete process;
  delete track;
  return visited;
}

/*
  Fill me in!
  ===========
  Purpose: perform a Depth-First Search (DFS) for a Node* with particular data
  Argument: graph -- a Graph* as defined above
  Argument: query -- the string data of the node we are searching for
  Argument: root_index -- the index (>=0) of the Node* in graph->nodes at which to start the search
  Returns: A deque* of Node*s visited during the search.
  Side effects: None
 */
deque<Node*>* dfs(Graph* graph, string query, unsigned int root_index){
  deque<Node*> *visited = new deque<Node*>();
  deque<Node*> *process = new deque<Node*>();
  vector<Node*> *track = new vector<Node*>();

  Node *n = graph->nodes->at(root_index);
  if(!n->data.compare(query)) {
        visited->push_back(n); 
        delete process;
        delete track;
        return visited;
      }
  process->push_back(n);
  track->push_back(n);
 
  while(!process->empty()) {  
    n = process->back();
    process->pop_back();
    visited->push_back(n);
    int size = n->edges->size();
    int i, j;

    for(i = 0; i < size; i++) {
      if(!n->edges->at(i)->data.compare(query)) {
        visited->push_back(n->edges->at(i));
        delete process;
        delete track; 
        return visited;
      }
    }
    for (i = size - 1; i >= 0; i--) {
      bool processed = false;
      int t_size = track->size();
      for(j = 0; j < t_size; j++) {
        if (track->at(j) == n->edges->at(i)) {
          processed = true;
          break;
        }
      }
      if(!processed) {    
        process->push_back(n->edges->at(i));
        track->push_back(n->edges->at(i));
      }
    }

  }
  if (visited->back()->data.compare(query))
     visited->clear();
  delete process;
  delete track;
  return visited;
}

/*
  Don't modify me!
  ===========
  This is just helper code that reads in a graph file for you.
 */
Graph* readFile(char* fileName){
  ifstream inFile(fileName);
  if(!inFile){
    cerr << "Cannot open '" << fileName << "'\n";
    exit( 1 );
  }

  int size = 0;
  inFile >> size; 
  Graph* graph = new Graph();
  graph->nodes = new vector<Node*>();
  for(int i = 0; i < size; i++){
    Node* n = new Node();
    n ->data = "";
    n -> edges = new vector<Node*>();
    graph->nodes->push_back(n);
  }

  string line;
  getline(inFile,line);  
  for(int i = 0; i < size; i++){    
    getline(inFile,line);
    istringstream ssin(line);
    vector<string> record;
    while(ssin){
      string field;
      if(!getline(ssin,field,','))break;
      record.push_back(field);
    }
    Node* node = graph->nodes->at(atoi(record[0].c_str()));
    node->data = record[1];
    for(unsigned int j = 2; j < record.size(); j++)
      node->edges->push_back(graph->nodes->at(atoi(record[j].c_str())));
  }
  return graph;
}

/*
  Don't modify me!
  ===========
  This is the code that runs your BFS and DFS functions on the input specified through the command line.
 */
int main(int argc, char* argv[]){
  assert(argc==4);
  Graph* graph = readFile(argv[1]);
  string query = argv[2];
  int root_index = atoi(argv[3]);
  try{
    deque<Node*>* bfsvalue = bfs(graph,query,root_index);
    cout<<"BFS: ";
    for(unsigned int i = 0; i < bfsvalue->size(); i++)
      cout<<bfsvalue->at(i)->data<<", ";
    if(bfsvalue->empty())
      cout<<"NO SOLUTION FOUND";
    cout<<endl;
    deque<Node*>* dfsvalue = dfs(graph,query,root_index);
    cout<<"DFS: ";
    for(unsigned int i = 0; i < dfsvalue->size(); i++)
      cout<<dfsvalue->at(i)->data<<", ";
    if(dfsvalue->empty())
      cout<<"NO SOLUTION FOUND";
    cout<<endl;
  }catch(string caught){
    cout<<"\033[1;31m"<<caught<<"\033[0m"<<endl;
  }
  
  for(unsigned int i = 0; i < graph->nodes->size(); i++){
    delete graph->nodes->at(i)->edges;
    delete graph->nodes->at(i);
  }
  delete graph->nodes;
  delete graph;
  
  return 0;
}
