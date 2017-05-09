class TECHit
{
public:
  TECHit();

  double E(); {return fE;} // Pedestal subtracted Energy in MeV
  int T(); {return ftime;} // TDC Time in ns
  int View(); {return fview;} // 1(U), 2(V), 3(W)
  int Sector() {return fsect;}
  
private:
  int fsect; // 1, 2, 3, 4, 5, 6
  int fview;   // 1(U), 2(V), 3(W)
  int fstrip;  // 1, 2, 3, ... N_strips in a corresponding Detector-view

  double fE;  // Pedestal subtracted Energy in MeV
  int ftime;  // The time in ns

  int fslot;
  int fchannel;
};
