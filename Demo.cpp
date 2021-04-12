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
     pm.setFrameCount(4);
     pm.input = "1234352678";
     pm.Least_Recently_Used();
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
