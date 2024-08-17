//       $Id: 101-fractals.cpp 47900 2023-12-01 09:40:55Z p20068 $
//      $URL: https://svn01.fh-hagenberg.at/bin/cepheiden/Inhalt/HPC/Threads/fractals/src/101-fractals.cpp $
// $Revision: 47900 $
//     $Date: 2023-12-01 10:40:55 +0100 (Fr., 01 Dez 2023) $
//   $Author: p20068 $
//   Creator: Peter Kulczycki
//  Creation: November 20, 2020
// Copyright: (c) 2021 Peter Kulczycki (peter.kulczycki<AT>fh-hagenberg.at)
//   License: This document contains proprietary information belonging to
//            University of Applied Sciences Upper Austria, Campus Hagenberg.
//            It is distributed under the Boost Software License (see
//            https://www.boost.org/users/license.html).

#include "pfc-bitmap.h"
#include "pfc-jobs.h"
#include "pfc-chrono.h"

#include <cstdio>
#include <filesystem>
#include <format>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include<thread>
#include<future>

#include <fstream> // Include fstream for file operations

#include <cuda_runtime.h>
#include "fractal.h"

// 0 for threads, 1 for tasks
const enum multithreading_t { Threads, Tasks };
const multithreading_t MULTITHREADING_TYPE{ multithreading_t::Threads };

const enum device_t { CPU, GPU };
const device_t DEVICE_TYPE{ device_t::GPU };

const int COUNT_IMAGES{ 256 };
const int COUNT_TASKS{ 128 };
const int COUNT_PARALLEL {1};

const bool BENCHMARK = true;

using namespace std::string_literals;

// -------------------------------------------------------------------------------------------------

template <typename T> concept is_numeric = std::is_integral_v <T> || std::is_floating_point_v <T>;
template <typename D, typename R> [[nodiscard]] constexpr auto && debug_release ([[maybe_unused]] D && d, [[maybe_unused]] R && r) noexcept {
   #if defined _DEBUG
      return std::forward <D> (d);
   #else
      return std::forward <R> (r);
   #endif
}


pfc::bitmap make_bitmap (std::size_t const width, double const aspect_ratio) {
   return pfc::bitmap {width, static_cast <std::size_t> (width / aspect_ratio + 0.5)};
}

void throw_on_not_existent (std::string const & entity) {
   if (!std::filesystem::exists (entity))
      throw std::runtime_error {"Filesystem entity '" + entity + "' does not exist."};
}

template <is_numeric T> pfc::byte_t to_byte (T const value) {
   return static_cast <pfc::byte_t> (value);
}

// -------------------------------------------------------------------------------------------------

using real_t    = double;
using complex_t = std::complex <real_t>;

constinit std::size_t g_colors   {debug_release (64, 256)};
constinit real_t      g_epsilon  {0.00001f};
constinit real_t      g_infinity {4};
constinit std::size_t g_width    {debug_release (1024, 4096*2)};

std::ostream nout {nullptr};
auto &       dout {debug_release (std::cout, nout)};

auto const g_bmp_path {"./bitmaps/"s};
auto const g_jbs_path {"./jobs/"s};

// -------------------------------------------------------------------------------------------------

pfc::bmp::pixel_t iterate (complex_t const c) {
   std::size_t i {};
   complex_t   z {};

   while ((i++ < g_colors) && (std::norm (z) < g_infinity))
      z = z * z + c;

   ++i;   // gives a nice effect

   pfc::bmp::pixel_t p{};
   return {p.green = to_byte (1.0 * i / g_colors * 255)};
}

void compute_part(pfc::bitmap* bmp, complex_t c, complex_t ll, double dx, double dy, double ratio, int threadIdx) {
    c.imag(c.imag() + ratio * bmp->height() * threadIdx * dy);
    for (std::size_t y{ static_cast<size_t>(ratio * bmp->height() * threadIdx) }; y < static_cast<size_t>(ratio * bmp->height() * (threadIdx + 1)); c.imag(c.imag() + dy), ++y) {
        c.real(ll.real());
        for (std::size_t x{ 0 }; x < bmp->width(); c.real(c.real() + dx), ++x)
            bmp->at(x, y) = iterate(c);
    }
}

