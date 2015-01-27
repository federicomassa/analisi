//script per calcolare probabilità di non identificazione e probabilità
// di misidentificazione nel caso in cui identifichiamo i K anche guardando
// quando scatta lo scintillatore

#include <TMath.h>
#include <TF1.h>
#include <TAxis.h>

double radiusPI_prob(double* x, double* par) {
  double p0 = 1580.26;
  // double p1 = 25.4128;
  double p2 = 0.070094;
  double p3 = 715.414;
  double p4 = 25.6919;
  double p5 = 0.0674463;
  double intPI = p3*p5*TMath::Sqrt(8*TMath::ATan(1));
  double intK = p0*p2*TMath::Sqrt(8*TMath::ATan(1));
  double fK = intK/(intK+intPI);
  double fPI = 1 - fK;
  double s1_int = 173.5988698;
  double tot_int = p0*p2*TMath::Sqrt(8*TMath::ATan(1));
  double s1_prob = s1_int/tot_int;
  double s0_prob = 1  - s1_prob;

  return TMath::Sqrt(2*TMath::ATan(1))*p3*p5*(1+TMath::Erf((x[0]-p4)/TMath::Sqrt2()/p5))/intPI;

}

double comp_radiusPI_prob(double* x, double* par) {
  return (1-radiusPI_prob(x,par));
}


double radiusK_prob(double* x, double* par) {
 double p0 = 1580.26;
  double p1 = 25.4128;
  double p2 = 0.070094;
  double p3 = 715.414;
  // double p4 = 25.6919;
  double p5 = 0.0674463;
  double intPI = p3*p5*TMath::Sqrt(8*TMath::ATan(1));
  double intK = p0*p2*TMath::Sqrt(8*TMath::ATan(1));
  double fK = intK/(intK+intPI);
  double fPI = 1 - fK;
  double s1_int = 173.5988698;
  double tot_int = p0*p2*TMath::Sqrt(8*TMath::ATan(1));
  double s1_prob = s1_int/tot_int;
  double s0_prob = 1  - s1_prob;
 
  return TMath::Sqrt(2*TMath::ATan(1))*p0*p2*(1+TMath::Erf((x[0]-p1)/TMath::Sqrt2()/p2))/intK;

}

double comp_radiusK_prob(double* x, double* par) {
  return (1-radiusK_prob(x,par));
}

double nonidvera2(double* x, double* par) {
 double p0 = 1580.26;
  // double p1 = 25.4128;
  double p2 = 0.070094;
  double p3 = 715.414;
  // double p4 = 25.6919;
  double p5 = 0.0674463;
  double intPI = p3*p5*TMath::Sqrt(8*TMath::ATan(1));
  double intK = p0*p2*TMath::Sqrt(8*TMath::ATan(1));
  double fK = intK/(intK+intPI);
  double fPI = 1 - fK;
  double s1_int = 173.5988698;
  double tot_int = p0*p2*TMath::Sqrt(8*TMath::ATan(1));
  double s1_prob = s1_int/tot_int;
  double s0_prob = 1  - s1_prob;

  return comp_radiusK_prob(x,par)*s0_prob;
}

double nonidvera3(double* x, double* par) {
 double p0 = 1580.26;
  // double p1 = 25.4128;
  double p2 = 0.070094;
  double p3 = 715.414;
  // double p4 = 25.6919;
  double p5 = 0.0674463;
  double intPI = p3*p5*TMath::Sqrt(8*TMath::ATan(1));
  double intK = p0*p2*TMath::Sqrt(8*TMath::ATan(1));
  double fK = intK/(intK+intPI);
  double fPI = 1 - fK;
  double s1_int = 173.5988698;
  double tot_int = p0*p2*TMath::Sqrt(8*TMath::ATan(1));
  double s1_prob = s1_int/tot_int;
  double s0_prob = 1  - s1_prob;

  return (comp_radiusK_prob(x,par)+s1_prob-comp_radiusK_prob(x,par)*s1_prob);

}

