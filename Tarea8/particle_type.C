#include <iostream>
using namespace std;

void particle_type(){
// Abrimos el archivo (guardado en la misma carpeta) y creamos árbol
TFile *file = TFile::Open("hawcsim_protons_M28L2000_nc.root");
TTree *arbol = (TTree*) file -> Get("XCDF");

// Definimos mínimo y máximo
int xmin = 0;
int m = 16;
TH1F *hist= new TH1F("Histograma","",m,0,m);

int n = 1987;
Long64_t Particle[n];
arbol -> SetBranchAddress("HAWCSim.WH.pType",Particle);
ULong64_t NumParticles;
arbol -> SetBranchAddress("HAWCSim.Evt.nWHit",&NumParticles);

// Iteramos sobre entradas para llenar histogramas
Int_t entradas = arbol -> GetEntries();
for (Int_t i=0;i<entradas;i++){
    arbol -> GetEntry(i);
    for (Int_t j=0;j<NumParticles;j++){
    hist -> Fill(Particle[j]);
    }
}

hist -> SetTitle("Tipo de particula en detectores de HAWC");
hist -> Scale(100.0/hist->GetEntries());
hist -> GetXaxis()->SetTitle("Id. particula");
hist -> GetXaxis()->SetNdivisions(-m);

hist -> GetYaxis()->SetTitle("%");
hist -> SetLineColor(kAzure);
hist -> SetFillColor(kAzure);
hist -> Draw("HIST F");
}