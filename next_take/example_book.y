// example from book *Modern Compiler Implementation in C* by Appel

%union {int num; string id;}
%token UMINUS PLUS MINUS TIMES
%token <num> INT
%token <id> ID
%type <num> exp
%start exp
%%
exp : INT {$$ = $1;}
| exp PLUS exp {$$ = $1 + $3;}
| exp MINUS exp {$$ = $1 - $3;}
| exp TIMES exp {$$ = $1 * $3;}
| MINUS exp %prec UMINUS {$$ = - $2;}
