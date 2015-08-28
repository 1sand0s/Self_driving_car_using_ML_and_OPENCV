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
      
      static String PORT,IP;
      static Object g,h,tex,tex1,but,but2,sen1,s1;
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
          ImageButton light=(ImageButton)findViewById(R.id.light);
          Intent i = getIntent();
        
          IP = i.getStringExtra("IP");
          PORT = i.getStringExtra("PORT");
          g=new String(IP);
          h=new String(PORT);
          but=exit;
          but2=light;
          sen1=sen;
          s1=s;
          Log.e("Second Screen", g + " " + h);
          Object y[]={g,h,but,but2,sen1,s1};
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
  	
  		PrintWriter pr=controlsend.getter();
  		float angle=Math.round(event.values[0]);
  		RotateAnimation ra = new RotateAnimation(curangle,-angle,Animation.RELATIVE_TO_SELF, 0.5f,Animation.RELATIVE_TO_SELF,0.5f);
  		ra.setDuration(210);
  		ra.setFillAfter(true);
  		compass.setAnimation(ra);
  		curangle=-angle;
  		if(angle==0)
  		{
  			Log.e("dir","front");
  			//pr.println(PORT + " "  + "DATA" + " " + "Front");
  			//pr.flush();
  		}
  		else if(angle>60 && angle <120)
  		{
  			Log.e("dir","rigjt");
  			//pr.println(PORT + " "  + "DATA" + " " + "Right");
  			//pr.flush();
  		
  		}
  		else if(angle >150 && angle <210)
  		{
  			Log.e("dir","back");
  			//pr.println(PORT + " "  + "DATA" + " " + "Back");
  			//pr.flush();
  			
  		}
  		else if(angle > 240 && angle <300)
  		{
  			Log.e("dir","left");
  			//pr.println(PORT + " "  + "DATA" + " " + "Left");
  			//pr.flush();
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
class controlsend extends AsyncTask
{
    static Socket soc;	
    static BufferedReader br;
    static PrintWriter pr;
    static String IP,PORT;
    static Button exit;
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
	lights=(ImageButton)params[3];
	sen=(SensorManager)params[4];
	s=(Sensor)params[5];
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
        exit.setOnClickListener(new View.OnClickListener() 
        {
        	 
            	public void onClick(View arg0) 
            	{
            		pr.println(IP+" LOGOUT");
            		pr.flush();
            		try {
						soc.close();
					
					} catch (IOException e) {
						
						e.printStackTrace();
					}
            	}
        });
        lights.setOnClickListener(new View.OnClickListener()
        {

		public void onClick(View v) 
		{
			pr.println(PORT + " "  + "DATA" + " " + "start");
			pr.flush();
		}
        	
        });

		return null;
	}
	public static PrintWriter getter()
	{
		return pr;
	}

}


