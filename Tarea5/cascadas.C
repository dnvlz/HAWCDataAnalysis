#include <iostream>
using namespace std;

void cascadas(){
int n;
cout << "Ingrese número de evento: ";
cin >> n;

// Abrimos el archivo (guardado en la misma carpeta) y creamos árbol
TFile *file = TFile::Open("trig_run009776_00692.root");
TTree *arbol = (TTree*) file -> Get("XCDF");

// Definimos mínimo y máximo del eje x (tiempo en ns)
int ymin = -100; //-100
int ymax = 400; // 400
// Ventana de tiempo de 20ns:
int bins = (ymax-ymin)/20;
TH2F *hist= new TH2F("hist","Detecciones",300,0,1200,bins,ymin,ymax);
hist -> SetStats(0);

// Puede haber un número grande de hits por evento (más que PMTs)
int NumHits = 1500;
// Variable que indica tiempo en ns en que se da el evento
ULong64_t NanoSecond;
arbol -> SetBranchAddress("trig.gpsNanosec",&NanoSecond);
// Tiempo en TDC (posteriormente multiplicamos por 0.1 para pasar a ns)
Long64_t Tiempo[NumHits];
arbol -> SetBranchAddress("trig.hitTime_4Edge",Tiempo);
// Id. del PMT
ULong64_t PMT[NumHits];
arbol -> SetBranchAddress("trig.channelID_4Edge",PMT);
// Corte de calidad
ULong64_t Flags[NumHits];
arbol -> SetBranchAddress("trig.flags_4Edge",Flags);
// 1 si forma parte del trigger, 0 si no
ULong64_t Trigger[NumHits];
arbol -> SetBranchAddress("trig.triggerFlags_4Edge",Trigger);

arbol -> GetEntry(n);
for (Int_t i=0;i<NumHits;i++){
    // // Con cortes de calidad
    // if (Flags[i]==0&Trigger[i]==1&PMT[i]>0&PMT[i]<=1200){
    // Sin cortes de calidad
    if (Trigger[i]==1&PMT[i]>0&PMT[i]<=1200){
        hist -> Fill(PMT[i],Tiempo[i]*0.1,Trigger[i]);
    }
}

int ns = NanoSecond;
TString evento =  Form("#splitline{Evento %d}{GPS: %d ns}",n,ns);
//auto legend = new TLegend(0.72,0.1,0.9,0.2);
auto legend = new TLegend(0.1,0.1,0.28,0.2);
legend->SetHeader(evento,"C");
gStyle->SetLegendTextSize(0.027);

hist -> GetXaxis()->SetTitle("Canal");
hist -> GetYaxis()->SetTitle("Tiempo (ns)");
hist-> Draw("colz");
legend -> Draw("Same");
}