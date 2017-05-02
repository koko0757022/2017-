/**
 *Board Panel
 * 
 * @author Tianyi
 */
package GUI;


//import Minimax.MinMaxFTz;
import org.opencv.core.Core;
import org.opencv.core.Mat;
//import org.opencv.highgui.VideoCapture;
import org.opencv.videoio.VideoCapture;
import org.opencv.videoio.Videoio;

import org.opencv.imgproc.Imgproc;
import org.opencv.core.Scalar;
import org.opencv.core.Size;
import org.opencv.core.Point;//얘랑



import Minimax.MinmaxT;
import GUI.BoardT;
import GeneticAlgorithm.GeneticAlg;

import javax.imageio.ImageIO;
import javax.swing.JPanel;
import javax.swing.JFrame;
import javax.swing.border.Border;
import javax.swing.border.LineBorder;

import java.awt.FlowLayout;
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.awt.image.DataBufferByte;
//import java.awt.Point;//얘랑 충돌해!!
import java.awt.RenderingHints;
import java.awt.Stroke;
import java.awt.TextField;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.image.BufferedImage;
import java.awt.BasicStroke;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.GridLayout;
import java.io.File;
import java.io.IOException;
import java.util.LinkedList;

import MyFrame;


public class BoardPanel extends JPanel{
	
	public static final int squareSize = 30;
	public static final int sizeX = squareSize * 19;
	public static final int sizeY = squareSize * 19;
	public static final int offset = 30;
	public boolean win = false;
	public static int winPlayer = 2;
	public static int valid = 0; //initial value
	public static boolean end = false; //not end
	//public Point last;였는데
	public static java.awt.Point last;
	public static int steps=0;
	static BoardT board;
	//BoardFTz boardf;
	public static int version=1 ;
	
	static int X=-1;
	static int Y=-1;
	boolean Black = true;
	int black = 1;
	int white = 0;
	
	BufferedImage wImage;
	BufferedImage bImage;
	BufferedImage background;
	
	public BoardPanel() {
		board = new BoardT(19, 19, black);
		//boardf = new BoardFTz(19, 19);
		//board.move(9, 9);
		String wPath = "img/white.gif";
		String bPath = "img/black.gif";
		String backgroundPath = "img/background.jpg";
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
/*
		this.addMouseListener(new MouseAdapter() {//addMouseListener는 임포트해서쓰는부분
			@Override
			public void mousePressed(MouseEvent e) {
				if (e.getButton() == 1 && end == false) {//마우스클릭 인식
					
					/*
					X = (e.getX() - squareSize/2) / squareSize;//좌표값 가공
					Y = (e.getY() - squareSize/2) / squareSize;
					//System.out.println(version);
					System.out.println("x,y : "+X+","+Y);
					
					if(board.board[X][Y] == 0)
					{
						steps++;
						valid = 1;
						if(version == 1){
							MinimaxT(X,Y);
						}
						if(version == 2){
							GAS(X,Y);
						}
						if(version == 3){
							MinimaxF(X, Y);
						}
		
					    if(board.evaluate(-1) > 500000) {
					    	winPlayer =board.currentPlayer;
					    	end = true;
					    }
					    if(board.evaluate(1) > 500000) {
					    	winPlayer = 1 - board.currentPlayer;
					    	end = true;
					    }
					}*/
/*
					repaint();
				}

			}
		});*/
	}
	
	public static int MinimaxT(int x, int y){
		board.move(x,y);	
		//Point bestMove = MinmaxT.bestMove(board);
		java.awt.Point bestMove = MinmaxT.bestMove(board);
		board.move(bestMove.x, bestMove.y);
		//last = bestMove;
		last = bestMove;
		return 1;
		
	}
	
	public int MinimaxF(int x, int y){
		board.move(x,y);
		//boardf.move(x, y);
		//MinMaxFTz minmaxF = new MinMaxFTz();
		//Point bestMoveF = minmaxF.bestPoint(boardf, Black);
		//board.move(bestMoveF.x, bestMoveF.y);
		//boardf.move(bestMoveF.x, bestMoveF.y);
		return 3;
	}
	
	public int GAS(int x, int y) {
		board.move(x, y);
		GeneticAlg ga = new GeneticAlg(board);
		java.awt.Point bestMoveG = ga.bestMove();
		board.move(bestMoveG.x, bestMoveG.y);
		return 2;
		
	}
	
	@Override
	public void paintComponent(Graphics g) {
		
		Graphics2D g2d = (Graphics2D)g;
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
        RenderingHints.VALUE_ANTIALIAS_ON);
        
		super.paintComponent(g);
		
		
		g.drawImage(background, 0 ,0, null);
		g2d.setStroke(new BasicStroke(2));
		
		
		// Draw vertical lines
		for (int i = 0; i < 19*squareSize+squareSize/2; i+=squareSize) {
			g.drawLine(i, 0, i, 19*squareSize);
		}
		// Draw horizontal lines
		for (int i = 0; i < 19*squareSize+squareSize/2; i+=squareSize) {
			g.drawLine(0, i, 19*squareSize, i);
		}
		
