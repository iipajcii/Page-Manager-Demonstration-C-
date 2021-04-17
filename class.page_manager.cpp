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
	cout << "Reference String: " << input << endl;
	cout << "Min: " << range[0] << "  Max: " << range[1] << endl;
	cout << "Page Faults: " << getPageFaultCount() << endl << endl << endl;

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
	getRange();
	page_fault_count = 0;
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
	Mirror_Prepage(v);
	if(!isLoaded(v)){incrementPageFaultCount();}
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
	getRange();
	for(int counter = 0, count = input.length(); counter < count; counter++)
	{
		add_page((*(new string(1, input.at(counter)))));
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
	cout << "Least Recently Used Algorithm" << endl;
	start();
	int frameCount = getFrameCount();			
	
	vector<Operation> s;
	for(int counter = 0, count = input.length(); counter < count; counter++){
		if(!add_page((*(new string(1, input.at(counter)))))){
			s = getPages();
			int countFrames = s.size();

			for(int historyCounter = 0, historyCount = history.size(); historyCounter < historyCount; historyCounter++){
				if(isLoaded(history.at(historyCounter)) && !isLoaded((*(new string(1, input.at(counter)))))){
					replace(history.at(historyCounter),(*(new string(1, input.at(counter)))));
			     	s = getPages();
					int countFrames = s.size();
					break;
                    }
               }
          }
          step();
     }
     display();
}

void PageManager::Clock_Algorithm(){
	cout << "Clock Algorithm" << endl;
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

string PageManager::getInput(){
	return input;
}

void PageManager::getRange(){
	//Minimum and Maximum value
	int min = 0, max = 0;
	for(int counter = 0, count = getInput().length(); counter < count; counter++){
		if((int)input.at(counter) - 48 /*ASCII Math*/ > max){max = (int)input.at(counter) - 48 /*ASCII Math*/;}
	}
	min = max;
	for(int counter = 0, count = getInput().length(); counter < count; counter++){
		if((int)input.at(counter) - 48 /*ASCII Math*/ < min){min = (int)input.at(counter) - 48 /*ASCII Math*/;}
	}
	range[0] = min;
	range[1] = max;
}

bool PageManager::Mirror_Prepage(string v) {
	//Get ranges
	int min = range[0];
	int max = range[1];
	int page_range = max - min;
	int page_input = std::stoi(v);
	int page_to_add;
	//If frames are not full then you can prepage, else no prepaging can be done.
	if(!isFull()) {
		//If range is odd then a number is the center.
		if(((max - min) % 2) == 0){
			//odd
			int center = (page_range / 2) + min;
			if(page_input == center){page_to_add = center;/*Decide what to do if the page requested is */}
			else{
				if(page_input < center){int distance = abs(center - page_input); page_to_add = center + distance;}
				if(page_input > center){int distance = abs(page_input - center); page_to_add = center - distance;}
			}
		}
		//If range is even then the center is between 2 numbers
		else {
			//even
			int center = min + (page_range / 2);
			if(page_input <= center){ page_to_add = center + abs(center - page_input) + 1;}
			if(page_input >  center){ page_to_add = center - (abs(page_input - center) - 1);}
		}
		string s = to_string(page_to_add);
		//if not full (checked in above condition) and not loaded. load the opposite of the input
		if(!isLoaded(s)){
			Operation o(s);
			pages.push_back(s);
			return true;
		}
		else{
			return false;
		}
	}
	return false;
}
#endif
