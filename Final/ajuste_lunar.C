#include <iostream>
using namespace std;

// DEFINIMOS LOS VECTORES QUE ALMACENARÁN INFORMACIÓN DE ARCHIVO .DAT
const int rows = 786431; //wc -l archivo.txt
Double_t D[rows], AR[rows], S[rows];

/////////////////////////////////////////////////////////////////
// GAUSSIANA BIDIMENSIONAL
Double_t gauss2D(Double_t *x, Double_t *par) {
    if(par[2]>0 && par[4]>0){
        Double_t r1 = Double_t((x[0]-par[1])/par[2]);
        Double_t r2 = Double_t((x[1]-par[3])/par[4]);
        return par[0]*exp(-0.5*(r1*r1+r2*r2));
   }
    else return 0;
}
/////////////////////////////////////////////////////////////////

// MACRO
void ajuste_lunar(TString num = "1", TString folder = ""){
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
h -> SetTitle("Ajuste de gaussiana bidimensional a la sombra lunar (bin "+num+")");
h -> GetXaxis()->SetTitle("Declinacion #delta [#circ]");
h -> GetYaxis()->SetTitle("Ascension recta #alpha [#circ]");
h -> SetStats(0);
h -> Draw("colz");

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

TF2 *f; 
// DEFINIMOS FUNCIÓN PARA EL AJUSTE Y LÍMITES EN X E Y
if (num=="4"|num=="3"|num=="6"){f = new TF2("f",gauss2D,-5,5,-4.5,3,5);}
else if (num=="8"|num=="9"){f = new TF2("f",gauss2D,-5,5,-4.5,3.5,5);}
else if (num=="2"){f = new TF2("f",gauss2D,-5,5,-5,3,5);}
else {f = new TF2("f",gauss2D,-5,5,-5.5,2.5,5);}
// INICIALIZACIÓN DE PARÁMETROS
Double_t pars[5] = {-3,0,2,-1,2};
f -> SetParameters(pars);
f -> SetParNames("A_{0}","x_{0}","#sigma_{x}","y_{0}","#sigma_{y}");
// CARACTERÍSTICAS
f -> SetLineColorAlpha(kBlack,0.6);
f -> SetLineWidth(1);
// AJUSTE
h -> Fit("f","R");

// LEYENDAS PARA IDENTIFICAR PARÁMETROS DEL AJUSTE
float parameter, error;
TString parnames[5] = {"A_{0}","x_{0}","#sigma_{x}","y_{0}","#sigma_{y}"};
TString str;
auto legend = new TLegend(0.05,0.68,0.4,0.87);
legend -> SetBorderSize(0);
legend -> SetFillStyle(0);
gStyle -> SetLegendTextSize(0.032);
for (i=0;i<5;i++){
    parameter = f -> GetParameter(i);
    error = f -> GetParError(i);
    str = parnames[i] + ": " + Form("%.2f #pm %.2f",parameter,error);
    legend -> AddEntry(h,str,"");
}
legend -> Draw("same");

// GUARDAMOS PDF DEL AJUSTE
c1 -> SaveAs("fit_"+num+folder+".pdf");
}
