/**
 * Copyright 2020, Juntong Chen
 * East China Normal University
 */
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <stack>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

/* If set to 1, will use precalculated rule table instead of
 * Calculating one by the program itself.
 *
 * Todo: Calculating a predict table.
 */
#define PREDEFINED_TRANSITION_TABLE 1
#define PARSEMODE_ERRORCHECKING 1
#define PARSEMPDE_PARSE 2

using namespace std;
/**
 * Predefined symbols and grammar rules.
 */
multimap<string, string> ruleMap = {
    {"program", "compoundstmt"},
    {"stmt", "ifstmt"},
    {"stmt", "whilestmt"},
    {"stmt", "assgstmt"},
    {"stmt", "compoundstmt"},
    {"compoundstmt", "{ stmts }"},
    {"stmts", "stmt stmts"},
    {"stmts", "E"},
    {"ifstmt", "if ( boolexpr ) then stmt else stmt"},
    {"whilestmt", "while ( boolexpr ) stmt"},
    {"assgstmt", "ID = arithexpr ;"},
    {"boolexpr", "arithexpr boolop arithexpr"},
    {"boolop", "<"},
    {"boolop", ">"},
    {"boolop", "<="},
    {"boolop", ">="},
    {"boolop", "=="},
    {"arithexpr", " multexpr arithexprprime"},
    {"arithexprprime", "+ multexpr arithexprprime "},
    {"arithexprprime", "- multexpr arithexprprime"},
    {"arithexprprime", "E"},
    {"multexpr", "simpleexpr multexprprime"},
    {"multexprprime", "* simpleexpr multexprprime"},
    {"multexprprime", "/ simpleexpr multexprprime "},
    {"multexprprime", "E"},
    {"simpleexpr", "ID"},
    {"simpleexpr", "NUM"},
    {"simpleexpr", "( arithexpr )"}
};

unordered_set<string> nonterminals = {
        "program", "stmt", "compoundstmt", "stmts", "ifstmt", "whilestmt","assgstmt", "boolexpr", "boolop",
        "arithexpr", "arithexprprime", "multexpr", "multexprprime", "simpleexpr"
};

/**
 * E stands for empty symbol.
 */
unordered_set<string> terminals = {
        "{", "}", "if", "(", ")", "then", "else", "while",
        "ID", "=", ">", "<", ">=", "<=", "==", "+", "-", "*",
        "/", "NUM", "E", ";", "$"
};

/**
 * Split a string by space. Return a string vector.
 * Line break is split by an <endl> token. (Used for calculating line numbers)
 */
vector<string> split(string const s) {
    vector<std::string> result ;
    istringstream stm(s);
    string token;
    string line;
    while (getline(stm, line)) {
        istringstream linestm(line);
        while (linestm >> token) result.push_back(token);
        if (token != "$") {
            result.push_back("<endl>");
        }
    }
    return result;
}

/**
 * Join the string vector into a consecutive string
 * @param v
 * @return
 */
string join(vector<string> &v){
    string out = "";
    for(auto it = v.begin(); it != v.end(); it++){
        out += *it;
        if (it != v.end() - 1) {
            out += " ";
        }
    }
    return out;
}


void read_prog(string &prog) {
    char c;
    while (scanf("%c", &c) != EOF) {
        prog += c;
    }
}

/**
 * A reduction. Statement is the left side of the expression,
 * while len is the number of tokens on the right side.
 */
struct Reduction {
    string stmt;
    int len;

    Reduction() {}

    Reduction(string s, int l) {
        stmt = s;
        len = l;
    }
};

/****************** Transition Table ******************/

class TransitionTable {

private:
    /**
     * These functions will generate a LALR transition table.
     */
    void initReduction();

    void initAction();

    void initGoto();

public:
    /**
     * @param rule
     * @param nt Non-terminals
     * @param t Terminals
     */
    TransitionTable(multimap<string, string> &rule, unordered_set<string> &nt, unordered_set<string> &t);

    /**
     * Three unordered map for LR parser.
     */
    unordered_map<string, Reduction> Reductions;
    unordered_map<string, unordered_map<string, string>> Action;
    unordered_map<string, unordered_map<string, string>> Goto;
};

