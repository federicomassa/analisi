#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

int pxx(int position) {

  return round((position -position%1000)/1000);
    }

double x_av(ifstream& in, int n) { //n = numero di pixel in quell'evento. Restituisce la media delle x in quell'evento
  int tellg;
    string str;
    int strnum;
    getline(in,str);
    getline(in,str);
    getline(in,str);
    int partial = 0;
    tellg = in.tellg();
    in.seekg(tellg-13); //torna indietro di una riga nel file
    
    
    for (int i = 0; i < n; i++) {
      getline(in,str);
      stringstream(str) >> strnum;
      partial = partial + pxx(strnum);
    }

    return double(partial)/double(n);    
}
