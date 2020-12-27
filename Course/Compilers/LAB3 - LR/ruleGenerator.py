rules = """program -> compoundstmt
stmt ->  ifstmt
stmt -> whilestmt
stmt -> assgstmt
stmt -> compoundstmt
compoundstmt ->  { stmts }
stmts ->  stmt stmts
stmts -> E
ifstmt ->  if ( boolexpr ) then stmt else stmt
whilestmt ->  while ( boolexpr ) stmt
assgstmt ->  ID = arithexpr ;
boolexpr  ->  arithexpr boolop arithexpr
boolop ->  <
boolop -> >
boolop -> <=
boolop -> >=
boolop -> ==
arithexpr  ->  multexpr arithexprprime
arithexprprime ->  + multexpr arithexprprime 
arithexprprime -> - multexpr arithexprprime
arithexprprime -> E
multexpr ->  simpleexpr  multexprprime
multexprprime ->  * simpleexpr multexprprime
multexprprime -> / simpleexpr multexprprime 
multexprprime -> E
simpleexpr ->  ID
simpleexpr ->  NUM
simpleexpr ->  ( arithexpr )"""

ruleList = rules.split("\n")
for one in ruleList:
    l = one.split("->")
    print('{"' + l[0] + '", "' + l[1] + '"},')
