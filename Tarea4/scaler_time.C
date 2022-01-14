#include <iostream>

using namespace std;

void scaler_time(){
// Abrimos el archivo (guardado en la misma carpeta) y creamos árbol
TFile *file = TFile::Open("tdcscaler_run009776_00692.root");
TTree *arbol = (TTree*) file->Get("XCDF");
Int_t entradas = arbol->GetEntries();


// Tiempo de evento en segundos
ULong64_t Second;
arbol->SetBranchAddress("scaler.GPSSecond",&Second);

// Primer evento
arbol->GetEntry(0);
// Tiempo del primer dato
ULong64_t t0 = Second;

// Último evento
arbol->GetEntry(entradas-1);
// Tiempo del último dato
ULong64_t t1 = Second;

// Frecuencia es número total de cuentas sobre tiempo que abarca la toma de datos (0.25 segundos)
cout << "La ventana de tiempo que abarca el archivo es de " << t1-t0 << " segundos." << endl;
cout << "Los datos se tomaron el 2 de enero de 2021 a las 9:30 horas (CDMX).\nGPS time: " << t1 << "." << endl; 
}