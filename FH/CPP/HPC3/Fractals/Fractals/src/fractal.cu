#include "fractal.h"

template <typename D, typename R> [[nodiscard]] constexpr auto&& debug_release_gpu([[maybe_unused]] D&& d, [[maybe_unused]] R&& r) noexcept {
#if defined _DEBUG
	return std::forward <D>(d);
#else
	return std::forward <R>(r);
#endif
}


__device__ const std::size_t g_colors_gpu{ debug_release_gpu(64, 256) };
__device__ const real_t      g_infinity_gpu{ 4 };

__device__ pfc::bmp::pixel_t iterate_gpu(complex_t_gpu const c) {
	std::size_t i{};
	complex_t_gpu   z{};

	while ((i++ < g_colors_gpu) && (pfc::norm(z) < g_infinity_gpu))
		z = z * z + c;

	++i;   // gives a nice effect

	pfc::bmp::pixel_t p{};
	return { p.green = static_cast<pfc::byte_t>(1.0 * i / g_colors_gpu * 255) };
}

__global__ void calculate_fractal(pfc::bmp::pixel_t* bmp_data, size_t width, size_t height, complex_t_gpu const ll, double dx, double dy) {
	int x = threadIdx.x + blockIdx.x * blockDim.x;
	int y = threadIdx.y + blockIdx.y * blockDim.y;

	if (x >= width || y >= height) return;

	float real = ll.real + x * dx;
	float imag = ll.imag + y * dy;
	complex_t_gpu c(real, imag);

	pfc::bmp::pixel_t value = iterate_gpu(c);

	bmp_data[y * width + x] = value;
}

cudaError_t calculate_fractal_caller(pfc::bmp::pixel_t* bmp_data, size_t width, size_t height, complex_t_gpu const ll, double dx, double dy) {
	dim3 dimBlock(32, 32);
	dim3 dimGrid(((width + dimBlock.x - 1) / dimBlock.x),
		((height + dimBlock.y - 1) / dimBlock.y));
	
	calculate_fractal <<<dimGrid, dimBlock>>> (bmp_data, width, height, ll, dx, dy);

	return cudaGetLastError();
}