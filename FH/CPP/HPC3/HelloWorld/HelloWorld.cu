#include "./HelloWorld.h"


__global__ void copy_string_kernel(int const size, char * const p_dst, char const * const p_src) {	//kernel function immer void!
	
	auto const t{blockIdx.x*blockDim.x + threadIdx.x}; //thread Number //threadIdx= wievielter Thread vom Block, blockIdx = welcher Block, BlockDim-> Threads pro Block -> x weil Blöcke zwischen 1 und 3 Dimensionen haben können
					
	//für bitmap eig sehr praktisch, ist 2 Dimensional und wenn man Blöcke 2 Dimensional anordnert kann man wieder wie hier arbeiten -> direkt zuweisen
	if(t < size)
		p_dst[t] = p_src[t];


}



void copy_string_kernel_caller(char* const p_dst, char const* const p_src, integer const size) {		//kernel aufrufen
	integer const tib{ 32 }; // threads in block
	integer const big{ (size + tib - 1) / tib }; // blocks in grid
	
	copy_string_kernel <<< big, tib >>> (size, p_dst, p_src); //<<<1, size>>> kernel configuration -> 1 Block mit size Menge an Threads
}








