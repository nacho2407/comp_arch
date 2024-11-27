# Recursive Descent Parser

어휘 분석기 `yylex()`가 단순히 표준 입력에서 한 문자를 읽는 순환 하강 구문 분석기 `yyparse()`의 코드입니다.

코드에서 사용된 문법의 EBNF는 아래와 같습니다.

리스트 문법은 LISP의 형태를 참고하였습니다.

\-

This is the code for a recursive descent parser `yyparse()`, where lexical analyzer `yylex()` simply reads a single character from standard input.
 
The EBNF of the grammars used in the code is shown below.

The list syntax is modeled after LISP.

```EBNF
<token> ::= { <whitespace> } ( <integer> | <synonym> | <list> | <nil> ) ;

<whitespace> ::= ' ' | '\t' | '\n' ;

<integer> ::= '0' | <non_zero> { <digit> } ;
<non_zero> ::= '1' | '2' | '3'
             | '4' | '5' | '6'
             | '7' | '8' | '9'
             ;
<digit> ::= <non_zero> | '0' ;

<synonym> ::= <non_digit> { <non_digit> | <digit> } ;
<non_digit> ::= <alphabet> | '_' ;
<alphabet> ::= ... ;

<list_begin> ::= '(' ;
<list_end> ::= ')' ;

<nil> ::= <list_begin> { <whitespace> } <list_end> ;
```

---

아래와 같이 빌드하고 실행합니다.

\-

Build and run as shown below.

```Bash
$ make
$ ./main
```
