// LR Parser By JJ

#ifndef C_LR_PARSER_LRPARSERJJ_H
#define C_LR_PARSER_LRPARSERJJ_H
// C语言词法分析器
#include <cstdio>
#include <cstring>
#include <iostream>
#include <unordered_map>
#include <deque>
#include <stack>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
/* 不要修改这个标准输入函数 */
void read_prog(string& prog)
{
    char c;
    while(scanf("%c",&c)!=EOF){
        prog += c;
    }
}

struct Reduction {
    string head;
    int count;

    Reduction() {

    }

    Reduction(string head, int count) {
        this->head = head;
        this->count = count;
    }
};

void initErrirTable(unordered_map<string, string>& ERRORS) {
    ERRORS["e1"] = ";";
}

void initReductions(unordered_map<string, Reduction>& REDUCTIONS) {
    REDUCTIONS["r0"] = *new Reduction("program'", 1);
    REDUCTIONS["r1"] = *new Reduction("program",  1);
    REDUCTIONS["r2"] = *new Reduction("stmt", 1);
    REDUCTIONS["r3"] = *new Reduction("stmt", 1);
    REDUCTIONS["r4"] = *new Reduction("stmt", 1);
    REDUCTIONS["r5"] = *new Reduction("stmt", 1);
    REDUCTIONS["r6"] = *new Reduction("compoundstmt", 3);
    REDUCTIONS["r7"] = *new Reduction("stmts", 2);
    REDUCTIONS["r8"] = *new Reduction("stmts", 0);
    REDUCTIONS["r9"] = *new Reduction("ifstmt", 8);
    REDUCTIONS["r10"] = *new Reduction("whilestmt", 5);
    REDUCTIONS["r11"] = *new Reduction("assgstmt", 4);
    REDUCTIONS["r12"] = *new Reduction("boolexpr", 3);
    REDUCTIONS["r13"] = *new Reduction("boolop", 1);
    REDUCTIONS["r14"] = *new Reduction("boolop", 1);
    REDUCTIONS["r15"] = *new Reduction("boolop", 1);
    REDUCTIONS["r16"] = *new Reduction("boolop", 1);
    REDUCTIONS["r17"] = *new Reduction("boolop", 1);
    REDUCTIONS["r18"] = *new Reduction("arithexpr", 2);
    REDUCTIONS["r19"] = *new Reduction("arithexprprime", 3);
    REDUCTIONS["r20"] = *new Reduction("arithexprprime", 3);
    REDUCTIONS["r21"] = *new Reduction("arithexprprime", 0);
    REDUCTIONS["r22"] = *new Reduction("multexpr", 2);
    REDUCTIONS["r23"] = *new Reduction("multexprprime", 3);
    REDUCTIONS["r24"] = *new Reduction("multexprprime", 3);
    REDUCTIONS["r25"] = *new Reduction("multexprprime", 0);
    REDUCTIONS["r26"] = *new Reduction("simpleexpr", 1);
    REDUCTIONS["r27"] = *new Reduction("simpleexpr", 1);
    REDUCTIONS["r28"] = *new Reduction("simpleexpr", 3);
}

