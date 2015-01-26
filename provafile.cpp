#include <fstream>
#include <sstream>
#include <string>
#include <iostream>


using namespace std;

void provafile() {
  string str;
  ifstream in("cerenkov.dat");
  int tellg;
  for ( int i = 0; i < 20; i++) {
    getline(in,str);
    cout << "i: " << i << endl;
    cout << "Stringa: " << str << endl;
    cout << "Tellg: " << in.tellg() << endl;
    if (i == 10) tellg = in.tellg(); 
    //    cout << "Tellp: " << in.tellp() << endl;
  }

  in.seekg(tellg-13);
  getline(in,str);
  cout << "!!! String: " << str << endl;

}
