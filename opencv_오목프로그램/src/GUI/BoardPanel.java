
package GUI;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
//import java.awt.Point;//��� �浹��!!
import java.awt.RenderingHints;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
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
import org.opencv.core.Core;
import org.opencv.core.Mat;
import org.opencv.core.Point;//���
import org.opencv.core.Scalar;
import org.opencv.core.Size;
import org.opencv.imgproc.Imgproc;
//import org.opencv.highgui.VideoCapture;
import org.opencv.videoio.VideoCapture;
import org.opencv.videoio.Videoio;

import Minimax.MinmaxT;
import tcpip.Tcp;

public class BoardPanel extends JPanel {

	public static final int squareSize = 30;
	public static final int sizeX = squareSize * 19;
	public static final int sizeY = squareSize * 19;
	public static final int offset = 30;
	public boolean win = false;
	public static int winPlayer = 2;
	public static int valid = 0; // initial value
	public static boolean end = false; // not end
	// public Point last;���µ�
	public static java.awt.Point last;
	public static int steps = 0;
	static BoardT board;
	// BoardFTz boardf;
	public static int version = 1;
	public static String strx;
	public static String stry;

	static Tcp t = new Tcp();

	public static int X = -1;
	public static int Y = -1;
	public int get_end = 1; // 1�� ����
	boolean Black = true;

	int black = 1;
	int white = 0;

	BufferedImage wImage;
	BufferedImage bImage;
	BufferedImage background;

	public void get_return(int end) {
		this.get_end = end;
	}

	public int set_return() {
		return get_end;
	}

	public BoardPanel(int end) {
		this.get_end = end;
	}

