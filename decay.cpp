#include <TRandom3.h>
#include <TMath.h>
#include <iostream>
#include <TFile.h>
#include <TH1F.h>

using namespace std;

double tan_theta(TRandom3& rnd) {
  double randcostheta;
  double randtheta;
  double tantheta;
  double EK = 120;
  double mK = 0.493;
  double mmu = 0.105658;
  double pK = TMath::Sqrt(EK*EK-mK*mK);
  double gamma = EK/mK;
  double beta = pK/EK;
  double E = (mK*mK+mmu*mmu)/(2*mK);
  double p = (mK*mK-mmu*mmu)/(2*mK);
  randcostheta = rnd.Uniform(2)-1;
  randtheta = TMath::ACos(randcostheta);
  tantheta = p*TMath::Sin(randtheta)/(gamma*(p*TMath::Cos(randtheta)+beta*E));
  
  return (tantheta); 
}

void decay() {
  TRandom3 rndgen;
  double ctau_K = 1.238*2.99792458*120/0.493*100; //beta*gamma*c*tau(cm)
  int imax = 1E7; //numero K generati
  double rtan_theta;
  double rdecay;
  double d_scint = 10000; //distanza scintillatore
  int zeros = 0;
  int ones = 0;
  int ndecays = 0;
  TFile* out = new TFile("decay.root","RECREATE");
  TH1F* decay_dist = new TH1F("decay_dist","Distribuzione dei decadimenti;Punto di decadimento;Conteggi",500,0,100000); 
  TH1F* theta_dist = new TH1F("theta_dist","Distribuzione dell'angolo di decadimento;Angolo (gradi);Conteggi",100,0.9999,1.0001); 			      
  for (int i = 0; i < imax; i++) {    
    rdecay = rndgen.Exp(ctau_K);
    decay_dist->Fill(rdecay);
    if (rdecay <= 10000) {
      ndecays += 1;
      rtan_theta = tan_theta(rndgen);
      theta_dist->Fill(TMath::Cos(TMath::ATan(rtan_theta)));
      if(rtan_theta*(d_scint-rdecay) >= 10 && rtan_theta*(d_scint-rdecay) <= 100) ones += 1;
      else zeros += 1;
    }
    else {zeros += 1;}
    
   
  }
  
 cout << "Zeros: " << zeros << endl;
 cout << "Ones: " << ones << endl;
 cout << "Decays: " << ndecays << endl;
 decay_dist->Write();
 theta_dist->Write();
 out->Close();
}
