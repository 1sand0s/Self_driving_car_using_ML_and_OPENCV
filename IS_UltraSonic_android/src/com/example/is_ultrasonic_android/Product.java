package com.example.is_ultrasonic_android;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnLongClickListener;
import android.widget.ImageView;
import android.widget.TextView;

public class Product extends ActionBarActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        
       setContentView(R.layout.activity_product);
      /*TextView textw=(TextView)findViewById(R.id.textView26);
       Typeface f=Typeface.createFromAsset(getAssets(),"fonts/TRON.TTF");
       textw.setTypeface(f);*/
       TextView text1=(TextView)findViewById(R.id.text1);
      TextView text2=(TextView)findViewById(R.id.text2);
       TextView text3=(TextView)findViewById(R.id.text3);
       /*TextView text4=(TextView)findViewById(R.id.text4);
       TextView text5=(TextView)findViewById(R.id.text5);
       TextView text6=(TextView)findViewById(R.id.text6);
       final ImageView view1=(ImageView)findViewById(R.id.Image1);*/
    
       text1.setOnLongClickListener(new OnLongClickListener()
       {


		public boolean onLongClick(View v) {
		    startActivity(new Intent(Product.this,Car.class));
			return false;
			
		}

		
    	   
       });
      
       text2.setOnLongClickListener(new OnLongClickListener()
       {

		public boolean onLongClick(View v) {
		    startActivity(new Intent(Product.this,Camera.class));
			return false;
			
		}
    	   
       });
       text3.setOnLongClickListener(new OnLongClickListener()
       {

		public boolean onLongClick(View v) {
		    startActivity(new Intent(Product.this,Path.class));
			return false;
			
		}
    	   
       });/*
       text4.setOnClickListener(new OnClickListener()
       {

		@Override
		public void onClick(View v) 
		{
			ImageView imag=view1;
			assert(R.id.image1==imag.getId());
			imag.setImageResource(R.drawable.i4);
			imag.setTag(R.drawable.i4);
		}
    	   
       });
       text4.setOnLongClickListener(new OnLongClickListener()
       {

		@Override
		public boolean onLongClick(View v) {
		    startActivity(new Intent(products.this,Cutting.class));
			return false;
			
		}
    	   
       });
       text5.setOnClickListener(new OnClickListener()
       {

		@Override
		public void onClick(View v) 
		{
			ImageView imag=view1;
			assert(R.id.image1==imag.getId());
			imag.setImageResource(R.drawable.i3);
			imag.setTag(R.drawable.i3);
		}
    	   
       });
       text5.setOnLongClickListener(new OnLongClickListener()
       {

		@Override
		public boolean onLongClick(View v) {
		    startActivity(new Intent(products.this,Pasting.class));
			return false;
			
		}
    	   
       });
       text6.setOnClickListener(new OnClickListener()
       {

		@Override
		public void onClick(View v) 
		{
			ImageView imag=view1;
			assert(R.id.image1==imag.getId());
			imag.setImageResource(R.drawable.i6);
			imag.setTag(R.drawable.i6);
		}
    	   
       });
       text6.setOnLongClickListener(new OnLongClickListener()
       {

		@Override
		public boolean onLongClick(View v) {
		    startActivity(new Intent(products.this,Regulations.class));
			return false;
			
		}
    	   
       });
     
       Button hom=(Button)findViewById(R.id.button1);
       Button Con=(Button)findViewById(R.id.button3);
       
      
      hom.setOnClickListener(new OnClickListener()
       {
    	   public void onClick(View v)
    	   {
    		   startActivity(new Intent(products.this,MainActivity.class));
    	   }
       });
       Con.setOnClickListener(new OnClickListener()
       {
    	   public void onClick(View v)
    	   {
    		   startActivity(new Intent(products.this,Contact1.class));
    	   }
       });*/
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
