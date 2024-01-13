#include "formatter.h"
#include <iomanip>

void SetFormatter::getStats(PartsLists::Part& p) {
    PartsLists::CompositePart* _CompositePart = dynamic_cast<PartsLists::CompositePart*>(&p);
    if (_CompositePart) {
        if (_CompositePart) {
            for (std::size_t k{ 0 }; k < _CompositePart->getParts().size(); ++k) {
                getStats(*(_CompositePart->getParts()[k]));
                Part current = *(_CompositePart->getParts()[k]);
                this->partStats.count(current.getName())					// check is key available
                    ? this->partStats[current.getName()]++				    // if yes, increase by 1
                    : this->partStats[current.getName()] = 1;			    // else initialize with 1
            }
        }
    }
}

void SetFormatter::printParts(PartsLists::Part &p, std::ostream& out) {
    out << p.getName() << '\n';
    getStats(p);

    for (auto it = this->partStats.begin(); it != this->partStats.end(); it++) {
        out << std::setfill(' ') << std::setw(3) << ' ';
        out << it->first << ": " << it->second << "\n";
        // Access to Key with first
        // Access to Value with second
    }

}

void HierarchyFormatter::printParts(Part& p, std::ostream& out) {
    // wrapper function to include level for indent
    size_t level{ 0 };
    printParts(p, level, out);
}

void HierarchyFormatter::printParts(Part &p, size_t level, std::ostream& out) {

    PartsLists::CompositePart* _CompositePart = dynamic_cast<PartsLists::CompositePart*>(&p);
    if (!_CompositePart) {
        out << "P: ";
    }
    else {
        out << "C: ";
    }
    out << std::setfill(' ') << std::setw(level*2) << "";
    out << p.getName() << "\n";
    if (_CompositePart) {

        for (size_t i{ 0 }; i < _CompositePart->getParts().size(); ++i) {
            // call recursive with next level of Parts/CompositeParts
            printParts(*(_CompositePart->getParts()[i]), level+1, out);
        }
    }
}

