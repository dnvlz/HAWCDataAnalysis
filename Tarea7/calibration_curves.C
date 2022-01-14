#include <iostream>
using namespace std;

void calibration_curves(){
int detector;
cout << "ID de detector: ";
cin >> detector;
int x;
cout << "Hi (1) o Lo (0): ";
cin >> x;

TFile *file = TFile::Open("recoext_run010222_00692.root");
TTree *arbol = (TTree*) file->Get("XCDF");

int n = 1860;
ULong64_t TOT[n];
if(x==1){arbol -> SetBranchAddress("event.hit.hiTOT",TOT);}
else if(x==0){arbol -> SetBranchAddress("event.hit.loTOT",TOT);}
Double_t Charge[n];
arbol -> SetBranchAddress("event.hit.charge",Charge);
ULong64_t PMT[n];
arbol -> SetBranchAddress("event.hit.gridId",PMT);

ULong64_t NumHits;
arbol -> SetBranchAddress("event.nHit",&NumHits);
ULong64_t EventFlags;
arbol -> SetBranchAddress("event.eventFlags",&EventFlags);
ULong64_t gtcFlags;
arbol -> SetBranchAddress("event.gtcFlags",&gtcFlags);
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
    if (EventFlags==0&gtcFlags==0){
    for (Int_t j=0;j<NumHits;j++){
    if (isGood[j]==1&HitFlags[j]==0&TOT[j]>0){
        if (PMT[j]==detector*4-3){p1 -> SetPoint(p1->GetN(),TOT[j],log10(Charge[j]));}
        else if (PMT[j]==detector*4-2){p2 -> SetPoint(p2->GetN(),TOT[j],log10(Charge[j]));}
        else if (PMT[j]==detector*4-1){p3 -> SetPoint(p3->GetN(),TOT[j],log10(Charge[j]));}
        else if (PMT[j]==detector*4){p4 -> SetPoint(p4->GetN(),TOT[j],log10(Charge[j]));}
            }
        }
    }
}

p1 -> SetMarkerColor(kRed);
p1 -> SetMarkerStyle(kFullDotMedium);
p2 -> SetMarkerColor(kAzure);
p2 -> SetMarkerStyle(kFullDotMedium);
p3 -> SetMarkerColor(kGreen+2);
p3 -> SetMarkerStyle(kFullDotMedium);
p4 -> SetMarkerColor(kOrange);
p4 -> SetMarkerStyle(kFullDotMedium);

p1 -> SetLineColor(kRed);
p2 -> SetLineColor(kAzure);
p3 -> SetLineColor(kGreen+2);
p4 -> SetLineColor(kOrange);
p1 -> SetLineWidth(3);
p2 -> SetLineWidth(3);
p3 -> SetLineWidth(3);
p4 -> SetLineWidth(3);

auto legend = new TLegend(0.2,0.5,0.4,0.8);
TString information =  Form("Detector %d",detector);
TString t1 =  Form("Canal %d",detector*4-3);
TString t2 =  Form("Canal %d",detector*4-2);
TString t3 =  Form("Canal %d",detector*4-1);
TString t4 =  Form("Canal %d",detector*4);
legend -> SetHeader(information,"C");
legend -> AddEntry(p1,t1,"l");
legend -> AddEntry(p2,t2,"l");
legend -> AddEntry(p3,t3,"l");
legend -> AddEntry(p4,t4,"l");
gStyle->SetLegendTextSize(0.035);

p1 -> SetTitle("Curva de calibracion");
p1 -> GetYaxis()->SetTitle("log_{10}(Carga calibrada [PEs])");
if(x==1){
    p1 -> GetXaxis()->SetTitle("HiToT [TDC]");
    TAxis *axisX = p1->GetXaxis();
    axisX-> SetLimits(0.,4500.);}
else if(x==0){
    p1 -> GetXaxis()->SetTitle("LoToT [TDC]");
    TAxis *axisX = p1->GetXaxis();
    axisX-> SetLimits(0.,4000.);}

p1 -> Draw("AP");
p2 -> Draw("SAME P");
p3 -> Draw("SAME P");
p4 -> Draw("SAME P");
legend -> Draw("SAME");
}