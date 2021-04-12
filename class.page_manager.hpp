#ifndef PAGE_MANAGER_HPP
#define PAGE_MANAGER_HPP
#include "class.operation.hpp"
#include <iostream>

class PageManager {
	public:
		PageManager();
		bool next_branch();
		bool next_leaf();
		bool add_branch();
		bool add_leaf(string v);
		string read_leaf();
		void traverse();
		int count();
		void start();
		string displayNumberFormatter(int num);
		string displayNumberFormatter(string n);

	private:
		Operation *root;
		Operation *branch;
		Operation *leaf;
};
#endif
