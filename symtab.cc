//jpms:bc
/*----------------------------------------------------------------------------*\
 * File:        symtab.cc
 *
 * Description: 
 *
 * Author:      jpms
 *
 *                                     Copyright (c) 2015, Joao Marques-Silva
\*----------------------------------------------------------------------------*/
//jpms:ec

#include "symtab.hh"

static int ind = 0;

bool TempElement::operator==(const TempElement& e) const{
	cout << "Komparing "<< this->getName() <<" with "<< e.getName() << " with kodes "<< this->getID() << " " << e.getID() << endl;
		if (e.getName().compare(this->getName()) == 0){
				return true;		
		}
	return false;
	}

TabData* SymbolTable::lookup(string& var) {
    TabData *td = NULL;
    for(int i=ind; i>=0; --i) {
	TabMap::iterator mpos = (*maps[i]).find(var);
	if (mpos != (*maps[i]).end()) {
	    td = mpos->second;
	    break;
	}
    }
    return td;
}

TabData* SymbolTable::lookup_top(string& var) {
   
	int i=ind;
    TabMap::iterator mpos = (*maps[i]).find(var);

    TabData* td = (mpos != (*maps[i]).end()) ? mpos->second : NULL;

return td;
}

TabData* SymbolTable::lookupclass() {
    TabData *td = NULL;
    for(int i=ind; i>=0; --i) {
		TabMap::iterator mpos = (*maps[i]).begin();
		for ( mpos; mpos != (*maps[i]).end(); ++mpos){
			if (mpos->second->is_class()){
				td = mpos->second;
				break;
			}
		}
    }
    return td;
}

TabData* SymbolTable::lookupmethod(string& var) {
    TabData *td = NULL;
    for(int i = ind; i>=0; --i) {
	TabMap::iterator mpos = (*maps[i]).find(var);
	if (mpos != (*maps[i]).end()) {
	
	    td = mpos->second;
	    break;
	
	}
    }
	if (td != NULL && td->is_method())
    		return td;
    return NULL;
}


TabData* SymbolTable::insert(string& var, int type)
{
    assert(lookup_top(var) == NULL);

    TabData* vdata = new TabData(var, type,this->globalClass);
    (*maps[ind])[var] = vdata;	
    return vdata;
}

TabData* SymbolTable::insertExt(string& var, int type, int etended)
{
    assert(lookup_top(var) == NULL);

    TabData* vdata = new TabData(var, type, etended);
    (*maps[ind])[var] = vdata;	
    return vdata;
}

void SymbolTable::push_scope()
{
if(ind==0){
	if (maps[1] == NULL){
		TabMap* tmap = new TabMap();
    		maps.push_back(tmap);
	}
    ind++;
}
else{
	TabMap* tmap = new TabMap();
    	maps.push_back(tmap);
	ind++;
	}


}

void SymbolTable::pop_scope()
{
    assert(ind >= 0);
if(ind>=2){
    TabMap* tmap = maps[ind];
    delete tmap;
    maps.pop_back();
	ind--;
}
else{
ind--;
}
}

void SymbolTable::incGlobalClass(){
	this->globalClass++;
}



/*----------------------------------------------------------------------------*/
