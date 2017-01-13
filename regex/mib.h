#ifndef GP_MIB_GEN_OBJECTS_H_
#define GP_MIB_GEN_OBJECTS_H_

#include <map>
#include "regex.h"

namespace mib
{
	namespace gplus_txt
	{
		struct data
		{
			std::string version;
		};

		const std::regex        reg_pattern
		(
			".*Genesys G-Plus Adapters MIB[[:blank:]]+([[:graph:]]+)"						//	... Genesys G-Plus Adapters MIB (capture #1) ...
			//											   ^(1)
		);
		inline gplus_txt::data	reg_transform(const std::smatch& m)
		{
			const gplus_txt::data d = { m.str(1) };
			return d;
		}
		inline std::string version(const std::string& content)
		{
			gplus_txt::data d;
			const bool res = reg_ex::find(content, gplus_txt::reg_pattern, [&d](const std::smatch& m){
				d = gplus_txt::reg_transform(m);
			});
			if (res)
				return d.version;
			throw std::runtime_error("[gplus_txt::version] not found");
		}
	}// --- namespace 'gplus_txt'

	namespace oid
	{	// <name> OBJECT IDENTIFIER ::= { <parent_oid> <oid> }
		struct data
		{
			std::string name;
			std::string parent;
			std::string id;
		};

		const std::regex reg_pattern
		(
			"([[:alpha:]]+)[[:blank:]]+OBJECT[[:blank:]]+IDENTIFIER\n"						//	(captute #1) OBJECT IDENTIFIER\n
			//   ^(1)
			".*\\{[[:blank:]]*([[:alpha:]]+)[[:blank:]]+([[:digit:]]+)[[:blank:]]*\\}"		//		... {(#2) (#3)}
			//					   ^(2)						 ^(3)
		);

		inline oid::data reg_transform(const std::smatch& m)
		{
			const oid::data d = { m.str(1), m.str(2), m.str(3) };
			return d;
		}

		template <typename UnaryFunction>
		UnaryFunction for_each(const std::string& content, UnaryFunction&& f)
		{
			reg_ex::for_each(content, oid::reg_pattern, [&f](const std::smatch& m) {
				std::forward<UnaryFunction>(f)(oid::reg_transform(m));
			});
			return std::move(f);
		}

	}// --- namespace 'oid'


	namespace otype
	{	// <name> OBJECT-TYPE SYNTAX <mib_type> ... ::= { <parent_oid> <oid> }
		struct data
		{
			std::string name;
			std::string parent;
			std::string id;
			std::string type;	// in C++ terms
		};

		const std::map<std::string, std::string> syntax = 
		{ 
			 {"DisplayString",	"const char*"} 
			,{"Unsigned32",		"unsigned long" }
			,{"TruthValue",		"bool"}
		};

		const std::regex reg_pattern
		(
			"([[:alpha:]]+)[[:blank:]]+OBJECT-TYPE\n"										// (Capture #1) OBJECT-TYPE\n 
			//     ^(1)
			".*SYNTAX[[:blank:]]+([[:alnum:]]+)[[:blank:]]*\n"								//     SYNTAX (#2)\n
			//						  ^(2)
			"(.*\n){1,9}"																	// ...\n (#3)
			// ^(3)
			".*\\{[[:blank:]]*([[:alpha:]]+)[[:blank:]]+([[:digit:]]+)[[:blank:]]*\\}"		// ... {(#4) (#5)}
			//					   ^(4)						  ^(5)
		);
		
		inline otype::data reg_transform(const std::smatch& m)
		{
			const otype::data d = { m.str(1), m.str(4), m.str(5), syntax.at(m.str(2)) };
			return d;
		}

		template <typename UnaryFunction>
		UnaryFunction for_each(const std::string& content, UnaryFunction&& f)
		{
			reg_ex::for_each(content, otype::reg_pattern, [&f](const std::smatch& m) {
				std::forward<UnaryFunction>(f)(otype::reg_transform(m));
			});
			return std::move(f);
		}

	}// --- nanespace 'otype'

	using OBJECT_IDENTIFIER = oid::data;
	using OBJECT_TYPE		= otype::data;

} // namespace 'mib'


#endif // GP_MIB_GEN_OBJECTS_H_
