{
  gROOT->Reset();
  gROOT->ProcessLine(".L ../plots/Functions/NormlizedByArea.C");

  TFile file("Si_0.root");
  TCanvas* c1 = new TCanvas("c1", "  ");
  c1->SetLogy(1); c1->SetLogx(1);
  c1->cd();
  c1->Update();
  
  THStack* hstack =new THStack("hs", "Enengy Deposited");
  const int n=5;
  int index[n]={2,5,8,11,14};
  TH1D* hists[n]; char hname[50];
  double unitscale=1.;
  for (int i=0 ; i<n; i++)
  { 
    sprintf(hname,"h%d", index[i]);
    hists[i]=(TH1D*)file.Get(hname);
    hists[i]->SetLineColor(i+1);
    hists[i]->SetLineWidth(3);
    NormlizedByArea(hists[i],unitscale);
    hstack->Add(hists[i]);
  }

  hstack->Draw("nostack HIST C");
  hstack->GetXaxis()->SetTitle("R (nm)");
  hstack->GetYaxis()->SetTitle("E (eV/nm3)");

  TLegend* leg=new TLegend();
  vector<string> legstrvec{"0.5fs","1fs","5fs","25fs","total"};
  for (int i=0; i<n; i++)
  {
    leg->AddEntry(hists[i],legstrvec[i].c_str(),"l");
  }
  leg->Draw();
}
