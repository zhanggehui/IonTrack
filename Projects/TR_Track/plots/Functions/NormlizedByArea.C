void NormlizedByArea(TH1D* hist, double unitscale)
{
  int binnum=hist->GetNbinsX();
  for (int i=0; i<binnum; i++)
  {
    double lowedge=hist->GetXaxis()->GetBinLowEdge(i);
    double upperedge=hist->GetXaxis()->GetBinLowEdge(i+1);
    //cout<<"lowedge: "<<lowedge<<"    "<<"upperedge: " <<upperedge<<endl;
    double area=TMath::Pi()*( pow(upperedge*unitscale,2)- pow(lowedge*unitscale,2) );
    double fac=1./area;
    //cout<<hist->GetBinContent(i);
    hist->SetBinContent( i, fac*(hist->GetBinContent(i)) );
    //cout<<"   " << hist->GetBinContent(i)<<endl;
  }
}