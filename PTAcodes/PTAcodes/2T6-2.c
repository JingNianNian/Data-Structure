#include <stdio.h>
#include <stdlib.h>
typedef char ElementType;

typedef struct Node* PtrToNode;
struct Node {
    ElementType Data; /* 存储结点数据 */
    PtrToNode   Next; /* 指向下一个结点的指针 */
};
typedef PtrToNode List; /* 定义单链表类型 */

void ReadInput(List L1, List L2); /* 裁判实现，细节不表 */
void PrintSublist(PtrToNode StartP); /* 裁判实现，细节不表 */
PtrToNode Suffix(List L1, List L2);

int main()
{
    List L1, L2;
    PtrToNode P;

    L1 = (List)malloc(sizeof(struct Node));
    L2 = (List)malloc(sizeof(struct Node));
    L1->Next = L2->Next = NULL;
    ReadInput(L1, L2);
    P = Suffix(L1, L2);
    PrintSublist(P);

    return 0;
}

PtrToNode Suffix(List L1, List L2) {
    PtrToNode p1 = L1;
    PtrToNode p2 = L2;

    int lenc = 0;
    while (p1->Next != NULL)
    {
        lenc++;
        p1 = p1->Next;
    }
    while (p2->Next != NULL)
    {
        lenc--;
        p2 = p2->Next;
    }

    if (p1 != p2) {
        return NULL;
    }

    PtrToNode cur = lenc > 0 ? L1 : L2;
    p2 = cur == L1 ? L2 : L1;
    lenc = abs(lenc);

    while (lenc--)
    {
        cur = cur->Next;
    }

    while (cur != p2)
    {
        cur = cur->Next;
        p2 = p2->Next;
    }
    return cur;
}

