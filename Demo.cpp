#ifndef DEMO_CPP
#define DEMP_CPP
#include <iostream>
#include <fstream>
#include <vector>
#include "class.page_manager.hpp"

using namespace std;

string current_page_output(int p);
void display(int f, vector<int> p);

int main(){
     int frameCount;
     string str;
     ifstream refstrings("refstrings.txt");
     if(!refstrings.is_open()){cout << "Could not open file \"refstrings.txt\"" << endl;return 0;}

     do {
          cout << "Enter Number of Frames, Ranging from 3 to 5: ";
          cin >> frameCount;
          if(!(frameCount > 5 || frameCount < 3)){cout << "Invalid" << endl;}
     } while(frameCount > 5 || frameCount < 3);

     while(refstrings >> str){
          cout << "Reference String: " << str << endl << endl;
          PageManager pm;
          pm.setInput(str);
          pm.setFrameCount(frameCount);
          pm.Least_Recently_Used();
          pm.Clock_Algorithm();
     }

     refstrings.close();

     return 0;
}

#endif
