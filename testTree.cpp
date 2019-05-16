//Rachel Festervand 4/21/2019 
//Program Translation
//This is the test parser file for project 2
#include <iostream> 
#include "node.h" 
#include "parser.h" 
#include "testTree.h" 

using namespace std; 


void print(Node *ptr) {

    if (ptr-> level != 0){
   		int printLevel = ptr->level;
    	string dash;
    	for(int i = 1; i <= printLevel; i++){
        	cout << "--";
  		  }
    	cout << ptr->key << " " << ptr->data << endl;
    }
   else
      cout << ptr->key << " " << ptr->data << endl;
}

void printPreorder(Node *ptr){ 

     if(ptr!= NULL){  
    	 print(ptr);
     	 //cout << "print left" << endl; 
     	 printPreorder(ptr->left);
     	 //cout << "print right" << endl; 
         printPreorder(ptr->right);
      }  
}



 
 
