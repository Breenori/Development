//
//  frequency_table.cpp
//  SWE3_Gassner_Ue8
//
//  Created by Christoph Gassner on 15.02.23.
//

#include "frequency_table.h"

frequencyTableException::frequencyTableException(std::string const& s) {
    message += s;
}

std::string& frequencyTableException::what() {
    return message;
}

frequency_table_entry::frequency_table_entry(char c_, double f_) : c(c_), frequency(f_) {
    
}

char frequency_table_entry::get_c() {
    return c;
}

double& frequency_table_entry::get_frequency() {
    return frequency;
}

void frequency_table_entry::print(std::ostream & out, bool const eol) const {
    out << "|" <<std::setw(8) << std::left << c << "|" <<std::right <<std::setw(9) << frequency << "|";
    if (eol) {
        out << std::endl;
    }
}
frequency_table::~frequency_table() {
    clear();
}

frequency_table::frequency_table() {
    table = {};
    count_table = std::map<char, int>();
}

frequency_table::frequency_table(std::string const * p_text) {
    count_table = std::map<char, int>();
    std::string const text = *p_text;
    for (char const c : text) {
        count_table[c]++;
    }
    
    generate(p_text);
    
}

void frequency_table::generate(std::string const* p_text) {
    table = {};
    size_t const size = p_text->size();
    std::string const text = *p_text;
    
    for (auto it = count_table.begin(); it != count_table.end();++it) {
        double freq = (double) it->second / (double) size;
        frequency_table_entry* current_entry = new frequency_table_entry(it->first, freq);
        table.push_back(current_entry);
        current_entry = nullptr;
    }
    sort();
}

void frequency_table::sort() {
    for (int i = 0; i < table.size()-1; ++i) {
        if (table[i]->get_frequency() < table[i+1]->get_frequency()) {
            std::swap(table[i], table[i+1]);
            sort();
            break;
        }
    }
}

double& frequency_table::get_frequency(char const c) {
    for (frequency_table_entry* f : table) {
        if (f->get_c() == c) {
            return f->get_frequency();
        }
    }
    
    throw frequencyTableException("'" + std::string(1, c) + "' not found in table.");
}

size_t frequency_table::get_size() const {
    return table.size();
}

std::vector<frequency_table_entry*>*  frequency_table::get_table() {
    return &table;
}

void  frequency_table::print(std::ostream & out) const {
    out << "--------------------" << std::endl;
    out << std::setw(20) << "  Frequency Table   " << std::endl;
    out << "--------------------" <<  std::endl;
    for (frequency_table_entry * entry : table) {
        entry->print();
    }
    
    out << "--------------------" << std::endl;
}

void frequency_table::clear() {
    for (frequency_table_entry* e : table) {
        delete e;
        e = nullptr;
    }
    table.clear();
    count_table.clear();
}

