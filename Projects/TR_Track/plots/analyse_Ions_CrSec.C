{
  gROOT->Reset();
  gROOT->ProcessLine(".L ../plots/Functions/NormlizedByArea.C");
  gROOT->ProcessLine(".L ../plots/Functions/Integral_CrSec.C");
  
  TCanvas* c1 = new TCanvas("c1", "  ");
  c1->cd();
  c1->Update();

  const int n = 5; 
  TFile* files[n];
  vector<string> fnamevec{"C","N","O","Si","Fe"};  
  string suffix=".root";
  TH1D* hists[n];
  double CrSec[n+1];CrSec[0]=0;
  for (int i=0 ; i<n; i++)
  {
    files[i]= new TFile( (fnamevec[i]+suffix).c_str() ); 
    hists[i]=(TH1D*)files[i]->Get("h14");
    NormlizedByArea(hists[i],1);
    CrSec[i+1]=Integral_CrSec(hists[i],1);
  }

  double dedx[n+1]={0,0.758,0.987,1.18,2.726,6.023}; 
  TGraph *gr= new TGraph(n+1,dedx,CrSec);
  gr->SetLineColor(8);
  gr->SetLineWidth(3);
  gr->SetMarkerStyle(2);
  gr->SetMarkerSize(2); 
  gr->SetMarkerColor(4);

  double experimentdedx[]={0.06569,0.14194,0.25208,0.3834,0.59098,0.79996,
                           0.97506,1.70792,2.14566,2.61729,2.9336,3.29509,
                           3.60151,3.89804,4.4784,4.7947,5.07994,5.52898,
                           5.82551,6.19124,6.53437,6.8888}; 
  double experimentcs[]={1.57043,6.97164,11.11553,15.11785,19.98934,24.15016,
                         27.52876,41.07221,47.73847,54.48276,58.62264,64.28268,
                         67.88635,71.1051,78.3348,82.30779,85.8482,90.54859,
                         93.70562,97.83404,100.9708,103.64684};

  TGraph *experimentgr= new TGraph(22,experimentdedx,experimentcs);
  experimentgr->SetLineColor(7);
  experimentgr->SetLineWidth(3);
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gr);
  mg->Add(experimentgr);
  mg->Draw("ACP");
  mg->SetTitle("CrSection vs. Spower");
  mg->GetXaxis()->SetTitle("dE/dX (keV/nm)");
  mg->GetXaxis()->SetTitleSize(0.04);
  mg->GetXaxis()->SetLabelSize(0.04);
  mg->GetYaxis()->SetTitle("CrSection (nm2)");
  mg->GetYaxis()->SetTitleSize(0.04);
  mg->GetYaxis()->SetLabelSize(0.04);

  TLegend* leg=new TLegend();
  leg->AddEntry(gr,"Simulation","l");
  leg->AddEntry(experimentgr,"Experimental","l");
  leg->SetTextSize(0.045);
  leg->Draw();
} 