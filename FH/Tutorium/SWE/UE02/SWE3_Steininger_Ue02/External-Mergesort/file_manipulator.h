//
// Created by Lukas Steininger on 24.10.22.
//

#ifndef EXTERNAL_MERGESORT_FILE_MANIPULATOR_H
#define EXTERNAL_MERGESORT_FILE_MANIPULATOR_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>


class file_manipulator {
public:
    using value_t = std::string;
    using cont_t = std::vector<value_t>;

    //file destination, amount of random elements, size/length of random element
    static void fill_randomly(value_t const &dst, std::size_t n = 10 , int const no_letters = 1);
    //returns amount of element that have been split into the two files
    //file to split up, collection of files in which to split up, amount of elements to read
    static std::size_t partition (value_t const &src, cont_t const & dst);
    //copies the content of src into the file dst and returns how many elements were copied
    //file to copy from, file to copy to
    static std::size_t copy(value_t const &src, value_t const &dst);
    //copies the content of a container to a file
    //container to copy, destination file
    static std::size_t copy(cont_t const &src, value_t const &dst);
    //print the content of the file on the console
    //file to print
    static std::size_t print(value_t const &src);

private:
    //write the data of an input stream to an output stream
    static std::size_t write_to_stream(std::istream& in, std::ostream& out);
    //write the content of a container to an output stream
    static std::size_t write_to_stream(cont_t data, std::ostream& out);
};


#endif //EXTERNAL_MERGESORT_FILE_MANIPULATOR_H
