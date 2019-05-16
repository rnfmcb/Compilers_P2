//Rachel Festervand 
//Program Translation
//This is the test scanner file for project 1. 
//This file tests the functionality of the scanner file.
#include <iostream> 
#include <string> 
#include <fstream>
#include <stdlib.h> 
#include <ctype.h> 
#include <sstream>
#include <bits/stdc++.h>   
#include "token.h" 
#include "scanner.h"
#include "parser.h"  
#include "node.h"
#include "testTree.h"  

using namespace std; 

Parser::Parser(){


} 

int Parser::getLevel(){ 
		return level; 
}

int Parser::addLevel(){ 
	level = level + 1;  
}
int Parser::setLevel(int i){
	level = i; 
}  


Node* Parser::newNode(string k){
	Node *node = new Node; 
	node->key = k; 
	node->level = getLevel(); 
	node->left = NULL; 
	node->right = NULL;  
	return node; 
}   

void Parser:: findEmpty(Node *tree, Node *leaf){ 
	if(tree->left != NULL){ 
		findEmpty(tree->left,leaf); 
    } 
	else { 
		tree->left = leaf; 
	} 
} 

void Parser::FADriver(ifstream &infile,string filename,Scanner& scanner){ 
	string line;
	string type;
	infile.open(filename.c_str());
    if(infile.fail()){
		cout << "File does not exit " << endl; 
        exit(EXIT_FAILURE); 
    }  
	if(infile.is_open()){  
		if(!infile){
			cout << "Scanner Error: unable to open file" << endl;
					exit(EXIT_FAILURE); 
			}
				if (infile.peek() == ifstream::traits_type::eof() ){
				  cout << "{EOFTkn,EOF,1}" << endl;
				  exit(EXIT_FAILURE);
				 }

	string word;
	int state;
	while(getline(infile,line)){
		scanner.setLine();
		//Comment filter 
		if (line[0]!= 92){      

			istringstream stm(line); 
			while(stm >> word){
				if(word.empty()){ 
					scanner.setLine();                              
			    }   
		//		cout << word << endl;  	  	
				state = scanner.table(word); 
				}
			}
		else { 
			//	cout << "{Comment filtered, " << scanner.getLine() << "}" << endl;  
	    }        		  
	//	scanner.print(); 
		} 

		//cout << "{EOFTkn,EOF," << scanner.getLine() << "}" << endl;
		//cout << "End state " << endl;  
		infile.close();

  } 
} 


Token* Parser:: getToken(Token *tkn){
    Token *temp = new Token; 
    temp = head; 
    head == NULL; 
 
    while(temp != NULL){ 
		if(temp->instance == tkn->instance){ 
		//	cout << "get token in getToken " << temp->instance << " " << tkn->instance;
			  
			if(temp->next == NULL){ 
				head = temp; 
				return temp;
			}  
            else{
			   head = temp->next; 
			   return temp->next; 
            } 
         }
        temp = temp->next;   
     } 
   
}

//I do not put this process in the tree 
void Parser::RO(Token *&tkn, Node*& tree){ 
  
   	if(tkn->instance == "<" ) {
	   tkn = getToken(tkn); 
         
	} 
    else if (tkn->instance == "="){
		tkn = getToken(tkn); 
		if (tkn->instance == ">" | tkn->instance == "<" | tkn->instance == "="){  
			tkn = getToken(tkn);  
	     
		}  
	} 
	else { 
		cout << "Parser error: Expected < | = < | = > | = = | ="; 
		cout << "recieved " << tkn -> instance << endl;
		exit(EXIT_FAILURE);  
	}
    
} 
 
void Parser::R(Token *&tkn, Node*& tree){
	string d;  
	addLevel(); 
	if(tkn->tokenType == "IDTkn" | tkn->tokenType == "intNumTkn"){ 
		tree->left = new Node; 
		tree->left = newNode("R");
		d = tkn->instance;  
	    tree->left->data = d;
	}
     else if(tkn->instance == "["){
		tree->left = new Node; 
		tree->left = newNode("expr"); 
		expr(tkn,tree->left); 
		
	 
    } 
    else{ 
		cout << "Parser error in R:  expected [, got "; 
		cout << tkn->instance; 
		exit(EXIT_FAILURE); 
	} 
    
 
} 

