#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>

using namespace std;

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

vector<string> reg = {"000", "001", "010", "011", "100", "101", "110", "111"};
vector<string> con = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111",
                      "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};

vector<command> commands;
vector<string>  binaries;

string translate_op_code(string op) {
    return op_code[distance(ops.begin(), find(ops.begin(), ops.end(), op))];
}

int main() {
    cin >> line_number;
    commands.resize(line_number);
    binaries.resize(line_number);

    for (auto& i : commands)
        cin >> i.op >> i.arg[0] >> i.arg[1] >> i.arg[2];

    for (int i = 0; i < line_number; i++) {
        binaries[i] = translate_op_code(commands[i].op) + "0" + reg[commands[i].arg[0]]
        + reg[commands[i].arg[1]];

        if(binaries[i][4] == '0') {
            binaries[i] += reg[commands[i].arg[2]] + "0";
        } else {
            binaries[i] += con[commands[i].arg[2]];
        }
    }

    for (auto& i : binaries)
        cout << i << endl;
}