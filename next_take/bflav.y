%{
#include <stdio.h>
int yylex(void); /* function prototype */
%}


%union {
	int pos;
	int ival;
	string sval;
	}

%token <sval> ID STRING
%token <ival> INT

%token
  COMMA COLON SEMICOLON
  LPAREN RPAREN
  L_SQR_BRCK R_SQR_BRCK
  L_MO_BRCK R_MO_BRCK DOT
  AND OR ASSIGN
  ARRAY IF ELSE WHILE FOR RETURN
  BREAK STRUCT
  ARROW REF

%start program

%right ASSIGN
%nonassoc EQ NEQ LT GT LE GE
%left PLUS MINUS
%left TIMES DIVIDE
%left UMINUS
%%

program : declaration_list ;

declaration_list : declaration declaration_list_aux ;

declaration_list_aux    :   declaration
                        |
                        ;

declaration : function_declaration
            |   struct_declaration
            ;

function_declaration : ID LPAREN type_fields RPAREN ARROW type_id bracket_expression ;

type_fields : first_type_field type_fields_aux ;

first_type_field: ID COLON type_id
                | ID
                ;

type_fields_aux : COMMA type_field type_fields_aux
                |
                ;

type_field  : ID COLON type_id ;

type_id :   ID
        |   REF ID
        |   type_id L_SQR_BRCK type_id R_SQR_BRCK
        ;

struct_declaration : STRUCT type_id interface_type L_MO_BRCK struct_stmts R_MO_BRCK ;

interface_type  : COLON type_id
                |
                ;


struct_stmts : struct_stmt struct_stmts_aux ;

struct_stmts_aux:   SEMICOLON struct_stmt struct_stmts_aux
                |
                ;

struct_stmt :   ID COLON type_id
            |   function_declaration
            ;

bracket_expression : L_MO_BRCK expression_list R_MO_BRCK ;

expression_list : expression expression_list_aux ;

expression_list_aux :   SEMICOLON expression expression_list_aux
                    |
                    ;

assign_type :   type_id
            |
            ;


/*
anonymous function declaration in the manner of given syntax:
```
func := add(a: int, b: int) -> int { return a + b };
```
*/

anon_func_declaration : ID LPAREN type_fields RPAREN ARROW type_id bracket_expression ;

func_exec_exp : ID LPAREN func_arguments RPAREN ;

func_arguments  :   expression func_arguments_aux
                |
                ;

func_arguments_aux  :   COMMA expression func_arguments_aux
                    |
                    ;

ops :   expression PLUS expression
    |   expression MINUS expression
    |   expression TIMES expression
    |   expression DIVIDE expression
    |   expression EQ expression
    |   expression NEQ expression
    |   expression LT expression
    |   expression LE expression
    |   expression GT expression
    |   expression GE expression
    |   MINUS expression    %prec UMINUS
    ;

expression  : ID COLON assign_type ASSIGN expression
            | bracket_expression
            | func_exec_exp
            | anon_func_declaration
            | STRING
            | INT
            | if_stmt
            | lvalue ASSIGN expression
            | ops
            ;

lvalue : ID lvalue_aux ;

lvalue_aux  : DOT ID lvalue_aux
            | L_SQR_BRCK expression R_SQR_BRCK lvalue_aux
            |
            ;

if_stmt :   IF LPAREN expression RPAREN expression if_stmt_aux ;

if_stmt_aux : ELSE expression
            |
            ;