void initActionTable(unordered_map<string, unordered_map<string, string>>& ACTION) {
    ACTION["s0"]["{"] = "s3";
    ACTION["s1"]["$"] = "acc";
    ACTION["s2"]["$"] = "r1";
    ACTION["s3"]["{"] = "s3";
    ACTION["s3"]["}"] = "r8";
    ACTION["s3"]["if"] = "s10";
    ACTION["s3"]["while"] = "s11";
    ACTION["s3"]["ID"] = "s12";
    ACTION["s4"]["}"] = "s13";
    ACTION["s5"]["{"] = "s3";
    ACTION["s5"]["}"] = "r8";
    ACTION["s5"]["if"] = "s10";
    ACTION["s5"]["while"] = "s11";
    ACTION["s5"]["ID"] = "s12";
    ACTION["s6"]["{"] = "r2";
    ACTION["s6"]["}"] = "r2";
    ACTION["s6"]["if"] = "r2";
    ACTION["s6"]["else"] = "r2";
    ACTION["s6"]["while"] = "r2";
    ACTION["s6"]["ID"] = "r2";
    ACTION["s7"]["{"] = "r3";
    ACTION["s7"]["}"] = "r3";
    ACTION["s7"]["if"] = "r3";
    ACTION["s7"]["else"] = "r3";
    ACTION["s7"]["while"] = "r3";
    ACTION["s7"]["ID"] = "r3";
    ACTION["s8"]["{"] = "r4";
    ACTION["s8"]["}"] = "r4";
    ACTION["s8"]["if"] = "r4";
    ACTION["s8"]["else"] = "r4";
    ACTION["s8"]["while"] = "r4";
    ACTION["s8"]["ID"] = "r4";
    ACTION["s9"]["{"] = "r5";
    ACTION["s9"]["}"] = "r5";
    ACTION["s9"]["if"] = "r5";
    ACTION["s9"]["else"] = "r5";
    ACTION["s9"]["while"] = "r5";
    ACTION["s9"]["ID"] = "r5";
    ACTION["s10"]["("] = "s15";
    ACTION["s11"]["("] = "s16";
    ACTION["s12"]["="] = "s17";
    ACTION["s13"]["{"] = "r6";
    ACTION["s13"]["}"] = "r6";
    ACTION["s13"]["if"] = "r6";
    ACTION["s13"]["else"] = "r6";
    ACTION["s13"]["while"] = "r6";
    ACTION["s13"]["ID"] = "r6";
    ACTION["s13"]["$"] = "r6";
    ACTION["s14"]["}"] = "r7";
    ACTION["s15"]["("] = "s24";
    ACTION["s15"]["ID"] = "s22";
    ACTION["s15"]["NUM"] = "s23";
    ACTION["s16"]["("] = "s24";
    ACTION["s16"]["ID"] = "s22";
    ACTION["s16"]["NUM"] = "s23";
    ACTION["s17"]["("] = "s24";
    ACTION["s17"]["ID"] = "s22";
    ACTION["s17"]["NUM"] = "s23";
    ACTION["s18"][")"] = "s27";
    ACTION["s19"]["<"] = "s29";
    ACTION["s19"][">"] = "s30";
    ACTION["s19"]["<="] = "s31";
    ACTION["s19"][">="] = "s32";
    ACTION["s19"]["=="] = "s33";
    ACTION["s20"][")"] = "r21";
    ACTION["s20"][";"] = "r21";
    ACTION["s20"]["<"] = "r21";
    ACTION["s20"][">"] = "r21";
    ACTION["s20"]["<="] = "r21";
    ACTION["s20"][">="] = "r21";
    ACTION["s20"]["=="] = "r21";
    ACTION["s20"]["+"] = "s35";
    ACTION["s20"]["-"] = "s36";
    ACTION["s21"][")"] = "r25";
    ACTION["s21"][";"] = "r25";
    ACTION["s21"]["<"] = "r25";
    ACTION["s21"][">"] = "r25";
    ACTION["s21"]["<="] = "r25";
    ACTION["s21"][">="] = "r25";
    ACTION["s21"]["=="] = "r25";
    ACTION["s21"]["+"] = "r25";
    ACTION["s21"]["-"] = "r25";
    ACTION["s21"]["*"] = "s38";
    ACTION["s21"]["/"] = "s39";
    ACTION["s22"][")"] = "r26";
    ACTION["s22"][";"] = "r26";
    ACTION["s22"]["<"] = "r26";
    ACTION["s22"][">"] = "r26";
    ACTION["s22"]["<="] = "r26";
    ACTION["s22"][">="] = "r26";
    ACTION["s22"]["=="] = "r26";
    ACTION["s22"]["+"] = "r26";
    ACTION["s22"]["-"] = "r26";
    ACTION["s22"]["*"] = "r26";
    ACTION["s22"]["/"] = "r26";
    ACTION["s23"][")"] = "r27";
    ACTION["s23"][";"] = "r27";
    ACTION["s23"]["<"] = "r27";
    ACTION["s23"][">"] = "r27";
    ACTION["s23"]["<="] = "r27";
    ACTION["s23"][">="] = "r27";
    ACTION["s23"]["=="] = "r27";
    ACTION["s23"]["+"] = "r27";
    ACTION["s23"]["-"] = "r27";
    ACTION["s23"]["*"] = "r27";
    ACTION["s23"]["/"] = "r27";
    ACTION["s23"]["}"] = "e1";// ERROR HANDLING
    ACTION["s24"]["("] = "s24";
    ACTION["s24"]["ID"] = "s22";
    ACTION["s24"]["NUM"] = "s23";
    ACTION["s25"][")"] = "s41";
    ACTION["s26"][";"] = "s42";
    ACTION["s27"]["then"] = "s43";
    ACTION["s28"]["("] = "s24";
    ACTION["s28"]["ID"] = "s22";
    ACTION["s28"]["NUM"] = "s23";
    ACTION["s29"]["("] = "r13";
    ACTION["s29"]["ID"] = "r13";
    ACTION["s29"]["NUM"] = "r13";
    ACTION["s30"]["("] = "r14";
    ACTION["s30"]["ID"] = "r14";
    ACTION["s30"]["NUM"] = "r14";
    ACTION["s31"]["("] = "r15";
    ACTION["s31"]["ID"] = "r15";
    ACTION["s31"]["NUM"] = "r15";
    ACTION["s32"]["("] = "r16";
    ACTION["s32"]["ID"] = "r16";
    ACTION["s32"]["NUM"] = "r16";
    ACTION["s33"]["("] = "r17";
    ACTION["s33"]["ID"] = "r17";
    ACTION["s33"]["NUM"] = "r17";
    ACTION["s34"][")"] = "r18";
    ACTION["s34"][";"] = "r18";
    ACTION["s34"]["<"] = "r18";
    ACTION["s34"][">"] = "r18";
    ACTION["s34"]["<="] = "r18";
    ACTION["s34"][">="] = "r18";
    ACTION["s34"]["=="] = "r18";
    ACTION["s35"]["("] = "s24";
    ACTION["s35"]["ID"] = "s22";
    ACTION["s35"]["NUM"] = "s23";
    ACTION["s36"]["("] = "s24";
    ACTION["s36"]["ID"] = "s22";
    ACTION["s36"]["NUM"] = "s23";
    ACTION["s37"][")"] = "r22";
    ACTION["s37"][";"] = "r22";
    ACTION["s37"]["<"] = "r22";
    ACTION["s37"][">"] = "r22";
    ACTION["s37"]["<="] = "r22";
    ACTION["s37"][">="] = "r22";
    ACTION["s37"]["=="] = "r22";
    ACTION["s37"]["+"] = "r22";
    ACTION["s37"]["-"] = "r22";
    ACTION["s38"]["("] = "s24";
    ACTION["s38"]["ID"] = "s22";
    ACTION["s38"]["NUM"] = "s23";
    ACTION["s39"]["("] = "s24";
    ACTION["s39"]["ID"] = "s22";
    ACTION["s39"]["NUM"] = "s23";
    ACTION["s40"][")"] = "s49";
    ACTION["s41"]["{"] = "s3";
    ACTION["s41"]["if"] = "s10";
    ACTION["s41"]["while"] = "s11";
    ACTION["s41"]["ID"] = "s12";
    ACTION["s42"]["{"] = "r11";
    ACTION["s42"]["}"] = "r11";
    ACTION["s42"]["if"] = "r11";
    ACTION["s42"]["else"] = "r11";
    ACTION["s42"]["while"] = "r11";
    ACTION["s42"]["ID"] = "r11";
    ACTION["s43"]["{"] = "s3";
    ACTION["s43"]["if"] = "s10";
    ACTION["s43"]["while"] = "s11";
    ACTION["s43"]["ID"] = "s12";
    ACTION["s44"][")"] = "r12";
    ACTION["s45"][")"] = "r21";
    ACTION["s45"][";"] = "r21";
    ACTION["s45"]["<"] = "r21";
    ACTION["s45"][">"] = "r21";
    ACTION["s45"]["<="] = "r21";
    ACTION["s45"][">="] = "r21";
    ACTION["s45"]["=="] = "r21";
    ACTION["s45"]["+"] = "s35";
    ACTION["s45"]["-"] = "s36";
    ACTION["s46"][")"] = "r21";
    ACTION["s46"][";"] = "r21";
    ACTION["s46"]["<"] = "r21";
    ACTION["s46"][">"] = "r21";
    ACTION["s46"]["<="] = "r21";
    ACTION["s46"][">="] = "r21";
    ACTION["s46"]["=="] = "r21";
    ACTION["s46"]["+"] = "s35";
    ACTION["s46"]["-"] = "s36";
    ACTION["s47"][")"] = "r25";
    ACTION["s47"][";"] = "r25";
    ACTION["s47"]["<"] = "r25";
    ACTION["s47"][">"] = "r25";
    ACTION["s47"]["<="] = "r25";
    ACTION["s47"][">="] = "r25";
    ACTION["s47"]["=="] = "r25";
    ACTION["s47"]["+"] = "r25";
    ACTION["s47"]["-"] = "r25";
    ACTION["s47"]["*"] = "s38";
    ACTION["s47"]["/"] = "s39";
    ACTION["s48"][")"] = "r25";
    ACTION["s48"][";"] = "r25";
    ACTION["s48"]["<"] = "r25";
    ACTION["s48"][">"] = "r25";
    ACTION["s48"]["<="] = "r25";
    ACTION["s48"][">="] = "r25";
    ACTION["s48"]["=="] = "r25";
    ACTION["s48"]["+"] = "r25";
    ACTION["s48"]["-"] = "r25";
    ACTION["s48"]["*"] = "s38";
    ACTION["s48"]["/"] = "s39";
    ACTION["s49"][")"] = "r28";
    ACTION["s49"][";"] = "r28";
    ACTION["s49"]["<"] = "r28";
    ACTION["s49"][">"] = "r28";
    ACTION["s49"]["<="] = "r28";
    ACTION["s49"][">="] = "r28";
    ACTION["s49"]["=="] = "r28";
    ACTION["s49"]["+"] = "r28";
    ACTION["s49"]["-"] = "r28";
    ACTION["s49"]["*"] = "r28";
    ACTION["s49"]["/"] = "r28";
    ACTION["s50"]["{"] = "r10";
    ACTION["s50"]["}"] = "r10";
    ACTION["s50"]["if"] = "r10";
    ACTION["s50"]["else"] = "r10";
    ACTION["s50"]["while"] = "r10";
    ACTION["s50"]["ID"] = "r10";
    ACTION["s51"]["else"] = "s56";
    ACTION["s52"][")"] = "r19";
    ACTION["s52"][";"] = "r19";
    ACTION["s52"]["<"] = "r19";
    ACTION["s52"][">"] = "r19";
    ACTION["s52"]["<="] = "r19";
    ACTION["s52"][">="] = "r19";
    ACTION["s52"]["=="] = "r19";
    ACTION["s53"][")"] = "r20";
    ACTION["s53"][";"] = "r20";
    ACTION["s53"]["<"] = "r20";
    ACTION["s53"][">"] = "r20";
    ACTION["s53"]["<="] = "r20";
    ACTION["s53"][">="] = "r20";
    ACTION["s53"]["=="] = "r20";
    ACTION["s54"][")"] = "r23";
    ACTION["s54"][";"] = "r23";
    ACTION["s54"]["<"] = "r23";
    ACTION["s54"][">"] = "r23";
    ACTION["s54"]["<="] = "r23";
    ACTION["s54"][">="] = "r23";
    ACTION["s54"]["=="] = "r23";
    ACTION["s54"]["+"] = "r23";
    ACTION["s54"]["-"] = "r23";
    ACTION["s55"][")"] = "r24";
    ACTION["s55"][";"] = "r24";
    ACTION["s55"]["<"] = "r24";
    ACTION["s55"][">"] = "r24";
    ACTION["s55"]["<="] = "r24";
    ACTION["s55"][">="] = "r24";
    ACTION["s55"]["=="] = "r24";
    ACTION["s55"]["+"] = "r24";
    ACTION["s55"]["-"] = "r24";
    ACTION["s56"]["{"] = "s3";
    ACTION["s56"]["if"] = "s10";
    ACTION["s56"]["while"] = "s11";
    ACTION["s56"]["ID"] = "s12";
    ACTION["s57"]["{"] = "r9";
    ACTION["s57"]["}"] = "r9";
    ACTION["s57"]["if"] = "r9";
    ACTION["s57"]["else"] = "r9";
    ACTION["s57"]["while"] = "r9";
    ACTION["s57"]["ID"] = "r9";

}

