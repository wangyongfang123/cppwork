#include <stdio.h>
#include<cstdlib>
#include<cstring>
#include<cstdio>

typedef struct _Node
{
	char name[256];
	int acctNum;
	char lastName[15];
	char firstName[10];
	double balance;
	struct _Node* next;
}Node, *NodePtr;

bool isEmpty(NodePtr list);
int insertData(NodePtr *ppNode, const char* name, const char* firstName, const char* lastName, int  acctNum, double balance);
int deleteData(NodePtr *ppNode, const char* data);
Node* UpData(NodePtr fptr);
NodePtr findData(NodePtr *list, const char* name);
void printNodeInfo(const NodePtr pNode);
void textFile(NodePtr header);
void processList(NodePtr list);
int enterChoice(void);

bool isEmpty(NodePtr list)
{
	return list == 0;
}

int insertData(NodePtr *ppNode, const char* name, const char* firstName, const char* lastName, int  acctNum, double balance)
{
	NodePtr pCurNode = *ppNode;
	NodePtr pNode = *ppNode;
	while (pNode != NULL)
	{
		if (pNode->acctNum == acctNum)
		{
			printf("this number already exist!\n");
			return -1;
		}
		pNode = pNode->next;
	}
	if (pCurNode == 0) //表为空的情况（插入节点位置为空）
	{
		*ppNode = (NodePtr)malloc(sizeof(Node));
		memset(*ppNode, 0, sizeof(Node));
		pCurNode = *ppNode;
	}
	else
	{

		Node* pNewNode = (Node*)malloc(sizeof(Node));
		memset(pNewNode, 0, sizeof(Node));
		pNewNode->next = pCurNode->next;
		pCurNode->next = pNewNode;
		pCurNode = pNewNode;
	}
	pCurNode->acctNum = acctNum;
	strcpy(pCurNode->name, name);
	strcpy(pCurNode->firstName, firstName);
	strcpy(pCurNode->lastName, lastName);
	pCurNode->balance = balance;
	return 0;
}

int deleteData(NodePtr *ppNode, const char* data)
{
	if (ppNode == 0 || *ppNode == 0)
	{
		return -1;
	}
	NodePtr pNode = *ppNode;
	NodePtr preNode = 0;
	while (pNode != 0)
	{
		if (strcmp(pNode->firstName, data) == 0)
		{
			if (preNode == 0)
			{
				*ppNode = (*ppNode)->next;
			}
			else
			{
				preNode->next = pNode->next;
			}
			free(pNode);
			return 0;
		}

		preNode = pNode;
		pNode = pNode->next;
	}
	printf("No information delete!\n");
	return 0;
}
Node* UpData(NodePtr fptr)
{
	int acctNum;
	char name;
	double transaction;
	NodePtr fpptr = fptr;
	printf("Enter account to update ( 1 - 100 ): ");
	scanf("%d", &acctNum);
	while (fpptr)
	{
		if (fpptr->acctNum == acctNum)
		{
			printf("%-6d%-16s%-11s%10.2f\n\n", fpptr->acctNum, fpptr->lastName, fpptr->firstName, fpptr->balance);
			printf("Enter charge ( + ) or payment ( - ): ");
			scanf("%lf", &transaction);
			fpptr->balance += transaction;
			fputs("acctNum,firstName,lastName,balance:\n", stdout);
			printf("%-6d%-16s%-11s%10.2f\n", fpptr->acctNum, fpptr->lastName, fpptr->firstName, fpptr->balance);
			return fpptr;
		}
		fpptr = fpptr->next;
	}

	if (fpptr->acctNum != acctNum)
	{
		printf("Acount #%d has no information.\n", acctNum);
		return 0;
	}
}

NodePtr findData(NodePtr *list, const char* name)
{
	if (list == 0 || *list == 0)
	{
		return 0;
	}
	NodePtr plist = *list;
	while (list != 0)
	{
		if (strcmp(plist->firstName, name) == 0)
		{
			return plist;
		}

		plist = plist->next;
	}

	return 0;
}

void printNodeInfo(const NodePtr pNode)
{
	if (pNode)
	{
		printf("find information:\n");
		printf("%d\t%s\t%s\t%f\n", pNode->acctNum, pNode->firstName, pNode->lastName, pNode->balance);
	}

}


void textFile(NodePtr header)//保存文本的作用
{
	FILE *writePtr;
	int num = 100;
	NodePtr temp = header;
	Node  client = { 0 };
	if ((writePtr = fopen("accounts.txt", "w")) == NULL)
		printf("File could not be opened.\n");
	else {
		rewind(writePtr);
		fprintf(writePtr, "%-6s%-6s%-16s%-11s%10s\n",
			"ID", "AcctNum", "Last Name", "First Name", "Balance");
		int i = 1;
		while (temp != NULL)
		{
			fprintf(writePtr, "%-6d%-6d%-16s%-11s%10.2f\n", i, temp->acctNum, temp->firstName, temp->lastName, temp->balance);
			i++;
			temp = temp->next;
		}
		fclose(writePtr);
	}

}


void processList(NodePtr list)
{
	//遍历单链表，输出数据
	Node* pNode = list;
	//int row = 1;
	while (pNode != 0)
	{
		printf("%d\t%s\t%s\t%f\n", pNode->acctNum, pNode->firstName, pNode->lastName, pNode->balance);
		pNode = pNode->next;
		//row++;
	}

	fputs("\n", stdout);
}



int enterChoice(void)
{
	int menuChoice;

	printf("\nEnter your choice\n"
		"1 - add a new account\n"
		"2 - delete an account\n"
		"3 - updata an account\n"
		"4 - print account info\n"
		"5 - write list contents\n"
		"6 - print list contents\n"
		"7 - end program\n? ");
	scanf("%d", &menuChoice);
	return menuChoice;
}

int main()
{
	NodePtr header = 0;
	Node* pCurNode = header;
	NodePtr pNode = 0;
	int acctNum = 1;
	char name[256];
	char lastName[15] = { 0 };
	char firstName[10] = { 0 };
	double balance = 1.0;
	Node information = { 0 };
	while (1)
	{
		int choice = enterChoice();
		switch (choice)
		{
		case 1:
		{
			fputs("input acctNum,name, firstName,lastName,balance:\n", stdout);
			memset(name, 0, 256);
			scanf("%d", &acctNum);
			scanf("%d", name);
			scanf("%s", firstName);
			scanf("%s", lastName);
			scanf("%lf", &balance);
			insertData(&header, name, firstName, lastName, acctNum, balance);
		}
		break;
		case 2:
		{
			fputs("input the name(delete):\n", stdout);
			memset(name, 0, 256);
			scanf("%s", name);
			deleteData(&header, name);

		}
		break;
		case 3:
		{
			UpData(header);
		}
		break;
		case 4:
		{
			fputs("input the name to find:\n", stdout);
			memset(name, 0, 256);
			scanf("%s", name);
			if (pNode = findData(&header, name))
			{
				printNodeInfo(pNode);
			}
			else
			{
				printf("[%s] not find!\n");
			}

		}
		break;
		case 5:
		{
			textFile(header);
		}
		break;
		case 6:
		{
			fputs("list contents:\n", stdout);
			fputs("acctNum,name,firstName,lastName,balance:\n", stdout);
			processList(header);
		}
		break;
		default:
			return 0;

		}
	}

	return 0;
}


