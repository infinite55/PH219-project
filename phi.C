#include <math.h>
#include <TStyle.h>

void PHI(char* arr, char* name){

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

TCanvas *c=new TCanvas();

TH1D *ptoward = new TH1D("phi","Phi Towards",100,-4, 4);
TH1D *paway = new TH1D("phi away","Phi Away",100,-4, 4);
TH1D *ptransverse = new TH1D("phi transverse","Phi Tansverse",100,-4, 4);

Int_t pTleadi;				//index of the (leading particle)
for(Int_t ii=0; ii<entries; ii++){  							
    // Event loop starts here
	tree->GetEntry(ii);
	Int_t ntrks = ntrack;


    //find index of leading particle
	pTleadi = 0;

	for(int i=0; i<ntrks; i++){
		if(pT[pTleadi]<pT[i]) pTleadi=i;
	} 
    
    
    //partition region
	for(int i=0; i<ntrks; i++){
	  if(TMath::Abs(phi[pTleadi]-phi[i])<1.04719){ 
        ptoward->Fill(phi[i]);}
	  else if(TMath::Abs(phi[pTleadi]-phi[i])>2.09439) {
        paway->Fill(phi[i]);}
		else {
            ptransverse->Fill(phi[i]);}
	}
  }

THStack *hsphi = new THStack("hsphi","phi"); //To stack histograms

//remove title and statistics box
gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);

//add to stack
hsphi->Add(ptoward);
hsphi->Add(paway);
hsphi->Add(ptransverse);

hsphi->Draw();
c->SetLogy(true); //make y axis is logscale

//color histograms
ptoward->SetMarkerStyle(kFullCircle);
paway->SetMarkerStyle(kFullSquare);
ptransverse->SetMarkerStyle(kFullTriangleUp);
ptoward->Draw("PLC PMC");
paway->Draw("SAME PLC PMC");
ptransverse->Draw("SAME PLC PMC");

//legend
TLegend *leg=new TLegend(0.84,0.85,0.98,0.99);
   leg->AddEntry(ptoward,"Towards","l");
   leg->AddEntry(paway,"Away","l");
   leg->AddEntry(ptransverse,"Transverse","l");
   leg->SetTextFont(32);
   leg->SetHeader("PHI DISTRIBUTION");
   leg->SetTextFont(42);
   leg->Draw();

c->Print(name);

}


void phi() {

    char trees[6][15] = {
        {"pytree020"}, {"pytree2040"}, {"pytree4060"}, 
        {"pytree6080"}, {"pytree80100"}, {"pytree100"}
    };

    char names[6][50] = {
        {"phi pytree020.png"}, {"phi pytree2040.png"},
         {"phi pytree4060.png"}, {"phi pytree6080.png"}, 
         {"phi pytree80100.png"}, {"phi pytree100.png"}
    };

    for(int c=0; c < 6; c++){ 
        PHI(trees[c], names[c]);
    }

}


