//
// Created by Lukas Steininger on 24.10.22.
//

#include "file_manipulator.h"
#include <random>
#include <chrono>

using clk = std::chrono::system_clock;
using rnd = std::default_random_engine;
using real_dist = std::uniform_real_distribution<double>; //value between 0 and 1
using int_dist = std::uniform_int_distribution<int>; //value within a specified scope

void file_manipulator::fill_randomly(file_manipulator::value_t const &dst, std::size_t n, int const no_letters) {

    unsigned int seed = clk::now().time_since_epoch().count();
    rnd generator{seed};
    real_dist dis_r{0.0,1.0};
    int_dist dist_alphabet{0, 25};
    int_dist dist_numbers{0, 9};
    std::ofstream out {dst};

    while (out && (n-- >0)){
        for (int i = 0; i < no_letters; ++i) {
            char c;
            double prop = dis_r(generator); //decide what character should be written
            if ( prop <= 0.33) {
                c = '0' +dist_numbers(generator);
            }
            else if (prop >0.33 && prop<0.66){
                c = 'a' + dist_alphabet(generator);
            }
            else {
            c = 'A' + dist_alphabet(generator);
            }
            out << c;
        }
        out << ' ';
    }
    out.close();
}

std::size_t file_manipulator::partition(file_manipulator::value_t const &src, file_manipulator::cont_t const &dst) {
    std::ifstream in {src};
    std::vector<std::ofstream*> out;

    for(std::size_t i{0}; i<dst.size(); ++i){
        out.push_back(new std::ofstream(dst[i])); //allocate memory for the outfile stream
    }
    std::size_t n{0}; //counter for elements
    value_t value;
    while (in >> value){
        std::ofstream & outFile{*(out[n%dst.size()])}; //alternate between the two files when writing to file
        if (outFile){
            outFile << value << ' ';

        }
        n++;
    }


    for(std::size_t i{0}; i<dst.size(); ++i){
        delete out[i]; //release the memory allocated by the outfile streams
    }
    return n;
}

std::size_t file_manipulator::copy(const file_manipulator::value_t &src, const file_manipulator::value_t &dst) {
    std::ifstream in {src};
    std::ofstream out {dst};
    size_t cnt {write_to_stream(in, out)};
    in.close();
    out.close();
    return cnt;
}
std::size_t file_manipulator::print(const file_manipulator::value_t &src) {
    std::ifstream in {src};
    size_t cnt {write_to_stream(in, std::cout)};
    std::cout<<"\n";
    in.close();
    return cnt;
}

//used by copy and print since std::cout is a stream
std::size_t file_manipulator::write_to_stream(std::istream &in, std::ostream &out) {
    std::size_t cnt {0};
    value_t value;

    while (in >> value) {    //read each value from input and write it to output
        if (out) {
            out << value << ' ';
        }
        cnt++;
    }
    return cnt;
}

std::size_t file_manipulator::copy(const file_manipulator::cont_t &src, const file_manipulator::value_t &dst) {
    std::ofstream out {dst};
    size_t cnt {write_to_stream(src, out)};
    out.close();
    return cnt;

}

std::size_t file_manipulator::write_to_stream(file_manipulator::cont_t data, std::ostream &out) {
    std::size_t cnt {0};
    value_t value;
    for (int i = 0; i <data.size() ; ++i) {
        if (out){
            out << data[i] << ' ';
        }
        cnt++;
    }
    return cnt;
}