TransitionTable::TransitionTable(multimap<string, string> &rule, unordered_set<string> &nt, unordered_set<string> &t)  {
    if (PREDEFINED_TRANSITION_TABLE) {
        initReduction();
        initAction();
        initGoto();
    }
    else {
        // todo: Calculate transition table run time.
    }
}

void TransitionTable::initReduction() {
    Reductions["r0"] = Reduction("program'", 1);
    Reductions["r1"] = Reduction("program",  1);
    Reductions["r2"] = Reduction("stmt", 1);
    Reductions["r3"] = Reduction("stmt", 1);
    Reductions["r4"] = Reduction("stmt", 1);
    Reductions["r5"] = Reduction("stmt", 1);
    Reductions["r6"] = Reduction("compoundstmt", 3);
    Reductions["r7"] = Reduction("stmts", 2);
    Reductions["r8"] = Reduction("stmts", 0);
    Reductions["r9"] = Reduction("ifstmt", 8);
    Reductions["r10"] = Reduction("whilestmt", 5);
    Reductions["r11"] = Reduction("assgstmt", 4);
    Reductions["r12"] = Reduction("boolexpr", 3);
    Reductions["r13"] = Reduction("boolop", 1);
    Reductions["r14"] = Reduction("boolop", 1);
    Reductions["r15"] = Reduction("boolop", 1);
    Reductions["r16"] = Reduction("boolop", 1);
    Reductions["r17"] = Reduction("boolop", 1);
    Reductions["r18"] = Reduction("arithexpr", 2);
    Reductions["r19"] = Reduction("arithexprprime", 3);
    Reductions["r20"] = Reduction("arithexprprime", 3);
    Reductions["r21"] = Reduction("arithexprprime", 0);
    Reductions["r22"] = Reduction("multexpr", 2);
    Reductions["r23"] = Reduction("multexprprime", 3);
    Reductions["r24"] = Reduction("multexprprime", 3);
    Reductions["r25"] = Reduction("multexprprime", 0);
    Reductions["r26"] = Reduction("simpleexpr", 1);
    Reductions["r27"] = Reduction("simpleexpr", 1);
    Reductions["r28"] = Reduction("simpleexpr", 3);
}

