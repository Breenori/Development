//
// Created by Anja Schwab on 25.12.22.
//

#include <sstream>
#include "part.h"

bool parts_list::part::equals(part * other) {
    return name == other->name;
}

string parts_list::part::get_name() const {
    return name;
}

parts_list::part::part(string name_):name(name_) {

}

void parts_list::composite_part::load(string const & filename) {
    std::ifstream in{filename};
    std::map<string,part*> map;
    string temp = "";
    int temp_num = 0;

    string instructions;
    std::getline(in,instructions);
    std::stringstream instructions_s{instructions};

    delete_parts();
    while (in.good()){
        string composite_part_name;
        vector<part * > parts;
        std::getline(in,temp);
        std::stringstream all_composite_parts{temp};
        all_composite_parts >> composite_part_name;
        if (map.count(composite_part_name)==0){
            while (all_composite_parts.good()){
                all_composite_parts >> temp;
                all_composite_parts >> temp_num;
                if(map.count(temp)!=0){//part exists already and doesn't need to be created
                    for (int i = 0; i < temp_num; ++i) {
                        parts.push_back(map[temp]);
                    }
                }
                else{
                    part * temp_part = new part(temp);
                    for (int i = 0; i < temp_num; ++i) {
                        parts.push_back(temp_part);
                    }
                }
            }
            map[composite_part_name] = new composite_part(composite_part_name, parts);
        }
    }
    instructions_s >> name;
    while (instructions_s.good()){
        instructions_s>> temp;
        instructions_s>> temp_num;
        for (int i = 0; i < temp_num; ++i) {
            add_part(map[temp]);
        }
    }
}

void parts_list::composite_part::add_part(part * p) {
    all_parts.push_back(p);
}

parts_list::composite_part::composite_part(string name_) : part(name_) {
    all_parts = {};
}

parts_list::composite_part::composite_part(string name_, const vector<part *> &parts_list): part(name_) {
    all_parts = parts_list;
}

vector<parts_list::part *> &parts_list::composite_part::get_parts() {
    return all_parts;
}

bool parts_list::operator==(const parts_list::composite_part &lhs, const parts_list::composite_part &rhs) {
    if (lhs.all_parts.size() == rhs.all_parts.size()){
        for (int i = 0; i < lhs.all_parts.size(); ++i) {
            if (!lhs.all_parts[i]->equals(rhs.all_parts[i])){
                return false;
            }
        }
    }
    else{
        return false;// vectors of different size cannot be the same
    }
    return true;
}

parts_list::composite_part::~composite_part() {
    delete_parts();
}

void parts_list::composite_part::delete_parts() {
    delete_parts_rec(this);
}

void parts_list::composite_part::delete_parts_rec(parts_list::part *p) {
    parts_list::composite_part *comp_part = dynamic_cast<parts_list::composite_part * >(p);
    if (comp_part != nullptr) {//composite part - only need to go through recursively if it is a composite part
        vector<parts_list::part *> all_parts = comp_part->get_parts();
        for (int i = 0; i < all_parts.size(); ++i) {//go through all parts that it is made of
            delete_parts_rec(all_parts[i]);//print part
        }
    }
    else{
        if (p!= nullptr){
            delete p;
        }
        p = nullptr;
    }
    all_parts.clear();
}

void parts_list::composite_part::store(const string &filename) {
    std::ofstream out{filename};
    vector<string> all_lines;
    all_lines.push_back(get_line(name,this->get_parts()));
    store_rec(out,this,all_lines);
    for (int i = 0; i < all_lines.size(); ++i) {
        out<< all_lines[i];
    }
}

void parts_list::composite_part::store_rec(std::ostream &out, part * part, std::vector<string> & all_lines) {
    parts_list::composite_part *comp_part = dynamic_cast<parts_list::composite_part * >(part);
    if (comp_part != nullptr) {//composite part - only need to go through recursively if it is a composite part
        std::vector<parts_list::part *> all_parts = comp_part->get_parts();
        for (int i = 0; i < all_parts.size(); ++i) {//go through all parts that it is made of
            store_rec(out,all_parts[i], all_lines);//print part
            string temp;
            temp = get_line(comp_part->get_name(),all_parts);
            if (std::find(all_lines.begin(), all_lines.end(),temp)==all_lines.end()){
                all_lines.push_back(temp);
            }
        }
    }
}

string parts_list::composite_part::get_line(string name, vector<part *> p) {
    string line;
    line = name;
    std::map<std::string,int> map;
    for (int i = 0; i < p.size(); ++i) {
        string temp = p[i]->get_name();
        if(map.count(temp)==0){
            map[temp]=1;
        }
        else{
            map[temp]++;
        }
    }
    for (const auto &[key, value]: map) {//for each key-value-pair in map
        line += " " + key + " " + std::to_string(value) +" ";
    }
    line +="\n";
    return line;
}

bool parts_list::composite_part::equals(parts_list::part *other) {
    parts_list::composite_part *comp_part = dynamic_cast<parts_list::composite_part * >(part);
    if (comp_part != nullptr) {//composite part - only need to go through recursively if it is a composite part
        if (comp_part->get_parts().size() == all_parts.size()){
            for (int i = 0; i < all_parts.size(); ++i) {
                if(!all_parts[i]->equals(comp_part->get_parts()[i])){
                    return false;//not the same parts
                }
            }
            return true;
        }
    }
    return false;//not same size or compare part with composite part
}




