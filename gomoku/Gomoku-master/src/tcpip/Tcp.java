package tcpip;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;

import GUI.BoardPanel;

public class Tcp extends Thread {
	int x, y;
	
	
	@Override
	public void run() {

		try {
			String ip = "localhost"; // 클라이언트의 임시 접속 주소
			int port = 50007; // 접속할 서버 포트
			Socket socket = new Socket(ip, port); // 클라이언트의 소켓 생성

			BufferedReader input = new BufferedReader(new InputStreamReader(System.in));

			OutputStream out = socket.getOutputStream(); // 서버의 소켓으로부터 출력을 받음
			InputStream in = socket.getInputStream(); // 서버의 소켓으로부터 입력을 받음

			PrintWriter pw = new PrintWriter(new OutputStreamWriter(out));
			BufferedReader br = new BufferedReader(new InputStreamReader(in));

			DataOutputStream dos = new DataOutputStream(out);

			String myMsg;
			String echo = null; // 받는 메시지

			// while (true) {
			//
			// dos.writeBytes("sefsef");
			// echo = br.readLine(); // 서버가 버퍼로 메시지를 전달하면 이를 읽음
			// // System.out.println("서버: " + echo);
			//
			// }
			while(true){
				
				//dos.writeBytes(x + " , " + y);
			
				myMsg = x +" "+ y; // 전달 메시지
				pw.println(myMsg); // PrintWriter를 이용하여 서버에게 전달
				pw.flush(); // 버퍼 비우기

				echo = br.readLine(); // 서버가 버퍼로 메시지를 전달하면 이를 읽음
				//System.out.println("서버: " + echo);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public void get(int x, int y) {
		this.x = x;
		this.y = y;
	}
	
	
}
