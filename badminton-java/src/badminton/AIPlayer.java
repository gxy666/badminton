package badminton;

public class AIPlayer 
{
	final int x1 = 860;
	final int x2 = 650;
	final int x3 = 500;
	final int y = 420;
	public int locate = x2;
	public boolean enable(boolean ifserve)
	{
		if(ifserve)
		{
			if(locate>x1&&locate<x2)
				return true;
			else
				return false;
		}
		else
		{
			if(locate>x1&&locate<x3)
				return true;
			else
				return false;
		}
	}
	public void renew()
	{
		locate = x2;
	}	
	public boolean frontenable()
	{
		if(locate>x3)
			return true;
		else
			return false;
	}
	public boolean backenable()
	{
		if(locate<x1)
			return true;
		else
			return false;
	}
	public void move(int a)
	{
		if(a>locate+100)
		{
			if(backenable())
				locate+=5;
		}
		else
		{
			if(frontenable())
			locate-=5;
		}
	}
}
