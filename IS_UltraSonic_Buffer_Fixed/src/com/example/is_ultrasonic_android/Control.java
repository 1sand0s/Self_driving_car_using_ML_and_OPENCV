package com.example.is_ultrasonic_android;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

import android.content.Context;
import android.content.Intent;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.animation.Animation;
import android.view.animation.RotateAnimation;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;


  public class Control extends ActionBarActivity implements SensorEventListener
  {
      
      static String PORT,IP,dir="";
      static Object g,h,tex,tex1,but,but2,but3,but4,but5,sen1,s1;
      int x,y,z;
      float curangle=0f;
      SensorManager sen;
      ImageView compass;
      Sensor s;
      @Override
      public void onCreate(Bundle savedInstanceState) 
      {
          super.onCreate(savedInstanceState);
          setContentView(R.layout.activity_control);
          sen=(SensorManager)getSystemService(Context.SENSOR_SERVICE);
          s=sen.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
          compass=(ImageView)findViewById(R.id.compass);
          Button exit = (Button) findViewById(R.id.exit);
          Button auto=(Button)findViewById(R.id.auto);
          Button man=(Button)findViewById(R.id.man);
          Button test=(Button)findViewById(R.id.test);
          ImageButton light=(ImageButton)findViewById(R.id.light);
          Intent i = getIntent();
        
          IP = i.getStringExtra("IP");
          PORT = i.getStringExtra("PORT");
          g=new String(IP);
          h=new String(PORT);
          but=exit;
          but2=light;
          but3=auto;
          but4=man;
          but5=test;
          sen1=sen;
          s1=s;
          Log.e("Second Screen", g + " " + h);
          Object y[]={g,h,but,but3,but4,but5,but2,sen1,s1};
          controlsend T=new controlsend();
          T.execute(y);
      }
    
      @SuppressWarnings("deprecation")
	protected void onResume()
      {
      	 super.onResume();
           sen.registerListener(this,sen.getDefaultSensor(Sensor.TYPE_ORIENTATION),SensorManager.SENSOR_DELAY_GAME);
      }
      protected void onPause()
      {
      	super.onPause();
      	sen.unregisterListener(this);
      }
  	public void onSensorChanged(SensorEvent event)
  	{
  		if(!controlsend.check)
  		{
  	
  			PrintWriter pr=controlsend.getter();
  			float angle=Math.round(event.values[0]);
  			RotateAnimation ra = new RotateAnimation(curangle,-angle,Animation.RELATIVE_TO_SELF, 0.5f,Animation.RELATIVE_TO_SELF,0.5f);
  			ra.setDuration(210);
  			ra.setFillAfter(true);
  			compass.setAnimation(ra);
  			curangle=-angle;
  			if(angle==0 && dir.compareTo("Front")!=0)
  			{
  				Log.e("dir","front");
  				dir="Front";
  				pr.println("Front");
  				pr.flush();
  			}
  			else if(angle>60 && angle <120 && dir.compareTo("Right")!=0)
  			{
  				Log.e("dir","rigjt");
  				dir="Right";
  				pr.println("Right");
  				pr.flush();
  				
  			}
  			else if(angle >150 && angle <210 && dir.compareTo("Back")!=0)
  			{
  				Log.e("dir","back");
  				dir="Back";
  				pr.println("Back");
  				pr.flush();
  				
  			}
  			else if(angle > 240 && angle <300 && dir.compareTo("Left")!=0)
  			{
  				Log.e("dir","left");
  				dir="Left";
  				pr.println("Left");
  				pr.flush();
  			}
  		}
  		
  	}
  	public void onAccuracyChanged(Sensor sensor, int accuracy)
  	{
  		// TODO Auto-generated method stub
  		
  	}
  	

  
  @Override
  public boolean onCreateOptionsMenu(Menu menu) {
      // Inflate the menu; this adds items to the action bar if it is present.
// getMenuInflater().inflate(R.menu.menu_products, menu);
      return true;
  }

  @Override
  public boolean onOptionsItemSelected(MenuItem item) {
      // Handle action bar item clicks here. The action bar will
      // automatically handle clicks on the Home/Up button, so long
      // as you specify a parent activity in AndroidManifest.xml.
      int id = item.getItemId();

      //noinspection SimplifiableIfStatement
     if (id == R.id.action_settings) {
          return true;
      }

      return super.onOptionsItemSelected(item);
  }
}
class controlsend extends AsyncTask implements OnClickListener
{
    static Socket soc;	
    static BufferedReader br;
    static PrintWriter pr;
    static boolean check=true;
    static String IP,PORT;
    static Button exit,auto,man,test;
	ImageButton lights;
    static int x,y,z;
    SensorManager sen;
    Sensor s;
    @Override
    protected Object doInBackground(Object params[]) 
    {
	Log.e("hello3", "hello3");
	IP=IP.valueOf(params[0]);
	PORT=PORT.valueOf(params[1]);
	exit=(Button)params[2];
	auto=(Button)params[3];
	man=(Button)params[4];
	test=(Button)params[5];
	lights=(ImageButton)params[6];
	sen=(SensorManager)params[7];
	s=(Sensor)params[8];
	exit.setOnClickListener(this);
	auto.setOnClickListener(this);
	man.setOnClickListener(this);
	test.setOnClickListener(this);
	lights.setOnClickListener(this);
	try
        {
		Log.e(IP,PORT);
		    InetAddress inet=InetAddress.getByName(IP);
        	soc=new Socket(inet,Integer.parseInt(PORT));
        	Log.e("hello", "hello");
        	pr=new PrintWriter(new OutputStreamWriter(soc.getOutputStream()),true);
            	br=new BufferedReader(new InputStreamReader(soc.getInputStream()));
            	pr.println(IP);
            	pr.flush();
	}
	catch(UnknownHostException e1)
	{
		e1.printStackTrace();
	}
	catch(IOException e)
        {
        	e.printStackTrace();
        }
        
		return null;
	}
	public static PrintWriter getter()
	{
		return pr;
	}
	public void onClick(View v) 
	{
		switch(v.getId())
		{
			case R.id.exit:
			pr.println(27);
        	pr.flush();
        	try 
        	{
				soc.close();
				
			}
        	catch (IOException e) 
        	{
				e.printStackTrace();
			}
        	break;
        	
			case R.id.auto:
			check=true;
			pr.println('a');
			pr.flush();
			break;
			
			case R.id.test:
			check=true;
			pr.println('t');
			pr.flush();
			break;
			
			case R.id.man:
			check=false;
			pr.println('m');
			pr.flush();
			break;
			
			case R.id.light:
			pr.println('l');
			pr.flush();
			break;
		}
		
	}

}


