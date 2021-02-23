{
  gROOT->Reset();
  gROOT->ProcessLine(".L ../plots/Functions/NormlizedByArea.C");

  TFile file("Si.root");
  TCanvas* c1 = new TCanvas("c1", "  ");
  c1->SetLogy(1); c1->SetLogx(1);
  c1->cd();
  c1->Update();
  
  THStack* hstack =new THStack("hs","Electron Density");
  const int n=4;
  int index[n]={1,4,7,10};
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
  hstack->GetXaxis()->SetTitleSize(0.04);
  hstack->GetXaxis()->SetLabelSize(0.04);
  hstack->GetYaxis()->SetTitle("Density (nm-3)");
  hstack->GetYaxis()->SetTitleSize(0.04);
  hstack->GetYaxis()->SetLabelSize(0.04);
  hstack->GetYaxis()->SetTitleOffset(1.1);

  TLegend* leg=new TLegend();
  vector<string> legstrvec{"0.5fs","1fs","5fs","25fs"};
  for (int i=0; i<n; i++)
  {
    leg->AddEntry(hists[i],legstrvec[i].c_str(),"l");
  }
  leg->SetTextSize(0.045);
  leg->Draw();
} 
