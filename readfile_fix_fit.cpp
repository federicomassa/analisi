//script come in readfile.cpp ma con i parametri di media e sigma della gaussiana
// K fissati grazie alla distribuzione del raggio con traccia scintillatore

#include <fstream>
#include <string>
#include <sstream>
#include <TH1F.h>
#include <TFile.h>
#include <iostream>
#include <cmath>
#include <TMath.h>
#include <TAxis.h>
#include <TF1.h>
#include <TRandom3.h>

using namespace std;

int pxy(int position){
int  posy=position%1000;
  return posy;
}

int pxx(int position){
  int  posx=round(double(position-pxy(position))/1000);
  return posx;
}

void average(ifstream& in, int n, double& x_av, double& y_av) { //n = numero di pixel in quell'evento. Restituisce la media delle x in quell'evento

    string str;
    int strnum;
    int partialx = 0;
    int partialy = 0;
    int tellg = in.tellg();
    in.seekg(tellg-13); //torna indietro di una riga nel file
    
    
    for (int i = 0; i < n; i++) {
      getline(in,str);
      stringstream(str) >> strnum;
      partialx = partialx + pxx(strnum);
      partialy = partialy + pxy(strnum);
    }
    in.seekg(tellg-13); //in questo modo quando fai getline ottieni il primo evento
     x_av = double(partialx)/double(n);    
     y_av = double(partialy)/double(n);
}

void fit_cerchio(ifstream& in, int n, double& cx, double& cy, double& r) {
  string str;
  int strnum;
  double x_av, y_av;

  double u = 0, v = 0;
  double uu = 0, vv = 0, uv = 0;
  double uuu = 0, vvv = 0, uvv = 0, vuu = 0; //vedi nota sul fit cerchio
  average(in, n, x_av, y_av); //trovo le medie in x e y
  for (int i = 0; i < n; i++) {
    getline(in,str);
    stringstream(str) >> strnum;
    u = double(pxx(strnum)) - x_av;
    v = double(pxy(strnum)) - y_av;
    uu += u*u;
    vv += v*v;
    uv += u*v;
    uuu += u*u*u;
    vvv += v*v*v;
    uvv += u*v*v;
    vuu += v*u*u;
  }
  
  cx = -0.5*(uv*(vvv+vuu)-vv*(uuu+uvv))/(uu*vv-uv*uv) + x_av;
  cy = 0.5*(uu*(vvv+vuu)-uv*(uuu+uvv))/(uu*vv-uv*uv) + y_av;  
  r = TMath::Sqrt((cx-x_av)*(cx-x_av)+(cy-y_av)*(cy-y_av)+(uu+vv)/n);



}


