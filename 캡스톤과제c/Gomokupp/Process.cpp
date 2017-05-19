#include "Process.h"
#include <cmath>
#define PLAYER 8
//BLANK, WHITE, BLACK -- 0 1 2

int checkpos[8][2] = {
	{ -1, 1 },  //���ʾƷ��밢��
	{ 0, 1 },  //�ؿ�
	{ 1, 1 },  //�����ʾƷ��밢��
	{ 1, 0 },  //�����U
	{1,-1},  //���������� �밢��
	{0,-1},	  //����
	{-1,-1},		//�������� �밢��
	{-1,0}		//����
};


void setWeight(Board *board) {
	int row, col;
	int i = 0;
	double count = 1.0;
	int tempPlayer = 0;

	for (row = 0; row < MAX; row++) {
		for (col = 0; col < MAX; col++) {
			
			if (col < MAX && board->pos[row][col + 1].state == 2 && board->pos[row][col].weight < 1.5) {
				
				board->pos[row][col].weight = 1;
			}else   // RIGHT �� 
				if (col > 0 && board->pos[row][col - 1].state == 2 && board->pos[row][col].weight < 1.5)
					board->pos[row][col].weight = 1;
				else   // DOWN ��
					if (row < MAX && board->pos[row + 1][col].state == 2 && board->pos[row][col].weight < 1.5)
						board->pos[row][col].weight = 1;
					else   // UP ��
						if (row > 0 && board->pos[row - 1][col].state == 2 && board->pos[row][col].weight < 1.5)
							board->pos[row][col].weight = 1;
						else // ��
							if ((row < MAX && col < MAX) && board->pos[row + 1][col + 1].state == 2 && board->pos[row][col].weight < 1.5)
								board->pos[row][col].weight = 1;
							else // ��
								if ((row > 0 && col > 0) && board->pos[row - 1][col - 1].state == 2 && board->pos[row][col].weight < 1.5)
									board->pos[row][col].weight = 1;
								else // ��
									if ((row > 0 && col < MAX) && board->pos[row - 1][col + 1].state == 2 && board->pos[row][col].weight < 1.5)
										board->pos[row][col].weight = 1;
									else // ��
										if ((row < MAX && col > 0) && board->pos[row + 1][col - 1].state == 2 && board->pos[row][col].weight < 1.5)
											board->pos[row][col].weight = 1;
			if (col < MAX && board->pos[row][col + 1].state == 1 && board->pos[row][col].weight < 1.5) {

				board->pos[row][col].weight = 1.1;
			}
			else   // RIGHT �� 
				if (col > 0 && board->pos[row][col - 1].state == 1 && board->pos[row][col].weight < 1.5)
					board->pos[row][col].weight = 1.1;
				else   // DOWN ��
					if (row < MAX && board->pos[row + 1][col].state == 1 && board->pos[row][col].weight < 1.5)
						board->pos[row][col].weight = 1.1;
					else   // UP ��
						if (row > 0 && board->pos[row - 1][col].state == 1 && board->pos[row][col].weight < 1.5)
							board->pos[row][col].weight = 1.1;
						else // ��
							if ((row < MAX && col < MAX) && board->pos[row + 1][col + 1].state == 1 && board->pos[row][col].weight < 1.5)
								board->pos[row][col].weight = 1.1;
							else // ��
								if ((row > 0 && col > 0) && board->pos[row - 1][col - 1].state == 1 && board->pos[row][col].weight < 1.5)
									board->pos[row][col].weight = 1.1;
								else // ��
									if ((row > 0 && col < MAX) && board->pos[row - 1][col + 1].state == 1 && board->pos[row][col].weight < 1.5)
										board->pos[row][col].weight = 1.1;
									else // ��
										if ((row < MAX && col > 0) && board->pos[row + 1][col - 1].state == 1 && board->pos[row][col].weight < 1.5)
											board->pos[row][col].weight = 1.1;
		}
		
	}

	for (row = 0; row < MAX; row++) {
		for (col = 0; col < MAX; col++) { //���� Ȯ���ϱ�����
			
			// RIGHT ��
			if (col < MAX
				&& board->pos[row][col].state < 1      //������ ���� {BLANK,WHITE,BLACK}
				&& board->pos[row][col + 1].state >= 1) {   //UP��  ���� �ִ°��

				count = 0;
				tempPlayer = board->pos[row][col + 1].state;
				if (tempPlayer == WHITE)
					count = 0.1;
				for (i = col + 1; i < MAX; i++) {
					if (board->pos[row][i].state == tempPlayer)
						count++;
					else
						break;
				}

				if (board->pos[row][col].weight < count) {   // �ش� ��ġ ����ġ�� count ���� �۴ٸ�
					board->pos[row][col].weight = count;
				}
			}

			// LEFT �� 
			if (col > 0
				&& board->pos[row][col].state < 1      //���� ����ġ�� ������ ��ġ
				&& board->pos[row][col - 1].state >= 1) {   //right�� ���� �ִ� ���

				count = 0;
				tempPlayer = board->pos[row][col - 1].state;
				if (tempPlayer == WHITE)
					count = 0.1;

				for (i = col - 1; i >= 0; i--) {
					if (board->pos[row][i].state == tempPlayer)
						count++;
					else
						break;
				}

				if (board->pos[row][col].weight < count) {   // �ش� ��ġ ����ġ�� count ���� �۴ٸ�
					board->pos[row][col].weight = count;
				}
			}
			// DOWN ��
			if (row < MAX
				&& board->pos[row][col].state < 1      //���� ����ġ�� ������ ��ġ
				&& board->pos[row + 1][col].state >= 1) {   //right�� ���� �ִ� ���

				count = 0;
				tempPlayer = board->pos[row + 1][col].state;
				if (tempPlayer == WHITE)
					count = 0.1;

				for (i = row + 1; i < MAX; i++) {
					if (board->pos[i][col].state == tempPlayer)
						count++;
					else
						break;
				}

				if (board->pos[row][col].weight < count) {   // �ش� ��ġ ����ġ�� count ���� �۴ٸ�
					board->pos[row][col].weight = count;
				}
			}
			// UP ��
			if (row > 0
				&& board->pos[row][col].state < 1      //���� ����ġ�� ������ ��ġ
				&& board->pos[row - 1][col].state >= 1) {   //right�� ���� �ִ� ���

				count = 0;
				tempPlayer = board->pos[row - 1][col].state;
				if (tempPlayer == WHITE)
					count = 0.1;

				for (i = row - 1; i >= 0; i--) {
					if (board->pos[i][col].state == tempPlayer)
						count++;
					else
						break;
				}

				if (board->pos[row][col].weight < count) {   // �ش� ��ġ ����ġ�� count ���� �۴ٸ�
					board->pos[row][col].weight = count;
				}
			}
			
			// �� right down
			if (row < MAX && col < MAX
				&& board->pos[row][col].state < 1      //���� ����ġ�� ������ ��ġ
				&& board->pos[row + 1][col + 1].state >= 1) {   //right�� ���� �ִ� ���

				count = 0;
				tempPlayer = board->pos[row + 1][col + 1].state;
				if (tempPlayer == WHITE)
					count = 0.1;

				for (i = 1; i < 5; i++) {
					if ((row + i < MAX && col + i < MAX) && (board->pos[row + i][col + i].state == tempPlayer))
						count++;
					else
						break;
				}

				if (board->pos[row][col].weight < count) {   // �ش� ��ġ ����ġ�� count ���� �۴ٸ�
					board->pos[row][col].weight = count;
				}
			}
			// �� left up
			if (row > 0 && col > 0
				&& board->pos[row][col].state < 1      //���� ����ġ�� ������ ��ġ
				&& board->pos[row - 1][col - 1].state >= 1) {   //right�� ���� �ִ� ���

				count = 0;
				tempPlayer = board->pos[row - 1][col - 1].state;
				if (tempPlayer == WHITE)
					count = 0.1;

				for (i = 1; i < 5; i++) {
					if ((row - i >= 0 && col - i > 0) && (board->pos[row - i][col - i].state == tempPlayer))
						count++;
					else
						break;
				}

				if (board->pos[row][col].weight < count) {   // �ش� ��ġ ����ġ�� count ���� �۴ٸ�
					board->pos[row][col].weight = count;
				}
			}
			// �� right up
			if (row > 0 && col < MAX
				&& board->pos[row][col].state < 1      //���� ����ġ�� ������ ��ġ
				&& board->pos[row - 1][col + 1].state >= 1) {   //right�� ���� �ִ� ���

				count = 0;
				tempPlayer = board->pos[row - 1][col + 1].state;
				if (tempPlayer == WHITE)
					count = 0.1;
				for (i = 1; i < 5; i++) {
					if ((row - i >= 0 && col + i < 15) && (board->pos[row - i][col + i].state == tempPlayer))
						count++;
					else
						break;
				}

				if (board->pos[row][col].weight < count) {   // �ش� ��ġ ����ġ�� count ���� �۴ٸ�
					board->pos[row][col].weight = count;
				}
			}
			// �� left down
			if (row < MAX && col>0
				&& board->pos[row][col].state < 1      //���� ����ġ�� ������ ��ġ
				&& board->pos[row + 1][col - 1].state >= 1) {   //right�� ���� �ִ� ���

				count = 0;
				tempPlayer = board->pos[row + 1][col - 1].state;
				if (tempPlayer == WHITE)
					count = 0.1;
				for (i = 1; i < 5; i++) {
					if ((row + i < MAX && col - i >0) && (board->pos[row + i][col - i].state == tempPlayer))
						count++;
					else
						break;
				}

				if (board->pos[row][col].weight < count) {   // �ش� ��ġ ����ġ�� count ���� �۴ٸ�
					board->pos[row][col].weight = count;
				}
			}
			
		
			if ((board->pos[row][col].state < 1 && board->pos[row + 1][col].state == 1 && board->pos[row - 1][col].state == 1)
			|| (board->pos[row][col].state < 1 && board->pos[row + 1][col].state == 1 && board->pos[row - 1][col].state == 1)){
				count = 0;
				tempPlayer = board->pos[row + 1][col].state;
				if (tempPlayer == WHITE)
					count = 0.1;
				for (i = 1; i < 4; i++) {
					if ((row + i < MAX) && (board->pos[row + i][col].state == tempPlayer)) {
						count++;
					}
					if ((row - i > 0) && (board->pos[row - i][col].state == tempPlayer)) {   //o_oo // o_ooo  ��� (����)
						count++;
					}

				}
				if (board->pos[row][col].weight < count) {   // �ش� ��ġ ����ġ�� count ���� �۴ٸ�
					board->pos[row][col].weight = count;
				}

			}
			if ((board->pos[row][col].state < 1 && board->pos[row][col+1].state == 1 && board->pos[row][col-1].state == 1)
				|| (board->pos[row][col].state < 1 && board->pos[row][col + 1].state == 2 && board->pos[row][col - 1].state == 2)) {
				count = 0;
				tempPlayer = board->pos[row][col+1].state;
				if (tempPlayer == WHITE)
					count = 0.1;
			
				for (i = 1; i < 4; i++) {
					if ((row + i < MAX) && (board->pos[row][col+i].state == tempPlayer)) {
						count++;
					}
					if ((row - i > 0) && (board->pos[row][col-i].state == tempPlayer)) {   //o_oo // o_ooo  ��� (����)
						count++;
					}

				}
				if (board->pos[row][col].weight < count) {   // �ش� ��ġ ����ġ�� count ���� �۴ٸ�
					board->pos[row][col].weight = count;
				}
			}
			
		}
	}
}
/*
void setWeight(Board *board)
{
	for (int k = 0; k < 4; k++)
	{ //ū for�� ����
		for (int i = 0; i < MAX; i++)
			for (int j = 0; j < MAX; j++)
				board->pos[i][j].checked = false; // false�� �ʱ�ȭ

		for (int i = 0; i < MAX; i++) //19
		{
			for (int j = 0; j < MAX; j++)//19
			{
				if (board->pos[i][j].state == 1 && board->pos[i][j].checked == false)
				{	//�������̰� false �̸�
					int cnt = 0;
					int tx = i, ty = j;
					while (board->pos[tx][ty].state == 1 &&
						tx >= 0 && ty >= 0 && tx <= MAX && ty <= MAX)//������ && 0~19 ������ tx�� ty
					{
						cnt++;
						board->pos[tx][ty].checked = true;
						tx += checkpos[k][0];//-1  dx
						ty += checkpos[k][1];// 1   dy
					}
					if (i - checkpos[k][0] >= 0 && j - checkpos[k][1] >= 0 && i - checkpos[k][0] <= MAX && j - checkpos[k][1] <= MAX)
					{
						if (board->pos[i - checkpos[k][0]][j - checkpos[k][1]].state == 0 &&
							board->pos[tx + checkpos[k][0]][ty + checkpos[k][1]].state == 0) board->pos[i - checkpos[k][0]][j - checkpos[k][1]].weight *= pow(4.0, cnt * cnt); // 2.1
						else board->pos[i - checkpos[k][0]][j - checkpos[k][1]].weight *= pow(4.0, cnt * cnt); //1.8
					}
					if (tx + checkpos[k][0] >= 0 && ty + checkpos[k][1] >= 0 && tx + checkpos[k][0] <= MAX && ty + checkpos[k][1] <= MAX)
					{
						if (board->pos[i - checkpos[k][0]][j - checkpos[k][1]].state == 0 &&
							board->pos[tx + checkpos[k][0]][ty + checkpos[k][1]].state == 0) board->pos[tx][ty].weight *= pow(4.0, cnt * cnt); //2.1
						else board->pos[tx][ty].weight *= pow(4.0, cnt * cnt); //1.8
					}
				}  //������ if end

				if (board->pos[i][j].state == 2 && board->pos[i][j].checked == false)
				{	//������̰� false �̸�
					for (int l = 0; l < 8; l++)
					{
						if (i + checkpos[l][0] >= 0 && j + checkpos[l][1] >= 0 && i + checkpos[l][0] <= MAX && j + checkpos[l][1] <= MAX)
							board->pos[i + checkpos[l][0]][j + checkpos[l][1]].weight *= 2.0;  //1.08
					}

					int cnt = 0;
					int tx = i, ty = j;
					while (board->pos[tx][ty].state == 2 &&
						tx >= 0 && ty >= 0 && tx <= MAX && ty <= MAX)
					{
						cnt++;
						board->pos[tx][ty].checked = true;
						tx += checkpos[k][0];
						ty += checkpos[k][1];
					}
					if (cnt > 0)
					{
						if (i - checkpos[k][0] >= 0 && j - checkpos[k][1] >= 0 && i - checkpos[k][0] <= MAX && j - checkpos[k][1] <= MAX)
							board->pos[i - checkpos[k][0]][j - checkpos[k][1]].weight *= pow(1.2, cnt * cnt * 2);
						if (tx + checkpos[k][0] >= 0 && ty + checkpos[k][1] >= 0 && tx + checkpos[k][0] <= MAX && ty + checkpos[k][1] <= MAX)
							board->pos[tx][ty].weight *= pow(1.2, cnt * cnt * 2);
					}
				} //��� if end
			}
		}
	}//ū for�� ����
}
*/

