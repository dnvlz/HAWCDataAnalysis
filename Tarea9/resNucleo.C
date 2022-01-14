#include <iostream>
using namespace std;

void resNucleo(){
// DATOS INTRODUCIDOS EN LA TERMINAL PARA DECIDIR QUÉ HISTOGRAMA SE MUESTRA
int x;
cout << "Cascada contenida <50 (0) o contenida <100 (1): ";
cin >> x;
int axis;
cout << "Eje x (0) o eje y (1): ";
cin >> axis;

TFile *file = TFile::Open("gamma.root");
TTree *arbol = (TTree*) file->Get("XCDF");

// CODIGO PARA IDENTIFICAR MINIMO Y MAXIMO PARA GRAFICAR
// int maxX=0, maxY=0;
// Int_t entradas = arbol -> GetEntries();
// for (Int_t i=0;i<entradas;i++){
//     arbol -> GetEntry(i);
//     double ResX = abs(CoreX-SimX*1E-3);
//     double ResY = abs(CoreY-SimY*1E-3);
//     if (Fidu<100){
//         if (ResX>maxX) {maxX=ResX;}
//         if (ResY>maxY) {maxY=ResY;}
//         }
// }

// DEPENDIENDO QUÉ EJE SE DESEA GRAFICAR, LOS LIMITES DEL HISTOGRAMA CAMBIAN
int max;
if (axis==0){max = 241;}
else if (axis==1){max = 373;}
TH1F *h= new TH1F("Histograma","",100,0,max);

// POSICION DEL NUCLEO: RECONSTRUCCION
Double_t CoreX;
arbol -> SetBranchAddress("rec.coreX",&CoreX);
Double_t CoreY;
arbol -> SetBranchAddress("rec.coreY",&CoreY);
// POSICION DEL NUCLEO: SIMULACION
Double_t SimX;
arbol -> SetBranchAddress("mc.coreX",&SimX);
Double_t SimY;
arbol -> SetBranchAddress("mc.coreY",&SimY);
// CONTENCION DE LA CASCADA
ULong64_t Fidu;
arbol -> SetBranchAddress("rec.coreFiduScale",&Fidu);

// LLENAMOS FILTROS DEFINIENDO RESOLUCION Y APLICANDO FILTROS CORRESPONDIENTES
Int_t entradas = arbol -> GetEntries();
for (Int_t i=0;i<entradas;i++){
    arbol -> GetEntry(i);
    double ResX = abs(CoreX-SimX);
    double ResY = abs(CoreY-SimY);
    if ((axis==0)&((x==0&Fidu<50)|(x==1&Fidu<100))){h -> Fill(ResX);}
    else if ((axis==1)&((x==0&Fidu<50)|(x==1&Fidu<100))){h -> Fill(ResY);}
}

TString filtro;
if (x==0){filtro = "rec.coreFiduScale<50";}
if (x==1){filtro = "rec.coreFiduScale<100";}
auto legend = new TLegend(0.4,0.82,0.5,0.87);
legend -> AddEntry(h,filtro,"");
legend -> SetBorderSize(0);
gStyle -> SetLegendTextSize(0.027);


if (axis==0){
    h -> SetTitle("Resolucion en X para reconstruir nucleos de cascadas iniciadas por fotones");
    h -> GetXaxis()->SetTitle("x (m)");}
if (axis==1){
    h -> SetTitle("Resolucion en Y para reconstruir nucleos de cascadas iniciadas por fotones");
    h -> GetXaxis()->SetTitle("y (m)");};


h -> SetLineColor(kAzure);
h -> SetFillColor(kAzure);
h -> Draw("HIST F");
legend -> Draw("Same");
}
