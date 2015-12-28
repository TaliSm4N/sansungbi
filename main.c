#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#pragma warning(disable: 4996)

typedef struct Node Node;

typedef struct Word
{
	int x;
	int y;
	char* word;
}Word;

struct Node
{
	Node *next;
	Node *prev;
	Word *data;
};

typedef struct List
{
	Node *head;
	Node *tail;
	Node *curr;
	int cnt;
}List;


int score = 0;

void gotoxy(int x,int y)
{
	COORD CursorPosition = { x*10,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

int equal(Word *a, Word *b)
{
	if ((a->x == b->x) && (a->y == b->y) && (strcmp(a->word, b->word)))
		return 1;
	else
		return 0;
}

void list_insert_tail(List *list, Word *item)
{
	Node *newNode = (Node *)malloc(sizeof(Node));//새 노드 생성
	newNode->next = NULL;
	newNode->prev = NULL;
	newNode->data = item;

	if (list->cnt == 0)
	{
		list->head = newNode;
		list->tail = newNode;
	}
	else
	{
		list->tail->next = newNode;
		newNode->prev = list->tail;
		list->tail = newNode;
	}

	list->cnt++;
}

Node *list_search_data(List *list, char *data)
{
	Node *curr = list->head;
	int check = 0;

	while (curr != NULL)
	{
		if (!strcmp(curr->data->word,data))
		{
			check = 1;
			break;
		}
		curr = curr->next;
	}

	if (check == 1)
		return curr;
	else
	{
		return NULL;
	}
}

void list_delete_data(List *list, char *data)
{
	Node *curr = list_search_data(list, data);

	if (curr != NULL)
	{
		if (curr == list->head)
		{
			list->head = list->head->next;
			free(curr->data);
			free(curr);
			list->cnt--;
			
		}
		else
		{
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			free(curr->data);
			free(curr);
			list->cnt--;
		}
		score++;
	}
}

void list_delete_curr(List *list, Node *curr)
{
	if (curr != NULL)
	{
		if (curr == list->head)
		{
			list->head = list->head->next;
			free(curr->data);
			free(curr);
			list->cnt--;

		}
		else
		{
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			free(curr->data);
			free(curr);
			list->cnt--;
		}
		
	}
}

void list_delete_head(List *list)
{
	//삭제할 노드가 마지막 노드 일때와 아닐때를 구분
	if (list->cnt == 1)
	{
		free(list->head);
		list->head = NULL;
		list->tail = NULL;
	}
	else
	{
		Node *temp = list->head;
		list->head = list->head->next;
		list->head->prev = NULL;

		free(temp);
	}

	list->cnt--;
}


void game()
{
	List *list = (List *)malloc(sizeof(List));
	list->cnt = 0;
	int key=0;
	char input[50]="";
	char word[10][20] = { "Protos","Zerg","Terran","Marine","Zealot","Overmind","Xel'Naga","StarCraft","Adun","Narud" };
	int index = 0;
	int x;
	int speed = 1000;
	int hard = 1;
	int life = 3;
	time_t start=0;
	time_t end = 0;

	

	x=rand()%8;
	Word *newWord=(Word *)malloc(sizeof(Word));
	newWord->x = x;
	newWord->word = word[rand() % 10];
	newWord->y = 1;
	list_insert_tail(list, newWord);
	start = clock();
	while (1)
	{
		if (score / 5 == hard)
		{
			hard++;
			speed = speed / 2;
		}

		if (end - start >= 1000)
		{
			list->curr = list->head;

			while (list->curr != NULL)
			{
				list->curr->data->y++;
				list->curr = list->curr->next;
			}

			if ((rand() % 2) == 0)
			{
				x = rand() % 8;
				newWord = (Word *)malloc(sizeof(Word));
				newWord->x = x;
				newWord->word = word[rand() % 10];
				newWord->y = 1;

				list_insert_tail(list, newWord);
			}

			start = clock();
		}

		system("cls");
		if (kbhit())
		{
			key = _getch();
			if (key == 13||key==10)
			{

				list_delete_data(list,input);


				input[0] = '\0';
				index = 0;
			}
			else if (key == 8)
			{
				if (index != 0)
				{
					input[--index] = '\0';
				}
			}
			else
			{
				input[index++] = key;
				input[index] = '\0';
			}
			
		}

		list->curr = list->head;

		printf("score : %3d\t\thard : %2d\t\tLife : ",score,hard);

		for (int i = 0; i < life; i++)
		{
			printf("♥");
		}
		if (life <= 0)
		{
			gotoxy(0, 22);
			return;
		}

		while (list->curr != NULL)
		{
			if (list->curr->data->y!=22)
			{
				gotoxy(list->curr->data->x, list->curr->data->y);
				printf("%s", list->curr->data->word);
				list->curr = list->curr->next;
				
			}
			else
			{
				list_delete_head(list);
				list->curr = list->head;
				life--;
			}

			

			
		}
		gotoxy(0, 22);
		printf(">>%s",input);


		

		end = clock();
	}
}

int main()
{
	srand(time(NULL));
	game();
	return 0;
}