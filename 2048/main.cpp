#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int data[4][4] = {0};

void rotate(int data[4][4], int count);
	
void init(int data[4][4], int initNum) {	//��l�Ʀr 
	int random[4];
	for(int i = 0; i < 4; i++) {
		srand((unsigned)time(NULL) + rand() + i);
		random[i] = rand() % 4;
	}
	if(random[0] == random[2] && random[1] == random[3]) {
		init(data, 2);
	}
	else{
		data[random[0]][random[1]] = initNum;
		data[random[2]][random[3]] = initNum;
	}
}

void newnum(int data[4][4], int initNum) {	//�ͦ��s�Ʀr 
	int random[2];
	for(int i = 0; i < 4; i++) {
		srand((unsigned)time(NULL) + rand() + i);
		random[i] = rand() % 4;
	}
	if(data[random[0]][random[1]] != 0) {
		newnum(data, 2);
	}
	else{
		data[random[0]][random[1]] = 2;
	}
}

void compact(int data[4][4]) {		//�V����� 
	int i, j, k = 0;
	
	for(i = 0; i < 4; i++) {
		k = 0;
		for(j = 0; j < 4; j++) {
			if(data[i][j] != 0) {
				data[i][k] = data[i][j];
				k++; 
			}	
		}
		for(; k < 4; k++)	data[i][k] = 0;	
		}
}
	
void mergeleft(int data[4][4]) {	//�V���X�� 
	compact(data);
	
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			if(data[i][j] == data[i][j+1]) {
				data[i][j] = data[i][j] * 2;
				data[i][j+1] = 0;
				compact(data);
			}
		}
	}
}

void mergeup(int data[4][4]) {	//�V�W�X�� 
	rotate(data, 3);
	mergeleft(data);
	rotate(data, 1);
}

void mergeright(int data[4][4]) {	`//�V�k�X�� 
	rotate(data, 2);
	mergeleft(data);
	rotate(data, 2);
}

void mergedown(int data[4][4]) {	//�V�U�X�� 
	rotate(data, 1);
	mergeleft(data);
	rotate(data, 3);
}

void copydata(int data[4][4], int scr[4][4]) {	//�ƻs�x�} 
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			data[i][j] = scr[i][j];
		}
	}
}

void rotate(int data[4][4], int count) {	//�V�k���� 
	int temp[4][4];
	copydata(temp, data);
	
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			data[i][j] = temp[3-j][i];
		}
	}
	if(count > 1)	rotate(data, count - 1);
}

void show(int data[4][4]) {		//��ܬɭ� 
	printf("\n|-----|-----|-----|-----|\n");
	for(int i = 0; i < 4; i++) {
		printf("|");
		for(int j = 0; j < 4; j++) {
			if(data[i][j] == 0) {
				printf("%5s|", " ");
			}
			else {
				printf("%5d|", data[i][j]);
			}
		}
		printf("\n|-----|-----|-----|-----|\n");
	}
}

int main(int argc, char** argv) {
	
	init(data, 2);
	show(data);
	while(true) {
		int ch = getch();
		switch(ch) {
			case 72:	//�W 
				mergeup(data);
				newnum(data, 2);
				break;
			case 80:	//�U 
				mergedown(data);
				newnum(data, 2);
				break;
			case 75:	//��
				mergeleft(data);
				newnum(data, 2);
				break;
			case 77:	//�k
				mergeright(data);
				newnum(data, 2);
				break; 
		}	
		system("cls");
		show(data);	
	
	}
	
	return 0;
}
