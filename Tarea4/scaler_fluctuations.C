#include <iostream>
using namespace std;

void scaler_fluctuations(){
// Abrimos archivo, creamos árbol e histograma
TFile *file = TFile::Open("tdcscaler_run009776_00692.root");
TTree *arbol = (TTree*) file->Get("XCDF");
TH1F *hist	= new TH1F("hist","Fluctuaciones entre primer y ultimo evento",1200+10,-5.5,1200+5.5);

// Hay 1200 PMT y 300 WCD
Int_t Canales=1200;
Int_t Detectores=300;

// Definimos vector que almacene info. de conteos por canal
ULong64_t Conteo[Canales];
arbol -> SetBranchAddress("scaler.channelCount",Conteo);
// Almacena id. de PMT
ULong64_t Info[Canales];
arbol -> SetBranchAddress("scaler.channelID",Info);
hist -> GetXaxis()->SetTitle("PMT id.");

// Evento 0
arbol -> GetEntry(0);
// Iteramos sobre PMT
for (Int_t j=0;j<Canales; j++){
    // Para ese PMT hay una frecuencia de conteo
    // Inicializamos en 0
    double Freq = 0.0;
    // Iteramos sobre PMT
    for (Int_t i=0; i<Canales; i++){
        // Si el id. del PMT coincide con este paso
        // de la iteración, sumamos a la freq. de conteo
        if (Info[i]==j+1&Conteo[i]<1E10){
        Freq += Conteo[i];
            } 
        }
    // Llenamos histograma
    hist->Fill(j+1,Freq/(24E3));
    }

// Último
arbol -> GetEntry(999);
// Iteramos sobre PMT
for (Int_t j=0;j<Canales; j++){
    // Para ese PMT hay una frecuencia de conteo
    // Inicializamos en 0
    double Freq = 0.0;
    // Iteramos sobre PMT
    for (Int_t i=0; i<Canales; i++){
        // Si el id. del PMT coincide con este paso
        // de la iteración, sumamos a la freq. de conteo
        if (Info[i]==j+1&Conteo[i]<1E10){
        Freq -= Conteo[i];
            } 
        }
    // Llenamos histograma
    hist->Fill(j+1,Freq/(24E3));
    }

hist -> GetYaxis()->SetTitle("Frecuencia de Conteo (kHz)");
hist -> SetStats(0);
hist -> Draw("HIST F");
}