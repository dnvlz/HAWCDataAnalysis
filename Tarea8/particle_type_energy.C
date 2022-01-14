#include <iostream>
using namespace std;

void particle_type_energy(){
int x;
cout << "Energía baja (0), media (1) o alta (2): ";
cin >> x;

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
Double_t Energy;
arbol -> SetBranchAddress("HAWCSim.Evt.Energy",&Energy);

//El rango de energía de 0 GeV a 2247 GeV contiene 765 eventos
//El rango de energía de 2247 GeV a 10526 GeV contiene 770 eventos
//El rango de energía de 10526 GeV a 2000000 GeV contiene 768 eventos
int E1 = 2247, E2 = 10526;

// Iteramos sobre entradas para llenar histogramas
Int_t entradas = arbol -> GetEntries();
for (Int_t i=0;i<entradas;i++){
    arbol -> GetEntry(i);
    for (Int_t j=0;j<NumParticles;j++){
        if (x==0&Energy<=E1){hist -> Fill(Particle[j]);}
        else if (x==1&Energy<=E2&Energy>E1){hist -> Fill(Particle[j]);}
        else if (x==2&Energy>E2){hist -> Fill(Particle[j]);}
    }
}

if (x==0){
    hist -> SetTitle("Tipo de particula en HAWC (energia baja)");}
else if (x==1){
    hist -> SetTitle("Tipo de particula en HAWC (energia media)");}
else if (x==2){
    hist -> SetTitle("Tipo de particula en HAWC (energia alta)");}

hist -> Scale(100.0/hist->GetEntries());
hist -> GetXaxis()->SetTitle("Id. particula");
hist -> GetXaxis()->SetNdivisions(-m);

hist -> GetYaxis()->SetTitle("%");
hist -> SetLineColor(kAzure);
hist -> SetFillColor(kAzure);
hist -> Draw("HIST F");
}