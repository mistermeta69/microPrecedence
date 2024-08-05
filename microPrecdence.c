/*
Precedence function implemented by precdl,2
See Aho and Ullman Dragon book.
Right associative.

 \ r |OR|XOR|XNOR|AND|NOT|LPAR|RPAR|EQ|ID|DONE|ASN|ST|
 l \ _________________________________________________
OR   |< | > | <  | < | < | <  | >  |  |  | >  |   |  |    5
XOR  |< | > | <  | < | < | <  | >  |  |  | >  |   |  |    5
XNOR |< | > | <  | < | < | <  | >  |  |  | >  |   |  |    5
AND  |> | > | >  | > | < | <  | >  |  |  | >  |   |  |    9
NOT  |> | > | >  | > |   | <  | >  |  |  | >  |   |  |    9
LPAR |< | < | <  | < | < | <  | =  |  |  | >  |   |  |    3
RPAR |> | > | >  | > | < | =  | >  |  |  | >  |   |  |    12
EQ   |  |   |    |   |   |    |    |  |  |    |   |  |    2
ID   |  |   |    |   |   |    |    |  |  |    |   |  |    2
DONE |  |   |    |   |   |    |    |  |  |    |   |< |    0
ASN  |  |   |    |   |   |    |    |  |  |    |   |  |    2
ST   |< | < |    | < | < | <  |    |  |< | >  |   |  |    2
     -------------------------------------------------
      6   4   6    8  13   12   3   2  2   0    2  2
*/

static int prvl[] = {5, 5, 5, 9, 9, 3, 12, 2, 2, 0, 2, 2};
static int prvr[] = {6, 4, 6, 8, 13, 12, 3, 2, 2, 0, 2, 2};

#define precdl(v) prvl[v - ATOM_BASE]
#define precdr(v) prvr[v - ATOM_BASE]

calc(char *inpstream, int time)
    /*
    This is a primitive precedence parser
    the precedence is given by precdl,precdr
    and we have an operator and an operand stack
    both stack pointers point to last value pushed
    INPUT: is   = ptr to stream of tokens
           time = time of evaluation in input pin queues
    */
{
  char *is = inpstream;     /*use a global for speed*/
  char *ops = op_stack - 1; /*clear stacks*/
  char *vals = val_stack - 1;

  *(++ops) = START; /*init the operator stack*/
  do
  {
    if (*is < ATOM_BASE) /*not an operator,must be an id*/
    {
      *(++vals) /*push*/
          = palptr->prodcode[*is - 1] & BREG ? pin[*is++]->d[time] : pin[*is++]->q[time];
      if (*vals == VEDGE)
        *vals = VLOW;
    }
    else                              /* *is must be an operator */
      if (precdl(*ops) < precdr(*is)) /*shift ?*/
        *(++ops) = *is++;
      else /*reduce*/
      {
        if (*ops == NOT)
          *vals = eval(*ops--, *vals, *vals); /*unary?*/
        else if (precdl(*ops) == precdr(*is)) /* (val) */
        {
          ops--;
          *is++;
        }
        else /*binary*/
        {
          *(vals - 1) = eval(*ops--, *vals, *(vals - 1));
          vals--;
        }
      }
  } while ((vals != val_stack) || (*is != DONE) || (*ops != START));
  return *vals;
}
