//Rachel Festervand 
//Compilors, project 2
//This is the header file for the nodes and where they are defined.
 
#ifndef NODE_H
#define NODE_H 
#include <string>
 
using namespace std;

struct Node {
   string  key;  
   struct Node *left; 
   struct Node *right;
   string data;     
   int level; 
};  

#endif  
