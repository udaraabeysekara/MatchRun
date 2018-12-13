readAnasum(){
//readfile("CrabMSCW1_2.2.root");
readfile("GemingaV5MSCW1_2.2.root");
}

void readfile(TString filename){
TFile *f = new TFile(filename);
TTree *treeSummary = (TTree*)f->Get("total_1/stereo/tRunSummary");
Int_t runOn =0,Total=0;
Double_t El=0,elevationOn=0,elevationOff=0,ElSelected=0;
Double_t WobbleNorth=0,WobbleWest=0, MJDOn=0;
Double_t DeadTimeFracOn=0, tOn=0;

Double_t countrate=0;

treeSummary->SetBranchAddress("runOn",&runOn);
treeSummary->SetBranchAddress("elevationOn",&elevationOn);
treeSummary->SetBranchAddress("elevationOff",&elevationOff);
treeSummary->SetBranchAddress("WobbleNorth",&WobbleNorth);
treeSummary->SetBranchAddress("WobbleWest",&WobbleWest);
treeSummary->SetBranchAddress("MJDOn", &MJDOn);
treeSummary->SetBranchAddress("DeadTimeFracOn",&DeadTimeFracOn);
treeSummary->SetBranchAddress("tOn",&tOn);

Int_t nevent = treeSummary->GetEntries();
for(Int_t i=0;i<nevent;i++){
	Total = 0;
	treeSummary->GetEntry(i);
        if(runOn>0){
		treepath = Form("run_%d/stereo/data_off",runOn);
		histpath = Form("run_%d/stereo/skyHistograms/hmap_stereoUC_off",runOn);

		TTree *treeA = (TTree*)f->Get(treepath);
		treeA->SetBranchAddress("El",&El);

		TH2D *hmap_stereoUC_off = (TH2D*)f->Get(histpath);	
	
		for(Int_t j=1;j<TMath::Sqrt(hmap_stereoUC_off->GetSize());j++){
			for(Int_t k=1;k<TMath::Sqrt(hmap_stereoUC_off->GetSize());k++){
				Total += hmap_stereoUC_off->GetBinContent(j,k);				
			}
		}		
	//	cout<<runOn<<"\t"<<Total<<"\t"<<TMath::Max(elevationOn,elevationOff)<<"\t"<<WobbleNorth<<"\t"<<WobbleWest<<"\t"<<MJDOn<<endl;		
		countrate = 60*20*(Total/tOn*(1-DeadTimeFracOn));//Here I used the count rate per 20 mins. Just because most of the Geminga runs are 20 mins
		cout<<runOn<<"\t"<<countrate<<"\t"<<TMath::Max(elevationOn,elevationOff)<<"\t"<<WobbleNorth<<"\t"<<WobbleWest<<"\t"<<MJDOn<<"\t"<<endl;	
	}
}

/*TString treepath("");
treepath = Form("run_%d/stereo/data_off",runOn);

TTree *treeA = (TTree*)f->Get(treepath);

Double_t  MSCW = 0;
treeA->SetBranchAddress("MSCW",&MSCW);
Int_t nevent = treeA->GetEntries();

TH1D *h1 = new TH1D("h1", "MSCW", 10, 0.7, 10);

for(Int_t i=0;i<nevent; i++){
	treeA->GetEntry(i);	
	h1->Fill(MSCW);
}
return h1;
*/
}
