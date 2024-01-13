#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

namespace PartsList {
    // Basisklasse "Teil"
    class Part {
    public:
        //Standartkonstruktor für "Teil"
        Part(const std::string& name) : name_(name) {}

        //Virtuelle funktion um den privaten Namen zu erhalten
        virtual std::string getName() const { return name_; }

        //Prüft die Gleichheit zweier Teile
        bool equals(const Part& o) const { return name_ == o.name_; }

        //Methode, um das Teil persistent zu speichern
        virtual void store(std::ofstream& out) const {
            out << name_ << '\n';
        }

    private:
        std::string name_;
    };

    // Klasse "Zusammengesetztes Teil"
    class CompositePart : public Part {
    public:
        // Standartkonstruktor für "Zusammengesetztes Teil"
        CompositePart(const std::string& name) : Part(name) {}

        // Hinzufügen eines Teils
        void addPart(Part* p) { parts_.push_back(p); }

        std::vector<Part*> getParts() const { return parts_; }

        // Überschreiben der store-Methode von Part, um auch die Teile des CompositeParts zu speichern
        void store(std::ofstream& out) const {
            out << getName() << '\n';
            for (const auto& part : parts_) {
                part->store(out);
            }
        }

        // Überschreiben der load-Methode von Part, um auch die Teile des CompositeParts zu laden
        static CompositePart* load(std::ifstream& in) {
            // Lesen des Namens des zusammengesetzten Teils aus der Datei
            std::string name;
            in >> name;

            // Erstelle ein neues zusammengesetztes Teil mit dem gelesenen Namen
            auto* composite_part = new CompositePart(name);

            // Lese die Anzahl der Teile aus der Datei
            int num_parts;
            in >> num_parts;

            // Lade die Teile aus der Datei
            for (int i = 0; i < num_parts; i++) {
                // Lese den Typ des Teils aus der Datei
                std::string part_type;
                in >> part_type;

                if (part_type == "CompositePart") {
                    // Lade das zusammengesetzte Teil aus der Datei
                    auto* subpart = CompositePart::load(in);
                    composite_part->addPart(subpart);
                }
                else if (part_type == "Part") {
                    // Lese den Namen des Teils aus der Datei
                    std::string part_name;
                    in >> part_name;

                    // Erstelle ein neues Teil mit dem gelesenen Namen
                    auto* subpart = new Part(part_name);
                    composite_part->addPart(subpart);
                }
            }
            return composite_part;
        }

    private:
        std::vector<Part*> parts_;
    };


    // Basisklasse "Formatter"
    class Formatter {              //Nur ein Interface also kann die Basisklasse alleine nicht Instanziert werden
    public:
        virtual void printParts(const Part& p) = 0;
    };

    // Klasse "SetFormatter"
    class SetFormatter : public Formatter {
    public:
        //Haupt Print Funktion die auch von außen aufgerufen werden kann
        void printParts(const Part& p) override {
            std::cout << p.getName() << ":\n";
            std::map<std::string, int> count_map;
            printPartsRecursive(p, count_map);
            for (const auto& kv : count_map) {
                std::cout << kv.second << ' ' << kv.first << '\n';
            }
        }

    private:
        //Recursive Funktion um auch alle Unterteile zu finden
        void printPartsRecursive(const Part& p, std::map<std::string, int>& count_map) {
            auto cp = dynamic_cast<const CompositePart*>(&p);
            if (cp) {
                for (const auto& subpart : cp->getParts()) {
                    // Zähle das Teil nur dann, wenn es kein CompositePart ist
                    if (!dynamic_cast<const CompositePart*>(subpart)) {
                        count_map[subpart->getName()]++;
                    }
                    // Führe die Rekursion fort, auch wenn das Teil ein CompositePart ist
                    printPartsRecursive(*subpart, count_map);
                }
            }
        }
    };

    // Klasse "HierarchyFormatter"
    class HierarchyFormatter : public Formatter {
    public:
        //Haupt Print Funktion die auch von außen aufgerufen werden kann
        void printParts(const Part& p) override {
            std::cout << p.getName() << '\n';
            printPartsRecursive(p, 1);
        }

    private:
        //Recursive Funktion um auch alle Unterteile zu finden
        void printPartsRecursive(const Part& p, int indent) {
            auto cp = dynamic_cast<const CompositePart*>(&p);
            if (cp) {
                for (const auto& subpart : cp->getParts()) {
                    std::cout << std::string(indent, '\t') << subpart->getName() << '\n';
                    printPartsRecursive(*subpart, indent + 1);
                }
            }
        }
    };
}
