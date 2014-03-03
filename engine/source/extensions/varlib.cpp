/* varlib.cpp
 * pkbasic test library
 * reads all variables
 * useless, but it's a test
 */


#include <iostream>
#include "pkb_plib.h"

using namespace std;

const string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

int main(int argc, char* argv[]) {
	if (argc != 4) {
		cout << "invocation failed\n";
		return 1;
	}
//	cout << "\nvardump: " << argv[1] << "\ninvocation: " << argv[2] << "\noutput: " << argv[3] << '\n';
	string vd,invoc;
//	cout << "invoked vars\n";
	try {
		vd = argv[1]; invoc = argv[2];
	} catch (int e) {
		cout << "failed to init vars";
	}
//	cout << "set vd and invoc\n";
	try {
		if (!plib::import_varlist(vd)) {
			cout << "\nfailed to read variables";
			return 1;
		}
	} catch (int e) {
		cout << "\ncritical error (" << e << ") occurred reading variables\n";
	}
//	cout << "read variables\n";
	try {
		plib::Parsedcmd pcmd = plib::parsecmd(invoc);
	} catch (int e) {
		cout << "critical error (" << e << ") occured while parsing input";
	}
//	cout << "parsed input\n";

	try {
		cout << "register | str  | float\n";
		for (int c = 0; c < letters.size(); c++) {
			cout << "     [" << letters.at(c) << "] | $(" << plib::sreg[c] << ") | #(" << plib::ireg[c] << ")\n";
		}
	} catch (int e) {
		cout << "reading variables failed with " << e;
	}
//	cout << "listed vars\n";
	ofstream ofile;
	ofile.open(argv[3]);
	ofile << "skip";
	ofile.close();
//	cout << "wrote outfile\n";
	return 0;
}
