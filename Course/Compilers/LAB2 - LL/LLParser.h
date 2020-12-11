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
#include <vector>
#include <unordered_set>
#include <algorithm>

/* If set to 1, will use precalculated rule table instead of
 * Calculating one by the program itself.
 *
 * Todo: Calculating a predict table.
 */
#define PREDEFINED_RULE_TABLE 1
#define PARSEMODE_ERRORCHECKING 1
#define PARSEMPDE_PARSE 2

typedef std::vector<std::string> trow;
typedef std::vector<trow> table;

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

set<string> nonterminals = {
        "program", "stmt", "compoundstmt", "stmts", "ifstmt", "whilestmt","assgstmt", "boolexpr", "boolop",
        "arithexpr", "arithexprprime", "multexpr", "multexprprime", "simpleexpr"
};

/**
 * E stands for empty symbol.
 */
set<string> terminals = {
        "{", "}", "if", "(", ")", "then", "else", "while",
        "ID", "=", ">", "<", ">=", "<=", "==", "+", "-", "*",
        "/", "NUM", "E", ";", "$"
};

/**
 * Split a string by space. Return a string vector.
 * Line break is split by an <endl> token.
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

/* ************************* SymbolLookup ***************************
 * Usage example: sl.n("stmt") to get a integer.
 * */

class SymbolLookup {
private:
    int ntCount = 0;
    int tCount = 0;
    map<string, int> tmap;
    map<string, int> ntmap;

public:
    int t(string s);

    int nt(string s);

    string t_r(int num);

    string nt_r(int num);

    bool is_t(string s);

    bool is_nt(string s);

    pair<int, int>  getSize();

    SymbolLookup(set<string> &_t, set<string> &_nt);
};

SymbolLookup::SymbolLookup(set<string> &_t, set<string> &_nt) {
    for (auto oneT : _t) {
        tmap[oneT] = tCount++;
    }
    for (auto oneNt : _nt) {
        ntmap[oneNt] = ntCount++;
    }
}

/**
 * Convert non-terminal symbol s to a integer.
 * @param s Non-terminal symbol.
 * @return
 */
int SymbolLookup::nt(string s) {
    auto it = ntmap.find(s);
    return it != ntmap.end() ? it->second : -1;
}

/**
 * Convert terminal symbol to a interger.
 * @param s The terminal symbol.
 * @return if -1 is returned, things goes wrong.
 */
int SymbolLookup::t(string s) {
    auto it = tmap.find(s);
    return it != tmap.end() ? it->second : -1;
}

/**
 * Get the size of the symbol look up table.
 * @return
 */
pair<int, int> SymbolLookup::getSize() {
    return make_pair(this->ntCount, this->tCount);
}

/**
 * Transform the terminal string number back to a terminal symbol string.
 * @param num
 * @return
 */
string SymbolLookup::t_r(int num) {
    for(auto one: tmap) {
        if (one.second == num) {
            return one.first;
        }
    }
    return "";
}

/**
 * Transform a non-terminal string number back to a non-terminal symbol string.
 * @param num
 * @return
 */
string SymbolLookup::nt_r(int num) {
    for(auto one: ntmap) {
        if (one.second == num) {
            return one.first;
        }
    }
    return "";
}

bool SymbolLookup::is_t(string s) {
    return tmap.find(s) != tmap.end();
}

bool SymbolLookup::is_nt(string s) {
    return ntmap.find(s) != ntmap.end();
}

/* ************************* RuleTable *************************** */

class RuleTable{
private:
    multimap<string, string> rules;
    table ruleTable;

    // First and follow set, used to calculate the ruleTable.
    map<string, unordered_set<string>> first;
    map<string, unordered_set<string>> follow;

    SymbolLookup sl;

    void generateFirst(string s);

    void generateFollow(string s);

public:
    RuleTable(multimap<string, string> &_rules, SymbolLookup sl);

    void printTableRow(string nonterminal);

    string getRule(string nt, string t);
};

