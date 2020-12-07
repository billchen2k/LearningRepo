/**
 * Copyright 2020, Juntong Chen
 * East China Normal University
 */
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void read_prog(string &prog) {
    char c;
    while (scanf("%c", &c) != EOF) {
        prog += c;
    }
}

map<string, short> typeNameMap = {
        {"auto",       1},
        {"break",      2},
        {"case",       3},
        {"char",       4},
        {"const",      5},
        {"continue",   6},
        {"default",    7},
        {"do",         8},
        {"double",     9},
        {"else",       10},
        {"enum",       11},
        {"extern",     12},
        {"float",      13},
        {"for",        14},
        {"goto",       15},
        {"if",         16},
        {"int",        17},
        {"long",       18},
        {"register",   19},
        {"return",     20},
        {"short",      21},
        {"signed",     22},
        {"sizeof",     23},
        {"static",     24},
        {"struct",     25},
        {"switch",     26},
        {"typedef",    27},
        {"union",      28},
        {"unsigned",   29},
        {"void",       30},
        {"volatile",   31},
        {"while",      32},
        {"-",          33},
        {"--",         34},
        {"-=",         35},
        {"->",         36},
        {"!",          37},
        {"!=",         38},
        {"%",          39},
        {"%=",         40},
        {"&",          41},
        {"&&",         42},
        {"&=",         43},
        {"(",          44},
        {")",          45},
        {"*",          46},
        {"*=",         47},
        {",",          48},
        {".",          49},
        {"/",          50},
        {"/=",         51},
        {":",          52},
        {";",          53},
        {"?",          54},
        {"[",          55},
        {"]",          56},
        {"^",          57},
        {"^=",         58},
        {"{",          59},
        {"|",          60},
        {"||",         61},
        {"|=",         62},
        {"}",          63},
        {"~",          64},
        {"+",          65},
        {"++",         66},
        {"+=",         67},
        {"<",          68},
        {"<<",         69},
        {"<<=",        70},
        {"<=",         71},
        {"=",          72},
        {"==",         73},
        {">",          74},
        {">=",         75},
        {">>",         76},
        {">>=",        77},
        {"\"",         78},
        {"Comment",    79},
        {"Constant",   80},
        {"Identifier", 81}
};

/************ Token ***********/

class Token {
private:
    int tokenId;
public:
    enum class TypeName {
        Keyword,
        Operator,
        Comments,
        Constant,
        Identifier,
        Init,
        End
    };
    TypeName type;
    string lexeme;

    Token(TypeName type, const string &lexeme);

    Token(TypeName type, const string &lexeme, int tokenId);

    short getTypeId();

    void print();
};

short Token::getTypeId() {
    switch (type) {
        case TypeName::Keyword:
        case TypeName::Operator:
            return typeNameMap.find(this->lexeme)->second;
        case TypeName::Comments:
            return 79;
        case TypeName::Constant:
            return 80;
        case TypeName::Identifier:
            return 81;
        default:
            return 0;
    }
}

Token::Token(Token::TypeName type, const string &lexeme) : type(type), lexeme(lexeme) {}

Token::Token(Token::TypeName type, const string &lexeme, int tokenId) : type(type), lexeme(lexeme), tokenId(tokenId) {}

void Token::print() {
    if (tokenId != 1) {
        cout << endl;
    }
    printf("%d: <%s,%d>", this->tokenId, this->lexeme.c_str(), this->getTypeId());
}

/************ Scanner ***********/

class Scanner {
private:
    // Total token count
    int tokenCount;
    // Current position in the string
    int pos;
    // Src program string
    string &src;

    short quoteStatus;

    enum class charType {
        Alphabet,
        Number,
        Symbol,
        Slash,
        Blank,
        Quote,
        Endl,
        Star,
        Dot,
        Eof
    };

    vector<string> Keywords = {
            "auto", "break", "case", "char", "const",
            "continue", "default", "do", "double", "else",
            "enum", "extern", "float", "for", "goto", "if",
            "int", "long", "register", "return", "return",
            "short", "signed", "sizeof", "static", "struct",
            "switch", "typedef", "union", "unsigned", "void",
            "volatile"
    };

public:
    Token next();

    charType peek();

    char get();

    Scanner(string &src);

    Token getIdentifierOrKeyword();

    Token getNumber();

    Token getOperator();

    Token getCommentOrOperator();

    Token getQuoteOrIdentifier();
};

Scanner::Scanner(string &src) : src(src) {
    this->pos = 0;
    this->tokenCount = 0;
    this->quoteStatus = 0;
}

Token Scanner::getIdentifierOrKeyword() {
    string out = "";
    while (peek() == charType::Alphabet || peek() == charType::Number) {
        out += get();
    }
    if (find(Keywords.begin(), Keywords.end(), out) != Keywords.end()) {
        return Token(Token::TypeName::Keyword, out, tokenCount);
    } else {
        return Token(Token::TypeName::Identifier, out, tokenCount);
    }
}

/**
 * Get next number Token. An automaton with 3 states.
 * @return
 */
Token Scanner::getNumber() {
    string out = "";
    short state = 0;
    while (1) {
        switch (state) {
            case 0:
                switch (peek()) {
                    case charType::Number:
                        out += get();
                        state = 0;
                        break;
                    case charType::Dot:
                        out += get();
                        state = 1;
                        break;
                    default:
                        return Token(Token::TypeName::Constant, out, tokenCount);
                }
                break;
            case 1:
                switch (peek()) {
                    case charType::Number:
                        out += get();
                        state = 1;
                        break;
                    default:
                        return Token(Token::TypeName::Constant, out, tokenCount);
                }

        }
    }
}