void Parser:: M(Token *&tkn, Node*& tree){ 
	addLevel(); 
	if( tkn->tokenType == "IDTkn" | tkn->tokenType == "intNumTkn"|tkn->instance == "["){ 
		tree->left = new Node; 
		tree->left = newNode("M"); 
	    R(tkn,tree->left); 
    } 
   else	if(tkn->instance == "-"){
		tkn = getToken(tkn);
		tree->left = new Node; 
		tree->left = newNode("M");  
		M(tkn,tree->left); 
    } 
	
 
} 

void Parser::N(Token *&tkn, Node*& tree){ 
	addLevel(); 
	if(tkn->tokenType == "IDTkn" | tkn->tokenType == "intNumTkn" | tkn->instance == "["){
		tree->left = new Node; 
		tree->left = newNode("N");
	 	 M(tkn,tree->left);
		if(tkn ->instance == "//"){
			tree->left->left = new Node; 
			tree->left->left = newNode("N"); 
			tkn = getToken(tkn); 
			N(tkn,tree->left->left); 
 		} 
	}   
} 

void Parser::A(Token *&tkn, Node*& tree){
	addLevel(); 
    if(tkn->tokenType == "IDTkn" | tkn->tokenType == "intNumTkn"| tkn->instance == "["){
       tree->left = new Node; 
	   tree->left = newNode("A");
	
	   N(tkn,tree->left);

	   if(tkn->instance == "*"){
		  A(tkn,tree->left->left); 
	   }   
      else if (tkn->instance == "+" | tkn->instance == "-"){ 
		  expr(tkn,tree->left);
	  } 
	  else{ //Empty 
	  }  	
   }
  else{ 
    cout << "Expected ID, int or [, but got " << tkn->instance;  
	exit(EXIT_FAILURE); 	
   } 
} 

//<expr>-> <A> + <expr> | <A> - <expr> | <A>
void Parser:: expr(Token *&tkn, Node *&tree){ 
	addLevel(); 
    //cout << "token in expr " << tkn->instance << endl;
  	tkn = getToken(tkn);  
	//cout << tkn->tokenType << endl;  
	if( tkn->tokenType == "intNumTkn" | tkn->tokenType == "IDTkn" | tkn->tokenType == "[") { 
		tree->right = new Node; 
		tree->right = newNode("expr");
		tree->right->data = tkn->instance; 
		addLevel();  
		A(tkn,tree->left);
        //cout << "tkn in expr after A  " << tkn->instance << endl;

    }      
}
void Parser::mstat(Token *&tkn, Node *&tree){ 
	addLevel(); 
	tree->right = new Node; 
	tree->right = newNode("mstat"); 
	stat(tkn,tree->right); 	 
} 


