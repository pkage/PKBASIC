/* testlib.cpp
 * pkbasic test library
 * increments var by 4
 * useless, but it's a test
 */


#include <iostream>
#include "pkb_plib.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 4) {
		cout << "invocation failed\n";
		return 1;
	}
	cout << "\nvardump: " << argv[1] << "\ninvocation: " << argv[2] << "\noutput: " << argv[3] << '\n';
	string vd = argv[1], invoc = argv[2];
	if (!plib::import_varlist(vd)) {
		cout << "\nfailed to read variables";
		return 1;
	}
	plib::Parsedcmd pcmd = plib::parsecmd(invoc);
	ofstream ofile;
	ofile.open(argv[3]);
	if (!ofile) {
		cout << "failed to process outfile\n";
		return 1;
	}
	ofile << pcmd.get_arg(0) << " += 4";
	ofile.close();
	return 0;
}
