#include <iostream>
#include <sstream>
#include <vector>
#include <string.h>

using namespace std;

namespace plib {
    class Parsedcmd {
    public:
        string cmd;
        vector<string> args;
        void add_arg(string arg) {
            args.push_back(arg);
        }
        int arg_count() {return args.size();}
        string get_arg(int n) {
            if (n > args.size() || n < 0) {
                return "";
            }
            return args.at(n);
        }
    };
    
    // Core function prototypes
    Parsedcmd parsecmd(string str);
    int chartovarindex(char &ch);
    void stripQuotes(string &in);
    
    // Variable registers
    string sreg[52];
    double ireg[52];
    const string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const string NM = "0123456789";
    
    int chartovarindex(char &ch) {
        return letters.find(ch);
    }
    
    bool import_varlist(string file) {
        ifstream ifile;
        ifile.open(file.c_str());
        if (!ifile) {
            return false;
        }
        string line; int tmp;
        while (!ifile.eof()) {
            line = getline(ifile);
            tmp = chartovarindex(line.at(1));
            if (tmp != -1) {
                if (line.at(0) == '#') {
                    ireg[tmp] = atof(line.substr(2).c_str());
                } else if (line.at(0) == '$') {
                    sreg[tmp] = line.substr(2);
                }
            }
        }
    }
    // Flags
    bool ERROR_THROWN = false;
    string ERROR_TYPE = "NONE";
    bool IPROMPT = false; // goto & lbl directives disabled in liveprompt mode
    
    // Command parser
    Parsedcmd parsecmd(string str) {
        int spos = str.find(" ");
        string cmd, arg;
        if (spos == -1) {
            cmd = str;
            arg = "";
        } else {
            cmd = str.substr(0, spos);
            arg = str.substr(spos + 1);
        }
        //cout << "Parsed command as: [" << cmd << "]";
        //cout << "\nParsed argument as [" << arg << "]";
        Parsedcmd pcmd;
        pcmd.cmd = cmd;
        pcmd.add_arg(arg);
        return pcmd;
    }
    
    
    void stripQuotes(string &in) {
        if (in.at(0) == '\"') {in.erase(0,1);}
        if (in.at(in.length() - 1) == '\"') {in.erase(in.length() - 1, 1);}
        return;
    }
    
    
}