//Stat <in> | <out> | <block> | <if> | <loop> | <assign>
void Parser::stat(Token *&tkn, Node *&tree){ 
	addLevel(); 
	//cout << "Token in stat " << tkn->instance << endl; 
 
	if(tkn->instance == "Output"){ 
		tree->right  = new Node; 
		tree->right = newNode("out");
	  //  cout << "out node " << tree->right->key << endl; 
		tkn = getToken(tkn);
		//cout << "tkn after output " << tkn->instance << endl;  
		if(tkn->instance == "["){
			tkn = getToken(tkn);  
		//	cout << "After [ " << tkn->instance << endl; 
		   	expr(tkn,tree->right); 
		//	cout << "after expr in out " << tkn->instance << endl;  
				if(tkn->instance == "]"){
				 
				} 
				else{
				    cout << "Parser error in output/stat: expect ], recieved ";					//cout << tkn->instance << endl; 
					exit(EXIT_FAILURE);
			    }
          }
	      else{ 
			cout << "Parser error in output/stat: expected [, got ";
			cout << tkn->instance << endl;
            exit(EXIT_FAILURE);
          }
      } 
      
	  else if (tkn->instance == "Read"){
		  string data;  
	      tkn = getToken(tkn); 
		  if(tkn->instance == "["){
			 tkn = getToken(tkn); 
			 if( tkn->tokenType == "IDTkn" ) {
				data = tkn->instance;  
				tkn = getToken(tkn); 
					if(tkn->instance == "]"){ 
						tree->left = new Node; 
						tree->left = newNode("in");
					    tree->left->data = data; 
						 
					} 
					else { 
						cout << "Parser error: expected ], recieved "; 
						cout << endl;
						exit(EXIT_FAILURE);
				 	 }
  			  }  
              else { 
			      cout << "Parser error: expected indetifier, recieved ";  
				  cout << tkn->tokenType << endl; 
				  exit(EXIT_FAILURE);
			  } 
           }
		   else { 
		       cout << "Parser error: expected [ recieved "; 
			   cout << endl;
			   exit(EXIT_FAILURE);
		    } 
        	
    } 
	else if(tkn->instance == "Begin"){ 
		tree->left = new Node; 
		tree->left = newNode("block"); 
		begin(tkn,tree->left); 
	} 

	else if(tkn->instance == "IFF"){
 	 	tree->left = new Node; 
		tree->left = newNode("IF"); 
		tkn = getToken(tkn);  
		if(tkn->instance == "[") { 
		    tkn = getToken(tkn);   
			expr(tkn, tree->left);
			RO(tkn,tree->left->left); 
			expr(tkn, tree->left->left->left);  
			if(tkn->instance == "]"){
				//stat(tkn,tree->left->left->left); 
			} 
			else{ 
				cout << "parser error: expected ], recieved "; 
				cout << tkn->instance << endl;
				exit(EXIT_FAILURE);
			}  	
		}
		else{ 
			cout << "Expected [, recieved "; 
			cout << tkn->instance << endl;
			exit(EXIT_FAILURE); 
		} 
 
	} 
	else if(tkn->instance == "Loop"){
		tree->left = new Node; 
		tree->left = newNode("Loop");  
        tkn = getToken(tkn);
        if(tkn->instance == "[") {
			tkn = getToken(tkn); 
            expr(tkn, tree->left);
			tkn = getToken(tkn); 
			//cout << "tkn in loop, after expr " << tkn->instance << endl;  
            RO(tkn,tree->left);
			//cout << "after ro " << tkn->instance;  
            expr(tkn, tree->right);
           // cout << "after expr 2 " << tkn->instance;
            if(tkn->instance == "]"){
              //  stat(tkn,tree->left->left->left; 
            }
            else{
                cout << "parser error: expected ], recieved " << tkn->instance << endl;
				exit(EXIT_FAILURE);
            }
        }
        else{
            cout << "Expected [, recieved ";
            cout << tkn->instance << endl;
			exit(EXIT_FAILURE);
        }

    }
 
	else if(tkn->tokenType == "IDTkn"){
		string data = tkn->instance; 
		tkn = getToken(tkn);
		if(tkn->instance == "="){ 
			tree->left = new Node; 
			tree->left = newNode("assign");
 			tree->left->data = data;   
			tkn = getToken(tkn); 
		   	expr(tkn,tree->left); 
		} 
		else{
			cout << "Parser error: Expected =, recieved "; 
			cout << endl; 
			exit(EXIT_FAILURE);
		} 
	} 

	else { 
		cout << "Parser error: expected a keyword, got "; 
		cout << tkn->instance << endl;
		exit(EXIT_FAILURE);  
     } 
  
} 


 
//Block -> Begin<vars><stats>End 
void Parser:: begin(Token *&tkn, Node *&tree){ 
           
     if (tkn->instance == "Begin"){
		if(tree->left== NULL){ //Check for vars on left 
		    tree->left = new Node;
		  	tree->left = newNode("Vars");         
	    	//cout << "left branch " << tree->left->key;
        }
		setLevel(1);   	
        tree->right = new Node; 
		tree->right = newNode("Block"); 
        tkn = getToken(tkn);
		//cout << "tkn in begin " << tkn->instance; 
		addLevel(); 
	   	if(tkn->instance == "INT"){ //Vars
			 setLevel(1);  
		     vars(tree->right);
		//	 cout << tkn->instance << "tkn in begin after vars " << endl;  
			 tkn = getToken(tkn);
			 if(tkn->instance == "INT"){ 	
				vars(tree->right->left); 
				tkn = getToken(tkn); 
			}  
         } 
		}  
        /* else{ //Vars is empty  
			 tree->left->left = new Node; 
			 tree->left->left = newNode("Vars"); 
          }*/ 

         //<stats> -><stat>:<mStat> 
	   	if(tkn->tokenType  == "keyword" ){ //Stats 
		   setLevel(2);  
	       tree->right->right = new Node; 
		   tree->right->right = newNode("Stats");
		   addLevel(); 
		   tree->right->right->left = new Node; 
		   tree->right->right->left = newNode("Stat");  
		   stat(tkn,tree->right->right->left);
		   tkn = getToken(tkn); 
		  // cout << "tkn after stat" << tkn->instance << endl;
           if(tkn->instance == ":") { 
			  tkn = getToken(tkn); 
		   	  if(tkn->instance == "Read" | tkn->instance == "Output"  | 
			  tkn->instance == "IFF" | tkn->instance == "Loop" | 
			  tkn->tokenType == "IDTkn" | tkn->instance == "Begin") { 
			       mstat(tkn,tree->right->right); 
		      } 
           	  else if (tkn->instance == "End"){ 
			 	 setLevel(3); 
			 	 tree->right->right->right = new Node; 
			  	 tree->right->right->right = newNode("mStat"); 
			  }
			  else{ 
				 cout << "parser erro in begin. Expected mstat or end"; 
				 cout << "received " << tkn->instance; 
				 exit(EXIT_FAILURE); 
			   }   

	       } 
       }  	 
  
}

