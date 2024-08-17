#include "./HelloWorld.h"
#include <iostream>
#include <format>
#include <string>
#include <memory>



int main() {
	int count{ -1 };
	cudaGetDeviceCount(&count);


	if (count > 0) { //if CUDA device was found graka available

		for (int d{ 0 }; d < count; ++d) { //iterate over all grakas
			cudaDeviceProp prop{};
			cudaGetDeviceProperties_v2(&prop, d);

			std::cout << std::format(
				"device #{}: '{}', compute capabilty {}.{}, memory: {}, Threads: {}\n", d, prop.name, prop.major, prop.minor, prop.totalGlobalMem, prop.multiProcessorCount*prop.maxThreadsPerMultiProcessor);

		}

		//if more than one graka: Chose one based on specs


		cudaSetDevice(0); //activate Cuda
		
		//allocate buffer on host
			
		std::string_view const scr{ "Hallo Welt!" };	//string_view statt String, da string eine Kopie der literalle erstellt -> sinnlos hier, String_view erstellt nur eine Ansicht auf die literale
		char const* const hp_src {scr.data() }; //heap pointer to src Buffer
		integer const size = {std::ssize(scr) + 1}; //std::size liefer unsigned long int (zu groß für int) -> std::ssize liefernt singed long long it
		
		auto hp_dst{ std::make_unique <char []> (size) }; //smart  pointer -> no delete notwendig, make_unique Funktion die new ersetzt

		
		//allocate buffer on device

		char* dp_src{ nullptr }; //erstmal keine Smartpointer - devicepointer
		char* dp_dst{ nullptr }; //erstmal keine Smartpointer - devicepointer
		cudaMalloc(&dp_src, size);	//allokiert speicher am Device
		cudaMalloc(&dp_dst, size);	//allokiert speicher am Device

		cudaMemcpy(dp_src, hp_src, size, cudaMemcpyHostToDevice);	//kopieren des wertes zum device


		//the part here happens within HelloWorld.cu
		copy_string_kernel_caller(dp_dst, dp_src, size);

		cudaMemcpy(hp_dst.get(), dp_dst, size, cudaMemcpyDeviceToHost);	//kopieren des wertes zum device - .get() liefert den rawpointer


		cudaFree(dp_src);
		cudaFree(dp_dst);

		cudaDeviceReset(); //end Cuda Application

		std::cout << std::format("hp_src: '{}'\n", hp_src);
		std::cout << std::format("hp_dst: '{}'\n", hp_dst.get());

	}

}