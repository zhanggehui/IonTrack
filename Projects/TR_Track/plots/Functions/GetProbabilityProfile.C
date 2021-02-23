#include "GetProbability.C"

TGraph * GetProbabilityProfile(TH1D* hist, double unitscale)
{
  int binnum=hist->GetNbinsX();
  TGraph *gr= new TGraph();
  for (int i=0; i<binnum; i++)
  {
    gr->SetPoint(i, hist->GetBinCenter(i)*unitscale, 
                 GetProbability(hist->GetBinContent(i)));
  }
  return gr;
}
