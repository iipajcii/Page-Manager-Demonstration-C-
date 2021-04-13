#ifndef PAGE_MANAGER_CPP
#define PAGE_MANAGER_CPP
#include "class.page_manager.hpp"

PageManager::PageManager(){
	root = new Operation("");
	branch = root;
	leaf = root;
	clock_hand = NULL;
};

PageManager::PageManager(string in){
	root = new Operation("");
	branch = root;
	leaf = root;
	input = in;
	clock_hand = NULL;
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

vector<Operation> PageManager::traverse(){
	Operation* b = root;
	Operation* o = b;
	vector<Operation> s;

	while(b){
		while(o){
			cout << o->getValue() << endl;
			Operation a(o->getValue());
			s.push_back(a);
			o = o->getAcross();
		}
		b = b->getUp();
		// cout << "Next Branch" << endl;
		o = b;
	}
	return s;
}

vector<Operation> PageManager::traverseReverse(){
	Operation* top_branch = root;
	Operation* current_branch = root;
	Operation* behind_current_branch = root;
	Operation* last_page = root;
	Operation* current_page = root;
	Operation* b = root;
	Operation* p = root;
	vector<Operation> s;

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
			Operation temp(p->getValue());
			s.push_back(temp);
		}
		cout << current_branch->getValue() << endl;
		Operation temp(current_branch->getValue());
		s.push_back(temp);
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

void PageManager::display(){
	int rows = getFrameCount();
	int columns = input.length();

	cout << "Get Page Data Start" << endl;
	for (int outerVector = 0, outerVectorSize = page_data.size(); outerVector < outerVectorSize; outerVector++)
	{ 
		for (int innerVector = 0, innerVectorSize = page_data.at(outerVector).size(); innerVector < innerVectorSize; innerVector++)
		{
			cout << page_data.at(outerVector).at(innerVector).getValue() << " ";
		}
		cout << endl;
	}
	cout << "Get Page Data Stop" << endl;
	int dataCounter = 0;
	for(int i = 0; i < columns; i++){cout << "+-------+";}
	cout << endl;
	for (int column_count = 0 ;column_count < columns; column_count++)
	{
		cout << "|   " << (input.at(column_count)) <<"   |";
	}
	cout << endl;
	for(int i = 0; i < columns; i++){cout << "+-------+";}
	cout << endl;
	for(int row_count = 0; row_count < rows; row_count++){
		for(int i = 0; i < columns; i++){cout << "+-------+";}
		cout << endl;
		for (int column_count = 0 ;column_count < columns; column_count++)
		{
			cout << "| " << displayNumberFormatter(getPageDataColumn(dataCounter)) <<" |";
			dataCounter++;
			// step();
		}
		cout << endl;
		if(row_count == rows - 1){for(int i = 0; i < columns; i++){cout << "+-------+";}}
	}
	cout << endl;

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
	if(n == ""){return "     ";}
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
	vector<Operation> p(pages);
	Operation a("");
	while(p.size() < frame_count){p.push_back(a);}
	page_data.push_back(p);

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
	page_data.clear();
	history.clear();
	pages.clear();
}

void PageManager::setFrameCount(int f){
	frame_count = f;
}

int PageManager::getFrameCount(){
	return frame_count;
}

vector<Operation> PageManager::getPages(){
	return pages;
}

bool PageManager::add_page(string v){
	history.push_back(v);
	if(!isFull() && !isLoaded(v)){
		Operation o(v);
		pages.push_back(o);
		return true;
	}
	else{
		return false;
	}
}

bool PageManager::setInput(string v){
	input = v;
	for(int counter = 0, count = v.length(); counter < count; counter++)
	{
		add_page(to_string(v.at(counter)));
	}
	start();
}

int PageManager::activePageCount(){
	return pages.size();
}

bool PageManager::isFull(){
	if(activePageCount() >= getFrameCount()){return true;}
	else {return false;}
}

vector<string> PageManager::getHistory(){
	return history;
}

bool PageManager::isLoaded(string a)
{
	for(int counter = 0, count = getPages().size(); counter < count; counter++){
		if(pages.at(counter).getValue() == a){return true;}
	}
	return false;
}

bool PageManager::replace(string a, string b)
{
	for(int counter = 0, count = getPages().size(); counter < count; counter++){
		if(pages.at(counter).getValue() == a){pages.at(counter).setValue(b);pages.at(counter).setTicks(1); return true;}
	}
	return false;
}

void PageManager::Least_Recently_Used(){
	start();
	int frameCount = getFrameCount();			
	
	vector<Operation> s;
	for(int counter = 0, count = input.length(); counter < count; counter++){
		if(!add_page((*(new string(1, input.at(counter)))))){
			s = getPages();
			cout << "Page Current State" << endl;
			int countFrames = s.size();
			for(int counterFrames = 0; counterFrames < countFrames; counterFrames++){
			    cout << s.at(counterFrames).getValue() << " ";
			}
			cout << endl;
			cout << endl;
			cout << "End Display Current State" << endl;
			cout << "Display History" << endl;
			for(int historyCounter = getHistory().size() - 1; historyCounter >= 0; historyCounter--){
			    cout << history.at(historyCounter) << " ";
			}
			cout << endl;
			cout << endl;
			cout << "End Display History" << endl;
			for(int historyCounter = 0, historyCount = history.size(); historyCounter < historyCount; historyCounter++){
				if(isLoaded(history.at(historyCounter)) && !isLoaded((*(new string(1, input.at(counter)))))){
					cout << "Replacing:" << history.at(historyCounter)<< endl;
					replace(history.at(historyCounter),(*(new string(1, input.at(counter)))));
			     	s = getPages();
					int countFrames = s.size();
					cout << "Page Current State" << endl;
					for(int counterFrames = 0; counterFrames < countFrames; counterFrames++){
						cout << s.at(counterFrames).getValue() << " ";
					}
					cout << endl;
					cout << endl;
					cout << "End Display Current State" << endl;
					break;
                    }
               }
          }
          step();
     }
     display();
}

void PageManager::Clock_Algorithm(){
	start();
	// Cycle through the user input to decide what how the pages requested are going to be loaded
	for(int counter = 0, count = input.length(); counter < count; counter++){
		//If memory is not full and the page is not loaded add page to a frame		
		if(!add_page((*(new string(1, input.at(counter)))))){
			string in = (*(new string(1, input.at(counter))));
			//If the page chosen is loaded in memory increment its ticks to one, this is equivalent to replacing a value with itself (ticks will be set back to 1)
			if(isLoaded(in)){replace(in,in);}
			else {
				// If the clock_hand pointer is pointing to null set it to point to the page in the first frame
				if(getClockHand() == NULL){setClockHand(0);}

				//Cycle through all the pages and decrement the value of the ticks as you go along. Do this until you land on a page that has ticks equal to 0
				while(getClockHand()->getTicks() > 0){
					getClockHand()->decrementTicks();
					tick();
				}
				// Victim Chosen!
				replace(getClockHand()->getValue(),in);
			}
		}
		// Save the current stage of the pages
		step();
	}
	// Display a table of the saved page data
	display();
}

vector<vector<Operation>> PageManager::getPageData(){
	return page_data;
}

string PageManager::getPageDataColumn(int selector){
	int cells = (getPageData().size()/*Column*/ * getPageData().at(0).size()/*Row*/);
	int column = (selector / getPageData().size());
	int row = (selector % getPageData().size());
	return getPageData().at(row).at(column).getValue();
}

void PageManager::incrementPageFaultCount(){
	page_fault_count++;
}

int PageManager::getPageFaultCount(){
	return page_fault_count;
}

bool PageManager::tick(){
	//Loop through all the inputs
	for(int counter = 0, count = pages.size()-1; counter < count; counter++){
		if(getClockHand() == &(pages.at(counter))){setClockHand(counter + 1); return true;}
	}
	setClockHand(0);
	return false;
}

void PageManager::setClockHand(int i){
	clock_hand = &(pages.at(i));
}

void PageManager::setClockHand(Operation* o){
	clock_hand = o;
}

Operation* PageManager::getClockHand(){
	return clock_hand;
}

Operation* PageManager::getPage(string a){
	for(int counter = 0, count = getPages().size(); counter < count; counter++){
		if(pages.at(counter).getValue() == a){return &(pages.at(counter));}
	}
	return NULL;
}
#endif
