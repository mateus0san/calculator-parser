#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXNUMBER 100

char number[MAXNUMBER];
char operator;

double sumSub(void);
double multDiv(void);
int getoperator(void);
int getnumber(void);
int gettoken(void);

int main(void) {
  double result;

  while (gettoken()) {
    result = sumSub();
    printf("%lf\n", result);
  }
  return 0;
}

int getch(void);
void ungetch(int);

int gettoken(void) {
  double result;
  int c;

  while ((c = getch()) == ' ' || c == '\t')
    ;
  if (c == '(') {
    if (gettoken()) {
      result = sumSub();
      if (operator!= ')')
        return 0;
      snprintf(number, sizeof(number), "%lf", result);
      return 1;
    } else
      return 0;
  } else if (isdigit(c) || c == '+' || c == '-') {
    ungetch(c);
    return getnumber();
  }
  return 0;
}

int getnumber(void) {
  int i, c;

  while ((c = getch()) == ' ' || c == '\t')
    ;
  i = 0;
  if (!isdigit(c) && c != '-' && c != '+') {
    ungetch(c);
    return 0; /* not a number */
  }
  number[i++] = c;
  while (isdigit(c = getch()) && i < MAXNUMBER - 1)
    number[i++] = c;
  if (c == '.' && i < MAXNUMBER - 1) {
    number[i++] = c;
    while (isdigit(c = getch()) && i < MAXNUMBER - 1)
      number[i++] = c;
  }
  if (c != EOF)
    ungetch(c);
  number[i] = '\0';
  return 1; /* is a number */
}

int getoperator(void) {
  int c;

  while ((c = getch()) == ' ' || c == '\t')
    ;
  operator= c;
  if (c == '+' || c == '-' || c == '*' || c == '/') {
    return 1; /* is a operator */
  }
  return 0; /* is not a operator */
}

#define BUFSIZE 100
int buf[BUFSIZE];
int bufp;

int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }
void ungetch(int c) {
  if (bufp < BUFSIZE)
    buf[bufp++] = c;
  else
    printf("ungetch: too many characters\n");
}

double multDiv(void) {
  double num1;
  int op;

  num1 = atof(number);
  if (getoperator()) {
    op = operator;
    if (op == '*' || op == '/')
      if (gettoken()) {
        double num2 = multDiv();
        if (op == '*')
          return num1 * num2;
        else if (num2 != 0)
          return num1 / num2;
      }
  }
  return num1;
}

double sumSub(void) {
  double num1;
  int op;

  num1 = multDiv();
  op = operator;
  if (op == '-' || op == '+')
    if (gettoken()) {
      double num2 = sumSub();
      return (op == '+') ? num1 + num2 : num1 - num2;
    }
  return num1;
}
