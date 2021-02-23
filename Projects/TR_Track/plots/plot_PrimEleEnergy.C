{
  gROOT->Reset();

  TFile file("Si.root");
  TCanvas* c1 = new TCanvas("c1", " ");
  c1->SetLogy(1); c1->SetLogx(1);
  c1->cd(); c1->Update();

  TH1D* hist = (TH1D*)file.Get("h12");
  hist->SetLineColor(2);
  hist->SetLineWidth(3);
  hist->SetStats(kFALSE);
  hist->Draw("HIST C");
  hist->GetXaxis()->SetTitle("E (eV)");
  hist->GetYaxis()->SetTitle("Counts (/eV)");
}  
