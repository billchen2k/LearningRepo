#include <cstring>
#include <iostream>
using namespace std;
const int MAX_DEGREE = 20;
const int PRECISE = 2;
void stdclean();
void instruct();
////// Term
struct Term {
  int degree;
  double coefficient;
  //	Term(int _degree = 0, double _coefficient = 0);
  Term();
  void setValue(int _degree = 0, double _coefficient = 0);
};
Term::Term() {
  degree = 0;
  coefficient = 0;
}
// Term::Term(int _degree, double _coefficient){
//	degree = _degree;
//	coefficient = _coefficient;
//}
void Term::setValue(int _degree, double _coefficient) {
  coefficient = _coefficient;
  degree = _degree;
}
////// Polynomio
class Polynomio {
public:
  void polyAdd(Polynomio a, Polynomio b);
  void polyMinus(Polynomio a, Polynomio b);
  void polyProduct(Polynomio p, double co, int de);
  void Simplify();
  void write();
  void read();
  // Term *term = new Term[MAX_DEGREE * MAX_DEGREE];
  Term term[MAX_DEGREE * MAX_DEGREE];
  int totalDegree;
};
void Polynomio::polyProduct(Polynomio p, double co, int de) {
  totalDegree = p.totalDegree + de;
  for (int i = 0; i < totalDegree; i++) {
    term[i + de].setValue(p.term[i].degree + de, p.term[i].coefficient * co);
  }
  Simplify();
}
void Polynomio::polyAdd(Polynomio a, Polynomio b) {
  totalDegree = a.totalDegree >= b.totalDegree ? a.totalDegree : b.totalDegree;
  for (int i = 0; i <= totalDegree; i++) {
    term[i].setValue(i, a.term[i].coefficient + b.term[i].coefficient);
  }
  Simplify();
}
void Polynomio::polyMinus(Polynomio a, Polynomio b) {
  totalDegree = a.totalDegree >= b.totalDegree ? a.totalDegree : b.totalDegree;
  for (int i = 0; i <= totalDegree; i++) {
    term[i].setValue(i, b.term[i].coefficient - a.term[i].coefficient);
  }
  Simplify();
}
//读入的数据中Terms[0]为最**低**次项，往后递增。打印的时候逆序打印。
void Polynomio::Simplify() {
  for (int i = totalDegree; i > 0; i--) {
    if (term[i].coefficient != 0)
      break;
    else
      totalDegree--;
  }
}
void Polynomio::write() {
  cout << "请输入指数最高项的指数：" << endl;
  int coMax;
  cin >> coMax;
  while (coMax <= 0 || cin.fail()) {
    cout << "请输入一个正整数。" << endl;
    stdclean();
    cin >> coMax;
  }
  totalDegree = coMax;
  cout << "接下来请按照降幂顺序，依次输入 x^" << coMax
       << " 到 x^0 (常数项)的系数，空格分隔：" << endl;
  for (int i = 0; i <= coMax; i++) {
    double temp;
    cin >> temp;
    term[coMax - i].setValue(coMax - i, temp);
  }
  Simplify();
}
void Polynomio::read() {
  for (int i = totalDegree; i >= 0; i--) {
    if (term[i].coefficient == 0)
      ;
    else if (term[i].degree == 0) {
      if (term[i].coefficient >= 0) {
        printf("+ %.*f ", PRECISE, term[i].coefficient);
      } else {
        printf("- %.*f ", PRECISE, -term[i].coefficient);
      }
    } else if (i == totalDegree) {
      printf("%*fx^%d ", PRECISE, term[i].coefficient, term[i].degree);
    } else {
      if (term[i].coefficient >= 0) {
        printf("+ %*fx^%d ", PRECISE, term[i].coefficient, term[i].degree);
      } else {
        printf("- %*fx^%d ", PRECISE, -term[i].coefficient, term[i].degree);
      }
    }
  }
  cout << endl;
}
////// NODE & STACK
struct nodePoly {
  Polynomio entry;
  nodePoly *next;
  nodePoly();
  nodePoly(Polynomio ety, nodePoly *nxt = NULL);
};
nodePoly::nodePoly() { next = NULL; }
nodePoly::nodePoly(Polynomio ety, nodePoly *nxt) {
  entry = ety;
  next = nxt;
}

