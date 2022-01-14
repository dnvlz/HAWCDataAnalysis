#include <iostream>
#include <math.h> 
using namespace std;

void distribucion_abundantes(){
int e1;
cout << "Evento: ";
cin >> e1;

int n = 1987;

TFile *file = TFile::Open("hawcsim_protons_M28L2000_nc.root");
TTree *arbol = (TTree*) file->Get("XCDF");

ULong64_t Event;
arbol -> SetBranchAddress("HAWCSim.Evt.Num",&Event);
Double_t CoreX;
arbol -> SetBranchAddress("HAWCSim.Evt.X",&CoreX);
Double_t CoreY;
arbol -> SetBranchAddress("HAWCSim.Evt.Y",&CoreY);
Double_t PosX[n];
arbol -> SetBranchAddress("HAWCSim.WH.XNE",PosX);
Double_t PosY[n];
arbol -> SetBranchAddress("HAWCSim.WH.YNE",PosY);
Double_t Energy[n];
arbol -> SetBranchAddress("HAWCSim.WH.Energy",Energy);
ULong64_t NumHits;
arbol -> SetBranchAddress("HAWCSim.Evt.nWHit",&NumHits);
Long64_t Particle[n];
arbol -> SetBranchAddress("HAWCSim.WH.pType",Particle);

TCanvas *c1 = new TCanvas("c1");

Double_t distX, distY, dist, energy;

auto p1 = new TGraph();
auto p2 = new TGraph();
auto p3 = new TGraph();

int i1 = 0, i2 = 0, i3 = 0;
int par1 = 1, par2 = 3, par3 = 2;

arbol -> GetEntry(e1);
for (ULong64_t j=0;j<NumHits;j++){
    distX = PosX[j]-CoreX;
    distY = PosY[j]-CoreY;
    dist = sqrt(pow(distX,2)+pow(distY,2));
    energy = log10(Energy[j]);
    if (Particle[j]==par1){p1->SetPoint(i1,dist,energy);i1++;}
    else if (Particle[j]==par2){p2->SetPoint(i2,dist,energy);i2++;}
    else if (Particle[j]==par3){p3->SetPoint(i3,dist,energy);i3++;}
}

p1 -> SetMarkerColor(kAzure);
p1 -> SetMarkerStyle(kFullDotMedium);
p1 -> SetLineColor(kAzure);
p1 -> SetLineWidth(3);

p2 -> SetMarkerColor(kGreen+2);
p2 -> SetMarkerStyle(kFullDotMedium);
p2 -> SetLineColor(kGreen+2);
p2 -> SetLineWidth(3);

p3 -> SetMarkerColor(kRed);
p3 -> SetMarkerStyle(kFullDotMedium);
p3 -> SetLineColor(kRed);
p3 -> SetLineWidth(3);

p1 -> SetTitle("Distribucion lateral");
p1 -> GetXaxis()->SetTitle("Distancia al nucleo (cm)");
p1 -> GetYaxis()->SetTitle("log_{10}(Energia [GeV])");

auto legend1 = new TLegend(0.1,0.8,0.27,0.9);
TString t =  Form("#splitline{Evento %d}{%d hits}",int(Event),int(NumHits));
legend1 -> AddEntry(p1,t,"l");

// LEYENDA CON NÚMERO DE EVENTO Y HITS
auto legend = new TLegend(0.75,0.78,0.9,0.88);
TString t1 =  "Fotones";
TString t2 =  "Electrones";
TString t3 =  "Positrones";
legend -> AddEntry(p1,t1,"l");
legend -> AddEntry(p2,t2,"l");
legend -> AddEntry(p3,t3,"l");
legend -> SetBorderSize(0);
gStyle -> SetLegendTextSize(0.027);

p1 -> Draw("AP");
p2 -> Draw("SAME P");
p3 -> Draw("SAME P");
legend -> Draw("SAME");
legend1 -> Draw("SAME");
}