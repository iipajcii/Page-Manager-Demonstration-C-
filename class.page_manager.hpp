#ifndef PAGE_MANAGER_HPP
#define PAGE_MANAGER_HPP
#include "class.operation.hpp"
#include <iostream>
#include <vector>

class PageManager {
	public:
		PageManager();
		PageManager(string input);
		bool next_branch();
		bool next_leaf();
		bool add_branch();
		bool add_leaf(string v);
		bool add_page(string v);
		string read_leaf();
		void traverse();
		void traverseReverse();
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
		int activePageCount();
		

	private:
		Operation *root;
		Operation *branch;
		Operation *leaf;
		int frame_count;
		vector<string> pages;
};
#endif
