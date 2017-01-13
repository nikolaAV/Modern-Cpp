#ifndef GP_MIB_GEN_FILE_H_
#define GP_MIB_GEN_FILE_H_

#include <fstream>
#include <exception>
#include <string>
#include <sstream>

namespace file
{
	/**
	Opens the file whose name is specified 'filename' and associates it with a stream that can be used in future operations

	@param [in]		filename	A string containing the name of the file to be opened.
								Its value shall follow the file name specifications of the running environment and can include a path (if supported by the system).
	@param [in]		FILE_STREAM		type which specifies required stream to be opened.
									ifstream - input stream to operate on files
									ofstream  - output stream to operate on files
									fstream   - input/output
	@retval			an object of the requested file stream, in case of success
	@exception		if file cannot be opened, std::runtime_error will be thrown

	Example usage:
	@code
		auto f1 = open<std::ifstream>("file.h");
		string content = read(f1);
		auto f2 = open<std::ofstream>("output.txt");
		f2 << "test" << endl;
	@endcode
	*/

	template <typename FILE_STREAM>
	FILE_STREAM open(const std::string& filename)
	{
		FILE_STREAM fs{ filename };
		if (!fs)
			throw std::runtime_error{ "cannot open file: " + filename };
		return fs;
	}

	std::string read(std::ifstream&& ifs)
	{
		std::string				line;
		std::stringstream		out;
		while (std::getline(ifs, line))
			out << line << std::endl;
		return out.str();
	}

	/**
	Opens in 'reading' mode, reads and closes the file whose name is specified 'filename'

	@param [in]		filename	A string containing the name of the file to be opened.
	@retval			a string which is a content of the file
	@exception		in case of failure, std::runtime_error will be thrown

	Example usage:
	@code
		auto file = read("file.h");
		cout << file << endl;
	@endcode
	*/

	inline std::string read(const std::string& filename)
	{
		return file::read(file::open<std::ifstream>(filename));
	}

}	// namespace 'file'


#endif // GP_MIB_GEN_FILE_H_
