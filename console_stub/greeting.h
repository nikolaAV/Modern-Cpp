#ifndef CPP_COMPILER_GREETING_H_
#define CPP_COMPILER_GREETING_H_

#include <sstream>

namespace compiler
{

#ifdef _MSC_VER
    template <size_t>   const char* visual_studio_title()       { return "???"; };
    template <>         const char* visual_studio_title<1700>() { return "VS 2012"; }
    template <>         const char* visual_studio_title<1800>() { return "VS 2013"; }
    template <>         const char* visual_studio_title<1900>() { return "VS 2015"; }
#endif

	static std::string greeting()
	{
		std::stringstream out;

    #if defined (_MSC_VER)
			out << "Microsoft (R) C/C++ Compiler: " << _MSC_FULL_VER << " (" << visual_studio_title<_MSC_VER>() << ")";
	#elif defined (__GNUC__)
			out << "GNU GCC Compiler: " << __VERSION__;
	#else
	#error  A C++ compiler is unknown!
	#endif

		return out.str();
	}

}	// namespace 'compiler'

#endif // CPP_COMPILER_GREETING_H_
