#include <iostream>
using namespace std;

void corr(){
int x;
cout << "Redes neuronales (0) o ground parameter (1): ";
cin >> x;

// Abrimos el archivo (guardado en la misma carpeta) y creamos árbol
TFile *file = TFile::Open("gamma.root");
TTree *arbol = (TTree*) file -> Get("XCDF");

// Definimos mínimo y máximo del eje x (tiempo en ns)
TH2F *hist= new TH2F("hist","",300,1,6,300,0,6);
hist -> SetStats(0);

// Energías simuladas para el rayo primario
Double_t Energy;
arbol -> SetBranchAddress("mc.logEnergy",&Energy);
// Energías reconstruidas con método de redes neuronales y ground parameter
Double_t RecEnergy;
if (x==0){arbol -> SetBranchAddress("rec.logNNEnergyV2",&RecEnergy);}
else if (x==1){arbol -> SetBranchAddress("rec.logGPV2",&RecEnergy);}

// Llenamos histograma bidimensional
Int_t entradas = arbol -> GetEntries();
for (Int_t i=0;i<entradas;i++){
    arbol -> GetEntry(i);
    hist -> Fill(Energy,RecEnergy);}


hist -> GetXaxis()->SetTitle("log_{10}(Energia [GeV])");
if (x==0){hist -> GetYaxis()->SetTitle("log_{10}(Energia estimada con redes neuronales [GeV])");}
else if (x==1){hist -> GetYaxis()->SetTitle("log_{10}(Energia estimada con Ground Parameter [GeV])");}

hist -> SetTitle("Correlacion entre energia de rayo primario y reconstruccion energetica (fotones)");
hist-> Draw("colz");
}