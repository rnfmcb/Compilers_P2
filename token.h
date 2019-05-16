//Rachel Festervand
//Program Translation
//This is the types including token file 


#ifndef TOKEN_H 
#define TOKEN_H 	

#include <string> 
using namespace std; 

  
//const char delimiter[] = {'=','<','>',':','+','-','*','/','%','.',',',';','(    ',')','{','}','[',']'};

struct Token{  
    int lineNum;
    string tokenType; 
	string instance;
    Token *next;   
};  

  

#endif 
