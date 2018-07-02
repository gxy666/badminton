package badminton;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.net.URL;

import javax.swing.*;

@SuppressWarnings("serial")
public class ControlPanel extends JPanel
{
	private JButton start = new JButton(); 
	URL url = ControlPanel.class.getResource("/"+"start.png");
	private ImageIcon startbackgronud = new ImageIcon(url);
	FlowLayout bd = new FlowLayout();
	boolean ifmusicstart = false;
	ControlPanel()
	{
		this.setBackground(Color.YELLOW);
		this.setPreferredSize(new Dimension(1000,100));
		start.setEnabled(true);
		start.setIcon(startbackgronud);
		start.setPreferredSize(new Dimension(140,70));
		start.addActionListener(new ButtonListener());
		this.setLayout(bd);
		this.add(start);
	}
	private class ButtonListener implements ActionListener
	{
		public void actionPerformed(ActionEvent arg0) 
		{
			Main1.mainpanel.ifstart = true;
			if(!ifmusicstart)
			{
				ShowPanel.musicthread.start();
				ifmusicstart = true;
			}
			else
			{
				ShowPanel.bgm.changetobgm();
			}
			Main1.mainpanel.ifserve = true;
			Main1.mainpanel.renewscore();
			Main1.mainpanel.repaint();
			Main1.mainpanel.requestFocus();
			Main1.mainpanel.refresh();
		}
	}
}
