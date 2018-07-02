package badminton;

import java.awt.BorderLayout;
import java.awt.Color;
import javax.swing.*;

public class Main1 {

	 
	static JFrame MyFrame = new JFrame("Matchstick Men Play Badminton!!");
	static JPanel bigpanel = new JPanel();
	static ControlPanel bottom = new ControlPanel();
	static ShowPanel mainpanel = new ShowPanel();
	@SuppressWarnings("static-access")
	public static void main(String[] args) 
	{	
		MyFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		BorderLayout bd = new BorderLayout();
		bigpanel.setLayout(bd);
		bigpanel.add(bottom,bd.SOUTH);
		bigpanel.add(mainpanel,bd.NORTH);
		mainpanel.setBorder(BorderFactory.createLineBorder(Color.black,2));
		bottom.setBorder(BorderFactory.createLineBorder(Color.black,2));
		MyFrame.getContentPane().add(bigpanel);
		MyFrame.setResizable(false);
		MyFrame.pack();
		MyFrame.setVisible(true);
	}
}
