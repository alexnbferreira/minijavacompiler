
#include "ast_utils.hh"
#include "includes.hh"
#include <algorithm>
string nili = "null";

string inteiro = "inteiro" ;
string intarray = "int[]";
string bol = "boolean";

extern int line_num;

static bool varsok = true;

static unsigned inwhile = 0;


static ASTNode* troot = NULL;

static SymbolTable* stab = NULL;

static vector<TempElement*> temps;



void ASTUtils::insertTemp(string* name, bool var){
	TempElement* ele = new TempElement(*name, stab->globalClass, var);
	cout << *name <<" " << stab->globalClass << endl;
	temps.push_back(ele);
	
}

void ASTUtils::deleteTemp(string* name){
	TempElement* aux = new TempElement(*name, stab->globalClass, false);
	int au = 0;
	while(1){
		if (temps.begin()+au == temps.end())
			break;
		if (temps[au]->getName() == aux->getName() && temps[au]->getID() <= aux->getID() && !temps[au]->isVar()){
			cout << "Erasing class/method "<< *name << aux->getID()<< endl;	
			temps.erase(temps.begin()+au);
		}
		else{
			au++;		
		}
			
	}
	
}

int ASTUtils::sizeTemp(){
 
for (int t = temps.size()-1; t != -1; t--)
	cout << "Temp: "<< temps[t]->getName() << endl;
return temps.size();
}


void
ASTUtils::init_ast_utils(SymbolTable& st)
{
    stab = &st;
}

bool
ASTUtils::get_varsok()
{

    return varsok;
}

ASTNode*
ASTUtils::get_root_node()
{
    return troot;
}

void
ASTUtils::set_root_node(ASTNode* rn)
{
    troot = rn;
}

void
ASTUtils::push_scope()
{
    assert(stab != NULL);
    stab->push_scope();
}

void
ASTUtils::pop_scope()
{
    assert(stab != NULL);
    stab->pop_scope();
}

void
ASTUtils::incGlobalClass(){
	assert(stab!= NULL);
	stab->incGlobalClass();
}

void
ASTUtils::enter_while()
{
    inwhile++;
}

void
ASTUtils::exit_while()
{
    inwhile--;
}

ASTNode*
ASTUtils::mk_stmts_node(ASTNode* n1)
{
    assert(n1 != NULL) ;
    
    return new ASTStmtsNode(n1);
}

ASTNode*
ASTUtils::mk_program_node(ASTNode* n1, ASTNode* n2){
	assert(n1 != NULL);
	return new ASTProgramNode(n1, n2);
}

ASTNode*
ASTUtils::mk_main_node(string* id1, string* id2, ASTNode* n1 ){
	assert(stab != NULL && n1 != NULL && id2 != NULL);
	ASTMainNode* node = NULL;
	TabData* vdata = stab->lookup(*id1);
	if(vdata != NULL){
		cout << "Already defined class";
		cout << id1 << ". Line " << line_num << endl;
		varsok = false;
		node = new ASTMainNode(id1,id2,n1);
		node->set_lineno(line_num);
	}
	else{
		vdata = stab->insert(*id1,3);
		cout << "Finished inserting main class" << endl;
		node = new ASTMainNode(id1, id2, n1);
		node->set_lineno(line_num);
		vdata->set_node(node);
	cout << "Deleting Temporarios . . . . " << *id1<< endl;
	deleteTemp(id1);
	}
	cout << "Returning new Main node" << endl;
	return node;
}


ASTNode*
ASTUtils::mk_classDeclAux_node(ASTNode* n1, ASTNode* n2){
	assert (n1 != NULL);
cout << "You are in class decl aux" << endl;
	if (n2 == NULL)
		return n1;
	ASTClassDeclAuxNode* node = new ASTClassDeclAuxNode(n1, n2);
	return node;
}


