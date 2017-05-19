//AI.h -> Process.h ->Board.h ��
#define _CRT_SECURE_NO_WARNINGS
#include "AI.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

void gotoxy(int x, int y)  //x, y ��ġ�� ���Ŀ���� �Ű��ִ� �Լ�

{
	COORD pos = { x, y };  //
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}  //x,y��ġ�� ���Ŀ���� �Ű��ְ� x,y,��ġ ����

int main(void)
{
	while (true)
	{//ū while ����

		Board board;  //class Board // Board.h // ������
		int record[361][2] = { 0 };  //?

		int x, y, putcnt;    //putcnt = ���� �� Ƚ��
		bool put;			// ���� �δ�
		char playerName[512] = ""; //������̸�

		system("cls"); //����â clear

		//printf("\n Gomoku++ v3.0\n\n �� 2016 Naissoft. All rights reserved.\n\n ����Ű : w, s, a, d, �� ���� Space\n");
		//printf("\n �����Ϸ��� �÷��̾� �̸��� �Է��Ͻð� Enter�� ��������.");
		scanf(" %s", playerName);

		system("cls"); //����â clear

		for (int i = 0; i < MAX * 2; i += 2)  // #define MAX=19 __ Board.h ������ 
			//19 * 19 �ٵ���  19�����ư���
		{
			for (int j = 0; j < MAX; j++)
				gotoxy(i, j), printf("��");  // x,y��ŭ �̵��ؼ� �ٵ����� �����  ���� 2ĭ�� ��ƸԱ⶧���� i+2�Ѵ�
			printf("\n");
		}

		x = y = putcnt = 0;

		while (true)
		{ //start while
			put = false;  //�ٵϵ��� ���� �ʾҴ�.
			while (!put)
			{		
				gotoxy(1, 20); printf("AI's turn");
				
				setWeight(&board);  //�ٵ����� ����ġ ���.
				
				Point pt = AISetPos(board); //AI.cpp  //��ǻ�Ͱ� �ִ밡��ġ ���� ��ǥ�� �޾ƿ´�.

				if (board.pos[pt.first][pt.second].state == BLANK) //�װ���ġ�� ��ǥ���� �ٵϵ��� ������
				{
					record[putcnt][0] = pt.first, record[putcnt][1] = pt.second; //
					putcnt++;
					doPut(WHITE, &board, pt);  //��ٵϵ��� ���´�.
					gotoxy(pt.first * 2, pt.second);
					printf("��"); 
					put = true;   //�ٵϵ��� ���Ҵ�.
				}
			}

			if (getWinner(board) == WHITE) break;

			//gotoxy(1, 20); printf("Your turn");
			gotoxy(x * 2, y);  //�� ������ x���� 2ĭ�� �����δ�.

			put = false;  //�ٵϵ��� ���� �ʾҴ�.

			while (!put)
			{ //start while
				switch (_getch()) //�����ϳ��� �Է¹��������� ����â �������ʴ´�.
				{
				case 'w':
					if (y > 0) y--;
					gotoxy(x * 2, y); //Ŀ�� �̵�
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
					if (board.pos[x][y].state == BLANK) // �ٵϵ��� ������
					{
						record[putcnt][0] = x, record[putcnt][1] = y;  // x�� y��ǥ�� ����
						putcnt++;
						doPut(BLACK, &board, std::make_pair(x, y)); //precess.h	//make_pair(x,y)--> ���� �˾Ƽ� ��ȯ����
						
						if (samsam(BLACK, &board, std::make_pair(x, y))) {
							put = false;
							gotoxy(1, 21);
							printf("3x3�̴ϱ� �ٽõֶ�");
							gotoxy(x * 2, y);
						}else{
							printf("��"); 
							put = true;
														
						}
						
						gotoxy(x * 2, y);
						//��ǻ�Ͱ� �ٵϵ��� ���� �ٽ� ���� ��ġ��					
											//�ٵϵ��� ���Ҵ�. //while�� Ż��	
						setWeight(&board);
					}
					break;
				}
				gotoxy(1, 21); printf(" Weight : %f", board.pos[x][y].weight);	//����ġ ���
				//gotoxy(1, 21); printf(" ��ǥ : %d , %d", x, y);	//��ǥ���~
				gotoxy(x * 2, y);
			}
			//end while
			//put = false;  //�ٵϵ��� ���� �ʾҴ�.

		if (getWinner(board) == BLACK) break;

			//Sleep(500);
			/*
			for (int i = 0; i < MAX; i++)
				for (int j = 0; j < MAX; j++)
					board.pos[i][j].weight = 0.0;  //����ġ 1�� �ʱ�ȭ  //��ǻ�ʹ� ����ġ�� ���� �����ڸ� �Ǵ�.
			*/
		
			//put = false;

			//Sleep(500);
		}// end while

		Sleep(500);
		gotoxy(1, 20);
		printf(" %s��(��) %d�� ���� ����߽��ϴ�!", (getWinner(board) == BLACK) ? playerName : "AI", putcnt);
		printf("\n\n �ٽ� �Ͻðڽ��ϱ�? Y / N, ���÷��� : R");

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
					gotoxy(i, j), printf("��");
				printf("\n");
			}

			for (int i = 0; i < putcnt; i++)
			{
				gotoxy(record[i][0] * 2, record[i][1]);
				if (board.pos[record[i][0]][record[i][1]].state == 1)
					printf("��");
				else if (board.pos[record[i][0]][record[i][1]].state == 2)
					printf("��");
				_getch();
			}
		}  //else if -- end
	}	//ū while��
	return 0;
}
