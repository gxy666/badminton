package badminton;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.net.URL;

import javax.swing.*;

@SuppressWarnings("serial")
public class ShowPanel extends JPanel
{
	URL backgroundurl = ShowPanel.class.getResource("/"+"background.jpg");
	URL playericonurl = ShowPanel.class.getResource("/"+"people1.png");
	URL aiiconurl = ShowPanel.class.getResource("/"+"people2.png");
	URL ballurl = ShowPanel.class.getResource("/"+"羽毛球h.png");
	URL victoryurl = ShowPanel.class.getResource("/"+"victory.jpg");
	URL loseurl = ShowPanel.class.getResource("/"+"lose.jpg");
	private ImageIcon background = new ImageIcon(backgroundurl);
	private ImageIcon playericon = new ImageIcon(playericonurl);
	private ImageIcon aiicon = new ImageIcon(aiiconurl);
	private ImageIcon ball = new ImageIcon(ballurl);
	private ImageIcon victory = new ImageIcon(victoryurl);
	private ImageIcon lose = new ImageIcon(loseurl);
	URL[] pat = new URL[13];
	JLabel playerscore = new JLabel("0",JLabel.CENTER);
	JLabel aiscore = new JLabel("0",JLabel.CENTER);
	Integer playerscorenum = 0;		Integer aiscorenum = 0;
	static Music bgm = new Music();
	static Thread musicthread = new Thread(bgm);
	public boolean ifstart = false;
	public boolean ifserve = true;
	private boolean iftoai = true;
	private final int balldertxai = 68;			
	private final int balldertyai = -45;
	private final int balldertxplayer = -18;	
	private final int balldertyplayer = -45;
	private final int patdertxai = 68;			
	private final int patdertxplayer = 2;
	private final int finishscore = 11;
	private final double f = 0.008;//阻力系数
	private PlayerPeople player = new PlayerPeople();
	private AIPlayer ai = new AIPlayer();
	private ball b = new ball(player.locate,player.y);
	private Key k = new Key();
	private int delay = 8;
	private Timer balltimer  = new Timer(delay,new ReboundListener());
	private Timer aitimer = new Timer(delay,new AiListener());
	private Timer playerpattimer = new Timer(delay,new PpatListener());
	private Timer aipattimer = new Timer(delay,new ApatListener());
	ImageIcon[] image = new ImageIcon[13];
	int i = 0,j = 12;	boolean ifaibeat = false;boolean ifspace = false;
	boolean iftoa = true;		boolean iftop = true;
	public void refresh()
	{
		ifserve = true;
		iftoai = true;
		ifaibeat = false;
		ifspace = false;
		iftoa = true;
		iftop = true;
	}
	ShowPanel()
	{
		pat[0] = ShowPanel.class.getResource("/"+"pat6.png");
		pat[1] = ShowPanel.class.getResource("/"+"pat5.png");
		pat[2] = ShowPanel.class.getResource("/"+"pat4.png");
		pat[3] = ShowPanel.class.getResource("/"+"pat3.png");
		pat[4] = ShowPanel.class.getResource("/"+"pat2.png");
		pat[5] = ShowPanel.class.getResource("/"+"pat1.png");
		pat[6] = ShowPanel.class.getResource("/"+"patmiddle.png");
		pat[7] = ShowPanel.class.getResource("/"+"pat7.png");
		pat[8] = ShowPanel.class.getResource("/"+"pat8.png");
		pat[9] = ShowPanel.class.getResource("/"+"pat9.png");
		pat[10] = ShowPanel.class.getResource("/"+"pat10.png");
		pat[11] = ShowPanel.class.getResource("/"+"pat11.png");
		pat[12] = ShowPanel.class.getResource("/"+"pat12.png");
		image[0] = new ImageIcon(pat[0]);
		image[1] = new ImageIcon(pat[1]);
		image[2] = new ImageIcon(pat[2]);
		image[3] = new ImageIcon(pat[3]);
		image[4] = new ImageIcon(pat[4]);
		image[5] = new ImageIcon(pat[5]);
		image[6] = new ImageIcon(pat[6]);
		image[7] = new ImageIcon(pat[7]);
		image[8] = new ImageIcon(pat[8]);
		image[9] = new ImageIcon(pat[9]);
		image[10] = new ImageIcon(pat[10]);
		image[11] = new ImageIcon(pat[11]);
		image[12] = new ImageIcon(pat[12]);
		this.setPreferredSize(new Dimension(1000,600));
		this.setLayout(null);
		this.addKeyListener(k);
	}
	public void paintComponent(Graphics page)
	{
		background.paintIcon(this,page,0,0);
		aiscore.setBounds(500,5,300,100);
		aiscore.setFont(new Font("宋体",Font.BOLD,64));
		playerscore.setBounds(200,5,300,100);
		playerscore.setFont(new Font("宋体",Font.BOLD,64));
		this.add(aiscore);
		this.add(playerscore);
		if(ifstart)
		{

			playericon.paintIcon(this,page,player.locate,player.y);
			aiicon.paintIcon(this,page,ai.locate,ai.y);
			if(iftoai)
			{
				if(ifserve)
				{
					b.x = player.locate;
					b.y = player.y;
					ifaibeat = false;
					ifspace = false;
					ball.paintIcon(this,page,b.x+balldertxplayer,b.y+balldertyplayer);
					this.drawpat(page,i,player.locate+patdertxplayer);
					this.drawpat(page,j,ai.locate+patdertxai);
				}
				else
				{
					ball.paintIcon(this,page,b.x+balldertxplayer,b.y+balldertyplayer);
					this.drawpat(page,i,player.locate+patdertxplayer);
					this.drawpat(page,j,ai.locate+patdertxai);
					if(b.y>421&&b.vy<0)
					{
						aipattimer.start();
						this.drawpat(page,j,ai.locate+patdertxai);
						if(b.y>438+20-image[j].getIconHeight()&&b.y<438-image[j].getIconHeight()+120)
							if(b.x>ai.locate+patdertxai+40-image[j].getIconWidth()&&b.x<ai.locate+patdertxai-image[j].getIconWidth()+100)
							{
								if(!ifaibeat) 
								{
									b.collisiontopat(j,iftoai);
									b.renewceiling();
									b.renewwall();
									ifaibeat = true;
									iftoai = false;
								}
							}
					}
					if(b.y<200)
					{
						b.collisiontoceiling();
					}
					if(b.x>940)
					{
						b.collisiontowall();
					}
					if(b.x<60)
					{
						b.collisiontowall();
					}
					if(b.x>500&&b.x<550)
					{
						if(b.y>500)
							b.collisiontonet();
					}
					if(b.y>550)
					{
						balltimer.stop();
						b.renewceiling();
						b.renewwall();
						b.renew();
						player.renew();
						ai.renew();
						aitimer.stop();
						ifaibeat = false;
						if(b.x>500)
						{
							playerscorenum++;
							playerscore.setText(playerscorenum.toString());
							if(playerscorenum==finishscore)
							{
								bgm.changetovictory();
							}
							iftoai = true;
							b.x = player.locate;
							b.y = player.y;
						}
						else
						{
							aiscorenum++;
							aiscore.setText(aiscorenum.toString());
							if(aiscorenum==finishscore)
							{
								bgm.changetolose();
							}
							b.x = ai.locate;
							b.y = ai.y;	
							iftoai = false;
						}
						try 
						{
							Thread.sleep(500);
						}
						catch (InterruptedException e) 
						{
							e.printStackTrace();
						}
						ifserve = true;
						repaint();
					}
				}
			}
			else
			{
				if(ifserve)
				{
					b.x = ai.locate;
					b.y = ai.y;
					b.renewa();
					ifaibeat = false;
					ifspace = false;
					ball.paintIcon(this,page,b.x+balldertxai,b.y+balldertyai);
					this.drawpat(page,i,player.locate+patdertxplayer);
					this.drawpat(page,j,ai.locate+patdertxai);
					aipattimer.start();
					balltimer.start();
					ifserve = false;
				}
				else
				{
					ball.paintIcon(this,page,b.x+balldertxplayer,b.y+balldertyplayer);
					this.drawpat(page,i,player.locate+patdertxplayer);
					this.drawpat(page,j,ai.locate+patdertxai);
					if(ifspace)
					{
						if(b.y>438-image[i].getIconHeight()+30&&b.y<438-image[i].getIconHeight()+80)
							if(b.x>player.locate+patdertxplayer-50-image[i].getIconWidth()&&b.x<player.locate+patdertxplayer-image[i].getIconWidth()+50)
							{
								b.collisiontopat(i,iftoai);
								b.renewceiling();         
								b.renewwall();
								ifaibeat = false;
								iftoai = true;
								ifspace = false;
								aitimer.start();
							}
					}
					if(b.y<200)
					{
						b.collisiontoceiling();
					}else
					if(b.x>940)
					{
						b.collisiontowall();
					}else
					if(b.x<60)
					{
						b.collisiontowall();
					}
					if(b.x>500&&b.x<550)
					{
						if(b.y>500)
							b.collisiontonet();
					}
					if(b.y>550)
					{
						balltimer.stop();
						b.renew();
						b.renewceiling();
						b.renewwall();
						player.renew();
						ai.renew();
						aitimer.stop();
						ifaibeat = false;
						if(b.x>500)
						{
							playerscorenum++;
							playerscore.setText(playerscorenum.toString());
							if(playerscorenum==finishscore)
							{
								bgm.changetovictory();
							}
							b.x = player.locate;
							b.y = player.y;
							iftoai = true;
						}
						else
						{
							aiscorenum++;
							aiscore.setText(aiscorenum.toString());
							if(aiscorenum==finishscore)
							{
								bgm.changetolose();
							}
							b.x = ai.locate;
							b.y = ai.y;	
							iftoai = false;
						}
						try 
						{
							Thread.sleep(500);
						}
						catch (InterruptedException e) 
						{
							e.printStackTrace();
						}
						ifserve = true;
						repaint();
					}
				}
			}
		}
		if(playerscorenum==finishscore)
		{
			ifstart = false;
			balltimer.stop();
			aitimer.stop();
			victory.paintIcon(this,page,260,240);
		}
		if(aiscorenum==finishscore)
		{
			ifstart = false;
			balltimer.stop();
			aitimer.stop();
			lose.paintIcon(this,page,260,240);
		}
	}
	private class Key implements KeyListener
	{
		@Override
		public void keyPressed(KeyEvent e) 
		{
			if(e.getKeyCode()==KeyEvent.VK_D&&player.frontenable(ifserve))
			{
				if(ifstart)
				{
					if(ifserve)
					{
						player.locate+=13;
						b.x = player.locate;
						repaint();
					}
					else
					{
						player.locate+=13;
						repaint();
					}
				}
			}
			if(e.getKeyCode()==KeyEvent.VK_A&&player.backenable())
			{
				if(ifstart)
				{	
					if(ifserve)
					{
						player.locate-=13;
						b.x = player.locate;
						repaint();
					}
					else
					{
						player.locate-=13;
						repaint();
					}
				}
			}
			if(e.getKeyCode()==KeyEvent.VK_SPACE)
			{
				if(ifstart)
				{	
					if(ifserve)
					{
						ifserve = false;
						balltimer.start();
						aitimer.start();
						playerpattimer.start();
					}
					else
					{
						playerpattimer.start();
						ifspace = true;
					}
				}
			}
		}
		@Override public void keyReleased(KeyEvent e) {}	
		@Override public void keyTyped(KeyEvent e) {}
	}
	private class ReboundListener implements ActionListener
	{
		@Override
		public void actionPerformed(ActionEvent e) 
		{
			if(ifstart)
			{
				b.x += b.vx;
				b.vx -= f*b.vx;
				b.y -= b.vy;
				b.vy -= f*b.vy+b.g;
				repaint();
			}
		}
	}
	private class AiListener implements ActionListener
	{
		public void actionPerformed(ActionEvent e) 
		{
			ai.move(b.x);
			repaint();
		}
	}

