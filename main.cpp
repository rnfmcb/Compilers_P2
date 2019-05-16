/*Rachel Festervand
Program Translation project 2
This is the main file for project 2. 
This project will implement a token as a triplet {tokenID, tokenInstance, line#} (if doing option with line numbers)
Implement the parser in a separate file (parser.c and parser.h) including the initial auxilary parser() function and all nonterminal functions. Call the parser function from main. The parser function generates error or returns the parse tree to main. In testTree.c (and testTree.h) implement a printing function using preorder traversal with indentations as before for testing purposes (2 spaces per level, print the node's label and any tokens from the node, then children left to right; one node per line). Call the printing function from main immediately after calling the parser and returning the tree. The printing function call must be later removed.*/

#include <iostream> 
#include <string>
#include <fstream>
#include <stdio.h> 
#include <stdlib.h>   
#include "token.h"
#include "testTree.h"
#include "scanner.h" 
#include "parser.h"  
#include "node.h" 

using namespace std; 


int main(int argc, char*argv[]){
Parser object; 
Node *mainRoot = new Node(); 
 

//If no argument, open a txt file
  if(argc == 1){
      string filename = "test.txt";
      string temp;
      ofstream file;
      file.open(filename.c_str());
      while(getline(cin,temp)){
         file << temp << " ";
      }
     file.close();
     ifstream infile;
	 cout << "Recieved file" << endl; 
	 mainRoot = object.parse(infile,filename);
     printPreorder(mainRoot);    
  	 
    
  }
  //take first argument and turn into file with .input1 as file name
  else if  (argc == 2) {
  string file = argv[1];
  string filename = file + ".input1";
  ifstream infile;  

  mainRoot = object.parse(infile,filename); 
  printPreorder(mainRoot); 
   }
  //If another file is piped
   else if (argc > 2 ){
   cout << "Too many command arguments, ending program" << endl;
   exit(EXIT_FAILURE);
  }
   return 0;
   }
   
   
