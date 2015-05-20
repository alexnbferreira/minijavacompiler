%{
#include "includes.hh"
#include "symtab.hh"
#include "ast.hh"
#include "ast_utils.hh"
#include "utils.hh"
using namespace std;
using namespace ASTUtils;

extern "C" int yylex();
extern "C" int yyparse();
extern "C" char *yytext;

extern int line_num;
extern int lexicalerror;
	int syntaxerror = 0;
 
void yyerror(const char *s);
%}

%union{
	int int_val;
	string* id_val;
	string* op_val;
	char type_val;
	ASTNode* node;
}


%expect 1 

%token COMMA PONTOEVIRGULA LP RP LB RB LC RC PONTO IGUAL EXCLAMACAO CLASS SYSTEMOUTPRINTLN PSVM STRING EXTENDS LENGTH
%token READERS WHILE IF TRUE FALSE NEW THIS INT BOOLEAN PUBLIC RETORNA ELSE 
%token <int_val> INTEGER_LITERAL
%token <id_val> ID 
%token <op_val> OPERATOR

%type <node> Program MainClass ClassDeclAux ClassDecl VarDecl VarDeclAux MethodDecl MethodDeclAux FormalList FormalRest FormalRestAux 
%type <node> Statement StatementAux Exp ExpList ExpRest ExpRestAux Type

%left OPERATOR PONTO LP RP LB RB
%right EXCLAMACAO
%debug
%%



Program: 	
		{start();} MainClass ClassDeclAux { $$ = mk_program_node($2,$3); set_root_node($$);}
		;
			

MainClass:	
		CLASS ID LC {push_scope();} PSVM LP STRING LB RB ID RP LC {push_scope();} Statement RC {pop_scope();} RC {pop_scope(); $$ = mk_main_node($2,$10,$14); incGlobalClass(); }
		;
		

		
ClassDeclAux: 
		ClassDecl ClassDeclAux { $$ = mk_classDeclAux_node($1,$2); }
		| { $$ = NULL; }
		;
		
ClassDecl:	
		CLASS ID LC {push_scope();} VarDeclAux MethodDeclAux RC {pop_scope(); $$ = mk_classDecl_node($2,$5,$6); incGlobalClass();}
		|CLASS ID EXTENDS ID LC {push_scope();} VarDeclAux MethodDeclAux RC {pop_scope(); $$ =  mk_ExtclassDecl_node($2,$4,$7,$8); incGlobalClass(); }
		;		
		
VarDecl: 
		Type ID PONTOEVIRGULA { $$ = mk_varDecl_node($1,$2);}
		;

VarDeclAux: VarDeclAux VarDecl { $$ = mk_varDeclAux_node($2,$1);}
		|error PONTOEVIRGULA {$$ = NULL;}
		|{$$ = NULL;}
		;
		
MethodDeclAux: MethodDecl MethodDeclAux {  $$ = mk_methDeclAux_node($1,$2); }
			|	{$$=NULL;}
			;
			
MethodDecl: 	
			PUBLIC Type ID LP {push_scope();} FormalList RP LC VarDeclAux StatementAux RETORNA Exp PONTOEVIRGULA RC {pop_scope(); $$ = mk_methDecl_node($2,$3,$6,$9,$10,$12);}
		;

FormalList: 
		Type ID FormalRestAux { $$ = mk_formList_node($1,$2,$3); }
		| { $$ = NULL; }
		;

FormalRestAux: 
			FormalRest FormalRestAux {  $$ = mk_formRestAux_node($1,$2);}
			| { $$ = NULL;}
			;
			
FormalRest:		
		COMMA Type ID  {  $$ = mk_formRest_node($2,$3);}
		;

Type: 
		INT LB RB { $$ = mk_type_node(&intarray);}
		|BOOLEAN { $$ = mk_type_node(&bol); }
		|INT { $$ = mk_type_node(&inteiro);}
		|ID {$$ = mk_type_node($1);}
		;


StatementAux:
		Statement StatementAux {$$ = mk_stAux_node($1,$2);}
		| {$$ = NULL;}
		| error PONTOEVIRGULA {$$ = NULL;}
		;


Statement: 	
			LC {push_scope();} StatementAux RC {pop_scope(); $$ = mk_stmts_node($3);}
			|IF LP Exp RP Statement ELSE Statement {$$ = mk_stIf_node($3,$5,$7);}
			|WHILE LP Exp RP Statement {$$ = mk_stWhile_node($3,$5);}
			|SYSTEMOUTPRINTLN LP Exp RP PONTOEVIRGULA {$$ = mk_stPrint_node($3);}
			|ID IGUAL Exp PONTOEVIRGULA {$$ = mk_stEq_node($1,$3);} 
			|ID LB Exp RB IGUAL Exp PONTOEVIRGULA {$$ = mk_stArrayEq_node($1,$3,$6);}
			;
			


	
Exp:		
			Exp OPERATOR Exp {mk_expOperator_node($1,$2,$3);}
			|Exp LB Exp RB {mk_expArray_node($1,$3);}
			|Exp PONTO LENGTH { $$=mk_length_node($1);}
			|Exp PONTO ID LP ExpList RP {mk_exp_call_node($1,$3,$5);}
			|READERS LP RP { $$ = mk_readers_node();}
			|INTEGER_LITERAL { $$ = mk_integer_node($1);}
			|TRUE {$$ =  mk_expBool_node(true);}
			|FALSE {$$ =  mk_expBool_node(false);}
			|ID {$$ = get_id_node($1);}
			|THIS {$$ = mk_expThis_node();}
			|NEW INT LB Exp RB { $$ = mk_newint_array_node($4);}
			|NEW ID LP RP { $$ = mk_newobject_node($2);}
			|EXCLAMACAO Exp { $$ = mk_negation_node($2);}
			|LP Exp RP {$$ = $2;}
			;

			
ExpList:  
		Exp ExpRestAux { $$ = mk_exp_list_node($1, $2);}
		| { $$ = NULL; }
		;
		
ExpRestAux: 
		ExpRest ExpRestAux { $$ = mk_exp_rest_aux_node($1, $2); }
		| { $$ = NULL;}
		;
		
ExpRest:		
		COMMA Exp { $$ = mk_exp_rest_node($2); }
		;
		

%%



void yyerror(const char *s) {
	syntaxerror++;
	cout << "error: syntax error -> " << yytext << " @ " << line_num << endl;
}
