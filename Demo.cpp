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
     pm.add_leaf("1");
     pm.add_leaf("2");
     pm.add_leaf("3");
     pm.add_leaf("4");
     pm.add_branch();
     pm.add_leaf("5");
     pm.add_leaf("6");
     pm.add_leaf("7");
     pm.add_branch();
     pm.add_leaf("8");
     pm.add_leaf("9");
     pm.add_leaf("10");
     pm.traverse();
     
	vector<int> vi;
	vi.push_back(1);
	vi.push_back(2);
     vi.push_back(5);
     vi.push_back(7);

	display(4,vi);
	return 0;
}

void display(int frame_count, vector<int> pages){
     int page_count = pages.size();
     for(int page = 0; page < page_count; page++)
     {
          //Output Transition Cells
          if(page == 0 ){
               //Output Top Lines
               for(int top_line = 0; top_line < page_count; top_line++){cout << "+-----";if(top_line == page_count - 1){ cout << "+\n";}}
               for(int page_number = 0; page_number < page_count; page_number++){cout << "|" << current_page_output(pages.operator[](page_number));if(page_number == page_count - 1){cout << "|\n";}}
               for(int bottom_line = 0; bottom_line < page_count; bottom_line++){cout << "+-----";if(bottom_line == page_count - 1){ cout << "+\n";}}
          }

     }

     for(int frames = 0; frames < frame_count; frames++)
     {
          if(frames != 0){cout << "+-----+" << endl;}
          cout << "|     |" << endl;
     }
     cout << "+-----+" << endl;
}

string current_page_output(int page){
     if(page < 9)
     {return "  " + to_string(page) + "  ";}
     else if (page < 99)
     {return "  " + to_string(page) + " ";}
     else if (page < 999)
     {return "  " + to_string(page) + "";}
     return to_string(page);
}


#endif
