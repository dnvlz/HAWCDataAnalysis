#include <iostream>
using namespace std;

void freq_hits(){
// Usuario decide qué histograma quiere ver
int x;
cout << "Histograma de pulsos cortos (0), largos (1) o ambos (2): ";
cin >> x;

// Abrimos el archivo (guardado en la misma carpeta) y creamos árbol
TFile *file = TFile::Open("trig_run009776_00692.root");
TTree *arbol = (TTree*) file -> Get("XCDF");

// Definimos mínimo y máximo
int xmin = 0;
int xmax = 300;
int bins = 300;
TH1F *hist2= new TH1F("hist2","",bins,xmin,xmax);
TH1F *hist4= new TH1F("hist4","",bins,xmin,xmax);
TH1F *hist= new TH1F("hist","",bins,xmin,xmax);

// Definimos variables: pulsos largos y cortos respectivamente
ULong64_t NumHits4;
arbol -> SetBranchAddress("trig.nHit4Edge",&NumHits4);
ULong64_t NumHits2;
arbol -> SetBranchAddress("trig.nHit2Edge",&NumHits2);

// Iteramos sobre entradas para llenar histogramas
Int_t entradas = arbol -> GetEntries();
for (Int_t i=0;i<entradas;i++){
    arbol -> GetEntry(i);
    hist2 -> Fill(NumHits2);
    hist4 -> Fill(NumHits4);}

if (x==0){
    hist -> Add(hist2);
    hist -> SetTitle("Eventos para pulsos cortos");}
else if (x==1){
    hist -> Add(hist4);
    hist -> SetTitle("Eventos para pulsos largos");}
else if (x==2){
    hist -> Add(hist2);
    hist -> Add(hist4);
    hist -> SetTitle("Eventos para ambos pulsos");}

// Para obtener frecuencia dividimos entre tiempo total: 120 s
hist -> Scale(1/120.);
hist -> GetXaxis()->SetTitle("Hits");
hist -> GetYaxis()->SetTitle("Frecuencia (Hz)");
hist -> Draw("HIST F");
}