void TransitionTable::initAction() {
    Action["s0"]["{"] = "s3";
    Action["s1"]["$"] = "acc";
    Action["s2"]["$"] = "r1";
    Action["s3"]["{"] = "s3";
    Action["s3"]["}"] = "r8";
    Action["s3"]["if"] = "s10";
    Action["s3"]["while"] = "s11";
    Action["s3"]["ID"] = "s12";
    Action["s4"]["}"] = "s13";
    Action["s5"]["{"] = "s3";
    Action["s5"]["}"] = "r8";
    Action["s5"]["if"] = "s10";
    Action["s5"]["while"] = "s11";
    Action["s5"]["ID"] = "s12";
    Action["s6"]["{"] = "r2";
    Action["s6"]["}"] = "r2";
    Action["s6"]["if"] = "r2";
    Action["s6"]["else"] = "r2";
    Action["s6"]["while"] = "r2";
    Action["s6"]["ID"] = "r2";
    Action["s7"]["{"] = "r3";
    Action["s7"]["}"] = "r3";
    Action["s7"]["if"] = "r3";
    Action["s7"]["else"] = "r3";
    Action["s7"]["while"] = "r3";
    Action["s7"]["ID"] = "r3";
    Action["s8"]["{"] = "r4";
    Action["s8"]["}"] = "r4";
    Action["s8"]["if"] = "r4";
    Action["s8"]["else"] = "r4";
    Action["s8"]["while"] = "r4";
    Action["s8"]["ID"] = "r4";
    Action["s9"]["{"] = "r5";
    Action["s9"]["}"] = "r5";
    Action["s9"]["if"] = "r5";
    Action["s9"]["else"] = "r5";
    Action["s9"]["while"] = "r5";
    Action["s9"]["ID"] = "r5";
    Action["s10"]["("] = "s15";
    Action["s11"]["("] = "s16";
    Action["s12"]["="] = "s17";
    Action["s13"]["{"] = "r6";
    Action["s13"]["}"] = "r6";
    Action["s13"]["if"] = "r6";
    Action["s13"]["else"] = "r6";
    Action["s13"]["while"] = "r6";
    Action["s13"]["ID"] = "r6";
    Action["s13"]["$"] = "r6";
    Action["s14"]["}"] = "r7";
    Action["s15"]["("] = "s24";
    Action["s15"]["ID"] = "s22";
    Action["s15"]["NUM"] = "s23";
    Action["s16"]["("] = "s24";
    Action["s16"]["ID"] = "s22";
    Action["s16"]["NUM"] = "s23";
    Action["s17"]["("] = "s24";
    Action["s17"]["ID"] = "s22";
    Action["s17"]["NUM"] = "s23";
    Action["s18"][")"] = "s27";
    Action["s19"]["<"] = "s29";
    Action["s19"][">"] = "s30";
    Action["s19"]["<="] = "s31";
    Action["s19"][">="] = "s32";
    Action["s19"]["=="] = "s33";
    Action["s20"][")"] = "r21";
    Action["s20"][";"] = "r21";
    Action["s20"]["<"] = "r21";
    Action["s20"][">"] = "r21";
    Action["s20"]["<="] = "r21";
    Action["s20"][">="] = "r21";
    Action["s20"]["=="] = "r21";
    Action["s20"]["+"] = "s35";
    Action["s20"]["-"] = "s36";
    Action["s21"][")"] = "r25";
    Action["s21"][";"] = "r25";
    Action["s21"]["<"] = "r25";
    Action["s21"][">"] = "r25";
    Action["s21"]["<="] = "r25";
    Action["s21"][">="] = "r25";
    Action["s21"]["=="] = "r25";
    Action["s21"]["+"] = "r25";
    Action["s21"]["-"] = "r25";
    Action["s21"]["*"] = "s38";
    Action["s21"]["/"] = "s39";
    Action["s22"][")"] = "r26";
    Action["s22"][";"] = "r26";
    Action["s22"]["<"] = "r26";
    Action["s22"][">"] = "r26";
    Action["s22"]["<="] = "r26";
    Action["s22"][">="] = "r26";
    Action["s22"]["=="] = "r26";
    Action["s22"]["+"] = "r26";
    Action["s22"]["-"] = "r26";
    Action["s22"]["*"] = "r26";
    Action["s22"]["/"] = "r26";
    Action["s23"][")"] = "r27";
    Action["s23"][";"] = "r27";
    Action["s23"]["<"] = "r27";
    Action["s23"][">"] = "r27";
    Action["s23"]["<="] = "r27";
    Action["s23"][">="] = "r27";
    Action["s23"]["=="] = "r27";
    Action["s23"]["+"] = "r27";
    Action["s23"]["-"] = "r27";
    Action["s23"]["*"] = "r27";
    Action["s23"]["/"] = "r27";
    Action["s23"]["}"] = "e1";  // ERROR HANDLING
    Action["s24"]["("] = "s24";
    Action["s24"]["ID"] = "s22";
    Action["s24"]["NUM"] = "s23";
    Action["s25"][")"] = "s41";
    Action["s26"][";"] = "s42";
    Action["s27"]["then"] = "s43";
    Action["s28"]["("] = "s24";
    Action["s28"]["ID"] = "s22";
    Action["s28"]["NUM"] = "s23";
    Action["s29"]["("] = "r13";
    Action["s29"]["ID"] = "r13";
    Action["s29"]["NUM"] = "r13";
    Action["s30"]["("] = "r14";
    Action["s30"]["ID"] = "r14";
    Action["s30"]["NUM"] = "r14";
    Action["s31"]["("] = "r15";
    Action["s31"]["ID"] = "r15";
    Action["s31"]["NUM"] = "r15";
    Action["s32"]["("] = "r16";
    Action["s32"]["ID"] = "r16";
    Action["s32"]["NUM"] = "r16";
    Action["s33"]["("] = "r17";
    Action["s33"]["ID"] = "r17";
    Action["s33"]["NUM"] = "r17";
    Action["s34"][")"] = "r18";
    Action["s34"][";"] = "r18";
    Action["s34"]["<"] = "r18";
    Action["s34"][">"] = "r18";
    Action["s34"]["<="] = "r18";
    Action["s34"][">="] = "r18";
    Action["s34"]["=="] = "r18";
    Action["s35"]["("] = "s24";
    Action["s35"]["ID"] = "s22";
    Action["s35"]["NUM"] = "s23";
    Action["s36"]["("] = "s24";
    Action["s36"]["ID"] = "s22";
    Action["s36"]["NUM"] = "s23";
    Action["s37"][")"] = "r22";
    Action["s37"][";"] = "r22";
    Action["s37"]["<"] = "r22";
    Action["s37"][">"] = "r22";
    Action["s37"]["<="] = "r22";
    Action["s37"][">="] = "r22";
    Action["s37"]["=="] = "r22";
    Action["s37"]["+"] = "r22";
    Action["s37"]["-"] = "r22";
    Action["s38"]["("] = "s24";
    Action["s38"]["ID"] = "s22";
    Action["s38"]["NUM"] = "s23";
    Action["s39"]["("] = "s24";
    Action["s39"]["ID"] = "s22";
    Action["s39"]["NUM"] = "s23";
    Action["s40"][")"] = "s49";
    Action["s41"]["{"] = "s3";
    Action["s41"]["if"] = "s10";
    Action["s41"]["while"] = "s11";
    Action["s41"]["ID"] = "s12";
    Action["s42"]["{"] = "r11";
    Action["s42"]["}"] = "r11";
    Action["s42"]["if"] = "r11";
    Action["s42"]["else"] = "r11";
    Action["s42"]["while"] = "r11";
    Action["s42"]["ID"] = "r11";
    Action["s43"]["{"] = "s3";
    Action["s43"]["if"] = "s10";
    Action["s43"]["while"] = "s11";
    Action["s43"]["ID"] = "s12";
    Action["s44"][")"] = "r12";
    Action["s45"][")"] = "r21";
    Action["s45"][";"] = "r21";
    Action["s45"]["<"] = "r21";
    Action["s45"][">"] = "r21";
    Action["s45"]["<="] = "r21";
    Action["s45"][">="] = "r21";
    Action["s45"]["=="] = "r21";
    Action["s45"]["+"] = "s35";
    Action["s45"]["-"] = "s36";
    Action["s46"][")"] = "r21";
    Action["s46"][";"] = "r21";
    Action["s46"]["<"] = "r21";
    Action["s46"][">"] = "r21";
    Action["s46"]["<="] = "r21";
    Action["s46"][">="] = "r21";
    Action["s46"]["=="] = "r21";
    Action["s46"]["+"] = "s35";
    Action["s46"]["-"] = "s36";
    Action["s47"][")"] = "r25";
    Action["s47"][";"] = "r25";
    Action["s47"]["<"] = "r25";
    Action["s47"][">"] = "r25";
    Action["s47"]["<="] = "r25";
    Action["s47"][">="] = "r25";
    Action["s47"]["=="] = "r25";
    Action["s47"]["+"] = "r25";
    Action["s47"]["-"] = "r25";
    Action["s47"]["*"] = "s38";
    Action["s47"]["/"] = "s39";
    Action["s48"][")"] = "r25";
    Action["s48"][";"] = "r25";
    Action["s48"]["<"] = "r25";
    Action["s48"][">"] = "r25";
    Action["s48"]["<="] = "r25";
    Action["s48"][">="] = "r25";
    Action["s48"]["=="] = "r25";
    Action["s48"]["+"] = "r25";
    Action["s48"]["-"] = "r25";
    Action["s48"]["*"] = "s38";
    Action["s48"]["/"] = "s39";
    Action["s49"][")"] = "r28";
    Action["s49"][";"] = "r28";
    Action["s49"]["<"] = "r28";
    Action["s49"][">"] = "r28";
    Action["s49"]["<="] = "r28";
    Action["s49"][">="] = "r28";
    Action["s49"]["=="] = "r28";
    Action["s49"]["+"] = "r28";
    Action["s49"]["-"] = "r28";
    Action["s49"]["*"] = "r28";
    Action["s49"]["/"] = "r28";
    Action["s50"]["{"] = "r10";
    Action["s50"]["}"] = "r10";
    Action["s50"]["if"] = "r10";
    Action["s50"]["else"] = "r10";
    Action["s50"]["while"] = "r10";
    Action["s50"]["ID"] = "r10";
    Action["s51"]["else"] = "s56";
    Action["s52"][")"] = "r19";
    Action["s52"][";"] = "r19";
    Action["s52"]["<"] = "r19";
    Action["s52"][">"] = "r19";
    Action["s52"]["<="] = "r19";
    Action["s52"][">="] = "r19";
    Action["s52"]["=="] = "r19";
    Action["s53"][")"] = "r20";
    Action["s53"][";"] = "r20";
    Action["s53"]["<"] = "r20";
    Action["s53"][">"] = "r20";
    Action["s53"]["<="] = "r20";
    Action["s53"][">="] = "r20";
    Action["s53"]["=="] = "r20";
    Action["s54"][")"] = "r23";
    Action["s54"][";"] = "r23";
    Action["s54"]["<"] = "r23";
    Action["s54"][">"] = "r23";
    Action["s54"]["<="] = "r23";
    Action["s54"][">="] = "r23";
    Action["s54"]["=="] = "r23";
    Action["s54"]["+"] = "r23";
    Action["s54"]["-"] = "r23";
    Action["s55"][")"] = "r24";
    Action["s55"][";"] = "r24";
    Action["s55"]["<"] = "r24";
    Action["s55"][">"] = "r24";
    Action["s55"]["<="] = "r24";
    Action["s55"][">="] = "r24";
    Action["s55"]["=="] = "r24";
    Action["s55"]["+"] = "r24";
    Action["s55"]["-"] = "r24";
    Action["s56"]["{"] = "s3";
    Action["s56"]["if"] = "s10";
    Action["s56"]["while"] = "s11";
    Action["s56"]["ID"] = "s12";
    Action["s57"]["{"] = "r9";
    Action["s57"]["}"] = "r9";
    Action["s57"]["if"] = "r9";
    Action["s57"]["else"] = "r9";
    Action["s57"]["while"] = "r9";
    Action["s57"]["ID"] = "r9";
}

