#include <iostream>
#include <math.h>
using namespace std;

void direccion(){
// Abrimos el archivo (guardado en la misma carpeta) y creamos árbol
TFile *file = TFile::Open("reco_run009776_00639.root");
TTree *arbol = (TTree*) file -> Get("XCDF");

// Definimos mínimo y máximo de ejes
int xmin = 0;
double xmax = 360;
// 2 bins por cada ángulo
int xbins = (xmax-xmin)*2;

double ymin = -90;
double ymax = 90;
// 2 bins por cada ángulo
int ybins = (ymax-ymin)*2;

TH2F *hist= new TH2F("hist","Direccion de cascadas",xbins,xmin,xmax,ybins,ymin,ymax);
//hist -> SetStats(0);

// Variable que indica ascension recta
Double_t AR;
arbol -> SetBranchAddress("rec.ra",&AR);
// Variable que indica declinacion
Double_t Dec;
arbol -> SetBranchAddress("rec.dec",&Dec);
// Reconstruccion angular de buena calidad
ULong64_t Flag;
arbol -> SetBranchAddress("rec.angleFitStatus",&Flag);

// Iteramos sobre entradas para llenar histogramas
Int_t entradas = arbol -> GetEntries();
for (Int_t i=0;i<entradas;i++){
    arbol -> GetEntry(i);
    // Pasamos de radianes a grados
    if (Flag==0){hist -> Fill(AR*180/M_PI,Dec*180/M_PI);}
}

hist -> GetXaxis()->SetTitle("Ascension recta (#circ)");
hist -> GetYaxis()->SetTitle("Declinacion (#circ)");
hist-> Draw("colz");
}