
#ifndef _AST_H
#define _AST_H 1

#include "includes.hh"
#include "visitor.hh"
#include <cstring>

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
class ASTStmtsNode;
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

extern string nili;
extern string inteiro ;
extern string intarray ;
extern string bol ;


class ASTNode {
public:
    ASTNode() { }
    virtual ~ASTNode() { }
    virtual void accept(Visitor& v) = 0;

    virtual string* get_type() = 0;
    virtual void set_lineno(int ln) = 0;
    virtual int get_lineno() = 0;
    virtual void dump() = 0;
};

class ASTProgramNode : public ASTNode {
public:
    ASTProgramNode(ASTNode* n1, ASTNode* n2) :ASTNode(), node1(n1), node2(n2) { }
    virtual ~ASTProgramNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return &nili; }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
    ASTNode* node2;
};

class ASTMainNode : public ASTNode {
public:
    ASTMainNode(string* name, string* vars, ASTNode* n1) : ASTNode(), name1(name), vars1(vars), node1(n1) { }
    virtual ~ASTMainNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return &nili; }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
    string* name1;
	string* vars1;
};

class ASTClassDeclAuxNode : public ASTNode {
public:
    ASTClassDeclAuxNode(ASTNode* n1, ASTNode* n2) : ASTNode(), node1(n1), node2(n2) { }
    virtual ~ASTClassDeclAuxNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return &nili; }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
    ASTNode* node2;
};


class ASTTypeNode : public ASTNode {
public:
    ASTTypeNode(string* name) : ASTNode(), name1(name) { }
    virtual ~ASTTypeNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return name1; }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    string* name1;
};


class ASTClassDeclNode : public ASTNode {
public:
    ASTClassDeclNode(ASTTypeNode* n1, ASTNode* n2, ASTNode* n3) : ASTNode(), type(n1), node1(n2), node2(n3) { }
    virtual ~ASTClassDeclNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return type->get_type(); }
	virtual ASTTypeNode* gettypenode() {return type;}
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
    ASTNode* node2;
	ASTTypeNode* type;
};

class ASTExtClassDeclNode : public ASTNode {
public:
    ASTExtClassDeclNode(ASTTypeNode* name, ASTTypeNode* extended, ASTNode* n1, ASTNode* n2) : ASTNode(), name1(name), extended1(extended), node1(n1), node2(n2) { }
    virtual ~ASTExtClassDeclNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }
    virtual string* get_type() { return &nili; }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
    ASTNode* node2;
	ASTTypeNode* name1;
	ASTTypeNode* extended1;
};


class ASTVarDeclAuxNode : public ASTNode {
public:
    ASTVarDeclAuxNode(ASTNode* n1, ASTNode* n2) : ASTNode(), node1(n1), node2(n2) { }
    virtual ~ASTVarDeclAuxNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return &nili; }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
    ASTNode* node2;
};

class ASTVarDeclNode : public ASTNode {
public:
    ASTVarDeclNode(ASTNode* n1, string* name) : ASTNode(), node1(n1), name1(name) { }
    virtual ~ASTVarDeclNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return node1->get_type(); }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
    string* name1;
};

class ASTMethodDeclAuxNode : public ASTNode {
public:
    ASTMethodDeclAuxNode(ASTNode* n1, ASTNode* n2) : ASTNode(), node1(n1), node2(n2) { }
    virtual ~ASTMethodDeclAuxNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return &nili; }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
    ASTNode* node2;
};

class ASTMethodDeclNode : public ASTNode {
public:
    ASTMethodDeclNode(ASTNode* n1, string* name, ASTNode* n2, ASTNode* n3, ASTNode* n4, ASTNode* n5) : 
	ASTNode(), node1(n1), name1(name), node2(n2), node3(n3), node4(n4), node5(n5) { }
    virtual ~ASTMethodDeclNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { node1->get_type(); }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
    ASTNode* node2;
	ASTNode* node3;
    ASTNode* node4;
	ASTNode* node5;
	string* name1;
};

class ASTFormListNode : public ASTNode {
public:
    ASTFormListNode(ASTNode* n1, string* name, ASTNode* n2) : ASTNode(), name1(name), node1(n1), node2(n2) { }
    virtual ~ASTFormListNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return node1->get_type(); }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
    ASTNode* node2;
	string* name1;
};

class ASTFormRestAuxNode : public ASTNode {
public:
    ASTFormRestAuxNode(ASTNode* n1, ASTNode* n2) : ASTNode(), node1(n1), node2(n2) { }
    virtual ~ASTFormRestAuxNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return &nili; }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
    ASTNode* node2;
};

class ASTFormRestNode : public ASTNode {
public:
    ASTFormRestNode(ASTNode* n1, string* name) : ASTNode(), node1(n1), name1(name) { }
    virtual ~ASTFormRestNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return node1->get_type(); }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
    string* name1;
};

class ASTStAuxNode : public ASTNode {
public:
    ASTStAuxNode(ASTNode* n1, ASTNode* n2) : ASTNode(), node1(n1), node2(n2) { }
    virtual ~ASTStAuxNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return &nili; }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
    ASTNode* node2;
};

class ASTStIfNode : public ASTNode {
public:
    ASTStIfNode(ASTNode* n1, ASTNode* n2, ASTNode* n3) : ASTNode(), node1(n1), node2(n2), node3(n3) { }
    virtual ~ASTStIfNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return node1->get_type(); }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
    ASTNode* node2;
    ASTNode* node3;
};

