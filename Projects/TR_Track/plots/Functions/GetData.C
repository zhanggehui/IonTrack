TGraph* GetData(string fielname,vector<int> linev, vector<int> posv, vector<double> scalev)
//linev: startline endline; posv: posx1 posx2 posy1 posy2; scalev: scalex scaley
{ 
  ifstream file;
  file.open(fielname,ios::in);
  string line;
  double x=0, y=0;
  int lineindex=0, dataindex=0;
  TGraph *gr= new TGraph();
  if(file.is_open())
  {
    while(!file.eof()) 
  	{ 
	    getline(file,line);
	    lineindex++;
	    if (lineindex>=linev[0] && lineindex<=linev[1]) //!line.empty())
	    {
	      x=atof(line.substr(posv[0],posv[1]).c_str());
	      y=atof(line.substr(posv[2],posv[3]).c_str());
	      gr->SetPoint(dataindex,x/scalev[0],y/scalev[1]);
	      dataindex++;
	    }
    }
	  gr->SetLineWidth(3);
	  file.close();
  }
  else
  {
    cout <<"No such file!" << endl;
  }
  return gr;
}