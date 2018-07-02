package badminton;

public class PlayerPeople
{
	final int x1 = 60;
	final int x2 = 260;
	final int x3 = 430;
	final int y = 420;
	public int locate = x2;
	public boolean frontenable(boolean ifserve)
	{
		if(ifserve)
		{
			if(locate<x2)
				return true;
			else
				return false;
		}
		else
		{
			if(locate<x3)
				return true;
			else
				return false;
		}
	}
	public boolean backenable()
	{
		if(locate>x1)
			return true;
		else
			return false;
	}
	public void renew()
	{
		locate = x2;
	}
}
