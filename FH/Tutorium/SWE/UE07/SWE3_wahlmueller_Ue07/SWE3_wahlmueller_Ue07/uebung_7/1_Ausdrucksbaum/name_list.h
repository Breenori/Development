#ifndef NAME_LIST_H
#define NAME_LIST_H

#include <map>
#include <iostream>

#include <string>

using std::map;
using std::string;

using std::ostream;

namespace xpr {

	//only passed pointer is copied
	//interface
	template<typename T>
	class NameList{
	public:
		NameList() {};
		virtual ~NameList() {};

		virtual T lookup_var(string name) = 0;
		virtual void register_var(string name, T value) = 0;
		virtual void print(ostream& os) = 0;

	};

	template<typename T>
	class NameListMap: public NameList<T>{
	public:
		NameListMap() {};
		virtual ~NameListMap() {

			for (auto it = name_list.begin(); it != name_list.end(); it++){

				delete it->second;

			}

		}

		virtual T lookup_var(string name) {
		
			return name_list[name];
		
		}

		virtual void register_var(string name, T value) {
		
			name_list[name] = value;
		
		}

		virtual void print(ostream& os) {

			for (auto it = name_list.begin(); it != name_list.end(); it++){

				os << it->first << ": " << "\n";
				it->second->print(os);
				os << "\n\n2d print:\n";
				it->second->print_2d(os);
				os << "\n\n2d upright print:\n";
				it->second->print_2d_upright(os);

			}

		}

	private:
		//is sorted by default
		map<string, T> name_list;

	};

};


#endif