#ifndef OPERATION_CPP
#define OPERATION_CPP
#include "class.operation.hpp"
#include <cstddef>

Operation::Operation(){up = NULL; across = NULL; value = "";}
Operation::Operation(string v){up = NULL; across = NULL; value = v;}
Operation* Operation::getUp()
{
	return up;
}
Operation* Operation::getAcross(){
	return across;
}
string Operation::getValue(){
	return value;
}
void Operation::setUp(Operation* u){
	up = u;
}
void Operation::setAcross(Operation* a){
	across = a;
}
void Operation::setValue(string v){
	value = v;
}
#endif
