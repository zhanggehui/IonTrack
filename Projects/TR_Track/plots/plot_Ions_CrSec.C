{
  gROOT->Reset();
  gROOT->ProcessLine(".L ../plots/Functions/NormlizedByArea.C");

  TCanvas* c1 = new TCanvas("c1", "  ");
  c1->SetLogy(1); c1->SetLogx(1);
  c1->cd();
  c1->Update();

  const int n = 5; 
  TFile* files[n];
  vector<string> fnamevec{"C","N","O","Si","Fe"};
  string suffix=".root";
  TH1D* hists[n];
  THStack* hstack =new THStack("hs", "Enengy Deposited of Different Ions");
  int color[n]={9,2,3,4,6} ;
  for (int i=0 ; i<n; i++)
  {
    files[i]= new TFile( (fnamevec[i]+suffix).c_str() ); 
    hists[i] = (TH1D*)files[i]->Get("h14");
    hists[i]->SetLineColor(color[i]);
    hists[i]->SetLineWidth(3);
    NormlizedByArea(hists[i],1);
    hstack->Add(hists[i]);
  }

  hstack->Draw("nostack HIST C");
  hstack->GetXaxis()->SetTitle("R (nm)");
  hstack->GetYaxis()->SetTitle("E (eV/nm3)");

  
  TLegend* leg=new TLegend();
  vector<string> legstrvec=fnamevec;
  for (int i=0; i<n; i++)
  {
    leg->AddEntry(hists[i],legstrvec[i].c_str(),"l");
  }
  leg->Draw();

} 