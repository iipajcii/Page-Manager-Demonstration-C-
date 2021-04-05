#ifndef OPERATION_HPP
#define OPERATION_HPP
#include <string>
using namespace std;

class Operation {
	public:
		Operation();
		Operation(string v);
		Operation* getUp();
		Operation* getAcross();
		string getValue();
		void setUp(Operation* u);
		void setAcross(Operation* a);
		void setValue(string v);
	private:
		Operation *up;
		Operation *across;
		string value;
};
#endif
