#include <string>
#include <iostream>
#include <exception>
#include <sstream>

#include "cmd_line.h"
#include "file.h"
#include "mib.h"

using namespace std;


string definitions(const string& mib_content)
{
	stringstream out;
	mib::oid::for_each(mib_content, [&out](const mib::OBJECT_IDENTIFIER& d) {
		out << "const snmp::oid " << d.name << "\t(" << d.parent << " + " << d.id << ");" << endl;
	});
	out << endl;
	mib::otype::for_each(mib_content, [&out](const mib::OBJECT_TYPE& d) {
		out << "GSNMP_DEFINE_VARIABLE(" << d.name << ",\t" << d.type << ",\t(" << d.parent << ",\t + " << d.id << ");" << endl;
	});
	return out.str();
}


void generate(const input::data& in)
{
	const string	mib_content{ file::read(in.mib_file) };
	string			out_content{ file::read(in.template_file) };

	out_content = regex_replace(out_content, regex("@REPLACE_GP_GENERATOR_VERSION@"),	string("1.00"));
	out_content = regex_replace(out_content, regex("@REPLACE_GP_MIBTXT_VERSION@"),		mib::gplus_txt::version(mib_content));
	out_content = regex_replace(out_content, regex("@REPLACE_GP_DEFINITIONS@"),			definitions(mib_content));

	file::open<ofstream>(in.out_file) << out_content;
}

int main(int argc, char** argv)
{
	try
	{
		//generate(input::read(argc, argv));
		generate({ "GPLUS-MIB.txt", "gp_mib.template", "gp_mib.template.h" });
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}

	cout << "Operation completed successfully" << endl;
	return 0;
}