ASTNode*
ASTUtils::mk_ExtclassDecl_node(string* id1,string* id2, ASTNode* n1, ASTNode* n2){
	assert(stab != NULL && id1 != NULL);
	int classid = -1;
	TabData* vdata = NULL;
	ASTExtClassDeclNode* node = NULL;
	ASTTypeNode* nodeExt = NULL;
	vdata = stab->lookup(*id2);
	if (vdata == NULL || (vdata != NULL && !vdata->is_class())){
		cout << "Undefined class ";
		cout << *id2 << ". Line " << line_num << endl;
		cout << "Inserting temporary ..." << *id2 << endl;
		insertTemp(id2, false);
		nodeExt = new ASTTypeNode(id2);
	}
	else{
		nodeExt = (ASTTypeNode*) vdata->get_node();
		classid = vdata->get_classID();	
	}
        if (classid == -1) classid = stab->globalClass;
	vdata = stab->lookup(*id1);
	if(vdata != NULL) {
		cout << "Already defined class";
		cout << id1 << ". Line " << line_num << endl;
		ASTTypeNode* nodeT = new ASTTypeNode(id1);
		node = new ASTExtClassDeclNode(nodeT,nodeExt , n1, n2);
		node->set_lineno(line_num);
	}
	else{
		vdata = stab->insertExt(*id1,3, classid);
		ASTTypeNode* nodeT = new ASTTypeNode(id1);
		node = new ASTExtClassDeclNode(nodeT, nodeExt, n1, n2);
		node->set_lineno(line_num);
		vdata->set_node(nodeT);
		cout << "Deleting Temporarios . . . . " << *id1<< endl;
		deleteTemp(id1);
	}
	return node;
}

ASTNode*
ASTUtils::mk_classDecl_node(string* id1, ASTNode* n1, ASTNode* n2){
	assert(stab != NULL && id1 != NULL);
	TabData* vdata = NULL;
	ASTClassDeclNode* node = NULL;
	vdata = stab->lookup(*id1);
	if(vdata != NULL) {
		cout << "Already defined class";
		cout << id1 << ". Line " << line_num << endl;
		ASTTypeNode* nodeT = new ASTTypeNode(id1);
		node = new ASTClassDeclNode(nodeT, n1, n2);
		node->set_lineno(line_num);
	}
	else{
		vdata = stab->insert(*id1,3);
		ASTTypeNode* nodeT = new ASTTypeNode(id1);
		node = new ASTClassDeclNode(nodeT, n1, n2);
		node->set_lineno(line_num);
		vdata->set_node(nodeT);
		cout << "Deleting Temporarios . . . . " << *id1<< endl;
		deleteTemp(id1);
	}
	return node;
}


ASTNode*
ASTUtils::mk_varDecl_node(ASTNode* n1, string* id1){
	assert(stab !=NULL && n1 != NULL && id1 != NULL);
	ASTVarDeclNode* node = NULL;
	TabData* vdata = stab->lookup_top(*id1);
	if(vdata != NULL){
		cout << "Already defined variable";
		cout << id1 << ". Line " << line_num << endl;
		varsok = false;
		node = (ASTVarDeclNode*) vdata->get_node();
	}
	else{
		vdata = stab->insert(*id1, 1);
		node = new ASTVarDeclNode(n1,id1);
		node->set_lineno(line_num);
		vdata->set_node(node);
		cout << "Deleting Temporarios . . . . " << *id1<< endl;
		deleteTemp(id1);
		}
	assert(node != NULL);
	return node;
}


ASTNode*
ASTUtils::mk_varDeclAux_node(ASTNode* n1, ASTNode* n2){

	assert( n1!= NULL);
	if (n2 == NULL)
		return n1;
	ASTVarDeclAuxNode* node = new ASTVarDeclAuxNode(n1, n2);
	return node;
}


ASTNode*
ASTUtils::mk_methDeclAux_node(ASTNode* n1, ASTNode* n2){
	assert(n1!=NULL);
	if (n2 == NULL)
		return n1;
	ASTMethodDeclAuxNode* node = new ASTMethodDeclAuxNode(n1, n2);
	return node;
}