class ASTStmtsNode : public ASTNode {
public:
    ASTStmtsNode(ASTNode* n1) : ASTNode(), node1(n1){ }
    virtual ~ASTStmtsNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return node1->get_type(); }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
};


class ASTStWhileNode : public ASTNode {
public:
    ASTStWhileNode(ASTNode* n1, ASTNode* n2) : ASTNode(), node1(n1), node2(n2) { }
    virtual ~ASTStWhileNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return node1->get_type(); }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
    ASTNode* node2;
};

class ASTStPrintNode : public ASTNode {
public:
    ASTStPrintNode(ASTNode* n1) : ASTNode(), node1(n1) { }
    virtual ~ASTStPrintNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return node1->get_type(); }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
};

class ASTStEqNode : public ASTNode {
public:
    ASTStEqNode(ASTNode* n1, ASTNode* n2) : ASTNode(), node2(n2), node1(n1) { }
    virtual ~ASTStEqNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return node1->get_type(); }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
	ASTNode* node2;
};

class ASTStArrayEqNode : public ASTNode {
public:
    ASTStArrayEqNode(ASTNode* n3, ASTNode* n1, ASTNode* n2) : ASTNode(), node3(n3), node1(n1), node2(n2) { }
    virtual ~ASTStArrayEqNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return node1->get_type(); }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
	ASTNode* node2;
	ASTNode* node3;
};

class ASTReadersNode : public ASTNode {
public:
    ASTReadersNode() : ASTNode() { }
    virtual ~ASTReadersNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return &nili; }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
};

class ASTExpThisNode : public ASTNode {
public:
    ASTExpThisNode(string* n1) : ASTNode(), name1(n1) { }
    virtual ~ASTExpThisNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return name1; }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
	
	string* name1;
};

class ASTExpBoolNode : public ASTNode {
public:
    ASTExpBoolNode(bool bool1) : ASTNode() , bolean(bool1) {}
    virtual ~ASTExpBoolNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return &bol; }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
	
	bool bolean;
};

class ASTExpOperatorNode : public ASTNode {
public:
    ASTExpOperatorNode(ASTNode* n1, string* op, ASTNode* n2) : ASTNode(), op1(op), node1(n1), node2(n2) { }
    virtual ~ASTExpOperatorNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return node1->get_type(); }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
    ASTNode* node2;
	string* op1;
};

class ASTExpArrayNode : public ASTNode {
public:
    ASTExpArrayNode(ASTNode* n1, ASTNode* n2) : ASTNode(), node1(n1), node2(n2) { }
    virtual ~ASTExpArrayNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return &inteiro; }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
    ASTNode* node2;
};

class ASTExpLengthNode : public ASTNode {
public:
    ASTExpLengthNode(ASTNode* n1) : ASTNode(), node1(n1) { }
    virtual ~ASTExpLengthNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return node1->get_type(); }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
};

class ASTExpCallNode : public ASTNode {
public:
    ASTExpCallNode(ASTNode* n1, string* op, ASTNode* n2) : ASTNode(), op1(op), node1(n1), node2(n2) { }
    virtual ~ASTExpCallNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return node1->get_type(); }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
    ASTNode* node2;
	string* op1;
};

class ASTExpIntNode : public ASTNode {
public:
    ASTExpIntNode(int num1) : ASTNode(), number(num1) {}
    virtual ~ASTExpIntNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return &inteiro; }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
	
	int number;
};

class ASTIDRefNode : public ASTNode {
public:
    ASTIDRefNode(string* name) : ASTNode(),  name1(name) { }
    virtual ~ASTIDRefNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return name1; }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
	
public:
	string* name1;
};


class ASTIntArrayNode : public ASTNode {
public:
    ASTIntArrayNode(ASTNode* n1) : ASTNode(), node1(n1) { }
    virtual ~ASTIntArrayNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return &intarray; }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
};

class ASTObjectNode : public ASTNode {
public:
    ASTObjectNode(string* name) : ASTNode(),  name1(name) { }
    virtual ~ASTObjectNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return name1; }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
	
public:
	string* name1;
};

class ASTNegationNode : public ASTNode {
public:
    ASTNegationNode(ASTNode* n1) : ASTNode(), node1(n1) { }
    virtual ~ASTNegationNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return &bol; }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
};

class ASTExpListNode : public ASTNode {
public:
    ASTExpListNode(ASTNode* n1, ASTNode* n2) : ASTNode(), node1(n1), node2(n2) { }
    virtual ~ASTExpListNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return node1->get_type(); }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
    ASTNode* node2;
};


class ASTExpRestAuxNode : public ASTNode {
public:
    ASTExpRestAuxNode(ASTNode* n1, ASTNode* n2) : ASTNode(), node1(n1), node2(n2) { }
    virtual ~ASTExpRestAuxNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return &nili; }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
    ASTNode* node2;
};

class ASTExpRestNode : public ASTNode {
public:
    ASTExpRestNode(ASTNode* n1) : ASTNode(), node1(n1) { }
    virtual ~ASTExpRestNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return node1->get_type(); }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
    ASTNode* node1;
};

class ASTStReadersNode : public ASTNode {
public:
    ASTStReadersNode() { }
    virtual ~ASTStReadersNode() { }
    virtual void accept(Visitor& v) { v.visit(*this); }

    virtual string* get_type() { return &nili; }
    virtual void set_lineno(int ln) { }
    virtual int get_lineno() { return 0; }
    virtual void dump() { }
public:
};


#endif /* _AST_H */

/*----------------------------------------------------------------------------*/
