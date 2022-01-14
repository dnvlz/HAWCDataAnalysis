#include <iostream>
using namespace std;

// creamos histograma que toma variables
// x: determina si queremos graficar dobles, triples o cuádruples coincidencias
// n: especifica evento (comienza en 0)
// archivo: nombre del subrun
TH1F* create_histogram(int x, int n, char const *archivo){
TFile *file = TFile::Open(archivo);
TTree *arbol = (TTree*) file->Get("XCDF");

// Variable que indica id. del detector (WCD)
Int_t Detectores=300;
ULong64_t Tanque[Detectores];
arbol->SetBranchAddress("scaler.tankID",Tanque);

// Dependiendo del valor de x graficamos doble triple o cuadruple coincidencia
ULong64_t Conteo[Detectores];
if(x==2){arbol->SetBranchAddress("scaler.multiplicity2Count",Conteo);}
if(x==3){arbol->SetBranchAddress("scaler.multiplicity3Count",Conteo);}
if(x==4){arbol->SetBranchAddress("scaler.multiplicity4Count",Conteo);}

auto h = new TH1F("h","h",300+10,0-5.5,300+5.5);
//Evento n
arbol -> GetEntry(n);
// Iteramos sobre detectores
for (Int_t j=0;j<Detectores; j++){
        double Freq = Conteo[j];
        if (Freq<1E10&Tanque[j]!=150){h->Fill(Tanque[j],Freq/(24.0E3));}}
h->Draw("HIST F Same");
return h;
}

void scaler_subruns(){
int x;
cout << "Histograma de dobles (2), triples (3) o cuádruples (4) coincidencias: ";
cin >> x;
int p,n;
string title;
cout << "Primer evento (0) ó último evento (1): ";
cin >> p;
// Dependiendo de respuesta creamos variable n que indica evento
if (p==0){n=0;}
else if (p==1){n=999;}

// Creamos un histograma para cada subrun y les ponemos colores distintos
TH1F *h1= new TH1F("h1","h1",300+10,0-5.5,300+5.5);
h1 = create_histogram(x,n,"tdcscaler_run009776_00001.root");
h1->SetLineColorAlpha(kRed,0.6);
TH1F *h2= new TH1F("h2","h2",300+10,0-5.5,300+5.5);
h2 = create_histogram(x,n,"tdcscaler_run009776_00173.root");
h2->SetLineColorAlpha(kAzure,0.6);
TH1F *h3= new TH1F("h3","h3",300+10,0-5.5,300+5.5);
h3 = create_histogram(x,n,"tdcscaler_run009776_00346.root");
h3->SetLineColorAlpha(kGreen,0.6);
TH1F *h4= new TH1F("h4","h4",300+10,0-5.5,300+5.5); 
h4 = create_histogram(x,n,"tdcscaler_run009776_00519.root");
h4->SetLineColorAlpha(kBlack,0.6);
TH1F *h5= new TH1F("h5","h5",300+10,0-5.5,300+5.5);
h5 = create_histogram(x,n,"tdcscaler_run009776_00692.root");
h5->SetLineColorAlpha(kOrange,0.6);

auto legend = new TLegend(.2,.15,.35,.53,"Subruns");
legend->AddEntry(h1,"001","l");
legend->AddEntry(h2,"173","l");
legend->AddEntry(h3,"346","l");
legend->AddEntry(h4,"519","l");
legend->AddEntry(h5,"692","l");

// Dependiendo de respuesta creamos título y variable n que indica evento
if (n==0&x==2){h1->SetTitle("Dobles coincidencias (primer evento)");}
if (n==0&x==3){h1->SetTitle("Triples coincidencias (primer evento)");}
if (n==0&x==4){h1->SetTitle("Cuadruples coincidencias (primer evento)");}
if (n==999&x==2){h1->SetTitle("Dobles coincidencias (ultimo evento)");}
if (n==999&x==3){h1->SetTitle("Triples coincidencias (ultimo evento)");}
if (n==999&x==4){h1->SetTitle("Cuadruples coincidencias (ultimo evento)");}

h1-> SetStats(0);
h1 -> GetYaxis()->SetTitle("Frecuencia de Conteo (kHz)");
h1 -> GetXaxis()->SetTitle("Detector id.");
legend->Draw("Same");
}