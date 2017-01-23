#include "hls_ectrig_peakfinder.h"

void peak_finder(
		ap_uint<4> echit_dt,
		ap_uint<13> echit_emin,
		ECStrip_t strips_ram[36][512],
		hls::stream<ECPeakDetect_t> &peakdetect_sin,
		hls::stream<ECPeak_t> &peak_sout
	)
{
  int i;
  ECPeakDetect_t peakDetect;
  ECStrip_t strips[36];
  ECPeak_t peak;
  ap_uint<13> e[36];

  peakdetect_sin.read(peakDetect);

  for(i = 0; i < 36; i++)
    {
      ap_uint<9> addr = (peakDetect.view, peakDetect.t(9,3));
      strips[i] = strips_ram[i][addr];
    }

  for(i = 0; i < 36; i++)
    {
      bool prev_strip_e_valid = (strips[i].past_energy > 0) ? true : false;
      bool curr_strip_e_valid = (strips[i].present_energy > 0) ? true : false;
      bool next_strip_e_valid = (strips[i].future_energy > 0) ? true : false;

      bool prev_strip_t_valid = (8 + peakDetect.t(2,0) - strips[i].past_tpulse <= echit_dt) ? true : false;
      bool curr_strip_t_valid = (strips[i].present_tpulse > peakDetect.t(2,0)) ?
	((strips[i].present_tpulse - peakDetect.t(2,0) <= echit_dt) ? true : false) :
	((peakDetect.t(2,0) - strips[i].present_tpulse <= echit_dt) ? true : false);
      bool next_strip_t_valid = (8 + strips[i].future_tpulse - peakDetect.t(2,0) <= echit_dt) ? true : false;

      if(curr_strip_e_valid && curr_strip_t_valid)
	e[i] = strips[i].present_energy;
      else if(prev_strip_e_valid && prev_strip_t_valid)
	e[i] = strips[i].past_energy;
      else if(next_strip_e_valid && next_strip_t_valid)
	e[i] = strips[i].future_energy;
      else
	e[i] = 0;
    }

  peak.e = 0;
  peak.t = 0;
  peak.coord = 0;

  ap_ufixed<26,23> coord = 0;
  bool end = false;
  for(i = 0; i < 36; i++)
    {
      if((i < peakDetect.n) || end)
	continue;

      if(!end)
	{
	  peak.e += e[i];
	  coord += i * e[i];
	}

      ap_uint<13> ei_25 = e[i]<<2;

      if(i != 35 && e[i+1] < echit_emin)
	end = true;

      if(i != 0 && e[i-1] > e[i] && ei_25 < e[i+1])
	end = true;

      if(i != 0 && e[i-1] > ei_25 && e[i] < e[i+1])
	end = true;
    }
  peak.t = peakDetect.t;
  peak.coord = (ap_ufixed<26,23>)0.5 + coord / peak.e;
  peak.view = peakDetect.view;

  peak_sout.write(peak);
}
