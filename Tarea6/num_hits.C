#include <iostream>
using namespace std;

void num_hits(){
// Usuario decide qué histograma quiere ver
int x;
cout << "Histograma con número de hits a 10 ns (0) ó 20 ns (1) del frente de la cascada: ";
cin >> x;

// Abrimos el archivo (guardado en la misma carpeta) y creamos árbol
TFile *file = TFile::Open("reco_run009776_00639.root");
TTree *arbol = (TTree*) file -> Get("XCDF");

// Definimos mínimo y máximo
int xmin = 0;
int xmax = 300;
int bins = 300;
TH1F *hist1= new TH1F("hist1","",bins,xmin,xmax);
TH1F *hist2= new TH1F("hist2","",bins,xmin,xmax);
TH1F *hist= new TH1F("hist","",bins,xmin,xmax);

// Definimos variables: no. hits de 10 y 20 ns del frente de cascada respectivamente
ULong64_t NumHits10;
arbol -> SetBranchAddress("rec.nHitSP10",&NumHits10);
ULong64_t NumHits20;
arbol -> SetBranchAddress("rec.nHitSP20",&NumHits20);

// Variables que almacenan 
// Num de cascadas con >100 hits a 10 ns del frente de la cascada
int n10 = 0;
// Num de cascadas con >500 hits a 20 ns del frente de la cascada
int n20 = 0;

// Iteramos sobre entradas para llenar histogramas
Int_t entradas = arbol -> GetEntries();
for (Int_t i=0;i<entradas;i++){
    arbol -> GetEntry(i);
    hist1 -> Fill(NumHits10);
    if (NumHits10>100){n10 += 1;}
    hist2 -> Fill(NumHits20);}
    if (NumHits20>500){n20 += 1;}

if (x==0){
    hist -> Add(hist1);
    hist -> SetTitle("Numero de hits a 10 ns del frente de la cascada");
    // Para calcular frecuencia dividimos entre tiempo que duró la toma de datos
    double freq10 = n10/120.0;
    cout << "Se detectan cascadas con más de 100 hits a 10 ns del frente de la cascada con una frecuencia de " << freq10 << " Hz." << endl;}
else if (x==1){
    hist -> Add(hist2);
    hist -> SetTitle("Numero de hits a 20 ns del frente de la cascada");
    // Para calcular frecuencia dividimos entre tiempo que duró la toma de datos
    double freq20 = n20/120.0;
    cout << "Se detectan cascadas con más de 500 hits a 20 ns del frente de la cascada con una frecuencia de " << freq20 << " Hz." << endl;}

// Para obtener histogramas de frecuencia dividimos entre tiempo total
hist -> Scale(1/120.);

hist -> GetXaxis()->SetTitle("Hits");
hist -> GetYaxis()->SetTitle("Frecuencia (Hz)");
hist -> SetLineColor(kAzure);
hist -> SetFillColor(kAzure);
hist -> Draw("HIST F");
}