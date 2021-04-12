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
		vector<string> traverse();
		vector<string> traverseReverse();
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
		vector<string> getPages();
		bool isFull();
		bool replace(string a, string b);
		int activePageCount();
		

	private:
		Operation *root;
		Operation *branch;
		Operation *leaf;
		int frame_count;
		int page_fault_count;
		vector<string> pages;
		vector<string> history;
		vector<vector<string>> page_data;
};
#endif
