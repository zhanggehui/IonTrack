double GetProbability(double e)
{
  //e0 = 25.7 
  //e=15*e;
  //int m =1; double e0 = 1 ,e1=100;
  //double eeff=max(e-e1,0.);
  int m =1; double e0 = 25.7;
  double probability=pow(1-exp(-e/e0), m);
  //double probability=exp(-e0/e);
  //cout<<probability<<endl;
  return probability;
}