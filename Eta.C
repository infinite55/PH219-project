#include <math.h>
#include <TStyle.h>

void ETA(char* arr, char* name){

TFile *f=new TFile("hist1.root"); //import .root file
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

TCanvas *c=new TCanvas();

  
TH1D *ntransverse = new TH1D("eta transverse","Eta Tansverse",200,-3, 3);
TH1D *ntoward = new TH1D("eta towards","Eta Towards",200,-3, 3);
TH1D *naway = new TH1D("eta away","Eta Away",200,-3, 3);
  
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
	for(int i=0; i<ntrks; i++) 
	{
	  if(TMath::Abs(phi[pTleadi]-phi[i])<1.04719){ 
        ntoward->Fill(eta[i]);}
	  else if(TMath::Abs(phi[pTleadi]-phi[i])>2.09439){
        naway->Fill(eta[i]);}
	  else {
            ntransverse->Fill(eta[i]);}
	}
  }

//remove title and statistics box
gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);

THStack *hseta = new THStack("hseta","eta"); //To stack histograms

//add to stack
hseta->Add(naway);
hseta->Add(ntoward);
hseta->Add(ntransverse);

hseta->Draw();

//color histograms
ntoward->SetMarkerStyle(kFullCircle);
naway->SetMarkerStyle(kFullSquare);
ntransverse->SetMarkerStyle(kFullTriangleUp);
naway->Draw("PLC PMC");
ntoward->Draw("SAME PLC PMC");
ntransverse->Draw("SAME PLC PMC");

//legend
TLegend *leg=new TLegend(0.84,0.85,0.98,0.99);
   leg->AddEntry(ntoward,"Towards","l");
   leg->AddEntry(naway,"Away","l");
   leg->AddEntry(ntransverse,"Transverse","l");
   leg->SetTextFont(32);
   leg->SetHeader("ETA DISTRIBUTION");
   leg->SetTextFont(42);
   leg->Draw();

c->Print(name);

}

void Eta() {

    char trees[6][15] = {
        {"pytree020"}, {"pytree2040"}, {"pytree4060"}, 
        {"pytree6080"}, {"pytree80100"}, {"pytree100"}
    };

    char names[6][50] = {
        {"n pytree020.png"}, {"n pytree2040.png"},
         {"n pytree4060.png"}, {"n pytree6080.png"}, 
         {"n pytree80100.png"}, {"n pytree100.png"}
    };

    for(int c=0; c < 6; c++){ 
        ETA(trees[c], names[c]);
    }

}










