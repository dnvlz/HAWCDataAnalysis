#include <iostream>
using namespace std;

// DEFINIMOS LOS VECTORES QUE ALMACENARÁN INFORMACIÓN DE ARCHIVO .DAT
const int rows = 786431;
Double_t D[rows], AR[rows], S[rows];

// MACRO
void deficit_significancia(){
// USUARIO DECIDE DE QUÉ FOLDER SE EXTRAEN DATOS
int x;
cout << "Folder: protonlhe (0), nn (1): ";
cin >> x;
TString folder;
if (x==0) folder = "Data/luna_protonlhe/";
else if (x==1) folder = "Data/luna_nn/";

// INICIALIZACIÓN DE VARIABLES
Double_t min = 0;
Double_t coordAR,coordD;
Int_t bin;

Int_t i;
// ITERAMOS SOBRE LOS ARCHIVOS
for (Int_t k=0;k<10;k++){
    TString num; num.Form("%d",k); 
    // DEFINIMOS ARCHIVO Y GUARDAMOS INFORMACIÓN EN VECTORES D, AR, S
    TString file = folder + "bin" + num + "/tabla_" + num + ".dat" ;
    std::ifstream infile(file.Data());
    i = 0;
    while(infile >> D[i] >> AR[i] >> S[i] && i<rows)i++;
    // BUSCAMOS EL VALOR MÁS PEQUEÑO DE LA SIGNIFICANCIA Y GUARDAMOS
    // INFO. DE ASCENSIÓN RECTA, DECLINACIÓN Y NÚMERO DE BIN
    for (Int_t j=1;j<rows;j++){
        if (S[j]<min){
            min = S[j];
            coordAR = AR[j];
            coordD = D[j];
            bin = k;
        }
    }
}

// IMPRIMIMOS RESULTADOS
cout << "El déficit en significancia es de " << min << endl;
cout << "Bin " << bin << endl;
cout << "Ascensión recta: " << coordAR << "°" << endl;
cout << "Declinación: " << coordD << "°" << endl;
}
