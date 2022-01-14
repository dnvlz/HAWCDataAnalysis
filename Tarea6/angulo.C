#include <iostream>
#include <math.h>
using namespace std;

void angulo(){
int x;
cout << "Histograma de ángulo cenital (0) ó azimutal (1): ";
cin >> x;
int y;
cout << "Sin cortes de selección (0) ó con cortes de selección (1): ";
cin >> y;

// Abrimos el archivo (guardado en la misma carpeta) y creamos árbol
TFile *file = TFile::Open("reco_run009776_00639.root");
TTree *arbol = (TTree*) file -> Get("XCDF");

// Definimos histograma enital
TH1F *hist1 = new TH1F("hist1","Angulo cenital",1000,-180,180);
// Definimos azimutal
TH1F *hist2 = new TH1F("hist2","Angulo azimutal",1000,-180,180);
TH1F *hist= new TH1F("hist","",1000,-180,180);

// Variable que indica ángulo cenital
Double_t Zenith;
arbol -> SetBranchAddress("rec.zenithAngle",&Zenith);
// Variable que indica ángulo azimutal
Double_t Azimuth;
arbol -> SetBranchAddress("rec.azimuthAngle",&Azimuth);
// Reconstruccion angular de buena calidad
ULong64_t Flag;
arbol -> SetBranchAddress("rec.angleFitStatus",&Flag);

// Variable que cuenta número de eventos que pasan por corte de selección
double n = 0;
// Iteramos sobre entradas para llenar histogramas
Int_t entradas = arbol -> GetEntries();
for (Int_t i=0;i<entradas;i++){
    arbol -> GetEntry(i);
    if (y==0){
        // Pasamos de radianes a grados
        hist1 -> Fill(Zenith*180.0/M_PI);
        hist2 -> Fill(Azimuth*180.0/M_PI);}
    else if (y==1&Flag==0){
        n += 1;
        // Pasamos de radianes a grados
        hist1 -> Fill(Zenith*180.0/M_PI);
        hist2 -> Fill(Azimuth*180.0/M_PI);}
}

if (x==0){
    hist -> Add(hist1);
    hist -> SetTitle("Coordenada cenital de las cascadas atmosfericas");
    if(y==0){hist->GetXaxis()->SetRangeUser(0,180);}
    else if(y==1){hist->GetXaxis()->SetRangeUser(0,90);}}
else if (x==1){
    hist -> Add(hist2);
    hist -> SetTitle("Coordenada azimutal de las cascadas atmosfericas");}

auto legend = new TLegend(0.1,0.8,0.3,0.9);
if (y==0){legend->SetHeader("Sin cortes de seleccion","C");}
else if (y==1){legend->SetHeader("Con cortes de seleccion","C");}
gStyle->SetLegendTextSize(0.027);


hist -> GetXaxis()->SetTitle("Angulo (#circ)");
hist -> SetLineColor(kAzure);
hist -> SetFillColor(kAzure);
hist -> Draw("HIST F");
legend -> Draw("Same");

if (y==1){cout << "La fracción de datos que pasa por el corte de selección es de " << n/entradas << endl;}
}