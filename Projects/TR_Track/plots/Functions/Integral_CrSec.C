#include "GetProbability.C"

double Integral_CrSec(TH1D* hist, double unitscale)
{
  int binnum=hist->GetNbinsX();
  double CrSec=0;
  for (int i=0; i<binnum; i++)
  {
    double lowedge=hist->GetXaxis()->GetBinLowEdge(i);
    double upperedge=hist->GetXaxis()->GetBinLowEdge(i+1);
    //cout<<"lowedge: "<<lowedge<<"    "<<"upperedge: " <<upperedge<<endl;
    double area=TMath::Pi()*( pow(upperedge*unitscale,2)- pow(lowedge*unitscale,2) );
    double bincontent=hist->GetBinContent(i);
    double dC=area*GetProbability(bincontent);
    CrSec=CrSec+dC;
  }
  return CrSec;
}
