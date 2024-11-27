# Recursive Descent Parser with flex

flex로 제작한 어휘 분석기 `yylex()`를 이용하는 순환 하강 구문 분석기 `yyparse()` 코드입니다.

코드에서 사용된 문법의 EBNF는 아래와 같습니다.

리스트 문법은 LISP의 형태를 참고하였습니다.

\-

This is the code for a recursive descent parser `yyparse()`, where `yylex()` built using flex.

The EBNF of the grammars used in the code is shown below.

The list syntax is modeled after LISP.

```EBNF
<token> ::= <iliteral>
          | <synonym>
          | <list_begin>
          | <list_end>
          | <whitespace>
          | <comment>
          | <string>
          | <operator>
          ;

<iliteral> ::= [ '+' | '-' ] <digit> { <digit> } ;
<digit> ::= '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' ;

<synonym> ::= <alphabet> { <alphabet> | <digit> } ;
<alphabet> ::= 'a' | ... | 'z' | 'A' | ... | 'Z' ;

<list_begin> ::= '(' ;
<list_end> ::= ')' ;

<whitespace> ::= ' ' | '\t' | '\n' ;

<comment> ::= ';' { <character> } '\n' ;

<character> ::= (any valid ASCII) ;

<string> ::= '"' { <character> } '"' ;

<operator> ::= '+' | '-' | '/' | '*' ;

```

---

이 코드를 실행하기 위해서는 flex가 필요합니다.

flex가 설치되어 있지 않은 경우, 아래와 같이 설치합니다.

\-

You will need flex to run this code.

If you don't have flex installed, install it as shown below.

```Bash
$ sudo apt update
$ sudo apt install flex

```

---

아래와 같이 빌드하고 실행합니다.

\-

Build and run as shown below.

```Bash
$ make
$ ./main

```
