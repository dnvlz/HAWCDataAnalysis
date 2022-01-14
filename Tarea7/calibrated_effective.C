#include <iostream>
using namespace std;

void calibrated_effective(){
int PMT1, PMT2, PMT3, PMT4;
cout << "ID de PMT 1: " ;
cin >> PMT1;
cout << "ID de PMT 2: " ;
cin >> PMT2;
cout << "ID de PMT 3: " ;
cin >> PMT3;
cout << "ID de PMT 4: " ;
cin >> PMT4;

TFile *file = TFile::Open("recoext_run010222_00692.root");
TTree *arbol = (TTree*) file->Get("XCDF");

int n = 1860;
Double_t Calibrated[n];
arbol -> SetBranchAddress("event.hit.charge",Calibrated);
Double_t Effective[n];
arbol -> SetBranchAddress("event.hit.effcharge",Effective);
ULong64_t PMT[n];
arbol -> SetBranchAddress("event.hit.gridId",PMT);

ULong64_t NumHits;
arbol -> SetBranchAddress("event.nHit",&NumHits);
ULong64_t EventFlags;
arbol -> SetBranchAddress("event.eventFlags",&EventFlags);
ULong64_t isGood[n];
arbol -> SetBranchAddress("event.hit.channelIsGood",isGood);
ULong64_t HitFlags[n];
arbol -> SetBranchAddress("event.hit.flags",HitFlags);

TCanvas *c1 = new TCanvas("c1");
c1->SetGrid();

auto p1 = new TGraph();
auto p2 = new TGraph();
auto p3 = new TGraph();
auto p4 = new TGraph();

Int_t entradas = arbol -> GetEntries();
for (Int_t i=0;i<entradas;i++){
    arbol -> GetEntry(i);
    if (EventFlags==0){
    for (Int_t j=0;j<NumHits;j++){
    if (isGood[j]==1&HitFlags[j]==0){
        if (PMT[j]==PMT1){p1 -> SetPoint(p1->GetN(),Calibrated[j],Effective[j]);}
        else if (PMT[j]==PMT2){p2 -> SetPoint(p2->GetN(),Calibrated[j],Effective[j]);}
        else if (PMT[j]==PMT3){p3 -> SetPoint(p3->GetN(),Calibrated[j],Effective[j]);}
        else if (PMT[j]==PMT4){p4 -> SetPoint(p4->GetN(),Calibrated[j],Effective[j]);}
            }
        }
    }
}

p1 -> SetMarkerColor(kRed);
p1 -> SetMarkerStyle(kFullDotMedium);
p2 -> SetMarkerColor(kAzure);
p2 -> SetMarkerStyle(kFullDotMedium);
p3 -> SetMarkerColor(kTeal);
p3 -> SetMarkerStyle(kFullDotMedium);
p4 -> SetMarkerColor(kOrange);
p4 -> SetMarkerStyle(kFullDotMedium);

p1 -> SetLineColor(kRed);
p2 -> SetLineColor(kAzure);
p3 -> SetLineColor(kTeal);
p4 -> SetLineColor(kOrange);
p1 -> SetLineWidth(3);
p2 -> SetLineWidth(3);
p3 -> SetLineWidth(3);
p4 -> SetLineWidth(3);

auto legend = new TLegend(0.1,0.6,0.3,0.9);
TString information =  "PMTs";
TString t1 =  Form("Canal %d",PMT1);
TString t2 =  Form("Canal %d",PMT2);
TString t3 =  Form("Canal %d",PMT3);
TString t4 =  Form("Canal %d",PMT4);
legend -> SetHeader(information,"C");
legend -> AddEntry(p1,t1,"l");
legend -> AddEntry(p2,t2,"l");
legend -> AddEntry(p3,t3,"l");
legend -> AddEntry(p4,t4,"l");
gStyle->SetLegendTextSize(0.035);

p1 -> SetTitle("Comparacion: carga calibrada y efectiva");
p1 -> GetXaxis()->SetTitle("Carga calibrada [PEs]");
p1 -> GetYaxis()->SetTitle("Carga efectiva [PEs]");

TAxis *axisX = p1->GetXaxis();
axisX-> SetLimits(0.,400.);  
p1 -> SetMaximum(400);

p1 -> Draw("AP");
p2 -> Draw("SAME P");
p3 -> Draw("SAME P");
p4 -> Draw("SAME P");
legend -> Draw("SAME");
}