void TransitionTable::initGoto() {
    Goto["s0"]["program"] = "s1";
    Goto["s0"]["compoundstmt"] = "s2";
    Goto["s3"]["stmt"] = "s5";
    Goto["s3"]["compoundstmt"] = "s9";
    Goto["s3"]["stmts"] = "s4";
    Goto["s3"]["ifstmt"] = "s6";
    Goto["s3"]["whilestmt"] = "s7";
    Goto["s3"]["assgstmt"] = "s8";
    Goto["s5"]["stmt"] = "s5";
    Goto["s5"]["compoundstmt"] = "s9";
    Goto["s5"]["stmts"] = "s14";
    Goto["s5"]["ifstmt"] = "s6";
    Goto["s5"]["whilestmt"] = "s7";
    Goto["s5"]["assgstmt"] = "s8";
    Goto["s15"]["boolexpr"] = "s18";
    Goto["s15"]["arithexpr"] = "s19";
    Goto["s15"]["multexpr"] = "s20";
    Goto["s15"]["simpleexpr"] = "s21";
    Goto["s16"]["boolexpr"] = "s25";
    Goto["s16"]["arithexpr"] = "s19";
    Goto["s16"]["multexpr"] = "s20";
    Goto["s16"]["simpleexpr"] = "s21";
    Goto["s17"]["arithexpr"] = "s26";
    Goto["s17"]["multexpr"] = "s20";
    Goto["s17"]["simpleexpr"] = "s21";
    Goto["s19"]["boolop"] = "s28";
    Goto["s20"]["arithexprprime"] = "s34";
    Goto["s21"]["multexprprime"] = "s37";
    Goto["s24"]["arithexpr"] = "s40";
    Goto["s24"]["multexpr"] = "s20";
    Goto["s24"]["simpleexpr"] = "s21";
    Goto["s28"]["arithexpr"] = "s44";
    Goto["s28"]["multexpr"] = "s20";
    Goto["s28"]["simpleexpr"] = "s21";
    Goto["s35"]["multexpr"] = "s45";
    Goto["s35"]["simpleexpr"] = "s21";
    Goto["s36"]["multexpr"] = "s46";
    Goto["s36"]["simpleexpr"] = "s21";
    Goto["s38"]["simpleexpr"] = "s47";
    Goto["s39"]["simpleexpr"] = "s48";
    Goto["s41"]["stmt"] = "s50";
    Goto["s41"]["compoundstmt"] = "s9";
    Goto["s41"]["ifstmt"] = "s6";
    Goto["s41"]["whilestmt"] = "s7";
    Goto["s41"]["assgstmt"] = "s8";
    Goto["s43"]["stmt"] = "s51";
    Goto["s43"]["compoundstmt"] = "s9";
    Goto["s43"]["ifstmt"] = "s6";
    Goto["s43"]["whilestmt"] = "s7";
    Goto["s43"]["assgstmt"] = "s8";
    Goto["s45"]["arithexprprime"] = "s52";
    Goto["s46"]["arithexprprime"] = "s53";
    Goto["s47"]["multexprprime"] = "s54";
    Goto["s48"]["multexprprime"] = "s55";
    Goto["s56"]["stmt"] = "s57";
    Goto["s56"]["compoundstmt"] = "s9";
    Goto["s56"]["ifstmt"] = "s6";
    Goto["s56"]["whilestmt"] = "s7";
    Goto["s56"]["assgstmt"] = "s8";
}


