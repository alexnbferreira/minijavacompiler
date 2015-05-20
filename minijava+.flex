%{
#include "includes.hh"
#include "symtab.hh"
#include "ast.hh"
#include "ast_utils.hh"
#include "utils.hh"

#include "minijava+.tab.h"


#include <cstdio>
#include <iostream>
using namespace std;
#define YY_DECL extern "C" int yylex()
int line_num = 1;
int lexicalerror = 0;
#include "minijava+.tab.h"  // to get the token types that we return

%}




digit		[0-9]
alphag		[A-Z]
alphap		[a-z]
alpha 		({alphap}|{alphag})
unders		_
op		([<+*]|-|&&)
inteiro {digit}+
id 		({alphap}|{alphag})({alpha}|{digit}|{unders})*

%x CommentBlock
%x CommentBlockL


%%

"/*"            { BEGIN(CommentBlock); }
<CommentBlock>"*/" { BEGIN(INITIAL); }
<CommentBlock>\n {++line_num;}
<CommentBlock>.    { }

"//"            { BEGIN(CommentBlockL); }
<CommentBlockL>\n { BEGIN(INITIAL);++line_num; }
<CommentBlockL>.    { }

"class" {return CLASS;}
"System.out.println" {return SYSTEMOUTPRINTLN;}
"public static void main" {return PSVM;}
"String" {return STRING;}
"extends" {return EXTENDS;}
"length" {return LENGTH;}
"new" {return NEW;}
"this" {return THIS;}
"int" {return INT;}
"boolean" {return BOOLEAN;}
"while" {return WHILE;}
"if" {return IF;}
"else" {return ELSE;}
"true" {return TRUE;}
"false" {return FALSE;}
"public" {return PUBLIC;}
"return" {return RETORNA;}
"Readers.IntReader.readInt" {return READERS;}
"," {return COMMA;}
";" { return PONTOEVIRGULA;}
"(" { return LP;}
")" { return RP;}
"[" { return LB;}
"]" { return RB;}
"{" { return LC;}
"}" { return RC;}
"." { return PONTO;}
"=" { return IGUAL;}
"!" { return EXCLAMACAO;}
[ \t]          ;
\n             { ++line_num;}
{op} {yylval.op_val = new string(yytext); return OPERATOR; }
{id} {yylval.id_val = new string(yytext); return ID; }
{inteiro} {yylval.int_val = atoi(yytext); return INTEGER_LITERAL; }
.                {lexicalerror++;}
%%