ASTNode*
ASTUtils::mk_methDecl_node(ASTNode* n1, string* id1,ASTNode* n2, ASTNode* n3, ASTNode* n4, ASTNode* n5){
	assert(stab!=NULL && n1 != NULL && id1 != NULL && n5 != NULL);
	TabData* vdata = stab->lookup(*id1);
	ASTMethodDeclNode* node = NULL;
	if (vdata != NULL && vdata->is_method()){
		cout << "Already defined method ";
		cout << *id1 << ". Line " << line_num << endl;
		varsok = false;
		node = new ASTMethodDeclNode(n1, id1, n2, n3, n4, n5);
		node->set_lineno(line_num);
	}
	else{
		node = new ASTMethodDeclNode(n1, id1, n2, n3, n4, n5);
		node->set_lineno(line_num);
		vdata = stab->insert(*id1, 2);
		vdata->set_node(node);
		cout << "Deleting Temporarios . . . . " << *id1<< endl;
		deleteTemp(id1);
	}
	return node;
}

ASTNode*
ASTUtils::mk_formList_node(ASTNode* n1,string* id1, ASTNode* n2){
	assert(stab != NULL && n1!=NULL && id1!=NULL);
	TabData* vdata = stab->insert(*id1, 1);
	ASTVarDeclNode*	node1 = new ASTVarDeclNode(n1,id1);
	node1->set_lineno(line_num);
	vdata->set_node(node1);
	ASTFormListNode* node = new ASTFormListNode(n1, id1, n2);
	node->set_lineno(line_num);
	return node;
}

ASTNode*
ASTUtils::mk_formRestAux_node(ASTNode* n1, ASTNode* n2){
	assert(n1 != NULL);
	if (n2 == NULL)
		return n1;
	ASTFormRestAuxNode* node = new ASTFormRestAuxNode(n1, n2);
	return node;
}


ASTNode*
ASTUtils::mk_formRest_node(ASTNode* n1, string* id1){
	assert(n1 != NULL && id1 != NULL);
TabData* vdata = stab->insert(*id1, 1);
	ASTVarDeclNode*	node1 = new ASTVarDeclNode(n1,id1);
	node1->set_lineno(line_num);
	vdata->set_node(node1);	
ASTFormRestNode* node = new ASTFormRestNode(n1, id1);
	node->set_lineno(line_num);
	return node;
}



ASTNode*
ASTUtils::mk_type_node(string* id1){
	assert(stab != NULL && id1 != NULL);
	ASTNode* node = NULL;
	TabData* vdata = stab->lookup(*id1);
	if (vdata == NULL){
		cout << "Type not defined ";
		cout << *id1 << ".Line" << line_num << endl;
		
	cout << "Inserir Temporarios . . . . " << *id1<< endl;
	insertTemp(id1, false);

	node = new ASTTypeNode(id1);
	vdata = stab->insert(*id1,3);
	vdata->set_node(node);
	return node;
	}
	if (vdata->is_class()){
		node = vdata->get_node();
		return node;
	}
	else{
		cout << "Not a type ";
		cout << id1 << ".Line" << line_num << endl;
		varsok = false;
		node = new ASTTypeNode(id1);
		return node;
	}
}


ASTNode*
ASTUtils::mk_stAux_node(ASTNode* n1, ASTNode* n2){
	assert(n1 != NULL);
	if (n2 == NULL)
		return n1;
	ASTStAuxNode* node = new ASTStAuxNode(n1, n2);
	return node;
}



ASTNode*
ASTUtils::mk_stIf_node(ASTNode* n1, ASTNode* n2, ASTNode* n3){
	assert(n1!=NULL && n2!=NULL && n3!=NULL);
	ASTStIfNode* node = new ASTStIfNode(n1, n2, n3);
	node->set_lineno(line_num);
	return node;
}

ASTNode*
ASTUtils::mk_stWhile_node(ASTNode* n1, ASTNode* n2){
	assert(n1!=NULL && n2!=NULL);
	ASTStWhileNode* node = new ASTStWhileNode(n1, n2);
	node->set_lineno(line_num);
	return node;
}

ASTNode*
ASTUtils::mk_stPrint_node(ASTNode* n1){
	assert(n1!=NULL);
	ASTStPrintNode* node = new ASTStPrintNode(n1);
	node->set_lineno(line_num);
	return node;
}

