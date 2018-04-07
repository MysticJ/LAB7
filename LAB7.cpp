//============================================================================
// Name        : LAB7.cpp
// Author      : QIAN Shiyi & JIN Menghe
// Version     :
// Copyright   : Your copyright notice
// Description : LAB7
//============================================================================

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

struct Minion
{
	char name[10];
	int Bananas;
	int Bombs;
	int col;
	char symbol;
};

void InitMap(int map[][31]);
void OnePlayer(int map[][31], int step, Minion& x, int duration);
bool OneMove(int map[][31], int step, Minion& x, time_t start, int duration);
void Display(int map[][31], Minion& x, time_t start, int duration);

int main() {
	// description
	cout<<"Welcome to the Magic Banana Collection!!!"<<endl;
	cout<<"There will be three players: Stewart, Bob and Harry."<<endl;
	cout<<"You will player the game one by one."<<endl;
	cout<<"You need to be careful, as there will be random bombs falling."<<endl;
	cout<<"If you have encountered the bomb, two bananas will be deducted from you collection!"<<endl;
	cout<<"If you have lost all you bananas, you have to exit the game!"<<endl;
	cout<<"Press \'a\' if you want to move left, and \'d\' to move right."<<endl;
	cout<<"If you don't want to move, press any other key."<<endl;
	cout<<"One thing to note, the bananas and bombs will not move if you do not press any key."<<endl;
	cout<<"So remember to press something even if you don't want to move!"<<endl;
	cout<<"Now, let's start the game!\n"<<endl;
	srand(time(NULL));
	int map[11][31], duration=60;
	InitMap(map);
	Minion Stewart={"Stewart", 0, 0, 15, '@'}, Bob={"Bob", 0, 0, 15, '#'}, Harry={"Harry", 0, 0, 15, '$'};
	int step=2;
	OnePlayer(map, step, Stewart, duration);
	OnePlayer(map, step, Bob, duration);
	OnePlayer(map, step, Harry, duration);
	return 0;
}

void InitMap(int map[][31]){
	for (int i=0; i<11; i++){
		for (int j=0; j<31; j++){
			map[i][j]=0;
		}
	}
}

// the purpose of this function is to check whether a certain key is pressed or not
void OnePlayer(int map[][31], int step, Minion& x, int duration){
	bool boom=false;
	char S;
	cout<<x.name<<"! It's your turn!"<<"Are you ready?!"<<endl;
	cout<<"Please enter \'r\' when you are ready!"<<endl;
	cin>>S;
	if (S=='r'){
		cout<<"Let's start!"<<endl<<flush;
		time_t start=time(nullptr);
		while (time(nullptr)-start<duration){
			boom = OneMove(map, step, x, start, duration);
			if (boom==true){
				cout<<"You loose all your bananas!"<<endl;
				break;
			}
		}
	}
	if (boom==false){
		cout<<"Time's up!"<<endl;
		cout<<"You have encountered "<<x.Bombs<<"times of bombs!"<<endl;
		cout<<"You have collected "<<x.Bananas<<" bananas in total!"<<endl;
		cout<<"\n\n\n";
	}
	cout<<"Now let's start the game of next player!"<<endl;
}

bool OneMove(int map[][31], int step, Minion& x, time_t start, int duration){
	// remove bananas at the last row
	for (int k=0; k<31; k++){
		map[10][k]=0;
	}
	// move all existing bananas one step down
	for (int i=9; i>=0; i--){
		for (int j=0; j<31; j++){
			if (map[i][j]!=0){
				int row = ((i+step)>10)?10:(i+step);
				map[row][j]=map[i][j];
				map[i][j]=0;
			}
		}
	}
	// creating new banana or new bomb
	int col = rand()%31;
	int bomb=rand()%8;
	map[0][col]=(bomb<6)?1:2;
	Display(map, x, start, duration);
	// move the player
	char direction;
	cin>>direction;
	if (direction=='a'){
		x.col=(x.col-1<0)?0:(x.col-1);
	}
	else if (direction=='d'){
		x.col=(x.col+1>30)?30:(x.col+1);
	}
	// check if bananas are attained
	if (map[10][x.col]==1){
		x.Bananas=x.Bananas+1;
	}
	else if (map[10][x.col]==2){
		x.Bananas=x.Bananas-2;
		x.Bombs=x.Bombs+1;
		if (x.Bananas<0){
			return true;
		}
	}
	Display(map, x, start, duration);
	return false;
}

void Display(int map[][31], Minion& x, time_t start, int duration){
	cout<<"Player: "<<x.name<<"\t\t"<<"Time Remaining: "<<duration-(time(nullptr)-start)<<"s"<<endl;
	cout<<"Number of Bananas Collected: "<<x.Bananas<<endl;
	cout<<"Number of Bombs Encountered: "<<x.Bombs<<endl;
	for (int i=0; i<10; i++){
		for (int j=0; j<30; j++){
			if (map[i][j]==0) {cout<<" |";}
			else {cout<<map[i][j]<<"|";}
		}
		if (map[i][30]==0){cout<<" ";}
		else if (map[i][30]==1) {cout<<map[i][30];}
		cout<<endl;
	}
	for (int k=0; k<30; k++){
		if ((x.col==k)&&(map[10][k]==1)) {cout<<"*|";}
		else if ((x.col==k)&&(map[10][k]==0)) {cout<<x.symbol<<"|";}
		else {
			if (map[10][k]==0) {cout<<" |";}
			else {cout<<map[10][k]<<"|";}
		}
	}
	if ((x.col==30)&&(map[10][30]==1)) {cout<<"*";}
	else if ((x.col==30)&&(map[10][30]==0)) {cout<<x.symbol;}
	else {
		if (map[10][30]==0) {cout<<" ";}
		else {cout<<map[10][30];}
	}
	cout<<endl;
}
