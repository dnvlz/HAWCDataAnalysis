#include <iostream>

using namespace std;

void scaler_coincidence_value(){
int p, n;
cout << "Primer evento (0) ó último evento (1): ";
cin >> p;
// Dependiendo de respuesta creamos título y variable n que indica evento
if (p==0){n=0;}
else if (p==1){n=999;}

// Abrimos el archivo (guardado en la misma carpeta) y creamos árbol
//tdcscaler_run009776_00001.root
//tdcscaler_run009776_00173.root
//tdcscaler_run009776_00346.root
//tdcscaler_run009776_00519.root
//tdcscaler_run009776_00692.root
TFile *file = TFile::Open("tdcscaler_run009776_00001.root");
TTree *arbol = (TTree*) file->Get("XCDF");
Int_t entradas = arbol->GetEntries();

Int_t Detectores=300;
// Doble coincidencia por detector
ULong64_t Count2[Detectores];
arbol->SetBranchAddress("scaler.multiplicity2Count",Count2);
// Triple coincidencia por detector
ULong64_t Count3[Detectores];
arbol->SetBranchAddress("scaler.multiplicity3Count",Count3);
// Cuadruple coincidencia por detector
ULong64_t Count4[Detectores];
arbol->SetBranchAddress("scaler.multiplicity4Count",Count4);


// n=0 para primer evento, 999 para último evento
arbol -> GetEntry(n);
// Inicializamos para contar coincidencias
ULong64_t Coincidencias2 = 0;
ULong64_t Coincidencias3 = 0;
ULong64_t Coincidencias4 = 0;

// Hay algunos valores muy altos que no forman parte del conteo
// Los filtramos
for (ULong64_t x:Count2){
    if (x<1E10){Coincidencias2 += x;}}
for (ULong64_t x:Count3){
    if (x<1E10){Coincidencias3 += x;}}
for (ULong64_t x:Count4){
    if (x<1E10){Coincidencias4 += x;}}

// Hay 292 detectores WCD. 24 segundos de duración.
cout << "Freq. de coincidencias dobles por detector WCD: " << Coincidencias2/(292*24E3) << " kHz."<< endl;
cout << "Freq. de coincidencias triples por detector WCD: " << Coincidencias3/(292*24E3) << " kHz."<< endl;
cout << "Freq. de coincidencias cuadruples por detector WCD: " << Coincidencias4/(292*24E3) << " kHz."<< endl;
cout << "Freq. de coincidencias totales por detector WCD: " << (Coincidencias2+Coincidencias3+Coincidencias4)/(292*24E3) << " kHz."<< endl;
}