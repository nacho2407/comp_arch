# LISP Operation AST

flex로 제작한 어휘 분석기 `yylex()`와 Bison으로 제작한 LR 구문 분석기 `yyparse()`를 이용하여 LISP 스타일 연산식의 추상 구문 트리를 출력하는 코드입니다.

코드에서 사용된 문법의 EBNF는 아래와 같습니다.

\-

This is the code to output an Abstract Syntax Tree of a LISP-style arithmetic expression using the lexical analyzer `yylex()` written in flex and the LR parser `yyparse()` written in Bison.

The EBNF of the grammars used in the code is shown below.

```EBNF
<expression> ::= '(' <operation> ')'
               | '(' <abs> ')'
               | '(' <setq> ')'
               | '(' <print> ')'
               | <null>
               ;

<operation> ::= <operator> <operation_term> ;

<operator> ::= '+' | '-' | '*' | '/' ;

<operation_term> ::= <operation_term> <iliteral>
                   | <operation_term> <synonym>
                   | <operation_term> <expression>
                   | <iliteral>
                   | <synonym>
                   | <expression>
                   ;

<iliteral> ::= [ '+' | '-' ] <digit> { <digit> } ;
<digit> ::= '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' ;

<synonym> ::= <non_digit> { <non_digit> | <digit> } ;
<non_digit> ::= '_' | <alphabet> ;
<alphabet> ::= 'a' | ... | 'z' | 'A' | ... | 'Z' ;

<abs> ::= <func_abs> <abs_term> ;
<func_abs> ::= "abs" ;
<abs_term> ::= <iliteral> | <synonym> | <expression> ;

<setq> ::= <func_setq> <synonym> <setq_term> ;
<func_setq> ::= "setq" ;
<setq_term> ::= <iliteral> | <synonym> | <expression> ;

<print> ::= <func_print> <print_term> ;
<func_print> ::= "print" ;
<print_term> ::= <iliteral> | <synonym> | <expression> ;

<null> ::= '(' ')' ;

```

---

이 코드를 실행하기 위해서는 flex와 Bison이 필요합니다.

flex 및 Bison이 설치되어 있지 않은 경우, 아래와 같이 설치합니다.

\-

You will need flex and Bison to run this code.

If you do not have flex and Bison installed, install them as shown below.

```Bash
$ sudo apt update
$ sudo apt install flex
$ sudo apt install bison

```

---

아래와 같이 빌드하고 실행합니다.

\-

Build and run as shown below.

```Bash
$ make
$ ./main

```
