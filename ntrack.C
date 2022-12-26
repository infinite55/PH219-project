//Graph of Ntracks of each multiplicity groups

#include <math.h>
#include <TStyle.h>

void NTRACK(char *arr, char* name){

TFile *f=new TFile("hist1.root"); //import .root file
TTree *tree = (TTree*)f->Get(arr); // use the required tree here
Int_t entries = tree->GetEntries(); //get no of entries

Int_t ntrack = 0;

tree->SetBranchAddress("ntrack",&ntrack);//create tree

TCanvas *c=new TCanvas();

TH1D *nt = new TH1D("ntrk","NTrack",250,0,250); //initialize histogram

for(Int_t ii=0; ii<entries; ii++){  							
    // Event loop starts here
	tree->GetEntry(ii);
	Int_t ntrks = ntrack;
    nt->Fill(ntrks); //fill histogram
    }


nt->Draw();

c->Print(name); //save histogram as a png

}

void ntrack() {

    char trees[6][15] = {
        {"pytree020"}, {"pytree2040"}, {"pytree4060"}, 
        {"pytree6080"}, {"pytree80100"}, {"pytree100"}
    };

    char names[6][50] = {
        {"ntark pytree020.png"}, {"ntark pytree2040.png"},
         {"ntark pytree4060.png"}, {"ntark pytree6080.png"}, 
         {"ntark pytree80100.png"}, {"ntark pytree100.png"}
    };

    for(int c=0; c < 6; c++){ 
        NTRACK(trees[c], names[c]);
    }

}












