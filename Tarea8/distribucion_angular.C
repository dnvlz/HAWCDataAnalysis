#include <iostream>
#include <math.h>
using namespace std;

void distribucion_angular(){
int x;
cout << "Histograma de ángulo cenital (0) ó azimutal (1): ";
cin >> x;

// Abrimos el archivo (guardado en la misma carpeta) y creamos árbol
TFile *file = TFile::Open("hawcsim_protons_M28L2000_nc.root");
TTree *arbol = (TTree*) file -> Get("XCDF");

int bins = 180;
// Definimos histograma enital
TH1F *hist1 = new TH1F("hist1","Angulo cenital",bins,0,360);
// Definimos azimutal
TH1F *hist2 = new TH1F("hist2","Angulo azimutal",bins,0,360);
TH1F *hist= new TH1F("Histograma","",bins,0,360);

// Variable que indica ángulo cenital
Double_t Theta;
arbol -> SetBranchAddress("HAWCSim.Evt.Theta",&Theta);
// Variable que indica ángulo azimutal
Double_t Phi;
arbol -> SetBranchAddress("HAWCSim.Evt.Phi",&Phi);

// Iteramos sobre entradas para llenar histogramas
Int_t entradas = arbol -> GetEntries();
for (Int_t i=0;i<entradas;i++){
    arbol -> GetEntry(i);
    hist1 -> Fill(Theta);
    hist2 -> Fill(Phi);
}

if (x==0){
    hist -> Add(hist1);
    hist -> SetTitle("Coordenada cenital del rayo primario");
    hist->GetXaxis()->SetRangeUser(0,65);}
else if (x==1){
    hist -> Add(hist2);
    hist -> SetTitle("Coordenada azimutal del rayo primario");}

hist -> Scale(100.0/hist->GetEntries());
hist -> GetXaxis()->SetTitle("Angulo (#circ)");
hist -> GetYaxis()->SetTitle("%");
hist -> SetLineColor(kAzure);
hist -> SetFillColor(kAzure);
hist -> Draw("HIST F");
}