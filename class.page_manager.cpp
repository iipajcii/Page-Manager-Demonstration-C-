#ifndef PAGE_MANAGER_CPP
#define PAGE_MANAGER_CPP
#include "class.page_manager.hpp"

PageManager::PageManager(){
	root = new Operation("");
	branch = root;
	leaf = root;
};

PageManager::PageManager(string in){
	root = new Operation("");
	branch = root;
	leaf = root;
	input = in;
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

vector<string> PageManager::traverseReverse(){
	Operation* top_branch = root;
	Operation* current_branch = root;
	Operation* behind_current_branch = root;
	Operation* last_page = root;
	Operation* current_page = root;
	Operation* b = root;
	Operation* p = root;
	vector<string> s;

	//Get Top Branch
	while(current_branch->getUp()){
		behind_current_branch = current_branch;
		current_branch = current_branch->getUp();
		cout << current_branch->getValue() << endl;
	}

	//This if-else is to correct an error found in reverseTraverse if addBranch is called with no leaf added
	if(current_branch->getValue() != ""){top_branch = current_branch;}
	else{top_branch = behind_current_branch;}
	
	//Progressively Go Down from Top Branch
	while(current_branch != root){
		b = root;
		while(b->getUp() != current_branch){
			b = b->getUp();
		}
		
		//Now at the branch below current branch
		current_branch = current_page = last_page = p = b;

		//Getting Last Page on Branch
		while(last_page->getAcross()){
			 last_page = last_page->getAcross();
		}

		//Now at the last page of the branch
		current_page = last_page;
		while(current_page != current_branch){
			p = b = current_branch;
			while(p != current_page){
				b = p;
				p = p->getAcross();
			}
			current_page = b;
			cout << p->getValue() << endl;
			s.push_back(p->getValue());
		}
		cout << current_branch->getValue() << endl;
		s.push_back(current_branch->getValue());
	}
	//Fun fact. If you remove the return line you can still compile the program but it won't run (-: (upside_down smiley face)
	return s;
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

bool PageManager::step(){
	if(leaf){
		if(leaf->getAcross()){
			leaf = leaf->getAcross();
			return true;
		}
		else if (branch->getUp()) {
			branch = branch->getUp();
			leaf = branch;
			return true;
		}
		return false;
	}
}

void PageManager::start(){
	leaf = root;
	branch = root;
}

void PageManager::setFrameCount(int f){
	frame_count = f;
}

int PageManager::getFrameCount(){
	return frame_count;
}

vector<string> PageManager::getPages(){
	return pages;
}

bool PageManager::add_page(string v){
	add_leaf(v);
	if(!isFull()){
		pages.push_back(v);
		return true;
	}
	else{
		return false;
	}
}

int PageManager::activePageCount(){
	return pages.size();
}

bool PageManager::isFull(){
	if(activePageCount() >= getFrameCount()){return true;}
	else {return false;}
}
#endif
