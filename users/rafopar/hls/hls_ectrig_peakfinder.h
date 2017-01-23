#ifndef HLS_ECTRIG_PEAKFINDER_H
#define HLS_ECTRIG_PEAKFINDER_H

#include <ap_int.h>
#include <ap_fixed.h>
#include <hls_stream.h>

typedef struct
{
	ap_uint<6>	n;
	ap_uint<11>	t;
	ap_uint<2>	view;
} ECPeakDetect_t;

typedef struct
{
	ap_uint<13>	past_energy;
	ap_uint<3>	past_tpulse;
	ap_uint<13>	present_energy;
	ap_uint<3>	present_tpulse;
	ap_uint<13>	future_energy;
	ap_uint<3>	future_tpulse;
} ECStrip_t;

typedef struct
{
	ap_uint<13>		e;
	ap_uint<11>		t;
	ap_ufixed<9,6>	coord;
	ap_uint<2>		view;
} ECPeak_t;

void peak_finder(
		ap_uint<4> echit_dt,
		ap_uint<13> echit_emin,
		ECStrip_t strips_ram[36][64],
		hls::stream<ECPeakDetect_t> &peakdetect_sin,
		hls::stream<ECPeak_t> &peak_sout
	);

#endif