/**
 * Get next operator Token that's not start with '/'. An automaton with 3 states.
 * @return
 */
Token Scanner::getOperator() {
    string out = "";
    short state = 0;
    while (1) {
        switch (state) {
            case 0:
                switch (src[pos]) {
                    case '(':
                    case ')':
                    case ',':
                    case '.':
                    case ':':
                    case ';':
                    case '?':
                    case '[':
                    case ']':
                    case '{':
                    case '}':
                    case '~':
                        out += get();
                        return Token(Token::TypeName::Operator, out, tokenCount);
                    default:
                        out += get();
                        if (peek() == charType::Symbol) {
                            state = 1;
                        } else {
                            return Token(Token::TypeName::Operator, out, tokenCount);
                        }
                }
                break;
            case 1:
                switch (src[pos]) {
                    case '-':
                    case '=':
                    case '&':
                    case '|':
                    case '+':
                        out += get();
                        return Token(Token::TypeName::Operator, out, tokenCount);
                    default:
                        out += get();
                        if (peek() == charType::Symbol) {
                            state = 2;
                        } else {
                            return Token(Token::TypeName::Operator, out, tokenCount);
                        }
                }
                break;
            case 2:
                out += get();
                return Token(Token::TypeName::Operator, out, tokenCount);
        }
    }
}

/**
 * When next token starts with '/', this method would judge if it's a comment or an operator.
 * @return
 */
Token Scanner::getCommentOrOperator() {
    string out = "";
    out += get();
    short state = 0;
    while (1) {
        switch (state) {
            case 0:
                switch (src[pos]) {
                    case '=':
                        out += get();
                        return Token(Token::TypeName::Operator, out, tokenCount);
                    case '*':
                        // Multiline comment
                        out += get();
                        state = 2;
                        break;
                    case '/':
                        // Single line comment
                        out += get();
                        state = 1;
                        break;
                    default:
                        return Token(Token::TypeName::Operator, out, tokenCount);
                }
                break;
            case 1:
                switch (peek()) {
                    case charType::Endl:
                        pos++;
                        return Token(Token::TypeName::Comments, out, tokenCount);
                    default:
                        out += get();
                }
                break;
            case 2:
                switch (peek()) {
                    case charType::Star:
                        out += get();
                        state = 3;
                        break;
                    default:
                        out += get();
                }
                break;
            case 3:
                switch (peek()) {
                    case charType::Slash:
                        out += get();
                        return Token(Token::TypeName::Comments, out, tokenCount);
                    default:
                        out += get();
                        state = 2;
                }
                break;
        }
    }
}

/**
 * Get next char and move position forward.
 * @return
 */
char Scanner::get() {
    return src[pos++];
}

/**
 * Peek next char. Char type is returned.
 * @return When returning charType::Slash, next Token might be comment or an operator.
 *         On contrast, tchartype::Symbol is returned.
 */
Scanner::charType Scanner::peek() {
    char nextChar = src[pos];
    if (nextChar >= 'A' && nextChar <= 'Z' || nextChar >= 'a' && nextChar <= 'z') {
        return charType::Alphabet;
    }
    if (nextChar >= '0' && nextChar <= '9') {
        return charType::Number;
    }
    switch (src[pos]) {
        case ' ':
        case '\t':
            return charType::Blank;
        case '\n':
            return charType::Endl;
        case '.':
            return charType::Dot;
        case '*':
            return charType::Star;
        case '/':
            return charType::Slash;
        case '"':
            return charType::Quote;
        case '\0':
            return charType::Eof;
        default:
            return charType::Symbol;
    }
}

/**
 * If quoteStatus == 1, the lexer should be in quote mode, returning enything but quotes inside.
 * @return
 */
Token Scanner::getQuoteOrIdentifier() {
    string out = "";
    switch (quoteStatus) {
        case (0):
            out += get();
            this->quoteStatus = 1;
            return Token(Token::TypeName::Operator, out, tokenCount);
            break;
        case (1):
            while (peek() != charType::Quote) {
                out += get();
            }
            this->quoteStatus = 2;
            return Token(Token::TypeName::Identifier, out, tokenCount);
        case (2):
            out += get();
            this->quoteStatus = 0;
            return Token(Token::TypeName::Operator, out, tokenCount);
    }
}

/**
 * Get next token.
 * @return
 */
Token Scanner::next() {
    while (peek() == charType::Blank || peek() == charType::Endl) {
        get();
    }
    tokenCount++;
    if (quoteStatus) {
        // Currently in quotes
        return getQuoteOrIdentifier();
    }
    switch (Scanner::peek()) {
        case charType::Alphabet:
            return getIdentifierOrKeyword();
        case charType::Number:
            return getNumber();
        case charType::Slash:
            return getCommentOrOperator();
        case charType::Dot:
        case charType::Symbol:
            return getOperator();
        case charType::Quote:
            return getQuoteOrIdentifier();
        case charType::Eof:
        default:
            return Token(Token::TypeName::End, "[end]", this->tokenCount);
    }
    return Token(Token::TypeName::End, "[end]", this->tokenCount);
}

void Analysis() {
    string prog;
    read_prog(prog);
    /********* Begin *********/
    Scanner sc = Scanner(prog);
    for (auto token = sc.next(); token.type != Token::TypeName::End; token = sc.next()) {
        token.print();
    }
    /********* End *********/
}

string prog;

