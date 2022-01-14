#include <iostream>
using namespace std;

// DEFINIMOS LOS VECTORES QUE ALMACENARÁN INFORMACIÓN DE ARCHIVO .DAT
const int rows = 786431;
Double_t D[rows], AR[rows], S[rows];
auto legend = new TLegend(.15,.35,.23,.85,"Bin");
TString folder;

/////////////////////////////////////////////////////////////////
// FUNCIÓN QUE CREA HISTOGRAMA DADO NÚMERO DE ARCHIVO COMO ARGUMENTO
TH1F* create_histogram(TString num){
// DEFINIMOS ARCHIVO Y GUARDAMOS INFORMACIÓN EN VECTORES D, AR, S
TString file = folder + "bin" + num + "/tabla_" + num + ".dat" ;
std::ifstream infile(file.Data());
Int_t i = 0;
while(infile >> D[i] >> AR[i] >> S[i] && i<rows)i++;

// LLENADO DE HISTOGRAMA
TH1F *h = new TH1F("","",300,-80,20);
for (Int_t j=0;j<rows;j++){
    if (S[j]!=0)h -> Fill(S[j]);}

// CARACTERÍSTICAS DEL HISTOGRAMA
h -> GetXaxis() -> SetTitle("Significancia [#sigma]");
h -> GetYaxis() -> SetTitle("Cuentas");
h -> SetMarkerStyle(kFullDotLarge);
h -> SetLineWidth(0);
h -> SetStats(0);
h -> Draw("HIST F Same");
legend -> AddEntry(h,num,"p");
return h;
}
/////////////////////////////////////////////////////////////////

// MACRO
void hist_significancia(){
// USUARIO DECIDE QUÉ HISTOGRAMA QUIERE VER
int x;
cout << "Folder: protonlhe (0), nn (1): ";
cin >> x;
TString file;
if (x==0) folder = "Data/luna_protonlhe/";
else if (x==1) folder = "Data/luna_nn/";

TCanvas *c1 = new TCanvas("c1");
// ESCALA LOGARÍTMICA
c1->SetLogy(1);
//////////////////////////////////////////////////////////
TH1F *h0 = create_histogram("0");
h0 -> SetFillColor(kBlack);
h0 -> SetMarkerColor(kBlack);
TH1F *h1 = create_histogram("1");
h1 -> SetFillColor(kViolet+2);
h1 -> SetMarkerColor(kViolet+2);
TH1F *h2 = create_histogram("2");
h2 -> SetFillColor(kAzure);
h2 -> SetMarkerColor(kAzure);
TH1F *h3 = create_histogram("3");
h3 -> SetFillColor(kCyan);
h3 -> SetMarkerColor(kCyan);
TH1F *h4 = create_histogram("4");
h4 -> SetFillColor(kGreen+2);
h4 -> SetMarkerColor(kGreen+2);
TH1F *h5 = create_histogram("5");
h5 -> SetFillColor(kGreen);
h5 -> SetMarkerColor(kGreen);
TH1F *h6 = create_histogram("6");
h6 -> SetFillColor(kOrange);
h6 -> SetMarkerColor(kOrange);
TH1F *h7 = create_histogram("7");
h7 -> SetFillColor(kRed+1);
h7 -> SetMarkerColor(kRed+1);
TH1F *h8 = create_histogram("8");
h8 -> SetFillColor(kMagenta);
h8 -> SetMarkerColor(kMagenta);
TH1F *h9 = create_histogram("9");
h9 -> SetFillColor(kGray);
h9 -> SetMarkerColor(kGray);
//////////////////////////////////////////////////////////

// DIBUJAMOS HISTOGRAMAS
h0 -> Draw("HIST F Same");
h1 -> Draw("HIST F Same");
h2 -> Draw("HIST F Same");
h3 -> Draw("HIST F Same");
h4 -> Draw("HIST F Same");
h5 -> Draw("HIST F Same");
h6 -> Draw("HIST F Same");
h7 -> Draw("HIST F Same");
h8 -> Draw("HIST F Same");
h9 -> Draw("HIST F Same");

legend -> SetBorderSize(0);
legend->Draw("Same");
// TÍTULO DE HISTOGRAMA. GUARDAMOS PDF
if (x==0){
    h0 -> SetTitle("Datos: luna_protonlhe");
    c1 -> SaveAs("hsigma_protonlhe.pdf");}
else if (x==1){
    h0 -> SetTitle("Datos: nn");
    c1 -> SaveAs("hsigma_nn.pdf");}
}