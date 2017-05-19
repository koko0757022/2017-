//AI.h -> Process.h ->Board.h 순
#define _CRT_SECURE_NO_WARNINGS
#include "AI.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

void gotoxy(int x, int y)  //x, y 위치로 출력커서를 옮겨주는 함수

{
	COORD pos = { x, y };  //
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}  //x,y위치로 출력커서를 옮겨주고 x,y,위치 저장

int main(void)
{
	while (true)
	{//큰 while 시작

		Board board;  //class Board // Board.h // 오목판
		int record[361][2] = { 0 };  //?

		int x, y, putcnt;    //putcnt = 돌을 둔 횟수
		bool put;			// 돌을 두다
		char playerName[512] = ""; //사용자이름

		system("cls"); //도스창 clear

		//printf("\n Gomoku++ v3.0\n\n ⓒ 2016 Naissoft. All rights reserved.\n\n 조작키 : w, s, a, d, 돌 놓기 Space\n");
		//printf("\n 시작하려면 플레이어 이름을 입력하시고 Enter를 누르세요.");
		scanf(" %s", playerName);

		system("cls"); //도스창 clear

		for (int i = 0; i < MAX * 2; i += 2)  // #define MAX=19 __ Board.h 에있음 
			//19 * 19 바둑판  19번돌아간다
		{
			for (int j = 0; j < MAX; j++)
				gotoxy(i, j), printf("┼");  // x,y만큼 이동해서 바둑판을 만든다  ┼는 2칸씩 잡아먹기때문에 i+2한다
			printf("\n");
		}

		x = y = putcnt = 0;

		while (true)
		{ //start while
			put = false;  //바둑돌을 두지 않았다.
			while (!put)
			{		
				gotoxy(1, 20); printf("AI's turn");
				
				setWeight(&board);  //바둑판의 가중치 계산.
				
				Point pt = AISetPos(board); //AI.cpp  //컴퓨터가 최대가중치 값의 좌표를 받아온다.

				if (board.pos[pt.first][pt.second].state == BLANK) //그가중치의 좌표값에 바둑돌이 없으면
				{
					record[putcnt][0] = pt.first, record[putcnt][1] = pt.second; //
					putcnt++;
					doPut(WHITE, &board, pt);  //흰바둑돌을 놓는다.
					gotoxy(pt.first * 2, pt.second);
					printf("●"); 
					put = true;   //바둑돌을 놓았다.
				}
			}

			if (getWinner(board) == WHITE) break;

			//gotoxy(1, 20); printf("Your turn");
			gotoxy(x * 2, y);  //┼ 때문에 x축은 2칸식 움직인다.

			put = false;  //바둑돌을 놓지 않았다.

			while (!put)
			{ //start while
				switch (_getch()) //문자하나를 입력받을때까지 도스창 꺼지지않는다.
				{
				case 'w':
					if (y > 0) y--;
					gotoxy(x * 2, y); //커서 이동
					break;
				case 's':
					if (y < MAX) y++;
					gotoxy(x * 2, y);
					break;
				case 'a':
					if (x > 0) x--;
					gotoxy(x * 2, y);
					break;
				case 'd':
					if (x < MAX) x++;
					gotoxy(x * 2, y);
					break;
				case ' ': //space
					if (board.pos[x][y].state == BLANK) // 바둑돌이 없으면
					{
						record[putcnt][0] = x, record[putcnt][1] = y;  // x와 y좌표를 저장
						putcnt++;
						doPut(BLACK, &board, std::make_pair(x, y)); //precess.h	//make_pair(x,y)--> 값을 알아서 변환해줌
						
						if (samsam(BLACK, &board, std::make_pair(x, y))) {
							put = false;
							gotoxy(1, 21);
							printf("3x3이니깐 다시둬라");
							gotoxy(x * 2, y);
						}else{
							printf("○"); 
							put = true;
														
						}
						
						gotoxy(x * 2, y);
						//컴퓨터가 바둑돌을 논후 다시 나의 위치로					
											//바둑돌을 놓았다. //while문 탈출	
						setWeight(&board);
					}
					break;
				}
				gotoxy(1, 21); printf(" Weight : %f", board.pos[x][y].weight);	//가중치 출력
				//gotoxy(1, 21); printf(" 좌표 : %d , %d", x, y);	//좌표출력~
				gotoxy(x * 2, y);
			}
			//end while
			//put = false;  //바둑돌을 두지 않았다.

		if (getWinner(board) == BLACK) break;

			//Sleep(500);
			/*
			for (int i = 0; i < MAX; i++)
				for (int j = 0; j < MAX; j++)
					board.pos[i][j].weight = 0.0;  //가중치 1로 초기화  //컴퓨터는 가중치를 보고 놓을자리 판단.
			*/
		
			//put = false;

			//Sleep(500);
		}// end while

		Sleep(500);
		gotoxy(1, 20);
		printf(" %s이(가) %d수 만에 우승했습니다!", (getWinner(board) == BLACK) ? playerName : "AI", putcnt);
		printf("\n\n 다시 하시겠습니까? Y / N, 리플레이 : R");

		char ch;
		scanf(" %c", &ch);

		if (ch == 'N') break;
		else if (ch == 'Y') system("cls");
		else if (ch == 'R')
		{
			system("cls");
			for (int i = 0; i < MAX * 2; i += 2)
			{
				for (int j = 0; j < MAX; j++)
					gotoxy(i, j), printf("┼");
				printf("\n");
			}

			for (int i = 0; i < putcnt; i++)
			{
				gotoxy(record[i][0] * 2, record[i][1]);
				if (board.pos[record[i][0]][record[i][1]].state == 1)
					printf("●");
				else if (board.pos[record[i][0]][record[i][1]].state == 2)
					printf("○");
				_getch();
			}
		}  //else if -- end
	}	//큰 while끝
	return 0;
}
