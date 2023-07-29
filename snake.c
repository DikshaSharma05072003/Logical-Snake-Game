//Logical Snake game
//2CS301-Data Structures and Algorithms
//21BCE058, 21BCE059, 21BCE060

#include <stdio.h>
#include <malloc.h>
#include <Windows.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include<stdbool.h>
#include<stdbool.h>

#define ff fflush(stdin)
# define max 10

int front = -1;
int rear = -1;
char queue[max][20];
int flag=0;
char ans[80];
int count=0;

struct node{
	int x;
	int y;

	struct node *next;
}*head, *tail;

int arr[40][120];

int sizeX = 90;
int sizeY = 20;
int score = 0;
int xFood = 4;
int yFood = 10;

void createBody(int x, int y){
    //used linked list to create snake body
	struct node *body = (struct node *) malloc (sizeof(struct node));
	body->x = x;
	body->y = y;
	if (!head){
		head = tail = body;
	}
	else{
		tail->next = body;
		tail = body;
	}
	tail->next = NULL;
}

void gotoxy(int x, int y){
	COORD c = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void createMap(){
	for (int i = 0; i < sizeY; i++){
		for (int j = 0; j < sizeX; j++){
			if (i == 0 || i == sizeY - 1 || j == 0 || j == sizeX - 1)
                arr[i][j] = 1;
			else
			   arr[i][j] = 0;
		}
	}
	arr[yFood][xFood] = 3;
}

void createFood(){
	srand(time(NULL));
	arr[yFood][xFood] = 0;
	do{
		xFood = rand() % (sizeX - 1) + 1;
		yFood = rand() % (sizeY - 1) + 1;
	} while (arr[yFood][xFood] != 0);

	arr[yFood][xFood] = 3;
	gotoxy(xFood, yFood);
	printf("*");
}

void viewMap(){
	for (int i = 0; i < sizeY; i++)
    {
		for (int j = 0; j < sizeX; j++)
		{
			if (arr[i][j] == 1)
                printf("%c", 35);
			else if (arr[i][j] == 3)
			    printf("*");
			else
                printf(" ");
		}
		puts("");
	}
}

void questions()
{
    //questions are stored in array
    char arr[10][500] = {"There are two ducks in front of a duck, two ducks behind a duck and a duck in the middle. How many ducks are there?"
    ,"Five people were eating apples, A finished before B, but behind C. D finished before E, but behind B. What was the finishing order?"
    ,"Jack is looking at Anne. Anne is looking at George. Jack is married, George is not, and we don’t know if Anne is married. Is a married person looking at an unmarried person?"
    ,"A man has 53 socks in his drawer: 21 identical blue, 15 identical black and 17 identical red. The lights are out and he is completely in the dark. How many socks must he take out to make 100 percent certain he has at least one pair of black socks?"
    ,"The day before two days after the day before tomorrow is Saturday. What day is it today?"
    ,"A girl meets a lion and unicorn in the forest. The lion lies every Monday, Tuesday and Wednesday and the other days he speaks the truth. The unicorn lies on Thursdays, Fridays and Saturdays, and the other days of the week he speaks the truth. “Yesterday I was lying,” the lion told the girl. “So was I,” said the unicorn. What day is it?"
    ," A bad guy is playing Russian roulette with a six-shooter revolver. He puts in one bullet, spins the chambers and fires at you, but no bullet comes out. He gives you the choice of whether or not he should spin the chambers again before firing a second time. Should he spin again?"
    ,"Susan and Lisa decided to play tennis against each other. They bet $1 on each game they played. Susan won three bets and Lisa won $5. How many games did they play?"
    ," Three men are lined up behind each other. The tallest man is in the back and can see the heads of the two in front of him; the middle man can see the one man in front of him; the man in front can’t see anyone. They are blindfolded and hats are placed on their heads, picked from three black hats and two white hats. The extra two hats are hidden and the blindfolds removed. The tallest man is asked if he knows what color hat he’s wearing; he doesn’t. The middle man is asked if he knows; he doesn’t. But the man in front, who can’t see anyone, says he knows. How does he know, and what color hat is he wearing?"
    ,"A teacher writes six words on a board: “cat dog has max dim tag.” She gives three students, Albert, Bernard and Cheryl each a piece of paper with one letter from one of the words. Then she asks, “Albert, do you know the word?” Albert immediately replies yes. She asks, “Bernard, do you know the word?” He thinks for a moment and replies yes. Then she asks Cheryl the same question. She thinks and then replies yes. What is the word?"
    };
    printf("\n\n\n\n");
    puts(arr[count]);
    printf("\n");
}

int insq(char queue[max][20], int rear)
{
    //ans stored in queue
    char ans1[10][250]={"three","cabde","yes","40","friday","thursday","yes","eleven","black","dog"};
    int i;
        for(i=0;i<max;i++)
        {
            strcpy(queue[++rear],ans1[i]);
        }
        puts("Enter your answer:");
        gets(ans);

    if(strcmp(queue[count], ans)==0)
            flag=0;
        else
            flag=1;

    if(flag==0)
        printf("\nCorrect");
    else
        printf("\nIncorrect Option");
        fflush(stdout);

       return flag;

}
bool run(int x, int y){
	struct node *current = head;
	int tempX;
	int tempY;
	int helpX;
	int helpY;
	while (current)
    {
        //insertion of node
		if (current == head){
			if(score>2){
				struct node *v_curr=head->next->next;
				while(v_curr)
				{
					if(v_curr->x == head->x && v_curr->y == head->y ){
                            return false;
					}
					v_curr=v_curr->next;
				}
			}
			arr[current->y][current->x] = 0;
			if(head->x + x < 1 || head->x + x > sizeX - 2 || head->y + y < 1 || head->y + y > sizeY - 2){
                    //checks the position if game over
				return false;
			}
			if (head->x == xFood && head->y == yFood)
            {
                printf("\a");
				int newX = tail->x - x;
				int newY = tail->y - y;
				createBody(newX, newY);

				questions();
                insq(queue, rear);
                count++;
                if(flag==0)
                    score++;

                system("cls");
                viewMap();
				createFood();
			}
			gotoxy(current->x, current->y);
			printf(" ");
			tempX = current->x;
			tempY = current->y;
			current->x = current->x + x;
			current->y = current->y + y;
		}
		else
        {
			arr[current->y][current->x] = 0;
			gotoxy(current->x, current->y);
			printf(" ");
			helpX = tempX;
			helpY = tempY;

			tempX = current->x;
			tempY = current->y;

			current->x = helpX;
			current->y = helpY;
		}

		arr[current->y][current->x] = 2;
		gotoxy(current->x, current->y);
		printf("%c", 'x');

		current = current->next;
	}
	return true;
}

void play(){
	char move;
	int direction = 4;
	bool walk = true;
	int speed;
	score = 0;
	while(walk)
    {
		if(score>3)
            speed=150;
		else if(score>5)
		    speed=100;
		else if(score<9)
            speed=200;
		else
		    speed=50;

		if (kbhit())
            //this checks if key is pressed
        {
			switch(move = getch())
			{
			case 'w':
				if (direction != 3)
				    direction = 1;
				if(direction==1)
                    speed/=2;
				break;
			case 'a':
				if (direction != 4)
                    direction = 2;
				if(direction==2)
                    speed/=2;
				break;
			case 's':
				if (direction != 1)
                     direction = 3;
				if(direction==3)
                    speed/=2;
				break;
			case 'd':
				if (direction != 2)
                    direction = 4;
				if(direction==4)
                    speed/=2;
				break;
			}
		}
		switch(direction){
		    case 1:
			    walk = run(0, -1);
			    break;
		    case 2:
			    walk = run(-1, 0);
			    break;
		    case 3:
			    walk = run(0, 1);
			    break;
		    case 4:
			    walk = run(1, 0);
                break;
		}
		gotoxy(1, sizeY + 1);
		printf("Score : %d", score);
		Sleep(speed);
	}
}
void popAll(){
	while(head){
		struct node *current;
		current=head;
		head=head->next;
		free(current);
	}
}

int main(){
	system("DSA");
	int input=0;

	while(input!=2)
    {
		system("cls");
		puts("\n-----Welcome to logical snake game-----");
		puts("\n           INSTRUCTIONS.....");
		puts("When the snake touches the boundary or it eats its own tail, the game is over.");
		puts("When the snake eats an egg(*) a logical reasoning question is asked from the player.");
		puts("If the player answers it correctly, the score increases by one but if the answer is wrong the score remains same.");
		puts("Use(lowercase letters only):");
		puts("                           'w' for up  ");
		puts("                           's' for down");
		puts("                           'a' for left");
		puts("                           'd' for right");
		puts("to move the snake in the specified direction.");

		puts("\sn\t1. To play");
		puts("\t2. To exit");
		scanf("%d",&input);
		ff;
		if(input==1)
        {
			system("cls");
			createBody(1, 1);
			createMap();
			viewMap();
			play();
			gotoxy(1, sizeY + 2);
			printf("Game over.......");
			char m;
			scanf("%c",&m);
			popAll();
        }
	}
	return 0;
}
