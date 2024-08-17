#pragma once

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include "complex.h"
#include<complex>


#include "pfc-bitmap.h"

using real_t = double;
using complex_t_gpu = pfc::complex <real_t>;

cudaError_t calculate_fractal_caller(pfc::bmp::pixel_t* bmp_data, size_t width, size_t height, complex_t_gpu const ll, double dx, double dy);