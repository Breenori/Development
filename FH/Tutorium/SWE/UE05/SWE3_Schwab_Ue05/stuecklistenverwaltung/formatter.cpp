//
// Created by Anja Schwab on 25.12.22.
//

#include <iomanip>
#include "formatter.h"

void formatters::set_formatter::print_parts(parts_list::part *p, std::ostream &out) {
    // Safely converts pointers to classes along the inheritance hierarchy.
    out << p->get_name() << "\n";
    parts_list::composite_part *comp_part = dynamic_cast<parts_list::composite_part *>(p);
    if (comp_part != nullptr) {

        std::map<std::string, int> num_each_part = count_parts(comp_part->get_parts());
        for (const auto &[key, value]: num_each_part) {//for each key-value-pair in map
            std::cout << value << " " << key << "\n";
        }
    }
}

std::map<string, int> formatters::set_formatter::count_parts(vector<parts_list::part *> const &parts) {
    std::map<std::string, int> num_each_part;
    count_parts_rec(parts, num_each_part);
    return num_each_part;
}

void formatters::set_formatter::count_parts_rec(vector<parts_list::part *> const &parts, std::map<string, int> &map) {
    for (int i = 0; i < parts.size(); ++i) {
        string temp_name = parts[i]->get_name();
        parts_list::composite_part *temp_part = dynamic_cast<parts_list::composite_part *>(parts[i]);
        if (temp_part != nullptr) {//composite part
            count_parts_rec(temp_part->get_parts(), map);
        } else {//atomic part
            //if the key exists increase the count - otherwise insert into map with value 1
            map.count(temp_name) == 0 ? map[temp_name] = 1 : map[temp_name]++;
        }
    }
}

void formatters::hierachy_formatter::print_parts(parts_list::part *p, std::ostream &out) {
    print_parts_rec(p, out, 0);//go through all the parts recursively
}


void formatters::hierachy_formatter::print_parts_rec(parts_list::part *p, std::ostream &out, int level) {
    for (int i = 0; i < level; ++i) {
        out<<"\t";
    }
    out << p->get_name() << "\n";
    // Safely converts pointers to classes along the inheritance hierarchy.
    parts_list::composite_part *comp_part = dynamic_cast<parts_list::composite_part * >(p);
    if (comp_part != nullptr) {//composite part - only need to go through recursively if it is a composite part
        vector<parts_list::part *> all_parts = comp_part->get_parts();
        for (int i = 0; i < all_parts.size(); ++i) {//go through all parts that it is made of
            print_parts_rec(all_parts[i], out, level + 1);//print part
        }
    }
}
