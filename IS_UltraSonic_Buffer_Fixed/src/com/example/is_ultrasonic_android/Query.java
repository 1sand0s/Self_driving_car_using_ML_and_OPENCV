package com.example.is_ultrasonic_android;


import android.content.Intent;
import android.graphics.Typeface;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;



import android.content.Intent;
import android.support.v7.app.ActionBarActivity;
import android.net.Uri;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ExpandableListView;
import android.widget.Toast;

import javax.mail.*;
import javax.mail.internet.*;
import javax.activation.*;

import java.util.*;


public class Query extends ActionBarActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
       setContentView(R.layout.query);
       Button buto=(Button)findViewById(R.id.button2);
       final EditText edit1=(EditText)findViewById(R.id.edit1);
       final EditText edit2=(EditText)findViewById(R.id.edit2);
       final EditText edittext=(EditText)findViewById(R.id.editText1);
       buto.setOnClickListener(new OnClickListener()
       {
    	   public void onClick(View v)
    	   {
    		   String to[]={edit2.getText()+""};
    		   String rec[]={"1sand0sardpi@gmail.com","rakshith.vishwanatha@gmail.com"};
    		   Intent intt=new Intent(Intent.ACTION_SEND);
    		   intt.setData(Uri.parse("mailto:"));
    		   intt.setType("text/plain");
    		   intt.putExtra(Intent.EXTRA_EMAIL,to);
    		   intt.putExtra(Intent.EXTRA_CC, rec);
    		   intt.putExtra(Intent.EXTRA_SUBJECT,"Query Regarding :"+edit1.getText());
    		   intt.putExtra(Intent.EXTRA_TEXT,edittext.getText());
    		   try{
    			   startActivity(Intent.createChooser(intt,"Send Mail"));
    			   finish();
    			   
    		   }catch(android.content.ActivityNotFoundException   e)
    		   {
    			   Toast.makeText(Query.this,"No Email Client found", Toast.LENGTH_SHORT).show();
    		   }
    		   
    	   }
       });
  
 


    } 

    



    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
     
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
