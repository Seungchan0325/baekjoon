#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>

using namespace std;
using namespace std::string_literals;

#define ADD     "00000",
#define ADDC    "00001",
#define SUB     "00010",
#define SUBC    "00011",
#define MOV     "00100",
#define MOVC    "00101",
#define AND     "00110",
#define ANDC    "00111",
#define OR      "01000",
#define ORC     "01001",
#define NOT     "01010",
#define MULT    "01100",
#define MULTC   "01101",
#define LSFTL   "01110",
#define LSFTLC  "01111",
#define LSFTR   "10000",
#define LSFTRC  "10001",
#define ASFTR   "10010",
#define ASFTRC  "10011",
#define RL      "10100",
#define RLC     "10101",
#define RR      "10110",
#define RRC     "10110",

struct command {
    string op;
    unsigned int arg[3];
};

int line_number;

vector<string> ops = {"ADD", "ADDC", "SUB", "SUBC", "MOV", "MOVC", "AND", "ANDC",
                    "OR", "ORC", "NOT", "MULT", "MULTC", "LSFTL", "LSFTLC",
                    "LSFTR", "LSFTRC", "ASFTR", "ASFTRC", "RL", "RLC", "RR", "RRC"};

vector<string> op_code = {"00000", "00001", "00010", "00011", "00100", "00101",
                        "00110", "00111", "01000", "01001", "01010", "01100",
                        "01101", "01110", "01111", "10000", "10001", "10010",
                        "10011", "10100", "10101", "10110", "10111"};

vector<command> commands;
vector<string>  binaries;

string translate_op_code(string op) {
    return op_code[distance(ops.begin(), find(ops.begin(), ops.end(), op))];
}

string dec_to_bin3(unsigned int num) {
    unsigned int a = 0b100;
    string result;
    for (int i = 0; i < 3; i++) {
        if ((a & num) == a)
            result += "1";
        else
            result += "0";
        a >>= 1;
    }
    return result;
}

string dec_to_bin4(unsigned int num) {
    unsigned int a = 0b1000;
    string result;
    for (int i = 0; i < 4; i++) {
        if ((a & num) == a)
            result += "1";
        else
            result += "0";
        a >>= 1;
    }
    return result;
}

int main() {
    cin >> line_number;
    commands.resize(line_number);
    binaries.resize(line_number);

    for (auto& i : commands)
        cin >> i.op >> i.arg[0] >> i.arg[1] >> i.arg[2];

    for (int i = 0; i < line_number; i++) {
        binaries[i] = translate_op_code(commands[i].op) + "0" + dec_to_bin3(commands[i].arg[0])
        + dec_to_bin3(commands[i].arg[1]);

        if(binaries[i][4] == '0') {
            binaries[i] += dec_to_bin3(commands[i].arg[2]) + "0";
        } else {
            binaries[i] += dec_to_bin4(commands[i].arg[2]);
        }
    }

    for (auto& i : binaries)
        cout << i << endl;
}