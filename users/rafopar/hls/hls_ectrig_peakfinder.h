#ifndef HLS_ECTRIG_PEAKFINDER_H
#define HLS_ECTRIG_PEAKFINDER_H

#include <ap_int.h>
#include <ap_fixed.h>
#include <hls_stream.h>

typedef struct
{
	ap_uint<6>	n;                           // Strip number [0-36]
	ap_uint<11>	t;                           // time of the peak,   Why 11 bits? Buffer length of 8 us?
	ap_uint<2>	view;                        // 0=U, 1=V, 2=W
} ECPeakDetect_t;

typedef struct
{
	ap_uint<13>	past_energy;                 // Previous peak energy in MeV
	ap_uint<3>	past_tpulse;                 // Previous peak time, the precision is 4ns/2^{3}
	ap_uint<13>	present_energy;              // Current  peak energy in MeV
	ap_uint<3>	present_tpulse; 	     // Current  peak time, the precision is 4ns/2^{3}
	ap_uint<13>	future_energy;               // Future   peak energy in MeV
	ap_uint<3>	future_tpulse;		     // Future   peak time, the precision is 4ns/2^{3}
} ECStrip_t;

typedef struct
{
	ap_uint<13>		e;                   // Peak energy in MeV
	ap_uint<11>		t;                   // Peak time [ns]
	ap_ufixed<9,6>	coord;                       // coordinate in units of strip wodth
	ap_uint<2>		view;                // 0=U, 1=V, 2=W
} ECPeak_t;

void peak_finder(
		ap_uint<4> echit_dt,
		ap_uint<13> echit_emin,
		ECStrip_t strips_ram[36][64],
		hls::stream<ECPeakDetect_t> &peakdetect_sin,
		hls::stream<ECPeak_t> &peak_sout
	);

#endif
