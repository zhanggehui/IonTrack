{
  gROOT->Reset();
  gROOT->ProcessLine(".L ../plots/Functions/GetData.C");
  TCanvas* c1 = new TCanvas("c1"," ");
  c1->cd(); c1->Update();
  
  const int n=2;
  TGraph* grs[n];
  vector<int> linev; vector<int> posv; vector<double> scalev;

  linev={26,46} ; posv={1,5,14,9};  scalev={1,100};
  grs[0]=GetData("../SI_in_138H2O/16_100.dat",linev,posv,scalev);

  linev={1,43} ; posv={0,12,13,12};  scalev={1e6,1000};
  grs[1]=GetData("../SI_in_138H2O/spower.txt",linev,posv,scalev);

  TMultiGraph *mg = new TMultiGraph();
  for (int i=0; i<n; i++)
  {
    grs[i]->SetLineColor(i+1);
    mg->Add(grs[i]);
  }

  mg->Draw("ACP");
  mg->SetTitle("Spower vs Energy");
  mg->GetYaxis()->SetTitle("dE/dx (keV/nm)");
  mg->GetXaxis()->SetTitle("E (MeV)");

  TLegend* leg=new TLegend();
  vector<string> legstrvec{"Srim","Geant4"};
  for (int i=0; i<n; i++)
  {
    leg->AddEntry(grs[i],legstrvec[i].c_str(),"l");
  }
  leg->Draw();
}  