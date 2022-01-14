#include <iostream>
using namespace std;

void h3(){
TString file = "CMSMuon.txt";
const int maxrows = 100000; //wc -l archivo.txt
Float_t Run[maxrows], Event[maxrows], E1[maxrows], px1[maxrows], py1[maxrows], pz1[maxrows], pt1[maxrows], eta1[maxrows], phi1[maxrows], Q1[maxrows], E2[maxrows], px2[maxrows], py2[maxrows], pz2[maxrows], pt2[maxrows], eta2[maxrows], phi2[maxrows], Q2[maxrows], M[maxrows]; //2 variables de punto flotante
char Type1[maxrows], Type2[maxrows];
Int_t i = 0;
std::ifstream infile(file.Data());

//Llenando los arreglos con la información de cada evento
while(infile >> Run[i] >> Event[i] >>  Type1[i] >> E1[i] >> px1[i] >> py1[i] >> pz1[i] >> pt1[i] >> eta1[i] >> phi1[i] >> Q1[i] >> Type2[i] >> E2[i] >> px2[i] >> py2[i] >> pz2[i] >> pt2[i] >> eta2[i] >> phi2[i] >> Q2[i] >> M[i] && i < maxrows ){
    i++;}

TH1F *h = new TH1F("Histograma","",500,0.5,25);
TH1F *h1 = new TH1F("Histograma","",500,0.5,25);
TH1F *h2 = new TH1F("Histograma","",500,0.5,25);

for (Int_t j=0;j<maxrows;j++){
    h -> Fill(pt1[j]);
    h -> Fill(pt2[j]);
    // Nos fijamos en la carga del primer muón: si es positiva va a h1 y si es negativa va a h2
    if (Q1[j]>0.0) h1 -> Fill(pt1[j]);
    else if (Q1[j]<0.0) h2 -> Fill(pt1[j]);
    // Nos fijamos en la carga del segundo muón: si es positiva va a h1 y si es negativa va a h2
    if (Q2[j]>0.0) h1 -> Fill(pt2[j]);
    else if (Q2[j]<0.0) h2 -> Fill(pt2[j]);}


h -> SetTitle("Histograma de momento transverso");
h -> GetXaxis() ->SetTitle("pt [GeV]");
h -> GetYaxis() ->SetTitle("Conteos");
h -> SetMinimum(0);
h1 -> SetMinimum(0);
h2 -> SetMinimum(0);

// Leyendas para etiquetar histogramas
TString s= "Todos los muones";
TString s1= "Muones positivos";
TString s2 = "Mones negativos";
auto legend = new TLegend(0.38,0.72,0.63,0.87);
legend -> AddEntry(h,s,"P");
legend -> AddEntry(h1,s1,"P");
legend -> AddEntry(h2,s2,"P");
legend -> SetBorderSize(0);
gStyle -> SetLegendTextSize(0.035);

h -> SetFillColorAlpha(kGreen+2,0.5);
h -> SetMarkerColor(kGreen+2);
h -> SetLineWidth(0);
h -> SetMarkerStyle(kFullDotLarge);

h1 -> SetFillColorAlpha(kAzure,0.5);
h1 -> SetMarkerColor(kAzure);
h1 -> SetLineWidth(0);
h1 -> SetMarkerStyle(kFullDotLarge);

h2 -> SetFillColorAlpha(kRed,0.5);
h2 -> SetMarkerColor(kRed);
h2 -> SetLineWidth(0);
h2 -> SetMarkerStyle(kFullDotLarge);


h -> Draw("HIST F");
h1 -> Draw("SAME HIST F");
h2 -> Draw("SAME HIST F");
legend -> Draw("SAME");
}
