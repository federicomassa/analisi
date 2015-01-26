#include <TGraphErrors.h>
#include <TF1.h>
#include <TMath.h>
#include <TAxis.h>
#include <TCanvas.h>

void display() {
  TCanvas* c1 = new TCanvas("c1","Canvas",700,700);
  // double x[27] = {2,7,7,9,10,11,12,12,15,23,26,28,30,37,38,40,41,43,44,44,47,48,48,49,49,50,50};
  // double y[27] = {13,43,44,45,3,3,2,47,49,50,50,50,50,2,3,4,45,7,8,41,37,14,36,18,33,21,27}; //evento 1

  double x[32] = {1,2,3,3,5,10,12,12,13,15,19,23,27,29,33,34,35,39,39,41,43,45,47,48,49,49,50,50,50,50,50,50};
  double y[32] = {34,12,37,38,40,4,46,47,47,1,49,50,50,50,49,1,1,4,45,5,7,39,14,14,19,32,18,21,22,26,28,30};

  TGraphErrors* graph = new TGraphErrors(27,x,y,NULL,NULL);
  // TF1* circ1 = new TF1("fit1","24.6669+TMath::Sqrt(25.7003*25.7003-(x-24.5341)*(x-24.5341))",0,50.2344);
  // TF1* circ2 = new TF1("fit2","24.6669-TMath::Sqrt(25.7003*25.7003-(x-24.5341)*(x-24.5341))",0,50.2344);

 TF1* circ1 = new TF1("fit1","24.5404+TMath::Sqrt(25.4022*25.4022-(x-24.7054)*(x-24.7054))",0,50.1);
 TF1* circ2 = new TF1("fit1","24.5404-TMath::Sqrt(25.4022*25.4022-(x-24.7054)*(x-24.7054))",0,50.1);

  c1->cd();
  circ1->SetLineColor(kRed);
  circ1->SetNpx(100000);
  circ2->SetLineColor(kRed);
  circ2->SetNpx(100000);
  graph->GetYaxis()->SetRangeUser(0,55);
  graph->GetXaxis()->SetRangeUser(0,55);
  graph->Draw("AP");
  circ1->Draw("same");
  circ2->Draw("same");
 


}
