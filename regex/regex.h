#ifndef GP_MIB_GEN_REGEX_H_
#define GP_MIB_GEN_REGEX_H_

#include <string>
#include <regex>
#include <utility>

namespace reg_ex
{
	/**
		Applies the given function object f to each macth in the target sequence of symbols, in order.

		@param [in]		content	A string with the target sequence (the subject) to be searched for a match of 'reg' expression
		@param [in]		reg		The pattern to match. Syntax is used to construct regex objects (or assign) that have selected ECMAScript as its grammar
		@param [in,out]	f		Unary function that accepts an match-subset of 'const std::smatch' type in 'content' as argument.
								Unary function requires concept::MoveConstructible<UnaryFunction> && ::Callable<UnaryFunction> with operator()(const std::smatch&)
								This can either be a function pointer, lambda expression or a move constructible function object.
								Its return value, if any, is ignored.
		@return			f
		@exception		regex_error and any exception which can be thrown by f

		Example usage:
		@code
						string data =	"<person>\n"
										"<first>Bjarne</first>\n"
										"<last>Stroustrup</last>\n"
										"</person>\n"
						regex reg("<(.*)>(.*)</(\\1)>");	// <-- ECMAScript
						for_each(data,reg,[](const std::smatch& m){
							cout << "match:" << m.str << ", tag: " << m.str(1) << ", value: " << m.str(2) << endl; 
						});														
		@endcode
		@see http://www.cplusplus.com/reference/regex/ECMAScript/	
	*/

	template <typename UnaryFunction>
	UnaryFunction for_each(const std::string& content, const std::regex& reg, UnaryFunction&& f)
	{
		std::sregex_iterator iter(content.cbegin(), content.cend(), reg);
		for (; iter != std::sregex_iterator(); ++iter)
			std::forward<UnaryFunction>(f)(*iter);
		return std::move(f);
	}

	template <typename UnaryFunction>
		// requires concept::callable<UnaryFunction> with operator()(const std::smatch&)
	bool find(const std::string& content, const std::regex& reg, UnaryFunction&& f)
	{
		std::smatch m;
		const bool res = std::regex_search(content, m, reg);
		if (res)
			std::forward<UnaryFunction>(f)(m);
		return res;
	}

}	// namespace 'reg_ex'


#endif // GP_MIB_GEN_REGEX_H_
