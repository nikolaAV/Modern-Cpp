#ifndef GP_MIB_GEN_CMDLINE_H_
#define GP_MIB_GEN_CMDLINE_H_

#include <string>
#include <sstream>
#include <stdexcept>

namespace input
{
	inline std::string usage(const std::string& app_name)
	{
		std::stringstream out;
		out << "Usage: " << app_name << " mib_file template_file [out_file]" << std::endl
			<< "\tif out_file is not specified then the result will be saved in template_file.h" << std::endl;
		return out.str();
	}

	struct data
	{
		std::string mib_file;
		std::string template_file;
		std::string out_file;
	};

	inline input::data read(int argc, char** argv)
	{
		// expected
			// app.exe <mib.txt> <gp.template> <gp_mib.h>
			// app.exe <mib.txt> <gp.template>
		if (argc < 3)
			throw std::invalid_argument(std::string("Invalid input arguments in command line\n")+usage(argv[0]));

		const data d = {
			 argv[1]
			,argv[2]
			,argc >= 4 ? argv[3] : (std::string(argv[2])+=".h").c_str()
		};
		return d;
	}

}	// namespace 'reg_ex'


#endif // GP_MIB_GEN_CMDLINE_H_
