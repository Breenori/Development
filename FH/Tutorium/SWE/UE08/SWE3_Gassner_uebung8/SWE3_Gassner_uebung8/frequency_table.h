//
//  frequency_table.h
//  SWE3_Gassner_Ue8
//
//  Created by Christoph Gassner on 15.02.23.
//

#ifndef frequency_table_h
#define frequency_table_h

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

// Exception for coding table
class frequencyTableException : public std::exception {
public: frequencyTableException(std::string const& s);
    
    std::string& what();
    
private:
    std::string message = "Frequency Table Exception: ";
    
};

class frequency_table_entry {
public:
    frequency_table_entry(char c_, double f_);
    
    char get_c();
    
    double& get_frequency();
    
    void print(std::ostream & out = std::cout, bool const eol = true) const;
    
private:
    char c;
    double frequency;
    
};

class frequency_table {
public:
    frequency_table();
    ~frequency_table();
    frequency_table(std::string const * p_text);
    void generate(std::string const* p_text);
    double& get_frequency(char const c);
    size_t get_size() const;
    std::vector<frequency_table_entry*>* get_table();
    void print(std::ostream & out = std::cout) const;
    void clear();
private:
    std::vector<frequency_table_entry*> table;
    std::map<char, int> count_table;
    void sort();
    
};

#endif /* frequency_table_h */