ASTNode*
ASTUtils::mk_stEq_node(string* name1, ASTNode* n2){
	
	assert(stab != NULL && name1 != NULL && n2 != NULL);
	TabData* vdata = stab->lookup(*name1);
	if(vdata== NULL){
		cout << "Assigning undefined variable ";
		cout << *name1 << " .Line" << line_num << endl;
		vdata = stab->insert(*name1, 1);
		ASTNode* node = new ASTVarDeclNode(new ASTTypeNode(&inteiro), name1);
		node->set_lineno(line_num);
		vdata->set_node(node);
		cout << "Inserir Temporarios . . . . " << *name1<< endl;
		insertTemp(name1, true);
	}
	ASTNode* node = vdata->get_node();
	ASTStEqNode* node2 = new ASTStEqNode(node, n2);
	node2->set_lineno(line_num);
	return node2;
}

ASTNode*
ASTUtils::mk_stArrayEq_node(string* name1, ASTNode* n2, ASTNode* n3){
	assert(stab!= NULL && name1 != NULL && n2 != NULL && n3 != NULL);
	TabData* vdata = stab->lookup(*name1);
	if(vdata== NULL){
		cout << "Assigning undefined variable ";
		cout << name1 << ".Line" << line_num << endl;
		vdata = stab->insert(*name1, 1);
		ASTNode* node = new ASTVarDeclNode(new ASTTypeNode(&intarray), name1);
		node->set_lineno(line_num);
		vdata->set_node(node);
		cout << "Inserir Temporarios . . . . " << *name1<< endl;
		insertTemp(name1,true);
	}
	ASTNode* node = vdata->get_node();
	ASTStArrayEqNode* node2 = new ASTStArrayEqNode(node, n2, n3);
	node2->set_lineno(line_num);
	return node2;
}
	

ASTNode*
ASTUtils::mk_readers_node(){
	ASTStReadersNode* node = new ASTStReadersNode();
	node->set_lineno(line_num);
	return node;
}

ASTNode*
ASTUtils::mk_expThis_node(){
	assert(stab != NULL);
	TabData* tab = stab->lookupclass();
	ASTExpThisNode* node = NULL;
	if (tab == NULL){
		cout << "Not inside a class";
		node = new ASTExpThisNode(&nili);
		varsok = false;
	}
	else{
		node = new ASTExpThisNode(&tab->get_name());
	}
	node->set_lineno(line_num);
	return node;
}

ASTNode*
ASTUtils::mk_expBool_node(bool bool1){
	ASTExpBoolNode* node = new ASTExpBoolNode(bool1);
	node->set_lineno(line_num);
	return node;
}
	

ASTNode*
ASTUtils::mk_expOperator_node(ASTNode* n1, string* op, ASTNode* n2){
	assert(n1!=NULL && op!=NULL && n2!=NULL);
	ASTExpOperatorNode* node = new ASTExpOperatorNode(n1,op,n2);
	node->set_lineno(line_num);
	return node;
}

ASTNode*
ASTUtils::mk_expArray_node(ASTNode* n1, ASTNode* n2){
	assert(n1 != NULL && n2 != NULL);
	ASTExpArrayNode* node = new ASTExpArrayNode(n1, n2);
	node->set_lineno(line_num);
	return node;
}

ASTNode*
ASTUtils::mk_length_node(ASTNode* n1){
	assert(n1 != NULL);
	ASTExpLengthNode* node = new ASTExpLengthNode(n1);
	node->set_lineno(line_num);
	return node;
}
	

ASTNode*
ASTUtils::mk_exp_call_node(ASTNode* n1, string* id1, ASTNode* n2){
	assert(stab != NULL && n1 != NULL && id1 != NULL);
	TabData* vdata = stab->lookup(*id1);
        if (vdata != NULL && !(vdata->is_method()))
           vdata = NULL;
	ASTExpCallNode* node = NULL;
	if (vdata == NULL){
		cout << "Undefined method ";
		cout << *id1 << "in expression. Line "<< line_num << endl;
		vdata = stab->insert(*id1, 2);
		cout << "Inserir Temporarios . . . . " << *id1<< endl;
		insertTemp(id1,false);
	}
	
	node = new ASTExpCallNode(n1, id1, n2);
	node->set_lineno(line_num);
	return node;
}

