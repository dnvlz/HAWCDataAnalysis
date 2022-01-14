#include <iostream>
using namespace std;

void pmt_trigger(){
// Usuario decide qué histograma quiere ver
int x;
cout << "Histograma de pulsos cortos (0), largos (1) o ambos (2): ";
cin >> x;

// Abrimos el archivo (guardado en la misma carpeta) y creamos árbol
TFile *file = TFile::Open("trig_reducido_300Hits.root");
TTree *arbol = (TTree*) file -> Get("XCDF");

// Definimos mínimo y máximo
int xmin = 0;
int xmax = 1200;
int bins = 1200;
TH1F *hist2 = new TH1F("hist2","",bins,xmin,xmax);
TH1F *hist4 = new TH1F("hist4","",bins,xmin,xmax);
TH1F *hist = new TH1F("hist","",bins,xmin,xmax);

// Definimos variables: pulsos largos y cortos respectivamente
int NumHits = 1500;
ULong64_t NumHits2;
arbol -> SetBranchAddress("trig.nHit2Edge",&NumHits2);
ULong64_t NumHits4;
arbol -> SetBranchAddress("trig.nHit4Edge",&NumHits4);
// Id. del PMT
ULong64_t PMT2[NumHits];
arbol -> SetBranchAddress("trig.channelID_2Edge",PMT2);
ULong64_t PMT4[NumHits];
arbol -> SetBranchAddress("trig.channelID_4Edge",PMT4);
// PMT forma parte de trigger?
ULong64_t Trigger2[NumHits];
arbol -> SetBranchAddress("trig.triggerFlags_2Edge",Trigger2);
ULong64_t Trigger4[NumHits];
arbol -> SetBranchAddress("trig.triggerFlags_4Edge",Trigger4);

// Iteramos sobre entradas para llenar histogramas
Int_t entradas = arbol -> GetEntries();
for (Int_t i=0;i<entradas;i++){
    arbol -> GetEntry(i);
    NumHits = NumHits2;
    for (Int_t j=0;j<NumHits;j++){
        if (Trigger2[j]==1){
        hist2 -> Fill(PMT2[j]);}}
    NumHits = NumHits4;
    for (Int_t j=0;j<NumHits;j++){
        if (Trigger4[j]==1){
        hist4 -> Fill(PMT4[j]);}}
}

if (x==0){
    hist -> Add(hist2);
    hist -> SetTitle("Triggers (2 edge) en los que participa PMT");}
else if (x==1){
    hist -> Add(hist4);
    hist -> SetTitle("Triggers (4 edge) en los que participa PMT");}
else if (x==2){
    hist -> Add(hist2);
    hist -> Add(hist4);
    hist -> SetTitle("Triggers totales en los que participa PMT");}

// Para obtener frecuencia dividimos entre tiempo total: 120 s
hist -> SetStats(0);
hist -> GetXaxis()->SetTitle("PMT");
hist -> GetYaxis()->SetTitle("No. de triggers");
hist -> Draw("HIST F");
}