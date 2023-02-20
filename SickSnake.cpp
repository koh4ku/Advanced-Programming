#include<iostream>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<queue>
using namespace std;

#define mp make_pair
#define fi first
#define se second

string matrix[16][16];
int cur_x, cur_y, score;
string dir;
bool gameOver = false;
queue <pair <int, int> > snake;

void clearScreen() {
	system("cls");
}
void buildMatrix();
void printMatrix();
void snakeBorn();
void check(int x, int y);
void food();
void move();
void _update();

signed main() {
	buildMatrix();
	printMatrix();
	snakeBorn();
	food();
	do {
		cout << "Score: " << score << endl;
		move();
		_update();
		clearScreen();
		printMatrix();
		Sleep(600);
		check(cur_x, cur_y);
	} while (!gameOver);

	cout << "\nScore: " << score << endl;
}

void buildMatrix() {
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
			matrix[i][j] = " . ";

	for (int i = 1; i <= 10; i++) {
		matrix[1][i] = "___";
		matrix[10][i] = "___";
		matrix[i][1] = "  |";
		matrix[i][10] = '|';
	}
	matrix[1][1] = "";
	matrix[1][10] = "";
}

void printMatrix() {
	cout << "\n\n   ";
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {
			cout << matrix[i][j];
		}
		cout << endl;
	}
}

void snakeBorn() {
	matrix[5][5] = " o ";
	cur_x = cur_y = 5;
	snake.push(mp(cur_x, cur_y));
}

void food() {
	srand((int)time(0));
	int r1 = 0;
	int r2 = 0;
	do {
		r1 = rand() % 8 + 2;
		r2 = rand() % 8 + 2;
	} while (matrix[r1][r2] == " o ");
	matrix[r1][r2] = " $ ";
}

void check(int x, int y) {
	if (x <= 1 or y <= 1 or x >= 10 or y >= 10) gameOver = true;
	else gameOver = false;
}

void move() {
	if (_kbhit()) {
		char m = _getch();
		if (m == 's') {
			dir = "down";
		}
		if (m == 'w') {
			dir = "up";
		}
		if (m == 'd') {
			dir = "right";
		}
		if (m == 'a') {
			dir = "left";
		}
	}
}

void drawSnake() {
	queue <pair <int, int> > q;
	q = queue <pair <int, int> >();
	q = snake;
	while (!q.empty()) {
		pair <int, int> u = q.front();
		q.pop();
		matrix[u.fi][u.se] = " o ";
	}
}

bool headOrTail(pair <int, int> head, pair <int, int> tail) {
	if (cur_x == head.fi and cur_y == head.se) return true;
	if (cur_x == tail.fi and cur_y == tail.se) return true;
	return false;
}

void _update() {
	int prev_x = cur_x;
	int prev_y = cur_y;
	if (dir == "left") {
		cur_y--;
	}
	if (dir == "right") {
		cur_y++;
	}
	if (dir == "up") {
		cur_x--;
	}
	if (dir == "down") {
		cur_x++;
	}
	pair <int, int> f = snake.front();
	pair <int, int> b = snake.back();
	if (matrix[cur_x][cur_y] == " $ ") {
		score++;

		food();
	}
	else if (matrix[cur_x][cur_y] == " o " and !headOrTail(b, f)) {
		gameOver = true;
		return;
	}
	else {
		pair <int, int> u = snake.front();
		snake.pop();
		matrix[u.fi][u.se] = " . ";
	}
	snake.push(mp(cur_x, cur_y));
	drawSnake();
}