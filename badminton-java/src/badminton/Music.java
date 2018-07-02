package badminton;

import java.applet.AudioClip;
import java.net.URL;

import javax.swing.JApplet;

public class Music implements Runnable
{
	private URL bgm = Music.class.getResource("/"+"Base.wav");
	private URL victory = Music.class.getResource("/"+"victor.wav");
	private URL lose = Music.class.getResource("/"+"lose.wav");
	private AudioClip backgroundmusic,victorymusic,losemusic;
	private AudioClip current;
	Music()
	{
		backgroundmusic = JApplet.newAudioClip(bgm);
		victorymusic = JApplet.newAudioClip(victory);
		losemusic = JApplet.newAudioClip(lose);
	}
	public void run() 
	{
		current = backgroundmusic;
		current.loop();	
	}
	public void changetolose()
	{
		if(current!=null)
			current.stop();
		current = losemusic;
		current.loop();
	}
	public void changetovictory()
	{
		if(current!=null)
			current.stop();
		current = victorymusic;
		current.loop();
	}
	public void changetobgm()
	{
		if(current!=null)
			current.stop();
		current = backgroundmusic;
		current.loop();
	}
	
}
