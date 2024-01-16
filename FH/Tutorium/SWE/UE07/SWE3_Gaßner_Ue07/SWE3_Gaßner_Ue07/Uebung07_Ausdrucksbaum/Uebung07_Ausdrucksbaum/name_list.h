#ifndef name_list_h
#define name_list_h

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
			for (auto it = name_list.begin(); it != name_list.end(); ++it) {
				delete it->second;
			}
		}

		virtual T lookup_var(std::string name) {
			return name_list[name];
		}

		virtual void register_var(std::string name, T value) {
			name_list[name] = value; // will overwrite value if exists
		}

		virtual void print(std::ostream& os) {
			for (auto it = name_list.begin(); it != name_list.end(); ++it) {
				os << it->first << ": " << it->second << "\n";
			}
		}

	private:
		std::map<std::string, T> name_list;
	};

}


#endif // !name_list_h
