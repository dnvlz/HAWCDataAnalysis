#include <iostream>
using namespace std;

// DEFINIMOS LOS VECTORES QUE ALMACENARÁN INFORMACIÓN DE ARCHIVO .DAT
const int rows = 786431;
Double_t D[rows], AR[rows], S[rows];

// MACRO
void mapa_lunar(int suavizado = 99, TString num = "1", TString folder = ""){
if (suavizado==99){
cout << "Suavizado: no (0), sí (1): ";
cin >> suavizado;}

TCanvas *c1 = new TCanvas("c1","c1");
c1->cd();

// DEFINIMOS ARCHIVO Y GUARDAMOS INFORMACIÓN EN VECTORES D, AR, S
TString file = "Data/luna_protonlhe" + folder + "/bin" + num + "/tabla_" + num + ".dat" ;
std::ifstream infile(file.Data());
Int_t i = 0;
while(infile >> D[i] >> AR[i] >> S[i] && i<rows)i++;

// CREAMOS HISTOGRAMA Y LLENAMOS CON DATOS DE ARCHIVO .DAT
int numbins = 115;
TH2F *h = new TH2F("","",numbins,-10,10,numbins,-10,10);
for (Int_t j=0;j<rows;j++){
    if (S[j]!=0)h -> Fill(D[j],AR[j],S[j]);}

// CARACTERÍSTICAS DEL HISTOGRAMA
h -> SetTitle("Mapa lunar (bin "+num+")");
h -> GetXaxis()->SetTitle("Declinacion #delta [#circ]");
h -> GetYaxis()->SetTitle("Ascension recta #alpha [#circ]");
h -> SetStats(0);
h -> Draw("colz");

if (suavizado==1){
    // SUAVIZADO
    Double_t mean;
    // EN LA REGIÓN INTERIOR (NO BORDES) ASIGNAMOS VALORES A BINS VACÍOS PROMEDIANDO LOS CUATRO ADYACENTES
    for (Int_t m=2;m<numbins;m++){
        for (Int_t n=2;n<numbins;n++){
            mean = 0;
            if ((h->GetBinContent(m,n)==0)&(n!=26)){
                mean += h -> GetBinContent(m+1,n)/4.0;
                mean += h -> GetBinContent(m-1,n)/4.0;
                mean += h -> GetBinContent(m,n+1)/4.0;
                mean += h -> GetBinContent(m,n-1)/4.0;
                h -> SetBinContent(m,n,mean);
            }  
            if (n==26){
                // N=26 CONTIENE SÓLO BINS VACÍOS
                if (h -> GetBinContent(m,n+1)!=0&h -> GetBinContent(m,n-1)!=0){
                    mean += h -> GetBinContent(m,n+1)/2.0;
                    mean += h -> GetBinContent(m,n-1)/2.0;
                    h -> SetBinContent(m,n,mean);}
                else if (h -> GetBinContent(m,n-1)!=0){
                    mean += h-> GetBinContent(m+1,n+1)/3.0;
                    mean += h-> GetBinContent(m-1,n+1)/3.0;
                    mean += h-> GetBinContent(m,n-1)/3.0;
                    h -> SetBinContent(m,n,mean);}
                else if (h -> GetBinContent(m,n+1)!=0){
                    mean += h-> GetBinContent(m+1,n-1)/3.0;
                    mean += h-> GetBinContent(m-1,n-1)/3.0;
                    mean += h-> GetBinContent(m,n+1)/3.0;
                    h -> SetBinContent(m,n,mean);}
            }
        }
    }
    // SUAVIZADO PARA LOS BORDES: ASIGNAMOS VALOR DE BIN ADYACENTE
    for (Int_t p=1;p<=numbins;p++){
        h -> SetBinContent(numbins,p,h->GetBinContent(numbins-1,p));
        h -> SetBinContent(1,p,h->GetBinContent(2,p));
        h -> SetBinContent(p,numbins,h->GetBinContent(p,numbins-1));
        h -> SetBinContent(p,1,h->GetBinContent(p,2));
    }
}

// GUARDAMOS PDF DEL MAPA
c1 -> SaveAs("map_"+num+folder+".pdf");
}
