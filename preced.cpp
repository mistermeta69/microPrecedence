// precedence parser - shift reduce, taken from simpal code
// April 1995 - rev 0
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#define DONE 8
#define START 7
#define RPAR 6

int gettoken(unsigned &val)
// gets next character in the input stream and translates it
// to an integer atom, value of token is returned in val if it is a number
{
char c;
static int token=-1;
if (token==DONE)
	return token;
do
{
	token =-1;
	putch(c=getch());
	if (isdigit(c))
		{
		val=(c-'0');
		token=0;			//identifier
		}
	else
		{
		val = (unsigned) c;
		switch(c)
			{
			case '+': token=1; break;
			case '-': token=2; break;
			case '*': token=3; break;
			case '/': token=4; break;
			case '(': token=5; break;
			case ')': token=RPAR; break;
			case '\r':
			case '\n':token=DONE; break;
			}
		}
} while (token < 0);
return token;
}
//
//simple evaluator for 4 basic arith operators
//
int eval(unsigned op,int p1,int p2)
{
unsigned r;
switch(op)
 {
 case 1:
	r= p1 + p2;   break;
 case 2:
	r= p1 - p2;   break;
 case 3:
	r= p1 * p2;   break;
 case 4:
	r= p1 / p2;   break;
 default: printf("\error in eval\n");
 }
return r;
}


// operator stack functions

int opstk[81]={START};
int oi=0;
int topop() { return opstk[oi];}
int popop() { return opstk[oi--];}
void pushop(int c) {opstk[++oi]=c;}

// operand (number) stack functions

int numstk[81];
int ni=-1;
int topnum() { return numstk[ni];}
int popnum() { return numstk[ni--];}
void pushnum(int val) {numstk[++ni]=val;}

/*
Precedence function implemented by prstk,prinp
If prinp > prstk then shift, if equal discard both, else reduce (eval stack)

 \inp|+ | - | * | / | ( | ) |START|DONE
stk \ ________________________________ 		(stk)
+    |> | > | > | > | > | < | <   | <		5
-    |> | > | > | > | > | < | <   | <		5
*    |< | < | < | < | > | < | <   | <		9
/    |< | < | < | < | > | < | <   | < 		9
(    |> | > | > | > | > | = | <   | <		3
)    |< | < | < | < | > | < | <   | <		12
START|> | > | > | > | > | > | =   | >		0
DONE |> | > | > | > | > | = | <   | =		3
	---------------------------------
(inp) 6   6   8   8  12   3    0    3

if inp > stk then shift, else reduce
*/
int prstk[]={0,5,5,9,9,3,12,0,3};
int prinp[]={0,6,6,8,8,12,3,0,3};


int calc()
/*
This is a primitive precedence parser
the precedence is given by prstk,prinp
and we have an operator and an operand stack
both stack pointers point to last value pushed
INPUT: gettoken   = returns token codes (see above)
*/
{
char c;
unsigned val;
do
	 {
	 c=gettoken(val);
	 if (c==0)   					//is a number
		pushnum(val);
	 else
	 if (prstk[topop()] < prinp[c])    // shift
		pushop(c);
	 else
	 if (prstk[topop()] == prinp[c])	 // (paren)
		popop();   	 	 		 // match with input, ignore input
	 else
		{
		pushnum(eval(popop(),popnum(),popnum()));
		if (c!=RPAR)
			pushop(c);
		}
	 }
while (c!=DONE || topop() != START);
return topnum() ;
}


int main()
{
	//clrscr();
	printf("\n%i\n", calc());
	getch();
	return 0;
}