RuleTable::RuleTable(multimap<string, string> &_rules, SymbolLookup sl) : sl(sl) {
    // Predefined Rules
    ruleTable.resize(sl.getSize().first);
    for(int i = 0; i < ruleTable.size(); i++){
        ruleTable[i].resize(sl.getSize().second);
    }
    if(PREDEFINED_RULE_TABLE) {
        // A predefined rule table.

        ruleTable[sl.nt("program")][sl.t("{")] = "compoundstmt";

        ruleTable[sl.nt("stmt")][sl.t("{")] = "compoundstmt";
        ruleTable[sl.nt("stmt")][sl.t("if")] = "ifstmt";
        ruleTable[sl.nt("stmt")][sl.t("while")] = "whilestmt";
        ruleTable[sl.nt("stmt")][sl.t("ID")] = "assgstmt";
        ruleTable[sl.nt("stmt")][sl.t("if")] = "ifstmt";

        ruleTable[sl.nt("compoundstmt")][sl.t("{")] = "{ stmts }";

        ruleTable[sl.nt("stmts")][sl.t("{")] = "stmt stmts";
        ruleTable[sl.nt("stmts")][sl.t("}")] = "E";
        ruleTable[sl.nt("stmts")][sl.t("if")] = "stmt stmts";
        ruleTable[sl.nt("stmts")][sl.t("while")] = "stmt stmts";
        ruleTable[sl.nt("stmts")][sl.t("ID")] = "stmt stmts";

        ruleTable[sl.nt("ifstmt")][sl.t("if")] = "if ( boolexpr ) then stmt else stmt";

        ruleTable[sl.nt("whilestmt")][sl.t("while")] = "while ( boolexpr ) stmt";

        ruleTable[sl.nt("assgstmt")][sl.t("ID")] = "ID = arithexpr ;";

        ruleTable[sl.nt("boolexpr")][sl.t("(")] = "arithexpr boolop arithexpr";
        ruleTable[sl.nt("boolexpr")][sl.t("ID")] = "arithexpr boolop arithexpr";
        ruleTable[sl.nt("boolexpr")][sl.t("NUM")] = "arithexpr boolop arithexpr";

        ruleTable[sl.nt("boolop")][sl.t("<")] = "<";
        ruleTable[sl.nt("boolop")][sl.t(">")] = ">";
        ruleTable[sl.nt("boolop")][sl.t("<=")] = "<=";
        ruleTable[sl.nt("boolop")][sl.t(">=")] = ">=";
        ruleTable[sl.nt("boolop")][sl.t("==")] = "==";

        ruleTable[sl.nt("arithexpr")][sl.t("(")] = "multexpr arithexprprime";
        ruleTable[sl.nt("arithexpr")][sl.t("ID")] = "multexpr arithexprprime";
        ruleTable[sl.nt("arithexpr")][sl.t("NUM")] = "multexpr arithexprprime";

        ruleTable[sl.nt("arithexprprime")][sl.t(")")] = "E";
        ruleTable[sl.nt("arithexprprime")][sl.t(";")] = "E";
        ruleTable[sl.nt("arithexprprime")][sl.t("<")] = "E";
        ruleTable[sl.nt("arithexprprime")][sl.t(">")] = "E";
        ruleTable[sl.nt("arithexprprime")][sl.t("<=")] = "E";
        ruleTable[sl.nt("arithexprprime")][sl.t(">=")] = "E";
        ruleTable[sl.nt("arithexprprime")][sl.t("==")] = "E";
        ruleTable[sl.nt("arithexprprime")][sl.t("+")] = "+ multexpr arithexprprime";
        ruleTable[sl.nt("arithexprprime")][sl.t("-")] = "- multexpr arithexprprime";

        ruleTable[sl.nt("multexpr")][sl.t("(")] = "simpleexpr multexprprime";
        ruleTable[sl.nt("multexpr")][sl.t("ID")] = "simpleexpr multexprprime";
        ruleTable[sl.nt("multexpr")][sl.t("NUM")] = "simpleexpr multexprprime";

        ruleTable[sl.nt("multexprprime")][sl.t(")")] = "E";
        ruleTable[sl.nt("multexprprime")][sl.t(";")] = "E";
        ruleTable[sl.nt("multexprprime")][sl.t("<")] = "E";
        ruleTable[sl.nt("multexprprime")][sl.t(">")] = "E";
        ruleTable[sl.nt("multexprprime")][sl.t("<=")] = "E";
        ruleTable[sl.nt("multexprprime")][sl.t(">=")] = "E";
        ruleTable[sl.nt("multexprprime")][sl.t("==")] = "E";
        ruleTable[sl.nt("multexprprime")][sl.t("+")] = "E";
        ruleTable[sl.nt("multexprprime")][sl.t("-")] = "E";
        ruleTable[sl.nt("multexprprime")][sl.t("*")] = "* simpleexpr multexprprime";
        ruleTable[sl.nt("multexprprime")][sl.t("/")] = "/ simpleexpr multexprprime";

        ruleTable[sl.nt("simpleexpr")][sl.t("(")] = "( arithexpr )";
        ruleTable[sl.nt("simpleexpr")][sl.t("ID")] = "ID";
        ruleTable[sl.nt("simpleexpr")][sl.t("NUM")] = "NUM";

    }
    else{
        // Calculate the rule table on the go.

        for (string one: terminals) {
            generateFirst(one);
        }
        for (string one : nonterminals) {
            generateFirst(one);
        }
    }
}

void RuleTable::generateFirst(string s) {
    if (terminals.find(s) != terminals.end()) {
        // for terminals
        first[s] = unordered_set<string>();
        first[s].insert(s);
    }
    else{
        //for nonterminals
    }
}

