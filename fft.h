#ifndef FFT
#define FFT

#include "BigInt.h"
#include <vector>
#include <complex>
#include <iostream>
#include <algorithm>
#include <cmath>

typedef std::complex<double> cd;
typedef std::vector<cd> vcd;

vcd fft(const vcd &as);

void multiply(const BigInt &A, const BigInt &B, BigInt &Res);

#endif