#include <iostream>
using namespace std;

void scaler_hist(){
// x=300 si queremos hist de detector, 1200 si queremos hist de PMT
int m,x;
cout << "Histograma de detectores (0) ó PMTs (1): ";
cin >> m;
if (m==0){x=300;}
else if (m==1){x=1200;}

// Creamos histograma
TH1F *hist	= new TH1F("hist","",x+10,-5.5,x+5.5);
int p,n;
string title;
cout << "Primer evento (0) ó último evento (1): ";
cin >> p;
// Dependiendo de respuesta creamos título y variable n que indica evento
if (p==0){n=0; hist->SetTitle("Conteos (primer evento)");}
else if (p==1){n=999; hist->SetTitle("Conteos (ultimo evento)");}

// Abrimos archivo, creamos árbol e histograma
TFile *file = TFile::Open("tdcscaler_run009776_00692.root");
TTree *arbol = (TTree*) file->Get("XCDF");


// Hay 1200 PMT y 300 WCD
Int_t Canales=1200;
Int_t Detectores=300;

// Definimos vector que almacene info. de conteos por canal
ULong64_t Conteo[Canales];
arbol -> SetBranchAddress("scaler.channelCount",Conteo);

// Definimos vector que dependiendo valor de x
// Almacena id. de PMT o de detector
ULong64_t Info[Canales];
if (x==Canales){
    arbol -> SetBranchAddress("scaler.channelID",Info);
    hist -> GetXaxis()->SetTitle("PMT id.");
    hist -> SetFillColor(kBlue);
    hist -> SetLineColor(kBlue);}
else if (x==Detectores){
    arbol -> SetBranchAddress("scaler.channelTankID",Info);
    hist -> GetXaxis()->SetTitle("Detector id.");}

// Evento n
arbol -> GetEntry(n);
// Iteramos sobre PMT o detector
for (Int_t j=0;j<x; j++){
    // Para ese PMT o detector hay una frecuencia de conteo
    // Inicializamos en 0
    double Freq = 0.0;
    // Iteramos sobre PMT
    for (Int_t i=0; i<Canales; i++){
        // Si el id. del PMT o detector coincide con este paso
        // de la iteración, sumamos a la freq. de conteo
        // Hay algunos valores espurios muy grandes que evitamos
        if (Info[i]==j+1&Conteo[i]<1E10&j+1!=150){
        Freq += Conteo[i];
            } 
        }
    // Llenamos histograma
    hist->Fill(j+1,Freq/(24E3));
    }

hist -> GetYaxis()->SetTitle("Frecuencia de Conteo (kHz)");
hist -> SetStats(0);
hist -> Draw("HIST F");
}