#include <iostream>
using namespace std;

void resAngular_hits(){
// DATOS INTRODUCIDOS EN LA TERMINAL PARA DECIDIR QUÉ HISTOGRAMA SE MUESTRA
int angle;
cout << "Zenith (0) o azimuth (1): ";
cin >> angle;

TFile *file = TFile::Open("gamma.root");
TTree *arbol = (TTree*) file->Get("XCDF");


double max=0.2;
TH1F *h1 = new TH1F("Histograma","",200,0,max);
TH1F *h2 = new TH1F("Histograma","",200,0,max);

// ANGULOS RECONSTRUIDOS
Double_t RZenith;
arbol -> SetBranchAddress("rec.zenithAngle",&RZenith);
Double_t RAzimuth;
arbol -> SetBranchAddress("rec.azimuthAngle",&RAzimuth);
// ANGULOS SIMULADOS
Double_t SZenith;
arbol -> SetBranchAddress("mc.zenithAngle",&SZenith);
Double_t SAzimuth;
arbol -> SetBranchAddress("mc.azimuthAngle",&SAzimuth);
// NUMERO DE HITS DE LA CASCADA
ULong64_t NumHits;
arbol -> SetBranchAddress("event.nHit",&NumHits);

// DEFINIMOS RESOLUCION ANGULAR Y APLICAMOS FILTROS CORRESPONDIENTES
Int_t entradas = arbol -> GetEntries();
for (Int_t i=0;i<entradas;i++){
    arbol -> GetEntry(i);
    double ResZ = abs(RZenith-SZenith);
    double ResA = abs(RAzimuth-SAzimuth);
    if (angle==0&NumHits<100){h1 -> Fill(ResZ);}
    else if (angle==0&NumHits>100){h2 -> Fill(ResZ);}
    else if (angle==1&NumHits<100){h1 -> Fill(ResZ);}
    else if (angle==1&NumHits>100){h2 -> Fill(ResZ);}
}

TString filtro1 = "event.nHit<100";
TString filtro2 = "event.nHit>100";
auto legend = new TLegend(0.42,0.76,0.5,0.87);
legend -> AddEntry(h1,filtro1,"P");
legend -> AddEntry(h2,filtro2,"P");
legend -> SetBorderSize(0);
gStyle -> SetLegendTextSize(0.03);


if (angle==0){
    h2 -> SetTitle("Resolucion cenital para reconstruir nucleos de cascadas iniciadas por fotones");
    h2 -> GetXaxis()->SetTitle("Angulo");}
if (angle==1){
    h2 -> SetTitle("Resolucion azimutal para reconstruir nucleos de cascadas iniciadas por fotones");
    h2 -> GetXaxis()->SetTitle("Angulo");};

h1 -> SetLineColor(kAzure);
h1 -> SetFillColorAlpha(kAzure,0.5);
h1 -> SetMarkerColor(kAzure);
h1 -> SetMarkerStyle(8);

h2 -> SetLineColor(kRed);
h2 -> SetFillColorAlpha(kRed,0.5);
h2 -> SetMarkerColor(kRed);
h2 -> SetMarkerStyle(8);

h1 -> SetStats(0);
h2 -> SetStats(0);
h1 -> Scale(1.0/h1->GetEntries());
h2 -> Scale(1.0/h2->GetEntries());

h2 -> Draw("HIST F");
h1 -> Draw("SAME HIST F");

legend -> Draw("Same");
}
