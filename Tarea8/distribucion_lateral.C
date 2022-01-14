#include <iostream>
#include <math.h> 
using namespace std;

void distribucion_lateral(){
// Usuario define evento
int e1;
cout << "Evento: ";
cin >> e1;

TFile *file = TFile::Open("hawcsim_protons_M28L2000_nc.root");
TTree *arbol = (TTree*) file->Get("XCDF");

int n = 1987;
// Evento
ULong64_t Event;
arbol -> SetBranchAddress("HAWCSim.Evt.Num",&Event);
// Posición de Núcleo
Double_t CoreX;
arbol -> SetBranchAddress("HAWCSim.Evt.X",&CoreX);
Double_t CoreY;
arbol -> SetBranchAddress("HAWCSim.Evt.Y",&CoreY);
// Posición de detección
Double_t PosX[n];
arbol -> SetBranchAddress("HAWCSim.WH.XNE",PosX);
Double_t PosY[n];
arbol -> SetBranchAddress("HAWCSim.WH.YNE",PosY);
// Energía de particulas secundarias
Double_t Energy[n];
arbol -> SetBranchAddress("HAWCSim.WH.Energy",Energy);
ULong64_t NumHits;
arbol -> SetBranchAddress("HAWCSim.Evt.nWHit",&NumHits);

TCanvas *c1 = new TCanvas("c1");

Double_t distX, distY, dist, energy;
auto p1 = new TGraph();
int i = 0;

arbol -> GetEntry(e1);
// FILTROS Y GRÁFICA
for (ULong64_t j=0;j<NumHits;j++){
            distX = PosX[j]-CoreX;
            distY = PosY[j]-CoreY;
            dist = sqrt(pow(distX,2)+pow(distY,2));
            energy = log10(Energy[j]);
            p1 -> SetPoint(i,dist,energy);
            i++;
}

p1 -> SetMarkerColor(kAzure);
p1 -> SetMarkerStyle(kFullDotMedium);

p1 -> SetLineColor(kAzure);
p1 -> SetLineWidth(3);

p1 -> SetTitle("Distribucion lateral");
p1 -> GetXaxis()->SetTitle("Distancia al nucleo (cm)");
p1 -> GetYaxis()->SetTitle("log_{10}(Energia [GeV])");

// LEYENDA CON NÚMERO DE EVENTO Y HITS
auto legend1 = new TLegend(0.73,0.8,0.9,0.9);
TString t1 =  Form("#splitline{Evento %d}{%d hits}",int(Event),int(NumHits));
legend1 -> AddEntry(p1,t1,"l");
gStyle -> SetLegendTextSize(0.025);

p1 -> Draw("AP");
legend1 -> Draw("SAME");
}