void fractal_tasks (pfc::bitmap* bmp, double dx, double dy, complex_t const ll, complex_t const ur, size_t const threads) {
   auto c {ll};

   std::vector<std::future<void>> tasks{ threads };

   for (int i{ 0 }; i < threads; i++) {
       tasks[i] = std::async(std::launch::async, compute_part, bmp, c, ll, dx, dy, 1.0f/threads, i);
   }

   for (int i{ 0 }; i < threads; i++) {
       tasks[i].wait();
   }
}

void fractal_threads(pfc::bitmap* bmp, double dx, double dy, complex_t const ll, complex_t const ur, size_t const threads) {
    auto c{ ll };

    std::vector<std::future<void>> tasks{ threads };

    std::vector < std::thread > group;

    for (int i{ 0 }; i < threads; i++) {
        group.emplace_back(compute_part, bmp, c, ll, dx, dy, 1.0f / threads, i);
    }

    for (auto& t : group) {
        if (t.joinable())
            t.join();
    }
}

// -------------------------------------------------------------------------------------------------

std::string make_filename_bmp (std::size_t const t, std::size_t const n) {
   return std::format ("{}fractal-test_{}-{:0{}}.bmp", g_bmp_path, t, n, 3);
}

void print_elapsed(pfc::details::std_chrono_duration auto const elapsed) {
    std::cout
        << elapsed << '\n'
        << std::chrono::duration_cast <std::chrono::milliseconds> (elapsed) << '\n';
}


void cpu_fractal(std::size_t const images = 4, size_t const mode = 0, size_t const filecount = 1, size_t const taskcount = 128) {
    // lower left, upper right, center point, width/height. First 3 are complex numbers, width/height normal numbers
    std::vector<pfc::bitmap> bmps(filecount);
    std::vector<std::future<void>> tasks(filecount);

   for (std::size_t i {}; auto const &[ll, ur, cp, wh] : pfc::jobs{ g_jbs_path + pfc::jobs <>::make_filename(images) }) {
      std::cout << '.'; 

      double complex_width{ ((complex_t)ur - complex_t(ll)).real() };
      double complex_height{ ((complex_t)ur - (complex_t)ll).imag() };

      if (i < filecount) {
        bmps[i % filecount] = make_bitmap(g_width, (complex_width / complex_height));
      }

      auto const dx{ complex_width / bmps[i%filecount].width()};
      auto const dy{ complex_height / bmps[i % filecount].height() };
      assert(std::abs(dx - dy) < g_epsilon);

      if (mode == 0) {
          tasks[i % filecount] = std::async(std::launch::async, fractal_threads, &bmps[i % filecount], dx, dy, ll, ur, 12/filecount);
      }
      else {
          tasks[i % filecount] = std::async(std::launch::async, fractal_tasks, &bmps[i % filecount], dx, dy, ll, ur, taskcount/filecount);
      }

      if ((i + 1) % filecount == 0) {
          for (auto& t : tasks) {
              t.wait();
          }

          /*for (int imgId{0}; imgId < bmps.size(); imgId++) {
              std::cout << std::format("Image {} done!", i - imgId) << std::endl;
              bmps[imgId % filecount].to_file(make_filename_bmp(2, i-filecount+1+imgId));
          }*/
      }

      ++i;
   }

   std::cout << '\n';
}

