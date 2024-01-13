#ifndef PART_T_H
#define PART_T_H

#include <string>
#include <vector>
#include <iostream>

namespace parts_list
{
	class storable_t
	{
	public:
		storable_t(storable_t const& src) = delete;
		virtual ~storable_t() = default;

		void store(std::string const& file_name) const;
		virtual void load(std::string const& file_name) = 0;
		
		// need to be public, because access via pointer deref is required 
		virtual void store_rec(std::ostream& out) const = 0;

	protected:
		storable_t() = default;
	};

	class part_t : public storable_t
	{
	protected:
		std::string name;
		static std::string const& get_default_part_name();
		static std::string const& get_regex_pattern();
	public:
		part_t();
		part_t(std::string const& name);
		part_t(part_t const& src) = delete;
		virtual ~part_t() = default;

		std::string const& get_name() const;
		virtual bool equals(part_t const& other) const;

		virtual void load(std::string const& file_name) override;

		// need to be public, because access via pointer deref is required 
		virtual void store_rec(std::ostream& out) const override;
	};

	class composite_part_t : public part_t
	{
		std::vector<part_t*> parts;
		bool loaded{ false };

	public:
		composite_part_t();
		composite_part_t(std::string const& name);
		composite_part_t(composite_part_t const& src) = delete;
		~composite_part_t();

		void add_part(part_t& part);
		std::vector<part_t*>& get_parts();
		std::vector<part_t*> const& get_parts() const;

		virtual bool equals(part_t const& other) const override;

		virtual void load(std::string const& file_name) override;

		// need to be public, because access via pointer deref is required 
		virtual void store_rec(std::ostream& out) const override;
		virtual void load_rec(std::istream& in);
	};
}

#endif // !PART_T_H
