#pragma once

#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <utility>

using integer = std::ptrdiff_t;

void copy_string_kernel_caller(char* const p_dst, char const* const p_src, integer const size);