void gpu_fractal(std::size_t const images = 4) {
    // lower left, upper right, center point, width/height. First 3 are complex numbers, width/height normal numbers
    pfc::bitmap bmp;
    pfc::bmp::pixel_t* pixel = nullptr;

    for (std::size_t i{}; auto const& [ll, ur, cp, wh] : pfc::jobs{ g_jbs_path + pfc::jobs <>::make_filename(images) }) {
        std::cout << '.';

        double complex_width{ ((complex_t)ur - complex_t(ll)).real() };
        double complex_height{ ((complex_t)ur - (complex_t)ll).imag() };

        if (i == 0) {
            bmp = make_bitmap(g_width, (complex_width / complex_height));
        }

        auto const dx{ complex_width / bmp.width() };
        auto const dy{ complex_height / bmp.height() };
        assert(std::abs(dx - dy) < g_epsilon);

        // copy over the image
        size_t image_bytes{ bmp.width() * bmp.height() * sizeof(pfc::bmp::pixel_t) };
        if (i == 0) {
            cudaMalloc(&pixel, image_bytes);
        }

        cudaMemcpy(pixel, bmp.data(), image_bytes, cudaMemcpyHostToDevice);
        
        auto err = calculate_fractal_caller(pixel, bmp.width(), bmp.height(), ll, dx, dy);
        if (err != cudaSuccess) {
            std::cerr << "Error launching CUDA kernel: " << cudaGetErrorString(err) << std::endl;
        }

        cudaMemcpy(bmp.data(), pixel, image_bytes, cudaMemcpyDeviceToHost);
        
        /*bmp.to_file(make_filename_bmp(2, i + 1));
        std::cout << "Writing to file" << std::endl;*/

        ++i;
    }
    cudaFree(pixel);

    std::cout << '\n';
}

// -------------------------------------------------------------------------------------------------

void checked_main ([[maybe_unused]] std::span <std::string_view const> const args) {
   std::cout << std::format ("I'm in {} mode ...\n", debug_release ("debug", "release"));

   throw_on_not_existent (g_bmp_path);
   throw_on_not_existent (g_jbs_path);
   if (!BENCHMARK) {
       if (DEVICE_TYPE == device_t::CPU) {
           if (MULTITHREADING_TYPE == multithreading_t::Threads) {
               std::cout << "Test with threads:\n";
           }
           else {
               std::cout << "Test with tasks:\n";

           }
           print_elapsed(pfc::timed_run(cpu_fractal, COUNT_IMAGES, MULTITHREADING_TYPE, COUNT_PARALLEL, COUNT_TASKS));
       }
       else {
           std::cout << "Test with GPU:\n";
           cudaSetDevice(0);

           print_elapsed(pfc::timed_run(gpu_fractal, COUNT_IMAGES));

           cudaDeviceReset();
       }
   }
   else {
       const multithreading_t multithreading_types[] = { multithreading_t::Threads, multithreading_t::Tasks };
       const int count_parallel_values[] = { 1, 128 };
       const int count_tasks_values[] = { 128, 256, 1024 };

       std::ofstream log_file("benchmark_results_new.csv", std::ios::out);
       log_file << "images;device;0threads1tasks;Thread/Task count;count_parallel;time(ns)" << std::endl;

       for (int count_task : count_tasks_values) {
           for (multithreading_t multithreading_type : multithreading_types) {
               for (int count_parallel : count_parallel_values) {
                   if (multithreading_type == multithreading_t::Threads) {
                       std::cout << "Test with threads:\n";
                   }
                   else {
                       std::cout << "Test with tasks:\n";
                   }

                   if (multithreading_type == Threads) {
                       if(count_task > 128)
                        continue;
                       count_task = 12;
                   }

                   
                   auto result = pfc::timed_run(cpu_fractal, COUNT_IMAGES, multithreading_type, count_parallel, count_task);
                   log_file << COUNT_IMAGES << ";" << "CPU;" << multithreading_type << ";" << count_task << ";" << count_parallel << ";" << result << std::endl;
               }
           }
       }

       auto result = pfc::timed_run(gpu_fractal, COUNT_IMAGES);
       log_file << COUNT_IMAGES << ";" "GPU;" << "-" << ";" << "-" << ";" << "-" << ";" << result << std::endl;

       log_file.close();
   }
}

int main(int const argc, char const* const* const argv) {
   try {
      checked_main (std::vector <std::string_view> (argv, argv + argc));

   } catch (...) {
      std::cerr << "ERROR\n" << std::flush;
   }
}
