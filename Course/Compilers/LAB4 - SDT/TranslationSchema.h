/**
 * Copyright 2020, Juntong Chen
 * East China Normal University
 */
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

/**
 * Split a string by space. Return a string vector.
 * Line break is split by an <endl> token. (Used for calculating line numbers)
 */
vector<string> split(string const& s) {
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

void read_prog(string &prog) {
    char c;
    while (scanf("%c", &c) != EOF) {
        prog += c;
    }
}

/**
 * Temp indicating a temp variable
 */
enum Type {
    Real, Int, Temp
};

enum Comparator {
    greater, greaterEqual, less, lessEqual, equal
};

enum Operator {
    plus, sub, divide, mult
};

/**
 * If name is "null", indicating this is an unnamed temp variable
 */
struct Identifier {
    string name;
    Type type;
    double value;

    Identifier() {};

    Identifier(string name, Type t, double v) {
        this->name = name;
        this->type = t;
        this->value = v;
    }
};

map<string, Identifier> IDMap;

/***************************** Error Handler *****************************/

class ErrorHandler{
public:
    static void conversionError(int lineNum);
    static void divisionByZeroError(int lineNum);
};

void ErrorHandler::conversionError(int lineNum) {
    printf("error message:line %d,realnum can not be translated into int type\n", lineNum);
}

void ErrorHandler::divisionByZeroError(int lineNum) {
    printf("error message:line %d,division by zero\n", lineNum);

}

/***************************** Expression *****************************/

class Expression {
public:
    int lineNum;

    Expression() {
        lineNum = 0;
    }
};

/**
 * target = srcLeft opt srcRight
 */
class AssignExpr: public Expression {
private:
    Identifier* target;
    Identifier* srcLeft;
    Identifier* srcRight;
    Operator opt;
public:
    double exectute();

    AssignExpr(Identifier *target, Identifier *srcLeft, Identifier *srcRight, Operator opt);
};

AssignExpr::AssignExpr(Identifier *target, Identifier *srcLeft, Identifier *srcRight, Operator opt) :
target(target),  srcLeft(srcLeft), srcRight(srcRight), opt(opt) {}

double AssignExpr::exectute() {
    switch (opt) {
        case Operator::plus:
            target->value = srcLeft->value + srcRight->value;
            break;
        case Operator::sub:
            target->value = srcLeft->value - srcRight->value;
            break;
        case Operator::mult:
            target->value = srcLeft->value * srcRight->value;
            break;
        case Operator::divide:
            if (srcRight->value == 0) {
                // Handle divide by error error.
                ErrorHandler::divisionByZeroError(this->lineNum);
                return 0;
            }
            target->value = srcLeft->value / srcRight->value;
            break;
    }
    return target->value;
}

/**
 * left cmp right
 */
class BoolExpr: public Expression {
private:
    Identifier* left;
    Identifier* right;
    Comparator cmp;
public:
    bool eval();

    BoolExpr(Identifier *left, Identifier *right, Comparator cmp);
};

BoolExpr::BoolExpr(Identifier *left, Identifier *right, Comparator cmp) : left(left), right(right), cmp(cmp) {}

/**
 * Evaluate the bool expression.
 * @return
 */
bool BoolExpr::eval() {
    switch (cmp) {
        case Comparator::greater:
            return left->value > right->value;
        case Comparator::greaterEqual:
            return left->value >= right->value;
        case Comparator::less:
            return left->value < right->value;
        case Comparator::lessEqual:
            return left->value <= right->value;
        case Comparator::equal:
            return left->value == right->value;
    }
}

/**
 * if (boolExpr) then thenExpr else elseExpr
 */
class IfExpr : public Expression {
private:
    BoolExpr boolExpr;
    AssignExpr thenExpr;
    AssignExpr elseExpr;
public:
    void execute();

    IfExpr(const BoolExpr &boolExpr, const AssignExpr &thenExpr, const AssignExpr &elseExpr) :
        boolExpr(boolExpr), thenExpr(thenExpr),elseExpr(elseExpr) {}
};

void IfExpr::execute() {
    if(boolExpr.eval()) {
        thenExpr.exectute();
    }
    else {
        elseExpr.exectute();
    }
}

/***************************** Translator *****************************/
class Translator {
private:

    string src;
    int pos;
    int lineNum;
    bool hasError;
    vector<string> tokens;

    /**
     * Move the position forward count tokens. Will ignore new line and update lineNum.
     * @param count The number of tokens to go forward.
     */
    void forward(int count);

    void swallowDeclare();
    AssignExpr * swallowAssign();
    IfExpr * swallowIf();
    /**
     * Swallow a bool expression.
     * @return A bool expression pointer.
     */
    BoolExpr* swallowBool();

    void printResult();

public:
    Translator(string &prog);

    void translate();
};

Translator::Translator(string &prog){
    src = prog;
    src += " $";
    lineNum = 1;
    pos = 0;
    hasError = false;
    tokens = split(src);
}

void Translator::forward(int count) {
    for(int i = 0; i < count;) {
        if (tokens[pos] == "<endl>") {
            lineNum++;
        }
        else {
            i++;
        }
        pos++;
    }
    if (tokens[pos] == "<endl>") {
        lineNum++;
        pos++;
    }
}

void Translator::swallowDeclare() {
    string varName = tokens[pos + 1];
    string type = tokens[pos];
    double value = stod(tokens[pos + 3]);
    Identifier id;
    if (type == "int") {
        id = Identifier(varName, Int, value);
        if (tokens[pos + 3].find('.') != string::npos) {
            // Handle conversion error
            ErrorHandler::conversionError(lineNum);
            hasError = true;
        }
    }
    else if(type == "real") {
        id = Identifier(varName, Real, value);
    }
    IDMap[varName] = id;
    forward(4);
}

AssignExpr* Translator::swallowAssign() {
    Identifier* target = &IDMap[tokens[pos]];
    Identifier* srcLeft;
    Identifier* srcRight;
    string Lstr = tokens[pos + 2];
    string Rstr = tokens[pos + 4];
    if (Lstr[0] >= '0' && Lstr[0] <= '9') {
        srcLeft = new Identifier("null", Type::Temp, stod(Lstr));
    }
    else{
        srcLeft = &IDMap[tokens[pos + 2]];
    }
    if (Rstr[0] >= '0' && Rstr[0] <= '9') {
        srcRight = new Identifier("null", Type::Temp, stod(Rstr));
    }
    else {
        srcRight = &IDMap[tokens[pos + 4]];
    }
    char optChar = tokens[pos + 3][0];
    AssignExpr* assignExpr = NULL;
    switch (optChar) {
        case '+':
            assignExpr = new AssignExpr(target, srcLeft, srcRight, Operator::plus);
            break;
        case '-':
            assignExpr = new AssignExpr(target, srcLeft, srcRight, Operator::sub);
            break;
        case '*':
            assignExpr = new AssignExpr(target, srcLeft, srcRight, Operator::mult);
            break;
        case '/':
            assignExpr = new AssignExpr(target, srcLeft, srcRight, Operator::divide);
            break;
    }
    assignExpr->lineNum = lineNum;
    forward(6);
    string next = tokens[pos - 1];

    // Handling compound assignment
    if (next == "+" || next == "-" || next == "*" || next == "/") {
        double tempValue = assignExpr->exectute();
        string RRstr = tokens[pos];
        Identifier* srcRRight = new Identifier("null", Type::Temp, stod(RRstr));
        Identifier* srcLLeft = new Identifier("null", Type::Temp, tempValue);
        char optChar = next[0];
        switch (optChar) {
            case '+':
                assignExpr = new AssignExpr(target, srcLLeft, srcRRight, Operator::plus);
                break;
            case '-':
                assignExpr = new AssignExpr(target, srcLLeft, srcRRight, Operator::sub);
                break;
            case '*':
                assignExpr = new AssignExpr(target, srcLLeft, srcRRight, Operator::mult);
                break;
            case '/':
                assignExpr = new AssignExpr(target, srcLLeft, srcRRight, Operator::divide);
                break;
        }
        forward(2);
    }

    return assignExpr;
}

IfExpr * Translator::swallowIf() {
    forward(2); // Forward if (
    BoolExpr * boolExpr = swallowBool();
    forward(2); // Forward ) then
    AssignExpr * thenExpr = swallowAssign();
    forward(1); // Forward else
    AssignExpr * elseExpr = swallowAssign();
    return new IfExpr(*boolExpr, *thenExpr, *elseExpr);
}

BoolExpr* Translator::swallowBool() {
    Identifier* left = &IDMap[tokens[pos]];
    Identifier* right = &IDMap[tokens[pos + 2]];
    string cmp = tokens[pos + 1];
    BoolExpr * boolExpr = NULL;
    if (cmp == "<") {
        boolExpr = new BoolExpr(left, right, Comparator::less);
    }
    else if(cmp == ">") {
        boolExpr = new BoolExpr(left, right, Comparator::greater);
    }
    else if(cmp == ">=") {
        boolExpr = new BoolExpr(left, right, Comparator::greaterEqual);
    }
    else if(cmp == "<=") {
        boolExpr = new BoolExpr(left, right, Comparator::lessEqual);
    }
    else if(cmp == "==") {
        boolExpr = new BoolExpr(left, right, Comparator::equal);
    }
    forward(3);
    return boolExpr;
}

void Translator::printResult() {
    for(auto it = IDMap.begin(); it != IDMap.end(); it++) {
        if (it->second.type == Type::Int) {
            cout << it->first << ": " << it->second.value << endl;
        }
        else {
            // Remove extra zeros after double number
            std::ostringstream oss;
            oss << it->second.value;
            cout << it->first << ": " << oss.str() << endl;
        }
    }
}

void Translator::translate() {
    while(1) {
        string next = tokens[pos];
        if (next == "$") {
            // Finished.
            if (!hasError) {
                printResult();
            }
            break;
        }
        if (next == "<endl>") {
            lineNum++;
            pos++;
            continue;
        }
        if (next == ";" || next == "{" || next == "}") {
            pos++;
            continue;
        }
        if (next == "real" || next == "int") {
            swallowDeclare();
        }
        else if(next == "if") {
            swallowIf()->execute();
        }
        else {
            swallowAssign()->exectute();
        }
    }
}


void Analysis() {
    string prog;
    read_prog(prog);
    /********* Begin *********/

    Translator t = Translator(prog);
    t.translate();

    /********* End *********/
}

string prog;