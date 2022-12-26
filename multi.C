#include <math.h>
#include <TStyle.h>

void MULTI(char* arr, THStack *hspt1, THStack *hspt2, THStack *hspt3){

TFile *f=new TFile("hist1.root");//import .root file
  TTree *tree = (TTree*)f->Get(arr); // use the required tree here
  Int_t entries = tree->GetEntries();//get no of entries

 const Int_t maxTrack=99999;
   
 Int_t ntrack = 0;
  Double_t pT[maxTrack];
  Double_t eta[maxTrack];
  Double_t phi[maxTrack];


  tree->SetBranchAddress("ntrack",&ntrack);//create tree
  tree->SetBranchAddress("phi",&phi);
  tree->SetBranchAddress("pT",&pT);
  tree->SetBranchAddress("eta",&eta);



TH1D *htoward = new TH1D("pT","pT Towards",1000,0.,10.0);
  TH1D *haway = new TH1D("pT away","pT Away",1000,0.0,10.0);
  TH1D *htransverse = new TH1D("pT transverse","pT Tansverse",1000,0,10.0);

Int_t pTleadi;				//index of the (leading particle)
for(Int_t ii=0; ii<entries; ii++)   
	{  							// Event loop starts here

	tree->GetEntry(ii);
	Int_t ntrks = ntrack;
//find index of leading particle
	pTleadi = 0;

	for(int i=0; i<ntrks; i++) {
		if(pT[pTleadi]<pT[i]) pTleadi=i;
	} //partition region
	for(int i=0; i<ntrks; i++) 
	{
	  if(TMath::Abs(phi[pTleadi]-phi[i])<1.04719){ 
        htoward->Fill(pT[i]);}
	  else if(TMath::Abs(phi[pTleadi]-phi[i])>2.09439) {
        haway->Fill(pT[i]);}
		else {
            htransverse->Fill(pT[i]);
        }
	}
  }







hspt1->Add(htoward);
hspt2->Add(haway);
hspt3->Add(htransverse);



}

void multi(){

    TCanvas *c=new TCanvas();
    //c->SetLogy(true);
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);

    THStack *hspt1 = new THStack("hspt1","pT");
    THStack *hspt2 = new THStack("hspt2","pT");
    THStack *hspt3 = new THStack("hspt3","pT");

    char trees[6][15] = {
        {"pytree020"}, {"pytree2040"}, {"pytree4060"}, 
        {"pytree6080"}, {"pytree80100"}, {"pytree100"}
    };

  

    for(int c=0; c < 6; c++){
 
        MULTI(trees[c], hspt1, hspt2, hspt3);

    }

    hspt1->SetMinimum(0.);
    hspt1->SetMaximum(500000);


    //hspt1->Draw("PLC");
    //hspt2->Draw("PLC");
    hspt3->Draw("PLC");

c->BuildLegend();

}