	public BoardPanel() {
		board = new BoardT(19, 19, black);

		String wPath = "C:/Users/koko0/workspace/Gomoku-master/Gomoku-master/img/white.gif";
		String bPath = "C:/Users/koko0/workspace/Gomoku-master/Gomoku-master/img/black.gif";
		String backgroundPath = "C:/Users/koko0/workspace/Gomoku-master/Gomoku-master/img/background.jpg";

		try {
			wImage = ImageIO.read(new File(wPath));
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		try {
			bImage = ImageIO.read(new File(bPath));
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		try {
			background = ImageIO.read(new File(backgroundPath));
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		// this.addMouseListener(new MouseAdapter() {
		// @Override
		// public void mousePressed(MouseEvent e) {
		//
		// if (e.getButton() == 1 && end == false) {
		// System.out.println("x = "+e.getX());
		// }
		// }
		// });
		this.addKeyListener(new KeyListener() {

			@Override
			public void keyTyped(KeyEvent e) {
				// TODO Auto-generated method stub

			}

			@Override
			public void keyReleased(KeyEvent e) {
				// TODO Auto-generated method stub

			}

			@Override
			public void keyPressed(KeyEvent e) {
				String str;
				int keycode = e.getKeyCode();
				switch (keycode) {
				case KeyEvent.VK_UP:
					// updirect = true;
					break;
				case KeyEvent.VK_DOWN:
					// downdirect = true;
					break;
				case KeyEvent.VK_LEFT:
					// leftdirect = true;
					break;
				case KeyEvent.VK_RIGHT:
					// rightdirect = true;
					break;
				}

				str = "KEY Press : " + e.getKeyChar();
				System.out.println(str);

			}
		});
	}

	public static int MinimaxT(int x, int y) {

		board.move(x, y);
		// Point bestMove = MinmaxT.bestMove(board);
		java.awt.Point bestMove = MinmaxT.bestMove(board);

		System.out.println("white x,y : " + bestMove.x + "," + bestMove.y);
		// ��ǻ�Ͱ� �δ� ���� ��ǥ
		t.get(bestMove.x, bestMove.y); // �ٵϵ��� ��ǥ�� tcp������� �Ѱ��ش�.
		new Thread(t).start();
		board.move(bestMove.x, bestMove.y);
		last = bestMove;

		return 1;
	}

	@Override
	public void paintComponent(Graphics g) {

		Graphics2D g2d = (Graphics2D) g;
		g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

		super.paintComponent(g);

		g.drawImage(background, 0, 0, null);
		g2d.setStroke(new BasicStroke(2));

		// Draw vertical lines
		for (int i = 0; i < 19 * squareSize + squareSize / 2; i += squareSize) {
			g.drawLine(i, 0, i, 19 * squareSize);
		}
		// Draw horizontal lines
		for (int i = 0; i < 19 * squareSize + squareSize / 2; i += squareSize) {
			g.drawLine(0, i, 19 * squareSize, i);
		}

		// Draw pieces
		int locX, locY;
		for (int i = 0; i < board.rows; i++) {
			for (int j = 0; j < board.cols; j++) {
				if (board.board[i][j] == 1) {
					locX = squareSize / 2 + squareSize * i;
					locY = squareSize / 2 + squareSize * j;
					g.drawImage(bImage, locX, locY, null);
				}
				if (board.board[i][j] == -1) {
					locX = squareSize / 2 + squareSize * i;
					locY = squareSize / 2 + squareSize * j;
					g.drawImage(wImage, locX, locY, null);
				}
			}
		}
		Font defaultFont = g.getFont();
		Font blackWin = new Font(defaultFont.getFontName(), 2, 80);
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

	static {
		// Load the native OpenCV library
		System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
	}

	public static void main(String[] args) {

		JFrame frame = new JFrame("Cute Gomoku");// jframe ��ü�� ���� ����

		int boardSize = 19 * squareSize + squareSize / 2;
		int frameWidth = boardSize;
		int frameLength = boardSize + offset;

		frame.setSize(frameWidth, frameLength);
		BoardPanel panel = new BoardPanel();// ���⼭ ����!!!!
		String ga = " (Genetic Algorithm)";
		String minmaxT = " (MinmaxT)";
		String minmaxF = " (MinmaxFTz)";

		// if (version == 2) {
		// System.out.println("You are now running version " + version + ga);
		// }
		// if (version == 3) {
		// System.out.println("You are now running version " + version +
		// minmaxF);
		// }
		// // }
		if (version == 1) {
			// version = v;
			System.out.println("You are now running version " + version + minmaxT);
		}

		Border menuBorder = new LineBorder(Color.BLACK); // ����
		panel.setSize(boardSize, boardSize);
		panel.setBorder(menuBorder);
		frame.add(panel); // frame(panel)
		frame.setResizable(false);
		frame.setVisible(true);
		panel.repaint();

		frame.addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});

		// opevcv start:�̺κ��� Cute Gomoku���� ���������� �ȵ��ư���
		VideoCapture cap = new VideoCapture(1);
		cap.set(Videoio.CAP_PROP_FRAME_WIDTH, 400);
		cap.set(Videoio.CAP_PROP_FRAME_HEIGHT, 400);

		if (!cap.isOpened()) {
			System.exit(-1); // ī�޶� �ȵǸ� ����
		}

		Mat image = new Mat(); // input image
		Mat image_pre = new Mat();// ���� image
		Mat image_diff = new Mat(); // image
		Mat circles = new Mat();
		Mat gray = new Mat();

		// Mat tmp1 = new Mat(gray.width(), gray.height(), CvType.CV_8UC1);
		// Imgproc.GaussianBlur(gray, gray, new Size (9,9), 2, 2);//

		MyFrame diffframe = new MyFrame();// ���� ����
		MyFrame imageinput = new MyFrame();// ���� ����
		MyFrame sampleframe = new MyFrame();// �׽�Ʈ��

		diffframe.setVisible(true);
		imageinput.setVisible(true);

		// sampleframe.setVisible(true);

		diffframe.

				alwaysOnTop(); // �������� �ö����
		if (1 == panel.set_return()) {
		}

		cap.read(image); // image�б�

		image_pre = image.clone();

		for (;;) {
			// Read current camera frame into matrix
			// try {
			// //Thread.sleep(500);
			// } catch (InterruptedException e) {
			// }
			if (1 == panel.set_return()) {
			}
			cap.read(image);
			BufferedImage tmp = new BufferedImage(image.width(), image.height(), BufferedImage.TYPE_BYTE_GRAY);
			Core.absdiff(image_pre, image, image_diff); // ���� ���� ���� �������
														// diff������

			// Imgproc.bilateralFilter(image_diff, gray, 15, 80, 80);
			// Imgproc.cvtColor(image_diff, gray, Imgproc.COLOR_RGB2GRAY);//
			// ȭ��
			Imgproc.cvtColor(image, gray, Imgproc.COLOR_RGB2GRAY);
			// ��麯ȯ

			Imgproc.GaussianBlur(gray, gray, new Size(5, 5), 2, 2);//

			Imgproc.erode(gray, gray, Imgproc.getStructuringElement(Imgproc.MORPH_RECT, new Size(9, 9)));
			Imgproc.dilate(gray, gray, Imgproc.getStructuringElement(Imgproc.MORPH_RECT, new Size(9, 9)));

			Imgproc.HoughCircles(gray, circles, Imgproc.CV_HOUGH_GRADIENT, 1, 10, 170, 25, 7, 15);// ����
																									// ã���ش�

			if (circles.cols() > 0)
				for (int x = 0; x < circles.cols(); x++) {
					double vCircle[] = circles.get(0, x);// �� ������� ã��
					System.out.println("circles.col = " + circles.cols());

					if (vCircle == null)
						break;
					// vCircle[0]-��ǥ vCircle[2]=������ �ڵ���
					Point pt = new Point(Math.round(vCircle[0]), Math.round(vCircle[1]));// ��������
					int radius = (int) Math.round(vCircle[2]);// ����������

					Imgproc.circle(gray, pt, radius, new Scalar(0, 255, 255), 2); // ���׸���

					System.out.println("orgin x,y: " + pt.x + "," + pt.y);

					// int px = 49; // 0,0������ �ȼ���?
					// int py = 77;
					//
					// X = (int) ((pt.x - px + 9) / 19); // 19�� ��ĭ�� ����
					// Y = (int) ((pt.y - py + 9) / 19);// +9�� �ݿø�����
					//
					// // System.out.println("x,y : "+X+","+Y);
					// // ���������� ����ұ� Math.abs()ó��??
					//
					// X = X % 20;
					// // Y=Y%10;
					// Y = Y % 20;
					System.out.println("x,y : " + X + "," + Y);
					if (X < 0)
						continue;
					if (Y < 0)
						continue;

					if (board.board[X][Y] == 0) {
						steps++;
						valid = 1;
						if (version == 1) {
							MinimaxT(X, Y);
						}

						if (board.evaluate(-1) > 500000) {
							winPlayer = board.currentPlayer;
							end = true;
						}
						if (board.evaluate(1) > 500000) {
							winPlayer = 1 - board.currentPlayer;
							end = true;
						}
					}

					frame.repaint();
				}

			if (!image.empty()) { // ���� ��� �κ�
				diffframe.render(gray);
				// diffframe.render(image_diff);
				imageinput.render(image);
				// sampleframe.render(gray);

			} else {
				System.out.println("No captured frame -- camera disconnected");
			}
			if (circles.cols() == 1) {
				image_pre = image.clone();// ������ ����
			}
		} // while(true) end

	}
}
