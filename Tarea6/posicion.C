#include <iostream>
using namespace std;

void posicion(){
// Abrimos el archivo (guardado en la misma carpeta) y creamos árbol
TFile *file = TFile::Open("reco_run009776_00639.root");
TTree *arbol = (TTree*) file -> Get("XCDF");

// Definimos mínimo y máximo de ejes
int xmin = -100;
int xmax = 180;
// un bin abarca 1.5 valores de x
int xbins = 187;

int ymin = 120;
int ymax = 370;
// un bin abarca 1.5 valores de y
int ybins = 167;

TH2F *hist= new TH2F("hist","Posicion de cascadas",xbins,xmin,xmax,ybins,ymin,ymax);
//hist -> SetStats(0);

// Variable que indica posición eje x
Double_t PosX;
arbol -> SetBranchAddress("rec.coreX",&PosX);
// Variable que indica posición eje y
Double_t PosY;
arbol -> SetBranchAddress("rec.coreY",&PosY);

// Iteramos sobre entradas para llenar histogramas
Int_t entradas = arbol -> GetEntries();
for (Int_t i=0;i<entradas;i++){
    arbol -> GetEntry(i);
    hist -> Fill(PosX,PosY);
}

hist -> GetXaxis()->SetTitle("x");
hist -> GetYaxis()->SetTitle("y");
hist-> Draw("colz");
}