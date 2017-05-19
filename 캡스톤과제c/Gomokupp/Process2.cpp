#include "Process.h"
#include <cmath>


int x[20][5] = {
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,1,2,3,4},
	{0,-1,-2,-3,-4},
	{1,0,-1,-2,-3},
	{2,-1,0,1,2},
	{3,2,1,0,-1},
	{4,3,2,1,0},
	{0,1,2,3,4},
	{-1,0,1,2,3},
	{-1,0,1,2,3},
	{-2,-1,0,1,2},
	{ -2,-1,0,1,2 },
	{-3,-2,-1,0,1},
	{ -3,-2,-1,0,1 },
	{-4,-3,-2,-1,0}, 
	{ -4,-3,-2,-1,0 }

};
int y[20][5] = {
	{0,-1,-2,-3,-4},
	{1,0,-1,-2,-3},
	{2,1,0,-1,-2},
	{3,2,1,0,-1},
	{4,3,2,1,0},
	{0,1,2,3,4},
	{0,1,2,3,4},
	{-1,0,1,2,3},
	{-2,-1,0,1,2},
	{-3,-2,-1,0,1},
	{-4,-3,-2,-1,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{-1,0,1,2,3},
	{0,0,0,0,0},
	{-2,-1,0,1,2},
	{0,0,0,0,0},
	{-3,-2,-1,0,1},
	{0,0,0,0,0},
	{-4,-3,-2,-1,0}
};



void setWeight(Board *board , Point pt) {
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			board->pos[i][j].checked = false; // false로 초기화

	for (int i = 0;i<20;i++) {
		int nSum = 0;
		for (int j = 0;j<5;j++) {
			int dx = x[i][j];
			int dy = y[i][j];
			if (board->pos[pt.first+dx][pt.second+dy].state == 1 ) {
				
				nSum++;
			}			
		}
		
		printf("%d\n",nSum);
	}
}

/*
void setWeight(Board *board)
{
	for (int k = 0; k < 4; k++)
	{
		for (int i = 0; i < MAX; i++)
			for (int j = 0; j < MAX; j++)
				board->pos[i][j].checked = false; // false로 초기화

		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
			{
				if (board->pos[i][j].state == 1 && board->pos[i][j].checked == false)
				{	//검은돌이고 false 이면
					int cnt = 0;
					int tx = i, ty = j;
					while (board->pos[tx][ty].state == 1 &&
						tx >= 0 && ty >= 0 && tx <= MAX && ty <= MAX)
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
				}  //검은색 if end

				if (board->pos[i][j].state == 2 && board->pos[i][j].checked == false)
				{	//흰색돌이고 false 이면
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
					if (cnt > 2)
					{
						if (i - checkpos[k][0] >= 0 && j - checkpos[k][1] >= 0 && i - checkpos[k][0] <= MAX && j - checkpos[k][1] <= MAX)
							board->pos[i - checkpos[k][0]][j - checkpos[k][1]].weight *= pow(1.2, cnt * cnt * 2);
						if (tx + checkpos[k][0] >= 0 && ty + checkpos[k][1] >= 0 && tx + checkpos[k][0] <= MAX && ty + checkpos[k][1] <= MAX)
							board->pos[tx][ty].weight *= pow(1.2, cnt * cnt * 2);
					}
				} //흰색 if end
			}
		}
	}
}

*/

void doPut(State state, Board *board, Point pt)
{
	board->Put(state, pt.first, pt.second);	 //Board.cpp

}
/*
State getWinner(Board board)
{
	int cnt, tx, ty;
	bool p1win, p2win;

	p1win = p2win = false;

	for (int i = 0; i < MAX; i++)
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


	for (int i = 0; i < MAX; i++)
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
						tx += checkpos[k][0];
						ty += checkpos[k][1];
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
*/