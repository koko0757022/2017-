
package Minimax;

import GUI.BoardT;

abstract class Algorithm {
	BoardT board;

	public Algorithm() {
		board = new BoardT();
	}

	public Algorithm(BoardT board) {
		this.board = board;
	}

	public static int[] bestMove() {
		return null;
	}
}