class LRParser {

private:
    string src;
    vector<string> tokens;
    int pos;
    int lineNum;
    int errorLineNum;
    int mode;
public:
    void setMode(int mode);

private:
    stack<string> states;
    vector<string> symbols;

    vector<vector<string>> ans;

    TransitionTable t;

public:

    LRParser(string prog, TransitionTable t);

    void parse();

    void printAns();

};

LRParser::LRParser(string prog, TransitionTable t): t(t) {
    pos = 0;
    src = prog + " $";
    tokens = split(src);
    this->lineNum = 0;
    this->errorLineNum = -1;
}

void LRParser::parse() {
    ans.clear();
    symbols.clear();
    while(!states.empty()) {
        states.pop();
    }
    pos = 0;
    states.push("s0");
    vector<string> oneAns;
    for (auto it = tokens.begin() + pos; it != tokens.end(); it++){
        if (*it != "<endl>" && *it != "$") {
            oneAns.push_back(*it);
        }
    }
    ans.push_back(oneAns);
    while(1) {
        if (tokens[pos] == "<endl>") {
            pos++;
            lineNum++;
        }
        string nextAction = t.Action[states.top()][tokens[pos]];
        if (nextAction[0] == 's') {
            // Shift
            states.push(nextAction);
            symbols.push_back(tokens[pos++]);
        }
        else if (nextAction[0] == 'r') {
            // Reduce
            Reduction nextReduction = t.Reductions[nextAction];
            vector<string> oneAns;
            for (int j = 0; j < nextReduction.len; j ++) {
                states.pop();
                symbols.pop_back();
            }
            symbols.push_back(nextReduction.stmt);
            // Generate Answers
            for(auto it = symbols.begin(); it != symbols.end(); it++) {
                oneAns.push_back(*it);
            }
            for (auto it = tokens.begin() + pos; it != tokens.end(); it++){
                if (*it != "<endl>" && *it != "$") {
                    oneAns.push_back(*it);
                }
            }
            ans.push_back(oneAns);
            states.push(t.Goto[states.top()][nextReduction.stmt]);
        }
        else if (nextAction[0] == 'e') {
            // Error handling
            tokens.insert(tokens.begin() + pos, ";");
            cout << "语法错误，第" << lineNum << "行，缺少\";\"" << endl;
        }
        else {
            // Accept
            break;
        }
    }
    if (mode == PARSEMPDE_PARSE) {
        printAns();
    }
}

void LRParser::printAns() {
    for(auto it = ans.rbegin(); it != ans.rend(); it ++) {
        string out = join(*it);
        cout << out;
        if (it != ans.rend() - 1) {
            cout << " =>" << endl;
        }
    }
}

void LRParser::setMode(int mode) {
    LRParser::mode = mode;
}

void Analysis() {
    string prog;
    read_prog(prog);

    /********* Begin *********/

    TransitionTable table = TransitionTable(ruleMap, nonterminals, terminals);
    LRParser parser = LRParser(prog, table);
    parser.setMode(PARSEMODE_ERRORCHECKING);
    parser.parse();
    parser.setMode(PARSEMPDE_PARSE);
    parser.parse();

    /********* End *********/
}

string prog;