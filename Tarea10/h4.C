#include <iostream>
using namespace std;

void h4(){
int xmax;
cout << "Hasta qué valor de la masa muestra el histograma? ";
cin >> xmax;

TString file = "CMSMuon.txt";
const int maxrows = 100000; //wc -l archivo.txt
Float_t Run[maxrows], Event[maxrows], E1[maxrows], px1[maxrows], py1[maxrows], pz1[maxrows], pt1[maxrows], eta1[maxrows], phi1[maxrows], Q1[maxrows], E2[maxrows], px2[maxrows], py2[maxrows], pz2[maxrows], pt2[maxrows], eta2[maxrows], phi2[maxrows], Q2[maxrows], M[maxrows]; //2 variables de punto flotante
char Type1[maxrows], Type2[maxrows];
Int_t i = 0;
std::ifstream infile(file.Data());

//Llenando los arreglos con la información de cada evento
while(infile >> Run[i] >> Event[i] >>  Type1[i] >> E1[i] >> px1[i] >> py1[i] >> pz1[i] >> pt1[i] >> eta1[i] >> phi1[i] >> Q1[i] >> Type2[i] >> E2[i] >> px2[i] >> py2[i] >> pz2[i] >> pt2[i] >> eta2[i] >> phi2[i] >> Q2[i] >> M[i] && i < maxrows ){
    i++;}

int bins = xmax*5;
TH1F *h = new TH1F("Histograma","",bins,0,xmax);

Float_t p_squared;
Float_t E_squared;
Float_t m0;

for (Int_t j=0;j<maxrows;j++){
    if (Q1[j]*Q2[j]<0){
        p_squared = pow(px1[j]+px2[j],2)+pow(py1[j]+py2[j],2)+pow(pz1[j]+pz2[j],2);
        E_squared = pow(E1[j]+E2[j],2);
        m0 = pow(E_squared-p_squared,1/2.);
        h -> Fill(m0);
    }
}


h -> SetTitle("Histograma de masa invariante para eventos de par muon-antimuon");
h -> GetXaxis() -> SetTitle("Masa invariante [GeV]");
h -> SetMinimum(0);

h -> SetFillColor(kGreen+2);
h -> SetMarkerColor(kGreen+2);
h -> SetLineWidth(0);
h -> SetMarkerStyle(kFullDotLarge);

h -> Scale(1.0/h->GetEntries());
h -> Draw("HIST F");
}
