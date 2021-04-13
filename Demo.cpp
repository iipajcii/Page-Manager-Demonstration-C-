#ifndef DEMO_CPP
#define DEMP_CPP
#include <iostream>
#include <vector>
#include "class.page_manager.hpp"

using namespace std;

string current_page_output(int p);
void display(int f, vector<int> p);

int main(){
     PageManager pm;
     pm.setFrameCount(5);
     // pm.input = "11212653452";
     pm.input = "948464342494142474";
     // pm.input = "3423656778343";
     pm.Least_Recently_Used();
     pm.Clock_Algorithm();
	return 0;
}

     }


}

#endif
