#include <stdio.h>
#include <string.h>
#include "hls_ectrig_peakfinder.h"

int main(int argc, char *argv[])
{
	hls::stream<ECPeakDetect_t> peakdetect_sin;
	hls::stream<ECPeak_t> peak_sout;
	ECStrip_t strips_ram[36][64];
	ap_uint<4> t_coin = 8;

	memset(strips_ram, 0, sizeof(strips_ram));
	strips_ram[10][20].energy = 100;
	strips_ram[10][20].tpulse = 2;
	strips_ram[11][20].energy = 101;
	strips_ram[11][20].tpulse = 7;
	strips_ram[12][19].energy = 102;
	strips_ram[12][19].tpulse = 5;

	ECPeakDetect_t pd;
	pd.strip1 = 10;
	pd.tframe = 20;
	pd.tpulse = 2;
	peakdetect_sin.write(pd);
	peakdetect_sin.write(pd);

	while(!peakdetect_sin.empty())
		peak_finder(t_coin, strips_ram, peakdetect_sin, peak_sout);

	int fail = 0;
	int nPeak = 0;
	while(!peak_sout.empty())
	{
		ECPeak_t p;

		peak_sout.read(p);

		printf("Peak# %d\n", nPeak);
		printf("   energy = %d\n", p.energy.to_int());
		printf("   tpeak  = %d\n", p.tpeak.to_int());
		printf("   coord  = %f\n", p.coord.to_float());

		if(p.energy.to_int() != 303) fail = 1;
		if(p.tpeak.to_int() != 162) fail = 1;
		if(p.coord.to_float() != 11.0) fail = 1;

		nPeak++;
	}
	return fail;
}
