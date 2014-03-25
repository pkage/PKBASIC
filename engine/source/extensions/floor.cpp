/* floor.cpp
 * pkbasic library
 * floors the passed variable
 */


#include <iostream>
#include "pkb_plib.h"
#include <cmath>
#include <sstream>

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
	plib::Parsedcmd pcmd;
	try {
		pcmd = plib::parsecmd(invoc);
	} catch (int e) {
		cout << "critical error (" << e << ") occured while parsing input";
	}
//	cout << "parsed input\n";


	ofstream ofile;
	ofile.open(argv[3]);
	string s = pcmd.get_arg(0);
	if (letters.find(s[1]) != -1) {
		stringstream ss; ss << floor(plib::ireg[letters.find(s[1])]);
		ofile << s << " = " << ss.str();
	} else {
		ofile << "print \"variable not found\"";
	}
	ofile.close();
//	cout << "wrote outfile\n";
	return 0;
}
