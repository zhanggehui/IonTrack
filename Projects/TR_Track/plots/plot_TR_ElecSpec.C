{
  gROOT->Reset();
  
  TFile file("Si.root");
  TCanvas* c1 = new TCanvas("c1", "  ");
  c1->SetLogy(1); 
  c1->SetLogx(1);
  c1->cd();
  
  THStack* hstack =new THStack("hs","Electron Energy Spectrum");
  const int n = 4; 
  int index[n]={0,3,6,9};
  TH1D* hists[n]; char hname[50];
  for (int i=0 ; i<n; i++)
  { 
    sprintf(hname,"h%d", index[i]);
    hists[i]=(TH1D*)file.Get(hname);
    hists[i]->SetLineColor(i+2);
    hists[i]->SetLineWidth(3);
    hstack->Add(hists[i]);
  }

  hstack->Draw("nostack HIST C");
  hstack->GetXaxis()->SetTitle("E (eV)");
  hstack->GetXaxis()->SetTitleSize(0.04);
  hstack->GetXaxis()->SetLabelSize(0.04);
  hstack->GetYaxis()->SetTitle("Counts (/eV)");
  hstack->GetYaxis()->SetTitleSize(0.04);
  hstack->GetYaxis()->SetLabelSize(0.04);
  hstack->GetYaxis()->SetTitleOffset(0.9);

  TLegend* leg=new TLegend();
  vector<string> legstrvec{"0.5fs","1fs","5fs","25fs"};
  for (int i=0; i<n; i++)
  {
    TLegendEntry *entry=leg->AddEntry(hists[i],legstrvec[i].c_str());
  }
  leg->SetTextSize(0.045);
  leg->Draw();
}