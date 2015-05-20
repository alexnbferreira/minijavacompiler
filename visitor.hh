//jpms:bc
/*----------------------------------------------------------------------------*\
 * File:        visitor.hh
 *
 * Description: 
 *
 * Author:      jpms
 * 
 *                                     Copyright (c) 2015, Joao Marques-Silva
\*----------------------------------------------------------------------------*/
//jpms:ec

#ifndef _VISITOR_H
#define _VISITOR_H 1

class ASTNode;
class ASTProgramNode;
class ASTMainNode;
class ASTClassDeclAuxNode;
class ASTClassDeclNode;
class ASTExtClassDeclNode;
class ASTVarDeclNode;
class ASTVarDeclAuxNode;
class ASTMethodDeclNode;
class ASTMethodDeclAuxNode;
class ASTFormListNode;
class ASTFormRestNode;
class ASTFormRestAuxNode;
class ASTStAuxNode;
class ASTStEqNode;
class ASTStArrayEqNode;
class ASTStIfNode;
class ASTStWhileNode;
class ASTStPrintNode;
class ASTStReadersNode;
class ASTExpThisNode;
class ASTExpBoolNode;
class ASTExpOperatorNode;
class ASTExpArrayNode;
class ASTExpLengthNode;
class ASTExpCallNode;
class ASTExpIntNode;
class ASTIDRefNode;
class ASTIntArrayNode;
class ASTObjectNode;
class ASTNegationNode;
class ASTExpListNode;
class ASTExpRestNode;
class ASTExpRestAuxNode;
class ASTTypeNode;


class Visitor {

public:

    virtual void visit(ASTNode& n) = 0;
	virtual void visit(ASTProgramNode& n) = 0;
    virtual void visit(ASTMainNode& n) = 0;
	virtual void visit(ASTClassDeclAuxNode& n) = 0;
    virtual void visit(ASTClassDeclNode& n) = 0;
	virtual void visit(ASTExtClassDeclNode& n) = 0;
    virtual void visit(ASTVarDeclNode& n) = 0;
	virtual void visit(ASTVarDeclAuxNode& n) = 0;
    virtual void visit(ASTMethodDeclNode& n) = 0;
	virtual void visit(ASTMethodDeclAuxNode& n) = 0;
    virtual void visit(ASTFormListNode& n) = 0;
	virtual void visit(ASTFormRestNode& n) = 0;
    virtual void visit(ASTFormRestAuxNode& n) = 0;
	virtual void visit(ASTStEqNode& n) = 0;
    virtual void visit(ASTStArrayEqNode& n) = 0;
	virtual void visit(ASTStIfNode& n) = 0;
    virtual void visit(ASTStWhileNode& n) = 0;
	virtual void visit(ASTStPrintNode& n) = 0;
    virtual void visit(ASTStReadersNode& n) = 0;
	virtual void visit(ASTExpThisNode& n) = 0;
    virtual void visit(ASTExpBoolNode& n) = 0;
	virtual void visit(ASTExpOperatorNode& n) = 0;
    virtual void visit(ASTExpArrayNode& n) = 0;
	virtual void visit(ASTExpLengthNode& n) = 0;
    virtual void visit(ASTExpCallNode& n) = 0;
	virtual void visit(ASTExpIntNode& n) = 0;
    virtual void visit(ASTIDRefNode& n) = 0;
	virtual void visit(ASTIntArrayNode& n) = 0;
    virtual void visit(ASTObjectNode& n) = 0;
	virtual void visit(ASTNegationNode& n) = 0;
    virtual void visit(ASTExpListNode& n) = 0;
	virtual void visit(ASTExpRestNode& n) = 0;
    virtual void visit(ASTExpRestAuxNode& n) = 0;
	virtual void visit(ASTTypeNode& n) = 0;

};

#endif /* _VISITOR_H */

/*----------------------------------------------------------------------------*/