class StackNode {
public:
  int push(Polynomio intro) {
    nodePoly *p = topnode;
    nodePoly *newPoly = new nodePoly(intro);
    topnode = newPoly;
    topnode->next = p;
    return 0;
  }
  int pop() {
    topnode = topnode->next;
    return 0;
  }
  void top(Polynomio &dstPoly) { dstPoly = topnode->entry; }
  void clear() { topnode = NULL; }
  int size() {
    int temp;
    nodePoly *p = topnode;
    for (temp = 0; p != NULL; temp++) {
      p = p->next;
    }
    return temp;
  }
  StackNode();

private:
  nodePoly *topnode;
};
StackNode::StackNode() { topnode = NULL; }

////// Core Functions
void stdclean() {
  while (cin.get() != '\n')
    continue;
  cin.clear();
  cin.sync();
}
int DoCommand(char command, StackNode &storedPolynomio) {
  Polynomio p, q, r;
  double a;
  int b;
  switch (command) {
  case '?':
    p.write();
    cout << "已记录多项式：";
    p.read();
    storedPolynomio.push(p);
    stdclean();
    break;
  case '=':
    if (storedPolynomio.size() != 0) {
      storedPolynomio.top(q);
      cout << "当前栈顶多项式：";
      q.read();
    } else {
      cout << "未记录任何多项式。" << endl;
    }
    break;
  case 'c':
    storedPolynomio.clear();
    cout << "已清空所有记录的多项式。" << endl;
    break;
  case 's':
    if (storedPolynomio.size() == 0)
      cout << "未记录任何多项式。" << endl;
    else
      printf("当前已记录了 %d 个多项式。\n", storedPolynomio.size());
    break;
  case '+':
    if (storedPolynomio.size() < 2) {
      cout << "当前记录的多项式个数少于 2 个，无法运算。" << endl;
    } else {
      storedPolynomio.top(p);
      storedPolynomio.pop();
      storedPolynomio.top(q);
      storedPolynomio.pop();
      r.polyAdd(p, q);
      storedPolynomio.push(r);
      cout << "计算完成。";
    }
    break;
  case '-':
    if (storedPolynomio.size() < 2) {
      cout << "当前记录的多项式个数少于 2 个，无法运算。" << endl;
    } else {
      storedPolynomio.top(p);
      storedPolynomio.pop();
      storedPolynomio.top(q);
      storedPolynomio.pop();
      r.polyMinus(p, q);
      storedPolynomio.push(r);
      cout << "计算完成。" << endl;
    }
    break;
  case '*':
    if (storedPolynomio.size() == 0) {
      cout << "当前未记录任何多项式，无法运算。" << endl;
    } else {
      cout << "请输入你要乘上的多项式的系数和指数：" << endl;
      cin >> a >> b;
      while (cin.fail()) {
        cout << "输入无效，请重试" << endl;
        stdclean();
        cin >> a >> b;
      }
      storedPolynomio.top(p);
      storedPolynomio.pop();
      q.polyProduct(p, a, b);
      storedPolynomio.push(q);
      cout << "计算完成。" << endl;
    }
    stdclean();
    break;
  case 'h':
    instruct();
    break;
  case 'x':
    cout << "输入无效，请重试。" << endl;
    break;
  case 'q':
    return -1;
  }
  return 0;
}
char GetCommand() {
  cout << "输入指令 >> ";
  char validInput[] = "?=+-*csqh";
  char ch;
  cin.get(ch);
  stdclean();
  ch = tolower(ch);
  if (strchr(validInput, ch) == NULL) {
    return 'x';
  }
  return ch;
}

void instruct() {
  cout << "欢迎来到逆波兰多项式计算器，以下是操作指引：" << endl
       << "[?] 输入一个新的多项式" << endl
       << "[=] 查看栈顶的多项式" << endl
       << "[+] [-] [*] 进行多项式的运算" << endl
       << "[c] 清空所有多项式" << endl
       << "[s] 查看当前已记录的多项式数量" << endl
       << "[h] 查看帮助" << endl
       << "[q] 退出" << endl;
}

////// main Function
int main() {
  StackNode storedPolynomio;
  instruct();
  while (DoCommand(GetCommand(), storedPolynomio) != -1)
    continue;
  cout << "Bye!" << endl;
  return 0;
}
