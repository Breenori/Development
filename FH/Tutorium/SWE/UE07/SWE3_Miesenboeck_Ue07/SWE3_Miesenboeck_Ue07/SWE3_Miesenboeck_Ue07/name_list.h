#pragma once

#include <map>
#include <iostream>
#include <string>

namespace xpr
{

	// abstract class
	template<typename T>
	class name_list
	{

	public:

		name_list() {}
		// has to be virtual because of pure virtual functions
		virtual ~name_list() {}

		// pure virtual functions
		virtual T lookup_var(std::string const& name) = 0;
		virtual void register_var(std::string const& name, T const& value) = 0;
		virtual void print(std::ostream& os) const = 0;

	};

	template<typename T>
	class name_list_map : public name_list<T>
	{

	public:

		// CONSTRUCTOR
		name_list_map() {}

		// DESTRUCTOR
		virtual ~name_list_map()
		{
			for (auto it = name_list.begin(); it != name_list.end(); ++it)
			{
				delete it->second;
			}
		}

		// return tree in name_list as variable 'name'
		virtual T lookup_var(std::string const& name) override
		{
			return name_list[name];
		}

		// register tree as variable 'name' in name_list
		virtual void register_var(std::string const& name, T const& value) override
		{
			// if name already in name_list --> delete entry
			if (lookup_var(name) != nullptr)
			{
				delete name_list[name];
				name_list[name] = nullptr;
			}
			// register in name_list
			name_list[name] = value;
		}

		// print name_list
		virtual void print(std::ostream& os) const override
		{
			// iterate through name_list and print if not nullptr
			for (auto it = name_list.begin(); it != name_list.end(); ++it)
			{
				if (it->second != nullptr) {
					os << it->first << ": " << it->second << std::endl;
				}
			}
		}



	private:

		//name_list
		std::map<std::string, T> name_list;

	};

}
