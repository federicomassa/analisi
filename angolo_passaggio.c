#include "TROOT.h"
#include "TMath.h"
#include <iostream>
#include "TF1.h"
#include "TAxis.h"

int pxy(int position){
int  posy=position%1000;
  return posy;
}

int pxx(int position){
 int  posx=(position-position%1000)/1000;
  return posx;
}

/*void evDisplay( double nev){

  TH2F* disp =new TH2F("d";"Display evento",50,50,0,50,0,50);
  for (i=0;i<npx;i++){
    disp->Fill(x.Px[i],y.Px[i]);
    }

    }*/

double En=120;
double mu_mass=0.10566;
double pi_mass=0.493;
double pmu=(-(mu_mass*mu_mass)+(pi_mass*pi_mass))/(2*pi_mass);
double g=En/pi_mass;
double beta=sqrt(1-1/(g*g));

double thprime(double th){

  double thetapr=180/3.1415*TMath::ATan((pmu*TMath::Sin(3.1415/180*th))/(g*(pmu*TMath::Cos(3.1415/180*th)+beta*sqrt(pmu*pmu+mu_mass*mu_mass))));
    return thetapr;
}

void tangent(){

  TF1* graph=new TF1("grafico","thprime(x)",0,180);
  graph->SetTitle("Theta' vs Theta for K generated muons;Theta' (grad);Theta(grad)");
  graph->GetYaxis()->SetTitleOffset(1.4);
  graph->Draw();
  graph->GetMaximum();
  graph->GetMaximumX();
  cout << "Theta' max: "<< graph->GetMaximum() << " per theta = " << graph->GetMaximumX() << endl;
    
}
