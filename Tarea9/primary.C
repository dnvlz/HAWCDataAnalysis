
#include <iostream>
using namespace std;

void primary(){
// Abrimos archivo de fotones y protones y creamos un árbol para cada uno
TFile *file1 = TFile::Open("gamma.root");
TFile *file2 = TFile::Open("protons.root");
TTree *arbol1 = (TTree*) file1->Get("XCDF");
TTree *arbol2 = (TTree*) file2->Get("XCDF");

TH1F *h1 = new TH1F("Histograma","",200,-2,6);
TH1F *h2 = new TH1F("Histograma","",200,-2,6);

// Para cada arbol definimos los valores que nos dan la energía y el ángulo zenital,
// esto con el objetivo de aplicar filtros al llenar los histogramas
Double_t logEnergy1;
arbol1 -> SetBranchAddress("mc.logEnergy",&logEnergy1);
Double_t logEnergy2;
arbol2 -> SetBranchAddress("mc.logEnergy",&logEnergy2);

Double_t Zenith1;
arbol1 -> SetBranchAddress("mc.zenithAngle",&Zenith1);
Double_t Zenith2;
arbol2 -> SetBranchAddress("mc.zenithAngle",&Zenith2);


//////////////////////////////////////////////////////////////////////////////
// LAS DISTRIBUCIONES ESTÁN BIEN SEPARADAS PERO PARECE QUE LA RECONSTRUCCIÓN MANDA 
// EN ALGUNO DE LOS CASOS (FOTONES O PROTONES) TODOS LOS DATOS A UN MISMO VALOR
//TString var = "rec.LHLatDistFitEnergy";
TString var = "rec.logCoreAmplitude";
Double_t Var1;
arbol1 -> SetBranchAddress(var,&Var1);
Double_t Var2;
arbol2 -> SetBranchAddress(var,&Var2);

// EN HITSP20 ESTÁ BIEN SEPARADA LA DISTRIBUCION
// EN WINDOWSHITS ESTÁ MEJOR QUE EN HITSP20 PORQUE LA DISTRIBUCIÓN DE FOTONES EMPIEZA DESPUÉS
// EN TANKHITTOT Y FIDUSCALE LAS DISTRIBUCIONES SE EMPALMAN BASTANTE
//TString var = "rec.nHitSP20";
//TString var = "rec.windowHits";
//TString var = "rec.nTankHitTot";
//TString var = "rec.coreFiduScale";
// ULong64_t Var1;
// arbol1 -> SetBranchAddress(var,&Var1);
// ULong64_t Var2;
// arbol2 -> SetBranchAddress(var,&Var2);
//////////////////////////////////////////////////////////////////////////////


// Llenamos primer histograma, i.e. de fotones
Int_t entradas1 = arbol1 -> GetEntries();
for (Int_t i=0;i<entradas1;i++){
    arbol1 -> GetEntry(i);
    double Energy1 = pow(10,logEnergy1)*1E-3;
    if (Energy1>1&Energy1<50&Zenith1<20){
        h1->Fill(Var1);
    }
}

// Llenamos segundo histograma, i.e. de protones
Int_t entradas2 = arbol2 -> GetEntries();
for (Int_t i=0;i<entradas2;i++){
    arbol2 -> GetEntry(i);
    double Energy2 = pow(10,logEnergy2)*1E-3;
    if (Energy2>1&Energy2<50&Zenith2<20){
        h2->Fill(Var2);
    }
}

h1 -> SetTitle("Histograma de variable reconstruida");
h1 -> GetXaxis()->SetTitle(var);
h2 -> SetTitle("Histograma de variable reconstruida");
h2 -> GetXaxis()->SetTitle(var);

TString filtro1 = "Fotones";
TString filtro2 = "Protones";
auto legend = new TLegend(0.73,0.76,0.86,0.87);
legend -> AddEntry(h1,filtro1,"P");
legend -> AddEntry(h2,filtro2,"P");
legend -> SetBorderSize(0);
gStyle -> SetLegendTextSize(0.035);

TString filtro = "#splitline{Energias entre 1 y 50 TeV}{Angulo azimutal menor a 20#circ}";
auto legend2 = new TLegend(0.33,0.81,0.5,0.86);
legend2 -> AddEntry(h2,filtro,"");
legend2 -> SetBorderSize(0);

h1 -> SetLineColor(kAzure);
h1 -> SetFillColorAlpha(kAzure,0.5);
h1 -> SetMarkerColor(kAzure);
h1 -> SetLineWidth(1);
h1 -> SetMarkerStyle(kFullDotLarge);

h2 -> SetLineColor(kRed);
h2 -> SetFillColorAlpha(kRed,0.5);
h2 -> SetMarkerColor(kRed);
h2 -> SetLineWidth(1);
h2 -> SetMarkerStyle(kFullDotLarge);


h1 -> SetStats(0);
h2 -> SetStats(0);
h1 -> Scale(1.0/h1->GetEntries());
h2 -> Scale(1.0/h2->GetEntries());
h1 -> Draw("HIST F");
h2 -> Draw("SAME HIST F");
legend -> Draw("Same");
legend2 -> Draw("Same");
}
