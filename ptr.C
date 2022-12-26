#include <math.h>
#include <TStyle.h>

void PTR(char *arr, char* name){

TFile *f=new TFile("hist1.root"); //import .root file
TTree *tree = (TTree*)f->Get(arr); // use the required tree here
Int_t entries = tree->GetEntries();//get no of entries

const Int_t maxTrack=99999;
   
Int_t ntrack = 0;
Double_t pT[maxTrack];
Double_t phi[maxTrack];

tree->SetBranchAddress("ntrack",&ntrack);//create tree
tree->SetBranchAddress("pT",&pT);
tree->SetBranchAddress("phi",&phi);


TCanvas *c=new TCanvas();

TH1D *htoward = new TH1D("pT towards","pT Towards",100,0.,75.0);
TH1D *haway = new TH1D("pT away","pT Away",100,0.0,75.0);
TH1D *htransverse = new TH1D("pT transverse","pT Tansverse",100,0,75.0);

Int_t pTleadi;				//index of the (leading particle)
for(Int_t ii=0; ii<entries; ii++){  							
    // Event loop starts here
	tree->GetEntry(ii);
	Int_t ntrks = ntrack;

    //find index of leading particle
	pTleadi = 0;

	for(int i=0; i<ntrks; i++) {
		if(pT[pTleadi]<pT[i]) pTleadi=i;
	}

    //partition region
	for(int i=0; i<ntrks; i++){
	  if(TMath::Abs(phi[pTleadi]-phi[i])<1.04719){
        htoward->Fill(pT[i]);}
	  else if(TMath::Abs(phi[pTleadi]-phi[i])>2.09439) {
        haway->Fill(pT[i]);}
		else {
            htransverse->Fill(pT[i]);}
	}
  }

THStack *hspt = new THStack("hspt","pT"); //To stack histograms

//remove title and statistics box
gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);

//add to stack
hspt->Add(htoward);
hspt->Add(haway);
hspt->Add(htransverse);

hspt->Draw();
c->SetLogy(true); //make y axis is logscale

//color histograms
htoward->SetMarkerStyle(kFullCircle);
haway->SetMarkerStyle(kFullSquare);
htransverse->SetMarkerStyle(kFullTriangleUp);
htoward->Draw("PLC PMC");
haway->Draw("SAME PLC PMC");
htransverse->Draw("SAME PLC PMC");

//legend
TLegend *leg=new TLegend(0.9,0.9,0.75,0.78);
   leg->AddEntry(htoward,"Towards","l");
   leg->AddEntry(haway,"Away","l");
   leg->AddEntry(htransverse,"Transverse","l");
   leg->SetTextFont(32);
   leg->SetHeader("PT DISTRIBUTION");
   leg->SetTextFont(42);
   leg->Draw();

c->Print(name);


}
    


void ptr() {

    char trees[6][15] = {
        {"pytree020"}, {"pytree2040"}, {"pytree4060"}, 
        {"pytree6080"}, {"pytree80100"}, {"pytree100"}
    };

    char names[6][50] = {
        {"Ptransverse pytree020.png"}, {"Ptransverse pytree2040.png"},
         {"Ptransverse pytree4060.png"}, {"Ptransverse pytree6080.png"}, 
         {"Ptransverse pytree80100.png"}, {"Ptransverse pytree100.png"}
    };

    for(int c=0; c < 6; c++){ 
        PTR(trees[c], names[c]);
    }

}