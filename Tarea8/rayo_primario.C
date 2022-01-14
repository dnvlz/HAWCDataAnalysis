#include <iostream>
using namespace std;

void rayo_primario(){
// Abrimos el archivo (guardado en la misma carpeta) y creamos árbol
TFile *file = TFile::Open("hawcsim_protons_M28L2000_nc.root");
TTree *arbol = (TTree*) file -> Get("XCDF");

// Definimos mínimo y máximo del eje x (tiempo en ns)
int xmin = 0; 
int xmax = 4E4; //4E5
int xbins = 2E2*(xmax-xmin)/xmax;
int ymin = 0; 
int ymax = 2E5; //2E6
int ybins = 2E2*(ymax-ymin)/ymax;

TH2F *hist= new TH2F("Histograma","Rayo cosmico primario",xbins,xmin,xmax,ybins,ymin,ymax);
hist -> SetStats(0);

// Id. del PMT
ULong64_t PMTs;
arbol -> SetBranchAddress("HAWCSim.Evt.nPE",&PMTs);
// Energía del rayo primario
Double_t Energy;
arbol -> SetBranchAddress("HAWCSim.Evt.Energy",&Energy);

// Llenamos histograma
Int_t entradas = arbol -> GetEntries();
for (Int_t i=0;i<entradas;i++){
    arbol -> GetEntry(i);
    hist -> Fill(PMTs,Energy);
}

hist -> GetXaxis()->SetTitle("No. de PMTs detectados");
hist -> GetYaxis()->SetTitle("Energia [GeV]");
hist-> Draw("colz");
}