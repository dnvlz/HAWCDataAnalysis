#include <iostream>
using namespace std;

void scaler_coincidence(){
int x;
cout << "Histograma de dobles (2), triples (3) o cuádruples (4) coincidencias: ";
cin >> x;
int p,n;
string title;
cout << "Primer evento (0) ó último evento (1): ";
cin >> p;

// Abrimos el archivo (guardado en la misma carpeta) y creamos árbol
TFile *file = TFile::Open("tdcscaler_run009776_00692.root");
TTree *arbol = (TTree*) file->Get("XCDF");
Int_t Detectores=300;
ULong64_t Tanque[Detectores];
arbol->SetBranchAddress("scaler.tankID",Tanque);
ULong64_t Conteo[Detectores];
if(x==2){arbol->SetBranchAddress("scaler.multiplicity2Count",Conteo);}
if(x==3){arbol->SetBranchAddress("scaler.multiplicity3Count",Conteo);}
if(x==4){arbol->SetBranchAddress("scaler.multiplicity4Count",Conteo);}

TH1F *hist= new TH1F("hist","",300+10,0-5.5,300+5.5);

// Dependiendo de respuesta creamos título y variable n que indica evento
if (p==0&x==2){n=0; hist->SetTitle("Dobles coincidencias (primer evento)");}
if (p==0&x==3){n=0; hist->SetTitle("Triples coincidencias (primer evento)");}
if (p==0&x==4){n=0; hist->SetTitle("Cuadruples coincidencias (primer evento)");}
if (p==1&x==2){n=999; hist->SetTitle("Dobles coincidencias (ultimo evento)");}
if (p==1&x==3){n=999; hist->SetTitle("Triples coincidencias (ultimo evento)");}
if (p==1&x==4){n=999; hist->SetTitle("Cuadruples coincidencias (ultimo evento)");}

// Evento n
arbol -> GetEntry(n);
// Iteramos sobre detectores
for (Int_t j=0;j<Detectores; j++){
        double Freq = Conteo[j];
        if (Freq<1E10&Tanque[j]!=150){hist->Fill(Tanque[j],Freq/(24.0E3));}}

hist -> GetYaxis()->SetTitle("Frecuencia de Conteo (kHz)");
hist -> GetXaxis()->SetTitle("Detector id.");
hist-> SetStats(0);
hist -> Draw("HIST F");
}