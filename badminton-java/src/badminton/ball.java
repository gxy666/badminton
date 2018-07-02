package badminton;

public class ball 
{
	public int x;
	public int y;
	public double vx = 7;
	public double vy = 6.2;
	public double g = 0.08;
	private boolean ifcollisiontoceiling = false;
	private boolean ifcollisiontonet = false;
	private boolean ifcollisiontowall = false;
	int a = 3;
	ball(int x,int y)
	{
		this.x = x;
		this.y = y;
	}
	public void collisiontoceiling()
	{
		if(!ifcollisiontoceiling)
		{
			vy = -vy;
		}
		ifcollisiontoceiling = true;
	}
	public void collisiontowall()
	{
		if(!ifcollisiontowall)
		{
			vx = -0.8*vx;
		}
		ifcollisiontowall = true;
	}
	public void collisiontonet()
	{
		if(!ifcollisiontonet)
		{
			vx = -vx;
		}
		ifcollisiontonet = true;
	}
	public void renew()
	{
		ifcollisiontonet = false;
		vx = 7;
		vy = 6.2;
	}
	public void renewa()
	{
		ifcollisiontonet = false;
		vx = -7;
		vy = 6.2;
	}
	public void renewceiling()
	{
		ifcollisiontoceiling = false;
	}
	public void renewwall()
	{
		ifcollisiontowall = false;
	}
	public void collisiontopat(int i,boolean iftoai)
	{
		if(iftoai)
		{
			if(vx>0)
			{
				double cos = Math.cos(Math.toRadians(180-2*(42+i))-Math.atan(-1*vy/vx));
				double v0 = Math.pow(Math.pow(vx,2)+Math.pow(vy,2),0.5)+a;
				double sin = Math.sin(Math.toRadians(180-2*(42+i))-Math.atan(-1*vy/vx));
				vx = -(v0+4)*cos;
				vy = v0*sin;
			}
			else
			{
				double cos = Math.cos(Math.toRadians(180-2*(132+i))-Math.atan(-1*vy/vx));
				double v0 = Math.pow(Math.pow(vx,2)+Math.pow(vy,2),0.5)+a;
				double sin = Math.sin(Math.toRadians(180-2*(42+i))-Math.atan(-1*vy/vx));
				vx = -(v0+4)*cos;
				vy = v0*sin;
			}
		}
		else
		{
			if(vx>0)
			{
				double cos = Math.cos(Math.toRadians(180-2*(150+i))-Math.atan(-1*vy/vx));
				double v0 = Math.pow(Math.pow(vx,2)+Math.pow(vy,2),0.5)+a;
				double sin = Math.sin(Math.toRadians(180-2*(42+i))-Math.atan(-1*vy/vx));
				vx = -(v0+4)*cos;
				vy = v0*sin;
			}
			else
			{
				double cos = Math.cos(Math.toRadians(180-2*(40+i))-Math.atan(-1*vy/vx));
				double v0 = Math.pow(Math.pow(vx,2)+Math.pow(vy,2),0.5)+a;
				double sin = Math.sin(Math.toRadians(180-2*(42+i))-Math.atan(-1*vy/vx));
				vx = -(v0+4)*cos;
				vy = v0*sin;
			}
		}
		if(vy>7) vy = 7;
		if(Math.abs(vx)<5) vx = 5*vx/Math.abs(vx);
	}
	
}
