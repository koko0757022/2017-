#pragma once

#include <utility>  // pair사용
#define MAX 19

typedef enum {BLANK, WHITE, BLACK} State; // State 에 3가지만 들어간다.
typedef std::pair<int, int> Point;  // Point로 재정의해서 x,y를 받는다.

struct Pos
{
	State state;
	bool checked;
	double weight;	
	
};

class Board
{
public:
	Pos pos[MAX][MAX] = { BLANK, false, 0 };  //pos 초기값 할당
public:
	void Put(State state, int x, int y);
};