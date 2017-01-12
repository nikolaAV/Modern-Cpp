#include <string>
#include <iostream>
#include "greeting.h"

using namespace std;

int main(int /*argc*/, char** /*argv[]*/)
{
	cout << compiler::greeting() << endl;
    cout << "Press any key + <enter> to exit" << endl;
	cin.get();
	return 0;
}
