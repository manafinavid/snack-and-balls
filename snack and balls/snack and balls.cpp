#include <iostream>
#include <thread>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
using namespace std;
struct location{location* next,*prv;int x, y;};
string map[20];
location* first;
int last_action;
void show_end();
thread *func1;
thread *func2;
location* last;
location apple;
time_t T;
int bug;
bool t,b,game;
char in;
int Source;
string NEW[] = { "########################################",
"#                                      #",
"#                                      #",
"#                                      #",
"#                                      #",
"#                                      #",
"#                                      #",
"#                                      #",
"#                                      #",
"#                                      #",
"#                                      #",
"#                                      #",
"#                                      #",
"#                                      #",
"#                                      #",
"#                                      #",
"#                                      #",
"#                                      #",
"#                                      #",
"########################################" };
void make_apple() {
a:	int x = rand() % 16+1 ;
	int y = rand() % 16+1;
	if (map[0][0] != NULL) {
		if (map[x][y] == '0'||(x==apple.x&&apple.y==y)) {
			goto a;
		}
	}
	apple.x = x;
	apple.y = y;

}
void show() {
	system("cls");
	/*for (size_t i = 0; i < 20; i++)
	{
		map[i] = NEW[i];
	}*/
	for (size_t i = 0; i < 20; i++)
	{
		map[i] = "";
	}
	for (size_t i = 0; i < 20; i++)
	{
		map[0]=map[0]+"##";
	}
	for (size_t i = 0; i < 18; i++)
	{
		map[i+1] = map[i+1] + "#";
		for (size_t j = 0; j <= 18; j++)
		{
			map[i + 1] = map[i + 1] + "  ";
		}
		map[i + 1] = map[i + 1] + "#";
	}
	for (size_t i = 0; i < 20; i++)
	{
		map[19] = map[19] + "##";
	}
	location* temp = first;
	map[apple.x][apple.y] = 'A';
	while (first!=NULL)
	{
		map[first->x+1][first->y+1] = '0';
		first = first->next;
	}
	first = temp;
	
	for (size_t i = 0; i < 20; i++)
	{
		cout << map[i]<<endl;
	}
	cout << "Sourse :" << Source;
}
void move(int x=0,int y=0) {
	location* temp = first;
	if (last->x + x == apple.x-1 && last->y + y == apple.y-1) {
		while (first->next != NULL)
			first = first->next;
		location* T = new location;
		T->next = NULL;
		T->prv = last;
		T->x = apple.x-1;
		T->y = apple.y-1;
		last->next = T;
		last = last->next;
		map[apple.x][apple.y] = ' ';
		make_apple();
		Source++;
		goto r;
	}
	if (!(last->x+x == last->prv->x && last->y+y == last->prv->y)) {
		while (first->next != NULL)
		{
			first->x = first->next->x;
			first->y = first->next->y;
			first = first->next;
		}
		first->x += x;
		first->y += y;
	}
	else
	{
		last_action = bug;
	}
r:	first = temp;
}
bool check(int x=0,int y=0) {
	if (map[last->x + x+1][last->y + y+1]=='#')
	{
		return false;
	}
	if (map[last->x + x+1][last->y + y+1] == '0')
	{
		return false;
	}
	return true;
}
void f1() {
	while (game)
	{
	in = _getch();
	switch (in)
	{
	case 'w':
	case 'W':
		if (!check(-1))
			show_end();
		bug=last_action = 0;
		move(-1);
		show();
		t = true;
		break;
	case 's':
	case 'S':
		if (!check(1))
			show_end();
		bug = last_action = 1;
		move(1,0);
		show();
		t = true;
		break;
	case 'a':
	case 'A':
		if (!check(0,-1))
			show_end();
		bug = last_action = 2;
		move(0,-1);
		show();
		t = true;
		break;
	case 'd':
	case 'D':
		if (!check(0, 1))
			show_end();
		bug = last_action = 3;
		move(0, 1);
		show();
		t = true;
		break;
	default:
		break;
	}
	show();
	}
}
void f2() {
	while (game)
	{
		if (t == true) {
			T = clock();
			t = false;
		}
		float tem = (float)(clock()-T) / CLOCKS_PER_SEC;
		if ( tem >= .7) {
			switch (last_action)
			{
			case 0:
				if (!check(-1))
					show_end();
				move(-1);
				show();
				t = true;
				break;
			case 1:
				if (!check(1))
					show_end();
				last_action = 1;
				move(1, 0);
				show();
				t = true;
				break;
			case 2:
				if (!check(0, -1))
					show_end();
				last_action = 2;
				move(0, -1);
				show();
				t = true;
				break;
			case 3:
				if (!check(0, 1))
					show_end();
				last_action = 3;
				move(0, 1);
				show();
				t = true;
				break;
			default:
				t = true;
				T = clock();
			}
		}
	}
}
int main()
{
	Source = 2;
	game = true;
	srand(time(NULL));
	location *loc=new location;
	last_action = 3;
	loc->x = 0;
	loc->y = 0;
	loc->next = new location;
	loc->prv = NULL;
	loc->next->x = 0;
	loc->next->y = 1;
	loc->next->next = NULL;
	loc->next->prv = loc;
	last = loc->next;
	first = loc;
	make_apple();
	show();
	thread fun1(f1);
	thread fun2(f2);
	func1 = &fun1; func2 = &fun2;
	fun1.join(); fun2.join();
}
void show_end() {
	game = false;
	cout <<("Game Over :)") << endl<<"Do you want try again? (y/n):";
a:	char i = _getch();
	switch (i)
	{
	case 'y':
	case 'Y':
		main();
	break;
	case 'n':
	case 'N':
		exit(0);
	default:
		goto a;
	}

}