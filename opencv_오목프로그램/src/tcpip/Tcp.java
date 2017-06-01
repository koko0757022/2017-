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

	public Boolean end = true;

	public Boolean getend() {
		return this.end;
	}

	public void getend(Boolean end) {
		this.end = end;
	}

	@Override

	public void run() {

		try {
			String ip = "localhost"; // Ŭ���̾�Ʈ�� �ӽ� ���� �ּ�
			int port = 50007; // ������ ���� ��Ʈ
			Socket socket = new Socket(ip, port); // Ŭ���̾�Ʈ�� ���� ����

			BufferedReader input = new BufferedReader(new InputStreamReader(System.in));

			OutputStream out = socket.getOutputStream(); // ������ �������κ��� ����� ����
			InputStream in = socket.getInputStream(); // ������ �������κ��� �Է��� ����

			PrintWriter pw = new PrintWriter(new OutputStreamWriter(out));
			BufferedReader br = new BufferedReader(new InputStreamReader(in));

			DataOutputStream dos = new DataOutputStream(out);

			String myMsg;
			String echo = null; // �޴� �޽���
			String echo1 = null;

			while (true) {
				// dos.writeBytes(x + " , " + y);
				this.getend(false);
				myMsg = x + " " + y; // ���� �޽���
				// this.getend(false);
				pw.println(myMsg); // PrintWriter�� �̿��Ͽ� �������� ����
				pw.flush(); // ���� ����

				// ������ ���۷� �޽����� �����ϸ� �̸� ����
				echo = br.readLine(); // 0
				BoardPanel b = new BoardPanel(Integer.parseInt(echo));

				System.out.println(echo);

				if (!echo.equals(echo1)) {

					echo1 = br.readLine();
					this.getend(true);
				}
				System.out.println("tcp's return = " + echo);
			}

			// System.out.println("����: " + echo);

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public void get(int x, int y) {
		this.x = x;
		this.y = y;

	}
}