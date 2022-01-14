#include <iostream>
using namespace std;

void h2(){
// Usuario decide qué histograma quiere ver
int x;
cout << "Eta (0) o phi (1): ";
cin >> x;

TString file = "CMSMuon.txt";
const int maxrows = 100000; //wc -l archivo.txt
Float_t Run[maxrows], Event[maxrows], E1[maxrows], px1[maxrows], py1[maxrows], pz1[maxrows], pt1[maxrows], eta1[maxrows], phi1[maxrows], Q1[maxrows], E2[maxrows], px2[maxrows], py2[maxrows], pz2[maxrows], pt2[maxrows], eta2[maxrows], phi2[maxrows], Q2[maxrows], M[maxrows]; //2 variables de punto flotante
char Type1[maxrows], Type2[maxrows];
Int_t i = 0;
std::ifstream infile(file.Data());

//Llenando los arreglos con la información de cada evento
while(infile >> Run[i] >> Event[i] >> Type1[i] >> E1[i] >> px1[i] >> py1[i] >> pz1[i] >> pt1[i] >> eta1[i] >> phi1[i] >> Q1[i] >> Type2[i] >> E2[i] >> px2[i] >> py2[i] >> pz2[i] >> pt2[i] >> eta2[i] >> phi2[i] >> Q2[i] >> M[i] && i < maxrows ){
    i++;}

// Dos histogramas: para carga positiva y negativa
TH1F *h1 = new TH1F("Histograma","",500,-3.15,3.15);
TH1F *h2 = new TH1F("Histograma","",500,-3.15,3.15);

for (Int_t j=0;j<maxrows;j++){
    // La cantidad eta1[j]*(1-x)+phi1[j]*x es igual a eta1[j] si x=0, y es igual a phi1[j] si x=1
    // Nos fijamos en la carga del primer muón: si es positiva va a h1 y si es negativa va a h2
    if (Q1[j]>0.0) h1 -> Fill(eta1[j]*(1-x)+phi1[j]*x);
    else if (Q1[j]<0.0) h2 -> Fill(eta1[j]*(1-x)+phi1[j]*x);
    // Nos fijamos en la carga del segundo muón: si es positiva va a h1 y si es negativa va a h2
    if (Q2[j]>0.0) h1 -> Fill(eta2[j]*(1-x)+phi2[j]*x);
    else if (Q2[j]<0.0) h2 -> Fill(eta2[j]*(1-x)+phi2[j]*x);}

// Título del histograma dependiendo qué se vaya a graficar
if (x==0){
    h1 -> SetTitle("Histograma de pseudorapidez");
    h1 -> GetXaxis() -> SetTitle("#eta");}
else if (x==1){
    h1 -> SetTitle("Histograma de angulo azimutal");
    h1 -> GetXaxis() -> SetTitle("#phi [rad]");}

h1 -> SetMinimum(0);
h1 -> Scale(1.0/h1->GetEntries());
h2 -> SetMinimum(0);
h2 -> Scale(1.0/h2->GetEntries());
h1 -> SetStats(0);

// Leyendas para etiquetar histogramas
TString s1= "Muones positivos";
TString s2 = "Mones negativos";
auto legend = new TLegend(0.35,0.76,0.6,0.87);
legend -> AddEntry(h1,s1,"P");
legend -> AddEntry(h2,s2,"P");
legend -> SetBorderSize(0);
legend -> SetFillStyle(0);
gStyle -> SetLegendTextSize(0.035);

h1 -> SetFillColorAlpha(kAzure,0.5);
h1 -> SetMarkerColor(kAzure);
h1 -> SetLineWidth(0);
h1 -> SetMarkerStyle(kFullDotLarge);

h2 -> SetFillColorAlpha(kRed,0.5);
h2 -> SetMarkerColor(kRed);
h2 -> SetLineWidth(0);
h2 -> SetMarkerStyle(kFullDotLarge);

h1 -> Draw("HIST F");
h2 -> Draw("SAME HIST F");
legend -> Draw("SAME");
}
