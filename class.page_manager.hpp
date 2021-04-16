#ifndef PAGE_MANAGER_HPP
#define PAGE_MANAGER_HPP
#include "class.operation.hpp"
#include <iostream>
#include <vector>

class PageManager {
	public:
		PageManager();
		PageManager(string input);
		bool setInput(string v);
		bool next_branch();
		bool next_leaf();
		bool add_branch();
		bool add_leaf(string v);
		bool add_page(string v);
		string read_leaf();
		vector<Operation> traverse();
		vector<Operation> traverseReverse();
		void display();
		int count();
		void start();
		bool step();
		string input;
		void setFrameCount(int f);
		void incrementPageFaultCount();
		int getPageFaultCount();
		int getFrameCount();
		string displayNumberFormatter(int num);
		string displayNumberFormatter(string n);
		vector<Operation> getPages();
		bool isFull();
		bool isLoaded(string a);
		bool replace(string a, string b);
		void Least_Recently_Used();
		void Clock_Algorithm();
		int activePageCount();
		vector<string> getHistory();
		vector<vector<Operation>> getPageData();
		string getPageDataColumn(int selector);
		bool tick();
		void setClockHand(int i);
		void setClockHand(Operation* o);
		Operation* getClockHand();
		Operation* getPage(string a);
		string getInput();
		void getRange();

	private:
		Operation *root;
		Operation *branch;
		Operation *leaf;
		int frame_count;
		int page_fault_count;
		vector<Operation> pages;
		vector<string> history;
		vector<vector<Operation>> page_data;
		Operation* clock_hand;
		int range[2]; //Minimum and Maximum value of input
};
#endif