ASTNode*
ASTUtils::mk_integer_node(int num1){
	ASTExpIntNode* node = new ASTExpIntNode(num1);
	node->set_lineno(line_num);
	return node;
}

ASTNode*
ASTUtils::get_id_node(string* id){
	assert(stab != NULL);
    ASTVarDeclNode* vn = NULL;
    TabData* vdata = stab->lookup(*id);
    if (vdata == NULL) {
	cout << "Undefined variable ";
	cout << *id << " in expression. Line " << line_num << endl;
	cout << "Inserir Temporarios . . . . " << *id<< endl;
	insertTemp(id, true);
	TabData* dt = stab->lookup(inteiro);
	ASTNode* nd1 = dt->get_node();
	vn = new ASTVarDeclNode(nd1,id);
	vn->set_lineno(line_num);
    }
    else {
		vn = (ASTVarDeclNode*) vdata->get_node();
    }
    assert(vn !=NULL);
    return vn;
}


ASTNode*
ASTUtils::mk_newint_array_node(ASTNode* n1){
	assert(n1 != NULL);
	ASTIntArrayNode* node = new ASTIntArrayNode(n1);
	node->set_lineno(line_num);
	return node;
}


ASTNode*
ASTUtils::mk_newobject_node(string* id1){
	assert(stab!=NULL && id1 != NULL);
	TabData* vdata = stab->lookup(*id1);
	ASTObjectNode* node = NULL;
	if (vdata == NULL){
		cout << "Undefined class ";
		cout << *id1 << "in expression. Line "<< line_num << endl;
		vdata = stab->insert(*id1, 3);
		cout << "Inserir Temporarios . . . . " << *id1 << endl;
		insertTemp(id1, false);
		
	}
	else{
		
		if (not (vdata->get_node()->get_type())->compare(nili)){
			cout << "Undefined class ";
			cout << *id1 << "in expression. Line "<< line_num << endl;
			cout << "Inserir Temporarios . . . . " << id1<< endl;
			insertTemp(id1, false);
		}
	}
	node = new ASTObjectNode(id1);
	node->set_lineno(line_num);
	return node;
}

ASTNode*
ASTUtils::mk_negation_node(ASTNode* n1){
	assert(n1 != NULL);
	ASTNegationNode* node = new ASTNegationNode(n1);
	node->set_lineno(line_num);
	return node;
}

ASTNode*
ASTUtils::mk_exp_list_node(ASTNode* n1, ASTNode* n2){
	assert(n1 != NULL);
	if (n2 == NULL)
		return n1;
	ASTExpListNode* node = new ASTExpListNode(n1, n2);
	return node;
}

ASTNode*
ASTUtils::mk_exp_rest_aux_node(ASTNode* n1, ASTNode* n2){
	assert(n1 != NULL);
	if(n2==NULL)
		return n1;
	ASTExpRestAuxNode* node = new ASTExpRestAuxNode(n1, n2);
	return node;
}

ASTNode*
ASTUtils::mk_exp_rest_node(ASTNode* n1){
	assert(n1 != NULL);
	ASTExpRestNode* node = new ASTExpRestNode(n1);
	node->set_lineno(line_num);
	return node;
}

void ASTUtils::start(){
	assert(stab != NULL);



ASTTypeNode* node = NULL;
	TabData* vdata = NULL;
		
node = new ASTTypeNode(&inteiro);
	vdata = stab->insert(inteiro,3);
		vdata->set_node(node);
node = new ASTTypeNode(&intarray);
	vdata = stab->insert(intarray,3);
		vdata->set_node(node);
node = new ASTTypeNode(&bol);
	vdata = stab->insert(bol,3);
		vdata->set_node(node);
cout << "Finished setting base types" << endl;


}

/*----------------------------------------------------------------------------*/
