#ifndef NAME_LIST_H
#define NAME_LIST_H

#include <string>
#include <map>
#include <iostream>
#include "exceptions.h"

namespace xpr {

	template<typename T> class NameList {
	public:
		virtual ~NameList(){};

		virtual T lookup_var(std::string const& _name_) 						= 0;
		virtual void register_var(std::string const& _name_, T const& _value_)	= 0;
		virtual std::ostream& print(std::ostream& _out_ = std::cout) const		= 0;

	};

	template<typename T> class NameListMap : public NameList<T> {
	public:
		NameListMap() = default;

		~NameListMap() {

			for (auto it = name_list.begin(); it != name_list.end(); ++it) {
				if (it->second != nullptr) {
					delete it->second;
					it->second = nullptr;
				}
			}

		}

		T lookup_var(std::string const& _name_) override {
			T value = get_var(_name_); return value;
		}

		void register_var(std::string const& _name_, T const& _value_) override {
			set_var(_name_, _value_);
		}

		std::ostream& print(std::ostream& _out_ = std::cout) const override {
			print_map(_out_); return _out_;
		}

	private:
		std::map<std::string, T> name_list;

		T get_var(std::string const& _name_) {
			if (!contains_var(_name_))
				throw VariableNotFound("Variable " + _name_ + " not registered!\n");

			return name_list[_name_];
		}

		void set_var(std::string const& _name_, T const& _value_) {
			if (contains_var(_name_)) {
				delete name_list[_name_];
				name_list[_name_] = nullptr;
			}

			name_list[_name_] = _value_;
		}

		std::ostream& print_map(std::ostream& _out_) const {
			for (auto it = name_list.begin(); it != name_list.end(); ++it)
				_out_ << it->first << ": " << it->second << "\n";

			return _out_;
		}

		bool contains_var(std::string const& _name_) const {
			return name_list.contains(_name_);
		}

	};

}

#endif // !NAME_LIST_H