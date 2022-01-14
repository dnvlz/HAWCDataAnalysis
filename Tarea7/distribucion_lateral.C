#include <iostream>
#include <math.h> 
using namespace std;

void distribucion_lateral(){
int x;
cout << "Cascada pequeña (0), mediana (1) o grande (2): ";
cin >> x;
int y;
cout << "Sin ajuste (0). Con ajuste (1): ";
cin >> y;

TFile *file = TFile::Open("recoext_run010222_00692.root");
TTree *arbol = (TTree*) file->Get("XCDF");

int n;
int e1;
if (x==0){
    e1 = 4172;
    n = 708;}
else if (x==1){
    e1 = 4383;
    n = 905;}
else if (x==2){
    e1 = 824;
    n = 1202;}

ULong64_t Event;
arbol -> SetBranchAddress("event.eventID",&Event);
Double_t CoreX;
arbol -> SetBranchAddress("rec.coreX",&CoreX);
Double_t CoreY;
arbol -> SetBranchAddress("rec.coreY",&CoreY);
// Double_t CoreX_error;
// arbol -> SetBranchAddress("coreFit.xCoreUncertainty",&CoreX_error);
// Double_t CoreY_error;
// arbol -> SetBranchAddress("coreFit.yCoreUncertainty",&CoreY_error);
Double_t PosX[n];
arbol -> SetBranchAddress("event.hit.xPMT",PosX);
Double_t PosY[n];
arbol -> SetBranchAddress("event.hit.yPMT",PosY);
Double_t EffCharge[n];
arbol -> SetBranchAddress("event.hit.effcharge",EffCharge);

ULong64_t NumHits;
arbol -> SetBranchAddress("event.nHit",&NumHits);
ULong64_t EventFlags;
arbol -> SetBranchAddress("event.eventFlags",&EventFlags);
ULong64_t gtcFlags;
arbol -> SetBranchAddress("event.gtcFlags",&gtcFlags);
ULong64_t Fidu;
arbol -> SetBranchAddress("rec.coreFiduScale",&Fidu);
ULong64_t isGood[n];
arbol -> SetBranchAddress("event.hit.channelIsGood",isGood);
ULong64_t HitFlags[n];
arbol -> SetBranchAddress("event.hit.flags",HitFlags);
ULong64_t HitTriggerFlags[n];
arbol -> SetBranchAddress("event.hit.triggerFlags",HitTriggerFlags);
ULong64_t AngleIsFit[n];
arbol -> SetBranchAddress("angleFit.isFit",AngleIsFit);

TCanvas *c1 = new TCanvas("c1");

Double_t distX, distY, dist, dist_error, charge, charge_error;
auto p1 = new TGraphErrors();
int i = 0;

arbol -> GetEntry(e1);
// FILTROS Y GRÁFICA
if (EventFlags==0&gtcFlags==0&Fidu<=100){
    for (ULong64_t j=0;j<NumHits;j++){
        if (isGood[j]==1&HitFlags[j]==0&HitTriggerFlags[j]==1&AngleIsFit[j]==1){
            distX = PosX[j]-CoreX;
            distY = PosY[j]-CoreY;
            dist = sqrt(pow(distX,2)+pow(distY,2));
            charge = log10(EffCharge[j]);
            //dist_error = sqrt(pow(distX*CoreX_error,2.)+pow(distY*CoreY_error,2.))/dist;
            charge_error = 0.3-2./3*log10(charge);
            p1 -> SetPoint(i,dist,charge);
            p1->SetPointError(i,0,charge_error);
            i++;
        }
    }
}


// AJUSTES
if (y==1){
    //TF1 *f = new TF1("f", "[2]*x*x + [1]*x + [0]");
    //TF1 *f = new TF1("f", "pow(10,[0]/x)");
    //TF1 *f = new TF1("f", "log10([0]/x)");
    //TF1 *f = new TF1("f", "[1]*x+[0]");
    TF1 *f = new TF1("f", "[0]/x");
    p1 -> Fit("f");}

p1 -> SetMarkerColor(kBlack);
p1 -> SetLineColor(kBlack);
p1 -> SetMarkerStyle(kFullDotMedium);

p1 -> SetTitle("Distribucion lateral");
p1 -> GetXaxis()->SetTitle("Distancia al nucleo (m)");
p1 -> GetYaxis()->SetTitle("log_{10}(Carga efectiva [PEs])");

// LEYENDA CON NÚMERO DE EVENTO Y HITS
auto legend1 = new TLegend(0.1,0.82,0.25,0.9);
TString t1 =  Form("#splitline{Evento %d}{%d hits}",int(Event),n);
legend1 -> AddEntry(p1,t1,"lep");
gStyle -> SetLegendTextSize(0.023);

auto txt = new TLegend(0.67,0.667,0.9,0.88);
TString tx1 = Form("#splitline{Filtros:}{rec.coreFiduScale<=15}");
TString tx2 = Form("#splitline{eventFlags=0}{gtcFlags=0}");
TString tx3 = Form("#splitline{hit.channelIsGood=1}{hit.flags=0}");
TString tx4 = Form("#splitline{event.hit.triggerFlags=1}{angleFit.isFit=1}");
txt -> AddEntry(p1,tx1,"");
txt -> AddEntry(p1,tx2,"");
txt -> AddEntry(p1,tx3,"");
txt -> AddEntry(p1,tx4,"");
txt -> SetBorderSize(0);
txt -> SetFillStyle(0);

p1 -> Draw("AP SAME");
legend1 -> Draw("SAME");
txt -> Draw("SAME");
}