void initGotoTable(unordered_map<string, unordered_map<string, string>>& GOTO) {
    GOTO["s0"]["program"] = "s1";
    GOTO["s0"]["compoundstmt"] = "s2";
    GOTO["s3"]["stmt"] = "s5";
    GOTO["s3"]["compoundstmt"] = "s9";
    GOTO["s3"]["stmts"] = "s4";
    GOTO["s3"]["ifstmt"] = "s6";
    GOTO["s3"]["whilestmt"] = "s7";
    GOTO["s3"]["assgstmt"] = "s8";
    GOTO["s5"]["stmt"] = "s5";
    GOTO["s5"]["compoundstmt"] = "s9";
    GOTO["s5"]["stmts"] = "s14";
    GOTO["s5"]["ifstmt"] = "s6";
    GOTO["s5"]["whilestmt"] = "s7";
    GOTO["s5"]["assgstmt"] = "s8";
    GOTO["s15"]["boolexpr"] = "s18";
    GOTO["s15"]["arithexpr"] = "s19";
    GOTO["s15"]["multexpr"] = "s20";
    GOTO["s15"]["simpleexpr"] = "s21";
    GOTO["s16"]["boolexpr"] = "s25";
    GOTO["s16"]["arithexpr"] = "s19";
    GOTO["s16"]["multexpr"] = "s20";
    GOTO["s16"]["simpleexpr"] = "s21";
    GOTO["s17"]["arithexpr"] = "s26";
    GOTO["s17"]["multexpr"] = "s20";
    GOTO["s17"]["simpleexpr"] = "s21";
    GOTO["s19"]["boolop"] = "s28";
    GOTO["s20"]["arithexprprime"] = "s34";
    GOTO["s21"]["multexprprime"] = "s37";
    GOTO["s24"]["arithexpr"] = "s40";
    GOTO["s24"]["multexpr"] = "s20";
    GOTO["s24"]["simpleexpr"] = "s21";
    GOTO["s28"]["arithexpr"] = "s44";
    GOTO["s28"]["multexpr"] = "s20";
    GOTO["s28"]["simpleexpr"] = "s21";
    GOTO["s35"]["multexpr"] = "s45";
    GOTO["s35"]["simpleexpr"] = "s21";
    GOTO["s36"]["multexpr"] = "s46";
    GOTO["s36"]["simpleexpr"] = "s21";
    GOTO["s38"]["simpleexpr"] = "s47";
    GOTO["s39"]["simpleexpr"] = "s48";
    GOTO["s41"]["stmt"] = "s50";
    GOTO["s41"]["compoundstmt"] = "s9";
    GOTO["s41"]["ifstmt"] = "s6";
    GOTO["s41"]["whilestmt"] = "s7";
    GOTO["s41"]["assgstmt"] = "s8";
    GOTO["s43"]["stmt"] = "s51";
    GOTO["s43"]["compoundstmt"] = "s9";
    GOTO["s43"]["ifstmt"] = "s6";
    GOTO["s43"]["whilestmt"] = "s7";
    GOTO["s43"]["assgstmt"] = "s8";
    GOTO["s45"]["arithexprprime"] = "s52";
    GOTO["s46"]["arithexprprime"] = "s53";
    GOTO["s47"]["multexprprime"] = "s54";
    GOTO["s48"]["multexprprime"] = "s55";
    GOTO["s56"]["stmt"] = "s57";
    GOTO["s56"]["compoundstmt"] = "s9";
    GOTO["s56"]["ifstmt"] = "s6";
    GOTO["s56"]["whilestmt"] = "s7";
    GOTO["s56"]["assgstmt"] = "s8";
}