double p1(double* x, double* par) {
 double p0 = 1580.26;
  // double p1 = 25.4128;
  double p2 = 0.070094;
  double p3 = 715.414;
  // double p4 = 25.6919;
  double p5 = 0.0674463;
  double intPI = p3*p5*TMath::Sqrt(8*TMath::ATan(1));
  double intK = p0*p2*TMath::Sqrt(8*TMath::ATan(1));
  double fK = intK/(intK+intPI);
  double fPI = 1 - fK;
  double s1_int = 173.5988698;
  double tot_int = p0*p2*TMath::Sqrt(8*TMath::ATan(1));
  double s1_prob = s1_int/tot_int;
  double s0_prob = 1  - s1_prob;

  return radiusPI_prob(x,par)*fPI/(radiusPI_prob(x,par)*fPI+radiusK_prob(x,par)*fK);
						      
} 
double p2(double* x, double* par) {
 double p0 = 1580.26;
  // double p1 = 25.4128;
  double p2 = 0.070094;
  double p3 = 715.414;
  // double p4 = 25.6919;
  double p5 = 0.0674463;
  double intPI = p3*p5*TMath::Sqrt(8*TMath::ATan(1));
  double intK = p0*p2*TMath::Sqrt(8*TMath::ATan(1));
  double fK = intK/(intK+intPI);
  double fPI = 1 - fK;
  double s1_int = 173.5988698;
  double tot_int = p0*p2*TMath::Sqrt(8*TMath::ATan(1));
  double s1_prob = s1_int/tot_int;
  double s0_prob = 1  - s1_prob;


  return radiusPI_prob(x,par)*fPI/(radiusPI_prob(x,par)*fPI+(radiusK_prob(x,par)+s1_prob-radiusK_prob(x,par)*s1_prob)*fK);
						      
} 

double p3(double* x, double* par) {
 double p0 = 1580.26;
  // double p1 = 25.4128;
  double p2 = 0.070094;
  double p3 = 715.414;
  // double p4 = 25.6919;
  double p5 = 0.0674463;
  double intPI = p3*p5*TMath::Sqrt(8*TMath::ATan(1));
  double intK = p0*p2*TMath::Sqrt(8*TMath::ATan(1));
  double fK = intK/(intK+intPI);
  double fPI = 1 - fK;
  double s1_int = 173.5988698;
  double tot_int = p0*p2*TMath::Sqrt(8*TMath::ATan(1));
  double s1_prob = s1_int/tot_int;
  double s0_prob = 1  - s1_prob;

  return radiusPI_prob(x,par)*fPI/(radiusPI_prob(x,par)*fPI+radiusK_prob(x,par)*s0_prob*fK);
						      
} 

double nonid1(double* x, double* par) { //occhio: questa non è proprio la prob di non identificazione, ma P(K | R> Rmax...)

 double p0 = 1580.26;
  // double p1 = 25.4128;
  double p2 = 0.070094;
  double p3 = 715.414;
  // double p4 = 25.6919;
  double p5 = 0.0674463;
  double intPI = p3*p5*TMath::Sqrt(8*TMath::ATan(1));
  double intK = p0*p2*TMath::Sqrt(8*TMath::ATan(1));
  double fK = intK/(intK+intPI);
  double fPI = 1 - fK;
  double s1_int = 173.5988698;
  double tot_int = p0*p2*TMath::Sqrt(8*TMath::ATan(1));
  double s1_prob = s1_int/tot_int;
  double s0_prob = 1  - s1_prob;

  return (1-radiusK_prob(x,par))*fK/((1-radiusK_prob(x,par))*fK+(1-radiusPI_prob(x,par))*fPI);
						      
} 

double nonid2(double* x, double* par) {
 double p0 = 1580.26;
  // double p1 = 25.4128;
  double p2 = 0.070094;
  double p3 = 715.414;
  // double p4 = 25.6919;
  double p5 = 0.0674463;
  double intPI = p3*p5*TMath::Sqrt(8*TMath::ATan(1));
  double intK = p0*p2*TMath::Sqrt(8*TMath::ATan(1));
  double fK = intK/(intK+intPI);
  double fPI = 1 - fK;
  double s1_int = 173.5988698;
  double tot_int = p0*p2*TMath::Sqrt(8*TMath::ATan(1));
  double s1_prob = s1_int/tot_int;
  double s0_prob = 1  - s1_prob;

  return (1-radiusK_prob(x,par))*fK*s0_prob/((1-radiusK_prob(x,par))*s0_prob*fK+(1-radiusPI_prob(x,par))*fPI);
						      
} 

void prob() {


  TF1* nonid = new TF1("nonid",nonidvera3,25.3,25.65,0);
 nonid->SetTitle("Probabilita' di errata identificazione e non identificazione: Caso 1;Raggio critico;Probabilita'");
  nonid->GetYaxis()->SetTitleOffset(1.4);
  nonid->SetNpx(100000);
  nonid->SetLineColor(kGreen);
  nonid->Draw();

  TF1* mis = new TF1("mis",p3,25.45,25.65,0); 
  mis->GetYaxis()->SetTitleOffset(1.4);
  mis->SetNpx(100000);
  mis->SetLineColor(kRed);
  mis->Draw("same");   


}
