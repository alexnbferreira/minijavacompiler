//jpms:bc
/*----------------------------------------------------------------------------*\
 * File:        symtab.hh
 *
 * Description: 
 *
 * Author:      jpms
 * 
 *                                     Copyright (c) 2015, Joao Marques-Silva
\*----------------------------------------------------------------------------*/
//jpms:ec

#ifndef _SYMTAB_H
#define _SYMTAB_H 1

#include "includes.hh"

class TabData;
class ASTNode;


	
typedef unordered_map<string,TabData*> TabMap;


class TempElement{

public: 
	TempElement(string n, int id, bool vari): name(n), ID(id), var(vari) {}
	int getID() const {return ID;}
	string getName() const {return name;}
	bool isVar(){return var;}
	bool operator==(const TempElement& e) const;
protected:
	string name;
	int ID;	
	bool var;
};

class SymbolTable {
public:
    SymbolTable() : maps() { TabMap* tmap = new TabMap(); maps.push_back(tmap); globalClass = 0;}

    TabData* lookup(string& var);
    TabData* lookupclass(); 
    TabData* lookup_top(string& var);
    TabData* lookupmethod(string& method); 
    TabData* insert(string& var,int t);
    TabData* insertExt(string& var, int type, int etended);
	
void incGlobalClass();

    void push_scope();

    void pop_scope();

 int globalClass;
protected:
    vector<TabMap*> maps;
};

class TabData {
public:
    TabData(string& nm, int type,int id) : name(nm), node(NULL),classID(id) {
		switch(type){ 
			case 1: isvar = true; ismethod = false; isclass= false; break; 
			case 2: isvar = false; ismethod = true; isclass= false; break; 
			case 3: isvar = false; ismethod = false; isclass= true; break; 
			}
	}
	
    inline void set_node(ASTNode* nn) { node = nn; }

    inline ASTNode* get_node() { return node; }
	inline int get_classID() {return classID;}
	inline bool is_var() {return isvar;}
	inline bool is_method() {return ismethod;}
	inline bool is_class() {return isclass;}

    inline string& get_name() { return name; }

protected:

    string& name;
	bool isvar;
	bool ismethod;
	bool isclass;
	
	int classID;

    ASTNode* node;

};

#endif /* _SYMTAB_H */

/*----------------------------------------------------------------------------*/