void doPut(State state, Board *board, Point pt)
{
	board->Put(state, pt.first, pt.second);	 //Board.cpp
	
}
bool samsam(State state, Board *board, Point pt) {

	if (board->pos[pt.first + 1][pt.second].state == 2 && board->pos[pt.first - 1][pt.second].state == 2
		&& board->pos[pt.first][pt.second - 1].state == 2 && board->pos[pt.first][pt.second + 1].state == 2) {

		board->pos[pt.first][pt.second].state = BLANK;
		
		return true;
	}else{
		return false;
	}
	
}

State getWinner(Board board)
{
	int cnt, tx, ty;
	bool p1win, p2win;

	p1win = p2win = false;

	for (int i = 0; i < MAX; i++) //������ ����Ȯ��
	{
		for (int j = 0; j < MAX; j++)
		{
			if (board.pos[i][j].state == BLACK)
			{
				for (int k = 0; k < 8; k++)
				{
					cnt = 0;
					tx = i, ty = j;
					while (board.pos[tx][ty].state == BLACK &&
						tx >= 0 && ty >= 0 && tx < MAX && ty < MAX)
					{
						cnt++;
						tx += checkpos[k][0];
						ty += checkpos[k][1];
					}
					if (cnt == 5) p1win = true;
					else cnt = 0;
					if (p1win) break;
				}
			}
			if (p1win) break;
		}
		if (p1win) break;
	}
	if (p1win) return BLACK;


	for (int i = 0; i < MAX; i++)  //white �� ����
	{
		for (int j = 0; j < MAX; j++)
		{
			if (board.pos[i][j].state == WHITE)
			{
				for (int k = 0; k < 8; k++)
				{
					cnt = 0;
					tx = i, ty = j;
					while (board.pos[tx][ty].state == WHITE &&
						tx >= 0 && ty >= 0 && tx < MAX && ty < MAX)
					{
						cnt++;
						tx += checkpos[k][0];	//-1
						ty += checkpos[k][1];	//+1
					}
					if (cnt == 5) p2win = true;
					else cnt = 0;
					if (p2win) break;
				}
			}
			if (p2win) break;
		}
		if (p2win) break;
	}
	if (p2win) return WHITE;
}

