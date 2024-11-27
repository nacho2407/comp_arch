# LISP Operation with Bison

flex로 제작한 어휘 분석기 `yylex()`와 Bison으로 제작한 LR 구문 분석기 `yyparse()`를 이용하여 구현한 LISP 스타일 연산식 계산기 코드입니다.

코드에서 사용된 문법의 EBNF는 아래와 같습니다.

\-

This is the code for a LISP-style arithmetic calculator implemented using the lexical analyzer `yylex()` written in flex and the LR parser `yyparse()` written in Bison.

The EBNF of the grammars used in the code is shown below.

```EBNF
<expression> ::= '(' <plus> ')'
               | '(' <minus> ')'
               | '(' <multi> ')'
               | '(' <divide> ')'
               | '(' <modulo> ')'
               | '(' <abs> ')'
               | <null>
               ;

<plus> ::= '+' <plus_term> ;

<plus_term> ::= <plus_term> <iliteral>
              | <plus_term> <expression>
              | <iliteral>
              | <expression>
              ;

<minus> ::= '-' <minus_term> ;

<minus_term> ::= <minus_term> <iliteral>
               | <minus_term> <expression>
               | <iliteral>
               | <expression>
               ;

<multi> ::= '*' <multi_term> ;

<multi_term> ::= <multi_term> <iliteral>
               | <multi_term> <expression>
               | <iliteral>
               | <expression>
               ;

<divide> ::= '/' <divide_term> ;

<divide_term> ::= <divide_term> <iliteral>
                | <divide_term> <expression>
                | <iliteral>
                | <expression>
                ;

<modulo> ::= '%' <modulo_term> ;

<modulo_term> ::= <modulo_term> <iliteral>
                | <modulo_term> <expression>
                | <iliteral>
                | <expression>
                ;

<abs> ::= <op_abs> <abs_term> ;

<abs_term> ::= <iliteral>
             | <expression>
             ;

<iliteral> ::= [ '+' | '-' ] <digit> { <digit> } ;
<digit> ::= '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' ;

<op_abs> ::= "Abs" ;
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
