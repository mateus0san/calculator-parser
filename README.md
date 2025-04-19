# C Calculator Parser
A recursive descent parser for a calculator, simple and bad

compiling -> `gcc main.c`

Input examples: 
```
(2+2)*2+1
5*5+(12-12)
8/4/2
```
Output:
```
9
25
4
```

8/4/2 -> 8/2 -> 4
