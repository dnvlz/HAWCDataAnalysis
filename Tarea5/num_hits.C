#include <iostream>

using namespace std;

void num_hits(){
// Abrimos el archivo (guardado en la misma carpeta) y creamos árbol
TFile *file = TFile::Open("trig_run009776_00692.root");
TTree *arbol = (TTree*) file->Get("XCDF");

// ULong64_t NumHits;
// arbol -> SetBranchAddress("trig.nHit4Edge",&NumHits);
// //PARA VER QUÉ EVENTOS TIENEN MUCHOS HITS
// Int_t entradas = arbol->GetEntries();
// //Iteramos sobre las entradas
// for(Int_t i=0; i<entradas; i++){
// arbol -> GetEntry(i);
// if (NumHits>1000&NumHits<1100){
// cout << i << " " << NumHits << endl;}
// }

arbol -> GetEntry(0);
arbol -> Show();
}