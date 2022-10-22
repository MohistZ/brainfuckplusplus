# BRAINF*CKPLUSPLUS
A new version of brainFuck.
The following functions have been added to it:
- somes pointers and related symbols
- more flow control statements
- function features
- more symbols make it fun

I was just starting to learn programming, so I hope to receive your criticism and suggestions.
## The original Brainfuck Symbols
```
>      becomes      ++p;
<      becomes      --p;
+      becomes      ++*p;
-      becomes      --*p;
.      becomes      putchar(*p);
,      becomes      *p = getchar();
[      becomes      while (*p) {
]      becomes      }
```
## New Symbols
[0-9]means any number from 0 to 9
[char]means any character following,including '\n'
```
>[1-9]      becomes          p+=[1-9];
>0          becomes          p+=10;
>@[0-9]     becomes          p+=*ptr[[0-9]];
symbols < + _ have the same behavior
:           becomes          printf("%d", int(*p));
=[char]     becomes          *p='[char]';
"[string]"  becomes          *p=string[0];*(p+1)=string[1];......
the pointer p will point at the next cell after the string
@[0-9]      becomes          *p=*ptr[[0-9]];
&[0-9]      becomes          *ptr[[0-9]]=*p;
*[0-9]      becomes          temp= *ptr[[0-9]];*ptr[[0-9]]=*p;*p=temp;
^           becomes          t_p=p;
v           becomes          p=t_p;
^[0-9]      becomes          ptr[[0-9]]=p;
v[0-9]      becomes          p=ptr[[0-9]];
!           becomes          p=0; (0 means the middle of the array)
/           becomes          *p=0;
(           becomes          if(*p==0){
(@[0-9]     becomes          if(*p==*ptr[[0-9]]){
)           becomes          } (can't mix with ']')
?           becomes          if(*p==0){/*next symbol*/}
?@[0-9]     becomes          if(*p==*ptr[[0-9]]){/*next symbol*/}
$[a-z]      becomes          goto [a-z];
#[a-z]      becomes          label: [a-z];
|           becomes          return 0;
|@[0-9]     becomes          return *ptr[[0-9]];('|' will end the script and return the value)
%           becomes          //
_           becomes          system("clear");
```
## Function
you can define a function with a name [A-Z] any where in your file like following:
```
B{*2.*2}
```
and use them in your script like following:
```
= *2=~+2*1+[:B+?@1|]
```
the script will print numbers from 1 to 127 with ' ' following
## Hello World!
With these new symbols,you can write a script to print Hello World! more easier:
```
"Hello World!"![.>]
```
compared with:
```
++++++++[>++++[>++>+++>+++>+>+<<<<<-]>+>+>->+[<]<-]>>.>---.+++++++..+++.>>++++.>.<<-.<.+++.------.--------.>>>+.
```