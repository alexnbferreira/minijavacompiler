#include "includes.hh"
#include "symtab.hh"
#include "ast.hh"
#include "ast_utils.hh"
#include "utils.hh"


extern "C" int yylex();
extern "C" int yyparse();
extern "C" char *yytext;
extern "C" FILE *yyin;

using namespace ASTUtils;

static ASTNode* root = NULL;

static SymbolTable symtab;


int main(int argc, char** argv)
{
    cout << "\n\nRunning ALSUL compiler. \n"; cout.flush();
    ASTUtils::init_ast_utils(symtab);
SymbolTable st;
    // 1. Parse the input file, run semantic checks, and create AST.
    ++argv, --argc;  /* skip over program name */
    yyin = (argc > 0) ? fopen(argv[0], "r") : stdin;
    int yyres = yyparse();
    if (yyres && !get_varsok() ) {
	err_exit(cout, "Terminating due to parsing errors.");
    }
    if(ASTUtils::sizeTemp()!=0){
	err_exit(cout, "Temporarios nao vazios!! Terminating due to parsing errors." );
	}
    else {
	cout << "\n\nLexical analysis: passed." << endl;
	cout << "Syntax analysis: passed.\n\n" << endl;
    }

    root = ASTUtils::get_root_node();
    if (root == NULL) {
	err_exit(cout, "AST not build.");
    }

   /*  // 2. Typecheck
    TypeChecker typecheck;
    root->accept(typecheck);
    if (not typecheck.typeok) {
	err_exit(cout, "Type checking: failed. Terminating ...");
	exit(1);
    } else {
	cout << "Type checking: passed." << endl;
    }

    // 3. Evaluate
    Interpreter interpret;
    root->accept(interpret); */
    return 0;
}

/*----------------------------------------------------------------------------*/
