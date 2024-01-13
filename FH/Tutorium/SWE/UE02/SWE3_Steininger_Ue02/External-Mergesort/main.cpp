#include <iostream>
#include "test_merge_sorter.h"
#include "test_file_maniuplator.h"
using std::cout;
int main() {
    bool r1 = test_merge_sorter::test_sort_unsorted();
    cout << "Result: "<<r1<<"\n\n";

    bool r2 = test_merge_sorter::test_sort_sorted();
    cout << "Result: "<<r2<<"\n\n";

    bool r3 = test_merge_sorter::test_sort_empty();
    cout << "Result: "<<r3<<"\n\n";

    bool r4 = test_merge_sorter::test_sort_random();
    cout << "Result: "<<r4<<"\n\n";

    bool r5 = test_merge_sorter::test_sort_random_long_strings();
    cout << "Result: "<<r5<<"\n\n";

    bool r6 = test_file_maniuplator::test_partitioning_of_file();
    cout << "Result: "<<r6<<"\n\n";

    bool r7 = test_file_maniuplator::test_partitioning_of_file_empty();
    cout << "Result: "<<r7<<"\n\n";

    bool r8 = test_file_maniuplator::test_partitioning_of_file_odd_elements();
    cout << "Result: "<<r8<<"\n\n";

    bool r9 = test_file_maniuplator::test_filling_randomly();
    cout << "Result: "<<r9<<"\n\n";

    bool r10 = test_file_maniuplator::test_filling_randomly_amount_and_length_of_elements();
    cout << "Result: "<<r10<<"\n\n";

    bool r11 = test_file_maniuplator::test_copy_of_file();
    cout << "Result: "<<r11<<"\n\n";

    bool r12 = test_file_maniuplator::test_copy_of_file_empty();
    cout << "Result: "<<r12<<"\n\n";

    bool r13 = test_file_maniuplator::test_copy_container();
    cout << "Result: "<<r13<<"\n\n";

    bool r14 = test_file_maniuplator::test_copy_container_empty();
    cout << "Result: "<<r14<<"\n\n";

    bool r15 = test_file_maniuplator::test_print();
    cout << "Result: "<<r15<<"\n\n";

    bool r16 = test_file_maniuplator::test_print_empty();
    cout << "Result: "<<r16<<"\n\n";

    return 0;
}
