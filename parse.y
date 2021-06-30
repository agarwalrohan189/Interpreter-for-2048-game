%{
#include <iostream>
#include <string.h>
#include <bits/stdc++.h>
#include "2048.h"
using namespace std;
int yyerror(char const *s);
extern int yylex(void);
%}
 
 
%union{
	char id[25];
	int val;
}

%token<val> OP DIR
%token<id> ASSIGN TO COMMA PERIOD
%token<val> NUMBER
%token<id> VAR VARNAME IS
%token<id> VALUE IN
%token INVALID EOL

%define parse.error verbose
 
%%
 

//Input Sentence Grammar
INPUT : {return -1;}|CORRECT | WRONG | error EOL {return 1;}

//Correct syntactical moves
CORRECT: MOVES | ASSIGNMENT | NAMING | QUERY 

//Wrong syntax and correction suggestions
WRONG: NOPERIOD EOL {	//No Fullstop at the end.
						cout<<"2048> You need to end a command with a full-stop."<<endl;
						return 1; 
						}
		| VAR KEYWORDS IS NUMBER COMMA NUMBER PERIOD EOL { //Keyword used as variable name.
			cout<<"2048> No, a keyword cannot be a variable name."<<endl;
			return 1;
			} 
		| EOL { //Nothing is entered.
			cout<<"2048> You need to enter something."<<endl;
			return 1;
				}
		| VAR INVALID IS NUMBER COMMA NUMBER PERIOD EOL { //Invalid variable name.
			cout<<"2048> Variable name can not contain anything other than alphabets."<<endl;
			return 1;
		}



MOVES: OP DIR PERIOD EOL {	//Move operations with computations.
							if(current_board->move($1, $2)){
								if(!current_board->random_insertion()) cout<<"ALL TILES OCCUPIED"<<endl;
							}
							return 0;
					};
ASSIGNMENT: ASSIGN NUMBER TO NUMBER COMMA NUMBER PERIOD EOL { //Assign value to a tile.
															if(current_board->set_val($4-1, $6-1, $2,{},1)) return 0;
															return -1;
														};
NAMING: VAR VARNAME IS NUMBER COMMA NUMBER PERIOD EOL { //Assign variable name to a tile.
														if(current_board->add_name($4-1,$6-1,$2,1))return -2;
														return -1;
												};
QUERY: VALUE IN NUMBER COMMA NUMBER PERIOD EOL { //Get value at postion.
												if(current_board->print_val($3-1,$5-1)) return -1;
												return 1;
											};

//Defining Grammar for non-Fullstop sentences
NOPERIOD : OP DIR 
		| ASSIGN NUMBER TO NUMBER COMMA NUMBER  
		| VAR VARNAME IS NUMBER COMMA NUMBER 	
		| VALUE IN NUMBER COMMA NUMBER 


//Keywords for our language.
KEYWORDS: OP | DIR | ASSIGN | TO | VAR | IS | VALUE | IN


		
%%
 
int yyerror(char const *s){
	char str[500];
	strcpy(str,s);
	char *token = strtok(str, " ");
	
	while (strcmp(token,"unexpected")!=0)
    {
        token = strtok(NULL, " ");
    }

	token = strtok(NULL, " ");
	token= strtok(token,",");
	char Keywords[][25]={"OP", "DIR", "ASSIGN","TO", "VAR", "IS", "VALUE", "IN","PERIOD", "COMMA", "EOL"};
	cout<<"2048> Syntax Error."<<endl;
	cout<<"2048> ";
	if(strcmp(token,"VARNAME")==0){
		cout<<"Unexpected variable."<<endl;
	}
	else if(strcmp(token,"INVALID")==0){
		cout<<"Unexpected and Invalid variable name."<<endl;
	}
	else{
		for(int i=0;i<11;i++){
			if(strcmp(token,Keywords[i])==0){
				cout<<"Unexpected Keyword ("<<token<<")."<<endl; 
			}
		}
	}
	return 0;
}
 
 