void readfile() {

  double entries = 0;
  int kmax;
  TRandom3 rndgen;
  double centro_x, centro_y, radius; //coordinate del centro del cerchio fittato e raggio
  string str; //riga di file
  int strnum; //conversione numerica di str
  int i = 1; //contatore all'interno di un evento
  int evnum = 1; //identificativo numero di evento
  int tracks; //numero di tracce presenti in un evento
  int pixnum; //numero di pixel colpiti in un evento
  TH1F* tracks_dist = new TH1F("tracks_dist","Numero di tracce nello scintillatore;Numero di tracce;Conteggio",11,0,11); //distribuzione numero di tracce
  TH1F* pixnum_dist = new TH1F("pixnum_dist","Distribuzione numero di pixel colpiti;Identificativo dei pixel colpiti;Conteggio", 50,1,51);
  TH1F* centrox_dist = new TH1F("centrox_dist","Distribuzione della coordinata x del centro; Coordinata x (px); Conteggio", 200,23,26);
  centrox_dist->GetYaxis()->SetTitleOffset(1.4);
  TH1F* centroy_dist = new TH1F("centroy_dist","Distribuzione della coordinata y del centro; Coordinata x (px); Conteggio", 200,23,26);
  centroy_dist->GetYaxis()->SetTitleOffset(1.4);
  TH1F* radius_dist = new TH1F("radius_dist","Distribuzione del raggio; Raggio(px); Conteggio",200,24.8,26.4);
  radius_dist->GetYaxis()->SetTitleOffset(1.4);
 TH1F* radius1_dist = new TH1F("radius1_dist","Distribuzione del raggio; Raggio(px); Conteggio",200,24.8,26.4);
  radius1_dist->GetYaxis()->SetTitleOffset(1.4);
 TH1F* radius0_dist = new TH1F("radius0_dist","Distribuzione del raggio; Raggio(px); Conteggio",200,24.8,26.4);
  radius0_dist->GetYaxis()->SetTitleOffset(1.4);
  TFile* out = new TFile("readfile_fix_fit.root","RECREATE");
  ifstream in("cerenkov.dat");

  cout << "Numero pseudoesperimenti? (0 = nulla) " << endl;
  getline(cin,str);
  stringstream(str) >> kmax;
  
      getline(in,str);
    stringstream(str) >> strnum;

  do{
    if (i == 1) {
    tracks = strnum;
    tracks_dist->Fill(tracks);}
    if (i == 2) {
    pixnum = strnum;
    pixnum_dist->Fill(pixnum);}
    
    if (i == 3) { // inizio eventi

      fit_cerchio(in, pixnum, centro_x, centro_y, radius);
      if(tracks == 1) radius1_dist->Fill(radius);
      else if(tracks == 0) radius0_dist->Fill(radius);
      centrox_dist->Fill(centro_x);
      centroy_dist->Fill(centro_y);
      radius_dist->Fill(radius);
    }
      
    getline(in,str);
    stringstream(str) >> strnum;
    i++;
    if (i == 4 && strnum < 1000) {
      evnum++;
      i = 1;
    }

  }
  while (!in.eof());

  TF1* gausfit = new TF1("gaus_fit","gaus(0)+gaus(3)",24.8,26.4);
  gausfit->SetParameters(1600,25.4,0.1,700,25.7,0.1);
  gausfit->FixParameter(1,25.4128);
  gausfit->FixParameter(2,0.070094);
  // TF1* gausfit = new TF1("gaus_fit","gaus(0)",24.8,25.5);
  // gausfit->SetParameters(1600,25.4,0.1);
  radius_dist->Fit(gausfit,"0SR");
  gausfit->SetRange(24.8,26.4);
  radius_dist->Draw();
  cout << "Integrale" << gausfit->Integral(24.8,26.4)/(8E-3) << endl;
  cout << "NDF: " << gausfit->GetNDF() << endl;
  gausfit->Draw("same");


 

  //PSEUDOESPERIMENTI
  if (kmax > 0)
  cout << "Inizio pseudoesperimenti..." << endl;
  double bincont[200];
  double rbincont[200];
  double integral;
  TH1F* integral_dist = new TH1F("integral_dist","Distribuzione della frazione di eventi di K;Frazione;Conteggio",200,0.67,0.71);
 TH1F* entries_dist = new TH1F("entries_dist","Distribuzione del numero di eventi generati;Eventi;Conteggio",200,49000,51000);
  for (int n = 1; n <= 200; n++) {
    bincont[n-1] = radius_dist->GetBinContent(n);
  }
  for (int k = 0; k < kmax; k++) {
    TH1F* rradius_dist = new TH1F("rradius_dist","Distribuzione raggio - Pseudoesperimento; Raggio (cm); Conteggi",200,24.8,26.4);
    for (int n = 1; n <= 200; n++) {
      if (bincont[n-1] != 0) {
	rbincont[n-1] = rndgen.Gaus(bincont[n-1]+0.5,TMath::Sqrt(bincont[n-1]*(1-bincont[n-1]/50000)) );}
      else {rbincont[n-1] = 0;}
      rradius_dist->SetBinContent(n,rbincont[n-1]);
      entries += rbincont[n-1];
    } //approssimazione gaussiana della binomiale
    rradius_dist->Fit(gausfit,"0QRS");
    entries_dist->Fill(entries);
    integral = gausfit->GetParameter(0)*gausfit->GetParameter(2)/(gausfit->GetParameter(0)*gausfit->GetParameter(2)+gausfit->GetParameter(3)*gausfit->GetParameter(5));
    integral_dist->Fill(integral);
    entries = 0;
    delete rradius_dist;
  }
  entries_dist->Write();
  integral_dist->Write();
  centrox_dist->Write();
  centroy_dist->Write();
  radius_dist->Write();
  radius1_dist->Write();
  radius0_dist->Write();
  tracks_dist->Write();
  pixnum_dist->Write();
  out->Close();
}
