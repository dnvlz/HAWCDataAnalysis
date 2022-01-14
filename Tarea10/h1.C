#include <iostream>
using namespace std;

void h1(){
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
while(infile >> Run[i] >> Event[i] >>  Type1[i] >> E1[i] >> px1[i] >> py1[i] >> pz1[i] >> pt1[i] >> eta1[i] >> phi1[i] >> Q1[i] >> Type2[i] >> E2[i] >> px2[i] >> py2[i] >> pz2[i] >> pt2[i] >> eta2[i] >> phi2[i] >> Q2[i] >> M[i] && i < maxrows ){
    i++;}

TH1F *h = new TH1F("Histograma","",500,-3.15,3.15);
for (Int_t j=0;j<maxrows;j++){
    // La cantidad eta1[j]*(1-x)+phi1[j]*x es igual a eta1[j] si x=0, y es igual a phi1[j] si x=1
    h -> Fill(eta1[j]*(1-x)+phi1[j]*x);
    h -> Fill(eta2[j]*(1-x)+phi2[j]*x);}

// Título del histograma dependiendo qué se vaya a graficar
if (x==0){
    h -> SetTitle("Histograma de pseudorapidez");
    h -> GetXaxis() -> SetTitle("#eta");}
else if (x==1){
    h -> SetTitle("Histograma de angulo azimutal");
    h -> GetXaxis() -> SetTitle("#phi [rad]");}

h->SetMinimum(0);

h -> SetLineColor(kAzure);
h -> SetFillColorAlpha(kAzure,0.5);
h -> SetMarkerColor(kAzure);
h -> SetLineWidth(1);
h -> SetMarkerStyle(kFullDotLarge);


h -> Scale(1.0/h->GetEntries());
h -> Draw("HIST F");
}
