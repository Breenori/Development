//
// Created by Lukas Steininger on 24.10.22.
//

#include "merge_sorter.h"
#include <cmath>
merge_sorter::value_t merge_sorter::sort(const merge_sorter::value_t &path) {
    std::cout << "Original:\n";
    file_manipulator::print(path);

    //create copy and remove the file ending
    size_t i = path.find_last_of(".");
    value_t path_copy = path;
    path_copy.replace(i,path.size()-i,"");

    //creat paths for auxiliary files
    file_manipulator::cont_t files_f {path_copy+"_f0.txt", path_copy+"_f1.txt"};
    file_manipulator::cont_t files_g {path_copy+"_g0.txt",path_copy+"_g1.txt"};

    //partition the input file into the first two files
    file_manipulator::partition(path, files_f);

    size_t cnt = 0;
    bool done = false;
    while (!done){ //alternate between the two auxiliary file groups in terms of reading and writing until end is signaled
        if (cnt%2==0){
            do_run(files_f, files_g, pow(2, cnt), done);
        }
        else {
            do_run(files_g, files_f, pow(2, cnt), done);
        }
        if (done && cnt==0){
            done=false;
        }
        ++cnt;
    }
    std::cout<<"Sorted:\n";
    file_manipulator::print(cnt%2==0 ? files_g[0] : files_f[0]); //return the path of the sorted file
    return cnt%2==0 ? files_g[0] : files_f[0];

}

void merge_sorter::do_run(const merge_sorter::cont_t &src, merge_sorter::cont_t const& dst, std::size_t k, bool &done) {
    std::vector<std::ifstream*> in;
    std::vector<std::ofstream*> out;

    for(std::size_t i{0}; i<src.size(); ++i){
        in.push_back(new std::ifstream (src[i])); //allocate memory for the infile stream
    }
    for(std::size_t i{0}; i<dst.size(); ++i){
        out.push_back(new std::ofstream(dst[i])); //allocate memory for the outfile stream
    }

    std::size_t n{0}; //counter for elements
    value_t value;
    bool is_reading = true;

    cont_t  temp_cont_1{};
    std::vector<size_t> cnt_1 = {0,0,0};

    cont_t  temp_cont_2{};
    std::vector<size_t> cnt_2 = {0,0,0};

    //check if second file is empty --> sorting is done
    if (in[1]->peek() == std::ifstream::traits_type::eof() && k!=1){
        done = true;
        return;
    }

    while (!in[0]->eof() && !in[1]->eof() ){ //alternate between the containers that cache the values until writing them to the files
        if (n%2 == 0){
            read_elements(in[0], in[1], temp_cont_1, cnt_1[0], cnt_1[1], cnt_1[2], k);
            ++n;
        }
        else {
            read_elements(in[0], in[1], temp_cont_2, cnt_2[0], cnt_2[1], cnt_2[2], k);
            ++n;

        }
    }
    file_manipulator::copy(temp_cont_1, dst[0]);
    file_manipulator::copy(temp_cont_2, dst[1]);
}

void merge_sorter::read_elements(std::ifstream *file1, std::ifstream *file2, merge_sorter::cont_t& cont, size_t &cnt_lo, size_t &cnt_mid, size_t &cnt_hi, size_t const k) {
    value_t value;
    cnt_mid = cnt_hi;
    size_t elem_cnt = 0;
    //read k elements from one file
    while (elem_cnt < k && *file1 >> value ){
        cont.push_back(value);
        ++elem_cnt;
        ++cnt_mid;
    }
    elem_cnt = 0;

    //read k elements from the other file
    while (elem_cnt < k && *file2 >> value ){
        cont.push_back(value);
        ++elem_cnt;
    }
    cnt_hi= cnt_mid + elem_cnt;
    //merge the sub array
    cont_t aux(cont.size());
    merge(cont, aux, cnt_lo, --cnt_mid, cnt_hi);
    cnt_lo = cnt_hi;
}


void merge_sorter::merge(merge_sorter::cont_t &v, merge_sorter::cont_t &aux, merge_sorter::index_t lo,
                         merge_sorter::index_t mid, merge_sorter::index_t hi) {
    index_t i = lo;
    index_t j = mid+1;

    for (index_t k = lo; k < hi; ++k) {
        aux[k]=v[k];
    }
    for (index_t k = lo; k < hi ; ++k) {
        if (i > mid) //corner case --> elements of left array depleted
        {
            v[k] = aux[j++];
        }
        else if (j >= hi){ //corner case --> elements of right array depleted
            v[k] = aux[i++];
        }
        else if (aux[j].compare(aux[i]) < 0 ){
            v[k] = aux[j++];
        }
        else {
            v[k] = aux[i++];
        }
    }

}

