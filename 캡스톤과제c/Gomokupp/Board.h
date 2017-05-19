#pragma once

#include <utility>  // pair���
#define MAX 19

typedef enum {BLANK, WHITE, BLACK} State; // State �� 3������ ����.
typedef std::pair<int, int> Point;  // Point�� �������ؼ� x,y�� �޴´�.

struct Pos
{
	State state;
	bool checked;
	double weight;	
	
};

class Board
{
public:
	Pos pos[MAX][MAX] = { BLANK, false, 0 };  //pos �ʱⰪ �Ҵ�
public:
	void Put(State state, int x, int y);
};