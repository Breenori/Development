#include "ext_merge_sort_test.h"


void ext_merge_sort_test::ems_test_1()
{
	merge_sorter::sort("test_files/sort1.txt", true, true,"test_files/sorted1.txt");
}

void ext_merge_sort_test::ems_test_2()
{
	merge_sorter::sort("test_files/sort2.txt", true, true, "test_files/sorted2.txt");
}

void ext_merge_sort_test::ems_test_3()
{
	merge_sorter::sort("", true, true, "test_files/sorted2.txt");
}

void ext_merge_sort_test::ems_test_4()
{
	merge_sorter::sort("test_files/sort4.txt", true, true, "");
}

void ext_merge_sort_test::ems_test_5()
{
	merge_sorter::sort("test_files/sort5.txt", true, true, "test_files/sorted5.txt");
}

void ext_merge_sort_test::ems_test_6()
{
	merge_sorter::sort("test_files/sort6.txt", true, true);
}

void ext_merge_sort_test::ems_test_7()
{
	merge_sorter::sort("test_files/sort7.txt", true, true,"test_files/sorted7.txt");
}

void ext_merge_sort_test::ems_test_8()
{
	merge_sorter::sort("test_files/sort8.txt", true, true, "test_files/sorted8.txt");
}

void ext_merge_sort_test::ems_test_9()
{
	merge_sorter::sort("test_files/sort9.txt", true, true, "test_files/sorted9.txt");
}

void ext_merge_sort_test::ems_test_10()
{
	merge_sorter::sort("test_files/sort10.txt", true, true, "test_files/sorted10.txt");
}

void ext_merge_sort_test::ems_test_11()
{
	merge_sorter::sort("test_files/sort11.txt", true, true, "test_files/sorted11.txt");
}

void ext_merge_sort_test::ems_test_12()
{
	merge_sorter::sort("test_files/sort12.txt", true, true, "test_files/sorted12.txt");
}

void ext_merge_sort_test::ems_test_13()
{
	merge_sorter::sort("test_files/sort13.txt", true, true, "test_files/sorted13.txt");
}

void ext_merge_sort_test::ems_test_14()
{
	merge_sorter::sort("test_files/sort14.txt", true, true, "test_files/sorted14.txt");
}

void ext_merge_sort_test::ems_test_15()
{
	merge_sorter::sort("test_files/sort15.txt", true, true, "test_files/sorted15.txt");
}

void ext_merge_sort_test::ems_test_16()
{
	merge_sorter::sort("test_files/sort16.txt", true, false, "test_files/sorted16.txt");
}

void ext_merge_sort_test::ems_test_17()
{
	merge_sorter::sort("test_files/sort17.txt", true, false, "test_files/sorted17.txt");
}

void ext_merge_sort_test::ems_test_18()
{
	merge_sorter::sort("test_files/sort18.txt", true, true, "test_files/sorted18.txt");
}

void ext_merge_sort_test::ems_test_19()
{
	merge_sorter::sort("test_files/sort19.txt", false, true, "test_files/sorted19.txt");
}

void ext_merge_sort_test::ems_test_20()
{
	merge_sorter::sort("test_files/sort20.txt", false, false, "test_files/sorted20.txt");
}

void ext_merge_sort_test::ems_test_21()
{
	merge_sorter::sort("test_files/sort21.txt", false, true, "test_files/sorted21.txt");
}

void ext_merge_sort_test::ems_test_22()
{
	file_manipulator::fill_randomly("test_files/sort22.txt", 150, 3);
	merge_sorter::sort("test_files/sort22.txt", false, true, "test_files/sorted22.txt");
}

void ext_merge_sort_test::ems_test_23()
{
	file_manipulator::fill_randomly("test_files/sort23.txt", 150, 1);
	merge_sorter::sort("test_files/sort23.txt", false, true, "test_files/sorted23.txt");
}

void ext_merge_sort_test::ems_test_24()
{
	merge_sorter::sort("test_files/sort24.txt", true, true, "test_files/sorted24.txt");
}

void ext_merge_sort_test::ems_test_25()
{
	file_manipulator::cont_t_str out{ "test_files/f0.txt","test_files/f1.txt" };

	std::cout << "Original file: ";
	file_manipulator::write_to_console("test_files/part1.txt");

	std::cout << "Amount of partitioned values: " << file_manipulator::partition("test_files/part1.txt", out);

	std::cout << std::endl << "Partition 1: ";
	file_manipulator::write_to_console("test_files/f0.txt");
	std::cout << "Partition 2: ";
	file_manipulator::write_to_console("test_files/f1.txt");
}

void ext_merge_sort_test::ems_test_26()
{
	file_manipulator::cont_t_str out{ "test_files/f0.txt","test_files/f1.txt" };

	std::cout << "Original file: ";
	file_manipulator::write_to_console("test_files/part2.txt");

	std::cout << "Amount of partitioned values: " << file_manipulator::partition("test_files/part2.txt", out);

	std::cout << std::endl << "Partition 1: ";
	file_manipulator::write_to_console("test_files/f0.txt");
	std::cout << "Partition 2: ";
	file_manipulator::write_to_console("test_files/f1.txt");
}

void ext_merge_sort_test::ems_test_27()
{
	file_manipulator::cont_t_str out{ "test_files/f0.txt","test_files/f1.txt" };

	std::cout << "Original file: ";
	file_manipulator::write_to_console("test_files/part3.txt");

	std::cout << "Amount of partitioned values: " << file_manipulator::partition("test_files/part3.txt", out);

	std::cout << std::endl << "Partition 1: ";
	file_manipulator::write_to_console("test_files/f0.txt");
	std::cout << "Partition 2: ";
	file_manipulator::write_to_console("test_files/f1.txt");
}

void ext_merge_sort_test::ems_test_28()
{
	file_manipulator::cont_t_str out{ "test_files/f0.txt","test_files/f1.txt" };

	std::cout << "Original file: ";
	file_manipulator::write_to_console("test_files/part4.txt");

	std::cout << "Amount of partitioned values: " << file_manipulator::partition("test_files/part4.txt", out);

	std::cout << std::endl << "Partition 1: ";
	file_manipulator::write_to_console("test_files/f0.txt");
	std::cout << "Partition 2: ";
	file_manipulator::write_to_console("test_files/f1.txt");
}

void ext_merge_sort_test::ems_test_29()
{
	file_manipulator::cont_t_str out{ "test_files/f0.txt","test_files/f1.txt" };

	std::cout << "Original file: ";
	file_manipulator::write_to_console("test_files/part5.txt");

	std::cout << "Amount of partitioned values: " << file_manipulator::partition("test_files/part5.txt", out);

	std::cout << std::endl << "Partition 1: ";
	file_manipulator::write_to_console("test_files/f0.txt");
	std::cout << "Partition 2: ";
	file_manipulator::write_to_console("test_files/f1.txt");
}

//
//file_manipulator::fill_randomly("file_to_sort.txt", 1500, 3);
//file_manipulator::write_to_console("file_to_sort.txt");
//file_manipulator::copy("f0.txt", "fcpy.txt");