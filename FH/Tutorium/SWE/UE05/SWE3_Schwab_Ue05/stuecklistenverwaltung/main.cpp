#include <iostream>
#include"part.h"
#include"formatter.h"
int main() {

    parts_list::part bein_k("bein (klein)");
    parts_list::part bein_g("bein (groß)");
    parts_list::part sitz("sitzfläche");
    parts_list::part tisch_p("tischfläche");

    vector<parts_list::part *> sessel_vektor{&bein_k,&bein_k,&bein_k,&bein_k,&sitz};
    vector<parts_list::part *> tisch_vektor{&bein_g,&bein_g,&bein_g,&bein_g,&tisch_p};

    parts_list::composite_part sessel("sessel",sessel_vektor);
    parts_list::composite_part tisch("tisch",tisch_vektor);

    vector<parts_list::part *> sitzgarnitur_vektor{&sessel,&sessel, &tisch};
    parts_list::composite_part sitzgarnitur("sitzgarnitur",sitzgarnitur_vektor);


    formatters::hierachy_formatter f1;
    f1.print_parts(&sitzgarnitur, std::cout);

    formatters::set_formatter f2;
    f2.print_parts(&sitzgarnitur,std::cout);

    parts_list::composite_part p("");
    p.load("storage.txt");

    f1.print_parts(&p,std::cout);
    f2.print_parts(&p,std::cout);

    p.store("test.txt");

    return 0;
}
