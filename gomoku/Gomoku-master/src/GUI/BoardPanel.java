/**
 *Board Panel
 * 
 * @author Tianyi
 */
package GUI;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.RenderingHints;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.Border;
import javax.swing.border.LineBorder;

//import Minimax.MinMaxFTz;
import Minimax.MinmaxT;
import tcpip.Tcp;

public class BoardPanel extends JPanel {

	public static final int squareSize = 30;
	public static final int sizeX = squareSize * 19;
	public static final int sizeY = squareSize * 19;
	public static final int offset = 30;
	public boolean win = false;
	public int winPlayer = 2;
	public int valid = 0; // initial value
	public boolean end = false; // not end
	public Point last;
	public int steps = 0;
	BoardT board;  //BoardT !!!
	public static int version = 1;

	public int X;
	public int Y;
	public int X1;
	public int Y1;
	boolean Black = true;
	int black = 1; // 우리가 두는 돌
	int white = 0;
	
	Tcp t;
	
	BufferedImage wImage;
	BufferedImage bImage;
	BufferedImage background; // image 집어넣기
	
	public BoardPanel() { // start BoardPanel()
		board = new BoardT(19, 19, black); // black = 1
		t= new Tcp();
		String wPath = "C:/Users/koko0/workspace/Gomoku-master/Gomoku-master/img/white.gif";
		String bPath = "C:/Users/koko0/workspace/Gomoku-master/Gomoku-master/img/black.gif";
		String backgroundPath = "C:/Users/koko0/workspace/Gomoku-master/Gomoku-master/img/background.jpg";

		try {
			wImage = ImageIO.read(new File(wPath));
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		} // 흰돌

		try {
			bImage = ImageIO.read(new File(bPath));
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		} // 검은돌

		try {
			background = ImageIO.read(new File(backgroundPath));
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		} // 바둑판
		
		this.addMouseListener(new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent e){
				
				if (e.getButton() == 1 && end == false) {
				
					X = (e.getX() - squareSize / 2) / squareSize; // X 좌표
					Y = (e.getY() - squareSize / 2) / squareSize; // Y 좌표
					
					if (board.board[X][Y] == 0) // 돌이 없으면..
					{
						steps++;
						valid = 1;
						if (version == 1) {
							MinimaxT(X, Y);
							
						}

						if (board.evaluate(-1) > 500000) { // board는 boardT
							winPlayer = board.currentPlayer;

							end = true;
						}
						if (board.evaluate(1) > 500000) {
							winPlayer = 1 - board.currentPlayer;
							end = true;
						}
					}

					repaint();
				}
			}
		});
	}// end BoardPanel()

	public int MinimaxT(int x, int y){ // 현재 좌표를 받는다.
		
		board.move(x, y); // hashset에 다 저장이 되어있는 상태이다.//사람이 둔 상태
		Point bestMove = MinmaxT.bestMove(board); //board판을 집어넣는다.//로봇이 둘 최고의 위치 결정
		board.move(bestMove.x, bestMove.y);		
		t.get(bestMove.x, bestMove.y);
		new Thread(t).start();
		
		X1 = bestMove.x;
		Y1 = bestMove.y;
		
		return 1;
	}

	@Override
	public void paintComponent(Graphics g) {

		// 2d
		Graphics2D g2d = (Graphics2D) g;
		g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

		super.paintComponent(g);

		g.drawImage(background, 0, 0, null); // 그림그리기
		g2d.setStroke(new BasicStroke(2)); // 선 굵게

		// Draw vertical lines
		for (int i = 0; i < 19 * squareSize + squareSize / 2; i += squareSize) {
			g.drawLine(i, 0, i, 19 * squareSize);
		}
		// Draw horizontal lines
		for (int i = 0; i < 19 * squareSize + squareSize / 2; i += squareSize) {
			g.drawLine(0, i, 19 * squareSize, i);
		}

		// 바둑돌 그리기
		int locX, locY;
		for (int i = 0; i < board.rows; i++) {
			for (int j = 0; j < board.cols; j++) {
				if (board.board[i][j] == 1) { // black
					locX = squareSize / 2 + squareSize * i;
					locY = squareSize / 2 + squareSize * j;
					g.drawImage(bImage, locX, locY, null);
				}
				if (board.board[i][j] == -1) {// white
					locX = squareSize / 2 + squareSize * i;
					locY = squareSize / 2 + squareSize * j;
					g.drawImage(wImage, locX, locY, null);
				}
			}
		}
		
		Font defaultFont = g.getFont();
		Font blackWin = new Font(defaultFont.getFontName(), 2, 80); // 폰트조절
		Font whiteWin = new Font(defaultFont.getFontName(), 2, 80);
		switch (winPlayer) {

		case 0: // black wins
			g.setColor(Color.red);
			g.setFont(blackWin);
			g.drawString("Black Wins!", 50, 200);
			System.out.println("Total Steps: " + steps);
			break;

		case 1:
			g.setColor(Color.red);
			g.setFont(whiteWin);// white wins
			g.drawString("White Wins!", 50, 200);
			System.out.println("Total Steps: " + steps);
			break;
		}
		if (valid == 2) {
			g.drawString("Invalid Move!", 50, 50);
		}
	}

	public static void main(String[] args) throws Exception {
		
		JFrame frame = new JFrame("Cute Gomoku");

		int boardSize = 19 * squareSize + squareSize / 2;
		int frameWidth = boardSize;
		int frameLength = boardSize + offset;

		frame.setSize(frameWidth, frameLength);

		BoardPanel panel = new BoardPanel(); // BoardPanel 초기 생성자
		
		String ga = " (Genetic Algorithm)";
		String minmaxT = " (MinmaxT)";
		String minmaxF = " (MinmaxFTz)";

		if (version == 1) {
			System.out.println("You are now running version " + version + minmaxT);
		}

		Border menuBorder = new LineBorder(Color.BLACK);
		panel.setSize(boardSize, boardSize);
		panel.setBorder(menuBorder);
		frame.add(panel);
		frame.setResizable(false);
		frame.setVisible(true);
		panel.repaint();		
		
		frame.addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});
	}
}
