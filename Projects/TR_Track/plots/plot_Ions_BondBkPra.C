{
  gROOT->Reset();
  gROOT->ProcessLine(".L ../plots/Functions/NormlizedByArea.C");
  gROOT->ProcessLine(".L ../plots/Functions/GetProbabilityProfile.C");

  TCanvas* c1 = new TCanvas("c1", "  ");
  c1->SetLogx(1);
  c1->cd(); c1->Update();

  const int n = 5; 
  TFile* files[n];
  vector<string> fnamevec{"C","N","O","Si","Fe"}; string suffix=".root";
  TH1D* hists[n];
  TGraph* grs[n];
  for (int i=0 ; i<n; i++)
  {
    files[i]= new TFile( (fnamevec[i]+suffix).c_str() ); 
    hists[i] = (TH1D*)files[i]->Get("h14");
    NormlizedByArea(hists[i],1);
    grs[i]=GetProbabilityProfile(hists[i],1);
  }
  
  TMultiGraph *mg = new TMultiGraph();
  int color[n]={9,2,3,4,6} ;
  for (int i=0; i<n; i++)
  {
    grs[i]->SetLineColor(color[i]);
    grs[i]->SetLineWidth(3);
    mg->Add(grs[i]);
  }

  mg->Draw("ALP");
  mg->SetTitle("Probability Profile");
  mg->GetXaxis()->SetTitle("R (nm)");
  mg->GetYaxis()->SetTitle("Probability");

  TLegend* leg=new TLegend();
  vector<string> legstrvec=fnamevec;
  for (int i=0; i<n; i++)
  {
    leg->AddEntry(grs[i],legstrvec[i].c_str(),"l");
  }
  leg->Draw();

} 