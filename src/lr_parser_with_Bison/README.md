# LR Parser with Bison

flex를 이용하여 제작한 어휘 분석기 `yylex()`와 Bison을 이용하여 제작한 LR 구문 분석기 `yyparse()`를 이용하여 문자열의 우파스를 출력하는 코드입니다.

코드에서 사용된 문법의 EBNF는 아래와 같습니다.

리스트 문법은 LISP의 형태를 참고하였습니다.

\-

This code outputs the right parse of a string using the lexical analyzer `yylex()` written in flex and the LR parser `yyparse()` written in Bison.

The EBNF of the grammars used in the code is shown below.

The list syntax is modeled after LISP.

```EBNF
<expression> ::= <iliteral>
               | <synonym>
               | <list>
               | <string>
               | <operation>
               ;

<iliteral> ::= [ '+' | '-' ] <digit> { <digit> } ;
<digit> ::= '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' ;

<synonym> ::= <alphabet> { <alphabet> | <digit> } ;
<alphabet> ::= 'a' | ... | 'z' | 'A' | ... | 'Z' ;

<list> ::= '(' <nullable_expression> ')' ;
<nullable_expression> ::= <expression> <nullable_expression>
                        | ε
                        ;

<string> ::= '"' { <character> } '"' ;
<character> ::= (any valid ASCII) ;

<operation> ::= <operator> <iliteral> <iliteral> ;
<operator> ::= '+' | '-' | '/' | '*' ;
```

---

이 코드를 실행하기 위해서는 flex와 Bison이 필요합니다.

flex 및 Bison이 설치되어 있지 않은 경우, 아래와 같이 설치합니다.

\-

You will need flex and Bison to run this code.

If you do not have flex and Bison installed, install them as shown below.

```shell
$ sudo apt update
$ sudo apt install flex
$ sudo apt install bison
```

---

아래와 같이 빌드하고 실행합니다.

\-

Build and run as shown below.

```shell
$ make
$ ./main
```