bool isState(string& input) {
    if (input.size()) {
        if (input[0] == 's' || input[0] == 'S') {
            return true;
        }
    }

    return false;
}

bool isReduce(string& input) {
    if (input.size()) {
        if (input[0] == 'r' || input[0] == 'R') {
            return true;
        }
    }

    return false;
}

bool isError(string& input) {
    if (input.size()) {
        if (input[0] == 'e' || input[0] == 'E') {
            return true;
        }
    }

    return false;
}

void toTerminals(string prog, vector<string>& input, vector<int>& inputLineRecord) {
    prog.append(" ");
    string s = "";
    int n = int(prog.size()), lineIndex = 1;
    for(int i = 0; i < n; ++i) {
        if(prog[i] != ' ' && prog[i] != '\n' && prog[i] != '\t') {
            s += prog[i];
        } else if(s != ""){
            input.push_back(s);
            inputLineRecord.push_back(lineIndex);
            s = "";
        }

        if(prog[i] == '\n') {
            lineIndex++;
        }
    }
}

void Analysis()
{
    string prog;
    read_prog(prog);

    prog += " $";

    unordered_map<string, unordered_map<string, string>> ACTION, GOTO;
    initActionTable(ACTION);
    initGotoTable(GOTO);
    unordered_map<string, Reduction> R;
    initReductions(R);
    unordered_map<string, string> E;
    initErrirTable(E);

    vector<string> input;
    vector<int> inputLineRecord;
    toTerminals(prog, input, inputLineRecord);

    stack<string> states;
    deque<string> symbols;
    stack<deque<string>> symbolHistroy;
    stack<int> reducedSymbolCount;

    states.push("s0");

    int i = 0;
    string errorMsg = "";
    while (i < input.size()) {
        if (ACTION[states.top()].count(input[i])) {
            // NO ERROR.
            string action = ACTION[states.top()][input[i]];
            if (isState(action)) {
                // Shift
                states.push(action);
                symbols.push_back(input[i]);
                symbolHistroy.push(symbols);
                if(!reducedSymbolCount.empty()) {
                    reducedSymbolCount.push(reducedSymbolCount.top());
                } else {
                    reducedSymbolCount.push(0);
                }
                reducedSymbolCount.top()++;
                i++;
            } else if (isReduce(action)){
                // Reduce
                Reduction r = R[action];
                for (int i = 0; i < r.count; ++i) {
                    states.pop();
                    symbols.pop_back();
                }
                states.push(GOTO[states.top()][r.head]);
                symbols.push_back(r.head);
                symbolHistroy.push(symbols);
                if(!reducedSymbolCount.empty()) {
                    reducedSymbolCount.push(reducedSymbolCount.top());
                } else {
                    reducedSymbolCount.push(0);
                }
            } else if (isError(action)) {
                errorMsg = "语法错误，第" + to_string(inputLineRecord[i]-1) + "行，缺少\""+ E[action] + "\"";
                input.insert(input.begin()+i, E[action]);
            } else {
                // ACC
                break;
            }
        }
    }

    cout << errorMsg << endl;

    int reduceTime = reducedSymbolCount.top();
    deque<string> outputs;
    while (!symbolHistroy.empty()) {
        string output = "";
        for(auto it = symbolHistroy.top().begin(); it != symbolHistroy.top().end(); ++it) {
            output += *it + " ";
        }
        int n = reduceTime - reducedSymbolCount.top();
        auto it = input.end();
        advance(it, -n-1);
        while (n--) {
            output += *it + " ";
            it++;
        }

        if(outputs.empty() || output != outputs.back()) {
            outputs.push_back(output);
        }

        symbolHistroy.pop();
        reducedSymbolCount.pop();
    }

    while (!outputs.empty()) {
        cout << outputs.front();
        if (outputs.size() > 1) {
            cout << "=>";
        }
        cout << endl;
        outputs.pop_front();
    }
}


#endif //C_LR_PARSER_LRPARSERJJ_H
