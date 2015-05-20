//jpms:bc
/*----------------------------------------------------------------------------*\
 * File:        typechecker.hh
 *
 * Description: Type check the RIXPR language.
 *
 * Author:      jpms
 * 
 *                                     Copyright (c) 2015, Joao Marques-Silva
\*----------------------------------------------------------------------------*/
//jpms:ec

#ifndef _TYPECHECKER_H
#define _TYPECHECKER_H 1

#include "visitor.hh"


class TypeChecker : public Visitor {

public:

    TypeChecker() : Visitor(), typeok(true) { }

    void visit(ASTStmtsNode& n) {
	n.node1->accept(*this);
	n.node2->accept(*this);
    }

    void visit(ASTAssignStmtNode& n) {
	n.node1->accept(*this);
	n.node2->accept(*this);
	bool tok = (n.node1->get_type() == n.node2->get_type());
	if (not tok) {
	    cout << "Type checking failed in line " << n.get_lineno() << endl;
	}
	typeok = typeok && tok;
    }

    void visit(ASTIfStmtNode& n) {
	n.node0->accept(*this);
	if (n.node1 != NULL) { n.node1->accept(*this); }
	if (n.node2 != NULL) { n.node2->accept(*this); }
	bool tok = (n.node0->get_type() == XBool);
	if (not tok) {
	    cout << "Type checking failed in line " << n.get_lineno() << endl;
	}
	typeok = typeok && tok;
    }

    void visit(ASTWhileStmtNode& n) {
	n.node1->accept(*this);
	if (n.node2 != NULL) { n.node2->accept(*this); }
	bool tok = (n.node1->get_type() == XBool);
	if (not tok) {
	    cout << "Type checking failed in line " << n.get_lineno() << endl;
	}
	typeok = typeok && tok;
    }

    void visit(ASTBreakStmtNode& n) { }

    void visit(ASTPrintStmtNode& n) {
	n.node1->accept(*this);
	bool tok = (n.node1->get_type() != XNone);
	if (not tok) {
	    cout << "Type checking failed in line " << n.get_lineno() << endl;
	}
	typeok = typeok && tok;
    }

    void visit(ASTRelExprNode& n) {
	n.node1->accept(*this);
	n.node2->accept(*this);
	bool tok =
	    ((n.node1->get_type() == n.node2->get_type()) &&
	     n.node1->get_type() != XBool);
	if (not tok) {
	    cout << "Type checking failed in line " << n.get_lineno() << endl;
	}
	typeok = typeok && tok;
    }

    void visit(ASTExprNode& n) {
	n.node1->accept(*this);
	if (n.node2 != NULL) { n.node2->accept(*this); }
	bool tok = true;
	if (n.node2 != NULL) {
	    tok = (n.node1->get_type() == n.node2->get_type());
	} else {
	    tok = (n.node1->get_type() == XBool);
	}
	if (not tok) {
	    cout << "Type checking failed in line " << n.get_lineno() << endl;
	}
	typeok = typeok && tok;
    }

    void visit(ASTIntConstNode& n) { }

    void visit(ASTBoolConstNode& n) { }

    void visit(ASTRealConstNode& n) { }

    void visit(ASTVarRefNode& n) { }

public:

    bool typeok;

};

#endif /* _TYPECHECKER_H */

/*----------------------------------------------------------------------------*/
