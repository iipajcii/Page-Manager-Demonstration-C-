#ifndef PAGE_MANAGER_CPP
#define PAGE_MANAGER_CPP
#include "class.page_manager.hpp"

PageManager::PageManager(){
	root = new Operation("");
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
	branch->setUp(new Operation(""));
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
	if(leaf == branch && leaf->getValue() == ""){
		leaf->setValue(v);
		return true;
	}
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

	while(b){
		while(o){
			cout << o->getValue() << endl;
			o = o->getAcross();
		}
		b = b->getUp();
		// cout << "Next Branch" << endl;
		o = b;
	}
}


int PageManager::count(){
	Operation* b = root;
	Operation* o = b;
	int count = 0;
	while(b){
		while(o){
			count++;
			o = o->getAcross();
		}
		b = b->getUp();
		o = b;
	}
	return count;
}

string PageManager::displayNumberFormatter(int num)
{
	if(num < 10)
	{return "  " + to_string(num) + "  ";}
	else if (num < 100)
	{return "  " + to_string(num) + " ";}
	else if (num < 1000)
	{return "  " + to_string(num) + "";}
 	return to_string(num);
}

string PageManager::displayNumberFormatter(string n)
{
	int num = std::stoi(n);
	if(num < 10)
	{return "  " + to_string(num) + "  ";}
	else if (num < 100)
	{return "  " + to_string(num) + " ";}
	else if (num < 1000)
	{return "  " + to_string(num) + "";}
 	return to_string(num);
}
#endif
