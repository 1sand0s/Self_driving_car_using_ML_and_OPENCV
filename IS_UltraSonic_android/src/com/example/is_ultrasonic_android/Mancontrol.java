package com.example.is_ultrasonic_android;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

public class Mancontrol extends ActionBarActivity
{

	  static EditText IP,PORT;
	  @Override
	    protected void onCreate(Bundle savedInstanceState)
	    {
	        super.onCreate(savedInstanceState);
	        setContentView(R.layout.activity_mancontrol);
	        Button connect;
	        IP=(EditText)findViewById(R.id.IP);
	        PORT=(EditText)findViewById(R.id.PORT);
	        connect=(Button)findViewById(R.id.connect);
        	connect.setOnClickListener(new OnClickListener()
        	{
		        
			
		        public void onClick(View v) 
		        {
		             String h=IP.getText().toString();
		             String p=PORT.getText().toString();
		             Intent i=new Intent(getApplicationContext(),Control.class);
		             i.putExtra("IP", h);
		             i.putExtra("PORT",p);
		             //Log.e("n",ip.getText()+"."+port.getText()); //For Testing if it works
		             startActivity(i);
		        }

        	});	
	   
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

