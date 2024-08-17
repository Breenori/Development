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
#include <future>

using namespace std::string_literals;

// -------------------------------------------------------------------------------------------------

namespace hpc::fractals::threads {

    template <typename T> concept is_numeric = std::is_integral_v <T> || std::is_floating_point_v <T>;

    template <typename D, typename R> [[nodiscard]] constexpr auto&& debug_release([[maybe_unused]] D&& d, [[maybe_unused]] R&& r) noexcept {
#if defined _DEBUG
        return std::forward <D>(d);
#else
        return std::forward <R>(r);
#endif
    }

    pfc::bitmap make_bitmap(std::size_t const width, double const aspect_ratio) {
        return pfc::bitmap{ width, static_cast <std::size_t> (width / aspect_ratio + 0.5) };
    }

    void throw_on_not_existent(std::string const& entity) {
        if (!std::filesystem::exists(entity))
            throw std::runtime_error{ "Filesystem entity '" + entity + "' does not exist." };
    }

    template <is_numeric T> pfc::byte_t to_byte(T const value) {
        return static_cast <pfc::byte_t> (value);
    }

    // -------------------------------------------------------------------------------------------------

    using real_t = double;
    using complex_t = std::complex <real_t>;

    constinit std::size_t g_colors{ debug_release(64, 256) };
    constinit real_t      g_epsilon{ 0.00001f };
    constinit real_t      g_infinity{ 4 };
    constinit std::size_t g_width{ debug_release(1024, 4096 * 2) };

    std::ostream nout{ nullptr };
    auto& dout{ debug_release(std::cout, nout) };

    auto const g_bmp_path{ "./bitmaps/"s };
    auto const g_jbs_path{ "./jobs/"s };

    // -------------------------------------------------------------------------------------------------

    pfc::bmp::pixel_t iterate(complex_t const c) {
        std::size_t i{};
        complex_t   z{};

        while ((i++ < g_colors) && (std::norm(z) < g_infinity))
            z = z * z + c;

        ++i;   // gives a nice effect

        pfc::bmp::pixel_t p{};
        return { p.green = to_byte(1.0 * i / g_colors * 255) };
    }

    void compute_part(pfc::bitmap* bmp, complex_t c, complex_t ll, double dx, double dy, double ratio, int threadIdx) {
        c.imag(c.imag() + ratio * bmp->height() * threadIdx * dy);
        for (std::size_t y{ static_cast<size_t>(ratio * bmp->height() * threadIdx) }; y < static_cast<size_t>(ratio * bmp->height() * (threadIdx + 1)); c.imag(c.imag() + dy), ++y) {
            c.real(ll.real());
            for (std::size_t x{ 0 }; x < bmp->width(); c.real(c.real() + dx), ++x)
                bmp->at(x, y) = iterate(c);
        }
    }

    pfc::bitmap fractal(pfc::bitmap& bmp, double dx, double dy, complex_t const ll, complex_t const ur) {
        auto c{ ll };

        const auto processor_count = 12;
        std::vector<std::future<void>> tasks{ processor_count };

        std::vector < std::thread > group;

        for (int i{ 0 }; i < processor_count; i++) {
            group.emplace_back(compute_part, &bmp, c, ll, dx, dy, 1.0f / processor_count, i);
        }

        for (auto& t : group) {
            if (t.joinable())
                t.join();
        }

        return bmp;
    }

    // -------------------------------------------------------------------------------------------------

    std::string make_filename_bmp(std::size_t const t, std::size_t const n) {
        return std::format("{}fractal-test_{}-{:0{}}.bmp", g_bmp_path, t, n, 3);
    }

    void print_elapsed(pfc::details::std_chrono_duration auto const elapsed) {
        std::cout
            << elapsed << '\n'
            << std::chrono::duration_cast <std::chrono::milliseconds> (elapsed) << '\n';
    }

    void test_1() {
        //fractal (g_width, {-2.0f, -1.0f}, {1.0f, 1.0f}).to_file (make_filename_bmp (1, 1));
    }

    void test_2(std::size_t const images = 4) {
        // lower left, upper right, center point, width/height. First 3 are complex numbers, width/height normal numbers
        pfc::bitmap bmp;

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

            fractal(bmp, dx, dy, ll, ur).to_file(make_filename_bmp(2, ++i));
        }

        std::cout << '\n';
    }

    // -------------------------------------------------------------------------------------------------

    void checked_main([[maybe_unused]] std::span <std::string_view const> const args) {
        std::cout << std::format("I'm in {} mode ...\n", debug_release("debug", "release"));

        throw_on_not_existent(g_bmp_path);
        throw_on_not_existent(g_jbs_path);

        //std::cout << "test_1\n"; test_1 ();
        std::cout << "test_2\n";
        print_elapsed(pfc::timed_run(test_2, 8));
    }
}