void RuleTable::printTableRow(string nonterminal) {
    trow row = ruleTable[sl.nt(nonterminal)];
    for(int i = 0; i < row.size(); i++) {
        string derive = row[i];
        if (derive.size() > 0) {
            cout << left << sl.t_r(i) <<  ": " << nonterminal << " -> " << derive << endl;
//            cout << setw(6) << left << sl.t_r(i) <<  ": " << nonterminal << " -> " << derive << endl;

        }
    }
}

/**
 * Get derived rule.
 * @param nt The nonterminal symbol, indicating a table row.
 * @param t  The terminal symbol to look up for, indicating a table column.
 * @return The rule found.
 */
string RuleTable::getRule(string nt, string t) {
    return ruleTable[sl.nt(nt)][sl.t(t)];
}

/* ************************* LLParser *************************** */

class LLParser {
private:
    int pos;
    int linenum;                    // Current line number.
    short mode;
    vector<string> tokens;
    int erroredLineNum;             // The line number which error occured

    SymbolLookup sl;
    RuleTable rt;

public:
    LLParser(string _src, RuleTable rt, SymbolLookup sl);

    void parse();

    void setMode(short _mode);

    void forward(string top, int layer);
};

LLParser::LLParser(string _src, RuleTable rt, SymbolLookup sl) : rt(rt), sl(sl) {
    this->pos = 0;
    this->linenum = 1;
    this->mode = PARSEMPDE_PARSE;
    _src += " $";
    this->tokens = split(_src);
}

void LLParser::setMode(short _mode) {
    mode = _mode;
}

void LLParser::forward(string top, int layer) {
    if (mode == PARSEMPDE_PARSE) {
        if (top != "program") cout << endl;
        for (int i = 0; i < layer; i++) cout << "\t";
        cout << top;
    }
    if (erroredLineNum || tokens[pos] == "$" ) {
        return;
    }
    if (tokens[pos] == "<endl>") {
        pos++;
        linenum++;
    }
    if (tokens[pos] == "$") {
        return;
    }
    string derives = rt.getRule(top, tokens[pos]);
    if (derives.size() == 0) {
        // Rule not found, error occurred.
        erroredLineNum = linenum;
        if (tokens[pos - 1] == "<endl>") erroredLineNum--;
        cout << "语法错误,第" << erroredLineNum<< "行,缺少\";\"" << endl;
        // Fix the error
        tokens.insert(tokens.begin() + pos, ";");
        return;
    }
    vector<string> deriveSplit = split(derives);
    deriveSplit.pop_back(); // Remove <endl>
//   Print current derivation
//  cout << top << " -> " << derives << " | " << tokens[pos] << endl;
    for(auto oneSymbol : deriveSplit) {
        if(sl.is_t(oneSymbol)) {
            if (mode == PARSEMPDE_PARSE) {
                cout << endl;
                for (int i = 0; i < layer + 1; i++) cout << "\t";
                cout << oneSymbol;
            }
            while (tokens[pos] == "<endl>"){
                pos++;
                linenum++;
            }
            if (tokens[pos] == oneSymbol) {
                pos++;
            }
//            if (oneSymbol == tokens[pos]) {
//                // Correctly matched
//                pos++;
//            }
            if (oneSymbol == "E") {
                // Empty derivation
                return;
            }
        }
        if(sl.is_nt(oneSymbol)) {
            forward(oneSymbol, layer + 1);
        }
    }
}

void LLParser::parse() {
    // Print the whole table
    //    for (auto nt: nonterminals) {
    //        cout << "---------------- " << nt << " ----------------\n";
    //        rt.printTableRow(nt);
    //    }
    //    for(string one: tokens) {
    //        printf("%s \n", one.c_str());
    //    }
    erroredLineNum = pos = 0;
    linenum = 1;
    // Let program be the initial token.
    try {
        forward("program", 0);
    }
    catch (exception e){
        cout << "未知错误" << endl;
    }
}

void read_prog(string &prog) {
    char c;
    while (scanf("%c", &c) != EOF) {
        prog += c;
    }
}

void Analysis() {
    string prog;
    read_prog(prog);

    /********* Begin *********/
//    auto it = ruleMap.equal_range("stmts");
//    for (auto itr = it.first; itr != it.second; ++itr) {
//        cout << itr->first<< "->" << itr->second << '\n';
//    }
    // A lookup table to convert string into numbers.

    SymbolLookup sl = SymbolLookup(terminals, nonterminals);
    // A predict table for parser to use.
    RuleTable rt = RuleTable(ruleMap, sl);
    // Main parser.
    LLParser parser = LLParser(prog, rt, sl);
    parser.setMode(PARSEMODE_ERRORCHECKING);
    parser.parse();
    parser.setMode(PARSEMPDE_PARSE);
    parser.parse();

    /********* End *********/
}

string prog;