	private class PpatListener implements ActionListener
	{
		public void actionPerformed(ActionEvent arg0) 
		{
			if(iftop)
			{
				if(i==11)
					iftop=false;
				i++;
			}
			else
			{
				i--;
			}
			if(i==0)
			{
				playerpattimer.stop();
				iftop = true;
			}
			repaint();
		}
	}	
	private class ApatListener implements ActionListener
	{
		public void actionPerformed(ActionEvent arg0) 
		{
			if(iftoa)
			{
				if(j==1)
					iftoa=false;
				j--;
			}
			else
			{
				j++;
			}
			if(j==12)
			{
				aipattimer.stop();
				iftoa = true;
			}
			repaint();
		}
	}
	public void drawpat(Graphics page,int i,int x)
	{
		if(i<6)
		{
			image[i].paintIcon(this,page,x-image[i].getIconWidth(),438-image[i].getIconHeight());
		}
		else
		{
			if(i == 6)
			{
				image[i].paintIcon(this,page,x-image[i].getIconWidth()/2,438-image[i].getIconHeight());
			}
			else
			{
				image[i].paintIcon(this,page,x,438-image[i].getIconHeight());
			}
		}
	}	
	public void renewscore()
	{
		playerscorenum = 0;
		aiscorenum = 0;
		playerscore.setText("0");
		aiscore.setText("0");
	}
}
