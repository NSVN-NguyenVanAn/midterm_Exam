#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#define ADD 1
#define SUB 2
#define MUL 3
#define DIV 4


typedef struct _STACK_ITEM
{
	int d;
	struct _STACK_ITEM* link;
}STACK_ITEM;

STACK_ITEM* pTH = NULL;
STACK_ITEM* pTT = NULL;

int isEmpty(STACK_ITEM* pStack)
{
	return pStack == NULL ? 1 : 0;
}
int isFull(STACK_ITEM* pStack)
{
	return 0;
}
STACK_ITEM* Push(STACK_ITEM* pStack, int value)
{
	STACK_ITEM* newItem = (STACK_ITEM*)calloc(1, sizeof(STACK_ITEM));
	newItem->d = value;
	newItem->link = pStack;
	return newItem;
}
int Peek(STACK_ITEM* pStack)
{
	if (isEmpty(pStack))
	{
		return -1;
	}else
		return pStack->d;
}
STACK_ITEM* Pop(STACK_ITEM** ppStack)
{
	STACK_ITEM* pStack = *ppStack;
	
	if (isEmpty(pStack))
		return NULL;
	else
	{
		STACK_ITEM* oldTop = pStack;
		STACK_ITEM* popItem = (STACK_ITEM*)calloc(1, sizeof(STACK_ITEM));
		popItem->d = oldTop->d;
		*ppStack = pStack->link;
		free(oldTop);
		return popItem;
	}
}
void Initialize(STACK_ITEM* pStack)
{
	while (pStack != NULL)
	{
		STACK_ITEM* next = pStack->link;
		free(pStack);
		pStack = next;
	}
	pStack = NULL;
}

void MakeStack(char* op, STACK_ITEM** pStack)
{
	for (int i = 0;i < strlen(op);i++)
	{
		*pStack = Push(*pStack, op[i] - 48);
	}
}

int Priority(int operand)
{
	switch (operand)
	{
		case ADD:
		case SUB:
			return 0;
		case MUL:
			return 2;
		default:
			return 1;
	}
}
int CharToOP(char op)
{
	switch (op)
	{
		case '+':
			return ADD;
		case '-':
			return SUB;
		case '*':
			return MUL;
		default:
			return DIV;
	}
}
void Calc(STACK_ITEM** ppTT, STACK_ITEM** ppTH)
{
	STACK_ITEM* item = Pop(ppTT);
	STACK_ITEM* op1 = Pop(ppTH);
	STACK_ITEM* op2 = Pop(ppTH);
	int result = 0;
	switch (item->d)
	{
		case ADD:
			result = op1->d + op2->d;
		break;
		case SUB:
			result = op2->d - op1->d;
		break;
		case MUL:
			result = op1->d * op2->d;
		break;
		default:
			result = op2->d / op1->d;
		break;
	}
	pTH = Push(*ppTH, result);
	free(item);
	free(op1);
	free(op2);
}

int main()
{
	char bt[8192];
	Initialize(pTH);
	Initialize(pTT);
	printf("Nhap bieu thuc: ");
	fflush(stdin);
	scanf("%s", bt);
	for (int i = 0;i < strlen(bt);i++)
	{
		if (isdigit(bt[i]))
		{
			pTH = Push(pTH, bt[i] - 48);
		}else{
			int d = Peek(pTT);
			if (d >= 0 && Priority(d) > Priority(CharToOP(bt[i])))
			{
				do
				{
					Calc(&pTT, &pTH);
					d = Peek(pTT);
				}while (d >=0 && Priority(d) > Priority(CharToOP(bt[i])));
			}
			pTT = Push(pTT, CharToOP(bt[i]));
		}
	}
	
	while (!isEmpty(pTT))
	{
		Calc(&pTT, &pTH);
	}
	
	STACK_ITEM* result = Pop(&pTH);
	printf("%d",result->d);
	free(result);
	getch();
}