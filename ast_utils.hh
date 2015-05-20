#ifndef _AST_UTILS_H
#define _AST_UTILS_H 1

#include "symtab.hh"
#include "ast.hh"

namespace ASTUtils
{

    void
    init_ast_utils(SymbolTable& st);

    bool
    get_varsok();

    ASTNode*
    get_root_node();
	void insertTemp(string* name, bool ar);
	void deleteTemp(string* name);

	int sizeTemp();
	void push_scope();
	void pop_scope();
	void enter_while();
	void exit_while();
	void incGlobalClass();

    void
    set_root_node(ASTNode* rn);

    ASTNode*
    mk_program_node(ASTNode* n1, ASTNode* n2);

    ASTNode*
    mk_main_node(string* id1, string* id2, ASTNode* n1 );

    ASTNode*
    mk_classDeclAux_node(ASTNode* n1, ASTNode* n2);

    ASTNode*
    mk_ExtclassDecl_node(string* id1, string* id2, ASTNode* n1, ASTNode* n2);

    ASTNode*
    mk_classDecl_node(string* id1, ASTNode* n1, ASTNode* n2);

    ASTNode*
    mk_varDecl_node(ASTNode* n1, string* id1);

    ASTNode*
    mk_varDeclAux_node(ASTNode* n1, ASTNode* n2);

    ASTNode*
    mk_methDeclAux_node(ASTNode* n1, ASTNode* n2);
	
	ASTNode*
    mk_methDecl_node(ASTNode* n1, string* id1,ASTNode* n2, ASTNode* n3, ASTNode* n4, ASTNode* n5);

    ASTNode*
    mk_formList_node(ASTNode* n1,string* id1, ASTNode* n2);

    ASTNode*
    mk_formRestAux_node(ASTNode* n1, ASTNode* n2);

    ASTNode*
    mk_formRest_node(ASTNode* n1, string* id1);

    ASTNode*
    mk_type_node(string* id1);

	ASTNode*
	mk_stmts_node(ASTNode* n1);
	
    ASTNode*
    mk_stAux_node(ASTNode* n1, ASTNode* n2);

    ASTNode*
    mk_stIf_node(ASTNode* n1, ASTNode* n2, ASTNode* n3);

    ASTNode*
    mk_stWhile_node(ASTNode* n1, ASTNode* n2);

    ASTNode*
    mk_stPrint_node(ASTNode* n1);
	
	   ASTNode*
    mk_stEq_node(string* name1, ASTNode* n2);
	
	   ASTNode*
    mk_stArrayEq_node(string* name1, ASTNode* n2, ASTNode* n3);
	
		ASTNode*
    mk_readers_node();
	
		ASTNode*
    mk_expThis_node();
	
	ASTNode*
    mk_expBool_node(bool bool1);
	
    ASTNode*
    mk_expOperator_node(ASTNode* n1, string* op, ASTNode* n2);
	
	ASTNode*
	mk_expArray_node(ASTNode* n1, ASTNode* n2);

    ASTNode*
    mk_length_node(ASTNode* n1);
	
	   ASTNode*
    mk_exp_call_node(ASTNode* n1, string* id1, ASTNode* n2);
	
	   ASTNode*
    mk_integer_node(int num1); 
	
    ASTNode*
    get_id_node(string* id);
	
	ASTNode*
	mk_newint_array_node(ASTNode* n1);

    ASTNode*
    mk_newobject_node(string* id1);
	
	   ASTNode*
    mk_negation_node(ASTNode* n1);
	
		ASTNode*
	mk_exp_list_node(ASTNode* n1, ASTNode* n2);
	
		ASTNode*
	mk_exp_rest_aux_node(ASTNode* n1, ASTNode* n2);
	
		ASTNode*
	mk_exp_rest_node(ASTNode* n1);
	
void start();
	
	
}

#endif /* _AST_UTILS_H */

/*----------------------------------------------------------------------------*/
