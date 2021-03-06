#pragma once

#include <cmath>
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <ctime> //only because <chrono> seems a bit hefty
#include <chrono> //so i snapped...



#define SAMPLE_RATE 48000
#define BUFFER_LENGTH 512
#define PI 3.14159265358979323846

enum Notes
{
	NONOTE = 0, cm2, csm2, dm2, dsm2, em2, fm2, fsm2, gm2, gsm2, am2, asm2, bm2,
	cm1, csm1, dm1, dsm1, em1, fm1, fsm1, gm1, gsm1, am1, asm1, bm1,
	c0, cs0, d0, ds0, e0, f0, fs0, g0, gs0, a0, as0, b0,
	c1, cs1, d1, ds1, e1, f1, fs1, g1, gs1, a1, as1, b1,
	c2, cs2, d2, ds2, e2, f2, fs2, g2, gs2, a2, as2, b2,
	c3, cs3, d3, ds3, e3, f3, fs3, g3, gs3, a3, as3, b3,
	c4, cs4, d4, ds4, e4, f4, fs4, g4, gs4, a4, as4, b4,
	c5, cs5, d5, ds5, e5, f5, fs5, g5, gs5, a5, as5, b5,
	c6, cs6, d6, ds6, e6, f6, fs6, g6, gs6, a6, as6, b6

};//could be in Note

float clamp(float value, float min, float max);
float convertToRange( float value, float oldmin, float oldmax, float newmin, float newmax);