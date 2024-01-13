#ifndef NAME_LIST_H
#define NAME_LIST_H

#include <map>
#include <iostream>
#include <string>

namespace xpr {

	template<typename T>
	class NameList {
	public:
		NameList() {}
		virtual ~NameList() {}
		virtual T lookup_var(std::string name) = 0;
		virtual void register_var(std::string name, T value) = 0;
		virtual void print(std::ostream& os) = 0;
	};
	
	template<typename T>
	class NameListMap : public NameList<T> {
	public:
		NameListMap() {}

		virtual ~NameListMap() {
			for (auto it = name_list.begin(); it != name_list.end(); it++) {
				delete it->second;
			}
		}

		virtual T lookup_var(std::string name) override {
			return name_list[name];
		}

		// adding a new identifier
		virtual void register_var(std::string name, T value) override {
			name_list[name] = value;
		}

		// print function that prints out key and value
		virtual void print(std::ostream& os) {
			for (auto it = name_list.begin(); it != name_list.end(); it++) {
				os << it->first << ": " << it->second << "\n";
			}
		}

	private:
		// using a map to save identifiers and their values
		std::map<std::string, T> name_list;
	};

}

#endif