#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second

int mat[10][10], visit[10][10], open[10][10];
string grid[10][10];
vector <pair <int, int> > bomb;

int x[8] = {0, 0, 1, -1, 1, 1, -1, -1};
int y[8] = {1, -1, 0, 0, 1, -1, 1, -1};

void init();
void bombLocation();
void hint();
void show();
void interact();

signed main(){
	cout << "Loading... Please wait...\n"; 
	init();
	bombLocation();
	hint();
	system("cls");
    show();
    interact();
}

void init(){
	for (int i=1; i<=9; i++){
        for (int j=1; j<=9; j++){
            grid[i][j] = "*";
        }
    }
}

void show(){
	cout << "     ";
	for (int i=1; i<=9; i++){
		cout << i << " ";
	}
	cout << "\n\n";
    for (int i=1; i<=9; i++){
    	cout << i << "    ";
        for (int j=1; j<=9; j++){
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

void showWhenLosing(){
	cout << "     ";
	for (int i=1; i<=9; i++){
		cout << i << " ";
	}
	cout << "\n\n";
	for (int i=1; i<=9; i++){
		cout << i << "    ";
        for (int j=1; j<=9; j++){
        	if (mat[i][j] == -1) cout << "! ";
            else cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

void bombLocation(){
    int bombNum = 0;
    while (bombNum < 10){
    	srand((int)time(0));
    	for (int i=0; i<2; i++){
    		int r1 = rand() % 9 + 1;
    		int r2 = rand() % 9 + 1;
    		if (mat[r1][r2] != -1){
    			mat[r1][r2] = -1;
    			bombNum++;
			}
		}
	}
    for (int i=1; i<=9; i++){
        for (int j=1; j<=9; j++){
        	if (mat[i][j] == -1) 
			    bomb.pb(mp(i, j));
        }
    }
}

bool check(int xx, int yy){
    if (xx < 1 or yy < 1 or xx > 9 or yy > 9 or mat[xx][yy] == -1) return false;
    return true;
}

void hint(){
    for (int j=0; j<(int)bomb.size(); j++){
        for (int i=0; i<8; i++){
            int x_neighbor = bomb[j].fi + x[i];
            int y_neighbor = bomb[j].se + y[i];
            if (check(x_neighbor, y_neighbor)){
                mat[x_neighbor][y_neighbor]++;
            }
        }
    }
}

void nextScreen(){
	system("cls");
}

bool zero(int xx, int yy){
	if (xx < 1 or yy < 1 or xx > 9 or yy > 9 or mat[xx][yy] != 0) return false;
    return true;
}

void bfs(int xx, int yy){
	queue <pair <int, int> > q;
	q.push(mp(xx, yy));
	while (!q.empty()){
		pair <int, int> u = q.front();
		q.pop();
		grid[u.fi][u.se] = (char)(mat[u.fi][u.se] + '0');
		for (int i=0; i<8; i++){
			int next_x = u.fi + x[i];
			int next_y = u.se + y[i];
			if (zero(next_x, next_y) and !visit[next_x][next_y]){
				q.push(mp(next_x, next_y));
				visit[next_x][next_y] = 1;
		    }
		}
		for (int i=0; i<8; i++){
			int next_x = u.fi + x[i];
			int next_y = u.se + y[i];
			if (check(next_x, next_y)){
				grid[next_x][next_y] = (char)(mat[next_x][next_y] + '0');
			}
		}
	}
}

void intro(){
	cout << "===================================================\n";
	cout << "So for this time, what is your movement?\n";
	cout << "Press ? if you want to flag any grid that might contain a bomb\n";
	cout << "Press ! if you want to open a grid\n";
}

void interact(){
	int xx, yy, correct = 0;
	char flag;
	do{
		intro();
		cin >> flag >> xx >> yy;
		nextScreen();
		if (flag == '?'){
			grid[xx][yy] = '?';
			if (mat[xx][yy] == -1) correct++;
		}
		else{
			visit[xx][yy] = 1;
			if (mat[xx][yy] == 0){
				bfs(xx, yy);
			}
			else if (mat[xx][yy] == -1){
			    cout << "Sorry, you lost :(\n";
			    showWhenLosing();
			    return ;
		    }
		    grid[xx][yy] = (char)(mat[xx][yy] + '0');
		}
		show();
	} while (correct < 10);
	cout << "Congratulations! You win!";
}
