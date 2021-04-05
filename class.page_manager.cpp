#ifndef PAGE_MANAGER_CPP
#define PAGE_MANAGER_CPP
#include "class.page_manager.hpp"

PageManager::PageManager(){
	root = new Operation("S");
	branch = root;
	leaf = root;
};

bool PageManager::next_branch(){
	if(branch->getUp() != NULL){
		branch = branch->getUp();
		leaf = branch;
		return true;
	}
	else{
		cout << "Next Branch Not Possible" << endl;
		return false;
	}
};


bool PageManager::next_leaf(){
	if(leaf->getAcross() != NULL){
		leaf = leaf->getAcross();
		return true;
	}
	else{
		cout << "Next Branch Not Possible" << endl;
		return false;
	}
};

bool PageManager::add_branch(){
	branch->setUp(new Operation());
	if(branch->getUp() != NULL){
		branch = branch->getUp();
		leaf = branch;
		return true;
	}
	else{
		cout << "Add Branch Not Possible" << endl;
		return false;
	}
};

bool PageManager::add_leaf(string v){
	leaf->setAcross(new Operation(v));
	if(leaf->getAcross() != NULL){
		leaf = leaf->getAcross();
		return true;
	}
	else{
		cout << "Add Leaf Not Possible" << endl;
		return false;
	}
};

string PageManager::read_leaf(){
	return leaf->getValue();
};

void PageManager::traverse(){
	Operation* b = root;
	Operation* o = b;

	while(b->getUp() != NULL){
		while(o != NULL){
			cout << o->getValue() << endl;
			o = o->getAcross();
		}
		b = b->getUp();
		cout << "Next Branch" << endl;
		o = b;
	}
}

#endif