//Vars empty| INT Identifier Integer <vars>
void Parser::vars( Node *&tree){
   addLevel();  
  // cout << tkn->instance << "token in vars " << endl; 
   string id; 
   string num; 
   Token *tkn1 = getToken(tkn); 
   Token *tkn2 = getToken(tkn1);
   id = tkn1->instance; 
   num = tkn2->instance;   
  // cout << "is and num " << id << " " << num;  
   if(tkn->instance  == "INT" && tkn1->tokenType == "IDTkn" && tkn2->tokenType == "intNumTkn"){ 
      
       tree->left = new Node;  
	   tree->left = newNode("Vars");  
	   tree->left->data =  id + " " +  num;
       
   }
 tkn = *&tkn2;
 //cout << "tkn in parser" << tkn->instance;      
} 



//Starts here <vars><block> 
Node* Parser::prog(Token *&tkn, Node *&tree){
	Token *temp = tkn; 
   
   // cout << "tokenType from prog " << tkn->instance << endl;
    //Vars 
    if(tkn->instance == "INT"){
        vars(tree);
		Token *tkn1  = getToken(tkn);
        tkn = *&tkn1; 
        if(tkn->instance == "INT"){
            vars(tree->left);
			tkn = getToken(tkn); 
            //cout << "second tkn in prog " << tkn->instance << endl;
            addLevel();			   
        } 
    }
    //<Block> 
    if (tkn->instance == "Begin"){
        begin(tkn,tree);
    }

   /* else{ //Error
        cout << "Parser error in program: Expected begin or INT, recieved ";
        cout << tkn->instance << endl;
		exit(EXIT_FAILURE); 
     }*/
 
 return tree;
}


Node*  Parser::parse (ifstream &infile,string filename){
    Scanner scan;      
    root = NULL; 
	branch = NULL;
	varNum = 0;   
    FADriver(infile,filename,scan);
   // Token *tkn = scanner(scan);     
   // cout << "parsing tkn " << tkn->instance << endl; 
	level = 0;  
	root = newNode("Program"); 
    head = scan.head; 
    tkn = scan.head; //First token 
    //cout << tkn->instance << " token " << endl;  
   root =  prog(tkn,root);
   /* if(tkn->tokenType == "EOFtk")
         cout << "parsing was a success" << endl;
    else {
        cout << "Parser error, expected EOFtkn" << endl;
     }*/
     return root; 

}
 
