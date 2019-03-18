// ********** Specification of struct Node **********
typedef struct Node
{
    int value;
    struct Node *next;
} NODE;
/*/////////////////////////////////////////////////////*/
NODE *FindLastNthNode(NODE *h, int n)
/* PreCondition:
h is a head pointer of a linked-list, n is an integer
PostCondition:
return the pointer of the last nth node in the linked-list,
or 0 if such node can’t be found
*/
{ //TODO: your definition
    NODE *p = h;
    int totalLen = 0;
    while (p->next != NULL){
        
    }
}
/*/////////////////////////////////////////////////////*/
/***************************************************************/
/*                                                             */
/*  DON'T MODIFY following code anyway!                        */
/*                                                             */
/***************************************************************/
#include <stdio.h>
#include <malloc.h>
static unsigned long next = 1;
int RND()
{
    next = next * 1103515245 + 12345;
    return (unsigned)(next / 65536) % 32768;
}
void SETSEED(unsigned seed) { next = seed; }
void solve()
{
    int i, s, n, m, t;
    NODE *head = 0, *p, *tail;
    scanf("%d%d%d%d", &s, &t, &m, &n);
    SETSEED(s);
    for (i = 0; i < t; i++)
    {
        p = (NODE *)malloc(sizeof(NODE));
        p->value = RND() % m;
        p->next = 0;
        if (head == 0)
            head = p;
        else
            tail->next = p;
        tail = p;
    }
    if (p = FindLastNthNode(head, n))
        printf("%d:", p->value);
    else
        printf("NONE:");
    n = 0;
    while (head)
    {
        p = head;
        head = head->next;
        if (t < 100 || t > 100 && n < 100)
        {
            printf("%d", p->value);
              if (head) printf(" ");
        }
        n++;
        free(p);
    }
    printf("\\n");
}
int main()
{
      int i, t;
      scanf("%d\\n", &t);
    for (i = 0; i < t; i++)
    {
        printf("case #%d:\\n", i);
        solve();
    }
    return 0;
}