		// Draw  pieces
		int locX, locY;
		for(int i=0; i<board.rows; i++) {
			for(int j=0; j<board.cols; j++) {
				if(board.board[i][j] == 1) {
					locX = squareSize/2 + squareSize*i;
					locY = squareSize/2 + squareSize*j;
					g.drawImage(bImage, locX, locY, null);		
				}
				if(board.board[i][j] == -1) {
					locX = squareSize/2 + squareSize*i;
					locY = squareSize/2 + squareSize*j;
					g.drawImage(wImage, locX, locY, null);
					
				}
			}

		}
		Font defaultFont = g.getFont();
		Font blackWin = new Font(defaultFont.getFontName(),2,80);
		Font whiteWin = new Font(defaultFont.getFontName(), 2, 80);
		switch(winPlayer) {
		
		case 0: // black wins
			g.setColor(Color.red);
			g.setFont(blackWin);
			g.drawString("Black Wins!",50, 200);
			System.out.println("Total Steps: " + steps);
			break;
			
		case 1:
			g.setColor(Color.red);
			g.setFont(whiteWin);//white wins
			g.drawString("White Wins!",50,200);
			System.out.println("Total Steps: " + steps);
			break;
		}
		if(valid == 2) {
			g.drawString("Invalid Move!", 50, 50);
		}


	}

	    
	    static {
	        // Load the native OpenCV library
	        System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
	    }
	
public static void main(String[] args){ 
     // Main loop

    // Matrix for storing image
		
	JFrame frame = new JFrame("Cute Gomoku");//jframe 객체를 직접 생성
		int startX = frame.getX();
		int startY = frame.getY();
		
		int boardSize = 19*squareSize+squareSize/2;
		int frameWidth = boardSize;
		int frameLength = boardSize + offset;
		
		frame.setSize(frameWidth, frameLength);
		BoardPanel panel = new BoardPanel();//여기서 생성!!!!
		String ga = " (Genetic Algorithm)";
		String minmaxT = " (MinmaxT)";
		String minmaxF = " (MinmaxFTz)";
		//if(args.length == 1)
		//{
			//int v = Integer.parseInt(args[0]);
			//if(v==2 || v==3){
			//	version = v;
				if(version == 2){
					System.out.println("You are now running version " + version + ga);	
				}
				if(version == 3){
					System.out.println("You are now running version " + version + minmaxF);
				}
			//}
			if(version==1) {
				//version = v;
				System.out.println("You are now running version " + version + minmaxT);
			}
	//	}
	//	else{
	//		version = 1;
		//	System.out.println("You are now running version " + version + minmaxT);
		//}
		Border menuBorder = new LineBorder(Color.BLACK);
		panel.setSize(boardSize, boardSize);
		panel.setBorder(menuBorder);
		frame.add(panel);
		frame.setResizable(false);
		frame.setVisible(true);
		panel.repaint();
		frame.addWindowListener(new WindowAdapter(){
			@Override
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});
		
		//opevcv start:이부분이 Cute Gomoku보다 위에있으면 안돌아갔음
		VideoCapture cap = new VideoCapture(1);
		cap.set(Videoio.CAP_PROP_FRAME_WIDTH, 400);
	    cap.set(Videoio.CAP_PROP_FRAME_HEIGHT, 400);
	    
		if (!cap.isOpened()) {
	        System.exit(-1);
	    }
		
		Mat image = new Mat();  //input image
	    Mat image_pre = new Mat();
	    Mat image_diff = new Mat();
	    Mat circles = new Mat();
	    Mat gray = new Mat();
	    
	    MyFrame ourframe =  new MyFrame();
	    MyFrame imageinput =  new MyFrame();
	    ourframe.setVisible(true);
	    imageinput.setVisible(true);
	    ourframe.alwaysOnTop();
	    cap.read(image);

	    image_pre = image.clone();
		
		while(true) {
	        // Read current camera frame into matrix
	        try {
	              Thread.sleep(500);
	        } catch (InterruptedException e) { }

	    
	        cap.read(image);
	        Core.absdiff(image_pre, image, image_diff); //차영상
	         
	         Imgproc.cvtColor(image_diff, gray, Imgproc.COLOR_RGB2GRAY);
	         
	         Imgproc.GaussianBlur(gray, gray, new Size (9,9), 2, 2);      
	         
	         Imgproc.HoughCircles(gray, circles, Imgproc.CV_HOUGH_GRADIENT, 1, 10, 200, 25, 7, 50); 

	         if (circles.cols() > 0)
	            for (int x = 0; x < circles.cols(); x++) {
	               double vCircle[] = circles.get(0, x);

	               if (vCircle == null)
	                  break;

	               Point pt = new Point(Math.round(vCircle[0]), Math.round(vCircle[1]));
	               int radius = (int) Math.round(vCircle[2]);

	               
	               Imgproc.circle(image_diff, pt, radius, new Scalar(0, 255, 0) ,2); //원그리기
	               
	               System.out.println("orgin x,y: "+pt.x+","+pt.y);
	               
	               int px = 53; //0,0놨을때 픽셀값?
	               int py = 22;
	               
	               X = (int) ((pt.x-px+9)/19); //19는 한칸의 길이
	               Y = (int) ((pt.y-py+9)/19);//+9는 반올림역할
	               
	              // System.out.println("x,y : "+X+","+Y);
	               
	               X=X%20;
	               //Y=Y%10;
	               Y=Y%20;
	               System.out.println("x,y : "+X+","+Y);
	               
	               if(board.board[X][Y] == 0)
					{
						steps++;
						valid = 1;
						if(version == 1){
							MinimaxT(X,Y);
						}
						
					    if(board.evaluate(-1) > 500000) {
					    	winPlayer =board.currentPlayer;
					    	end = true;
					    }
					    if(board.evaluate(1) > 500000) {
					    	winPlayer = 1 - board.currentPlayer;
					    	end = true;
					    }
					}
	               //java.awt.Component.repaint();
	               
	               frame.repaint();

	            }
	         
	         
	      
	      if (!image.empty()) { // 영상 출력 부분
	            
	            //frame.render(image);
	    	  ourframe.render(image_diff);
	    	  imageinput.render(image);
	            
	         } else {
	            System.out.println("No captured frame -- camera disconnected");
	         }
	         if (circles.cols() == 1) {
	            image_pre = image.clone();// 차영상 복사
	         }
	    }//while(true) end
	}
    

}
