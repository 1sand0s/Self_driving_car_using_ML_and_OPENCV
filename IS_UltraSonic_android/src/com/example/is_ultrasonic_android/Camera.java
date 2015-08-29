package com.example.is_ultrasonic_android;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;

public class Camera extends ActionBarActivity{

	@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
       setContentView(R.layout.activity_camera);

      Button Home=(Button) findViewById(R.id.button6);
        Home.setOnClickListener(new View.OnClickListener() {
        
            public void onClick(View v) {
                startActivity(new Intent(Camera.this, INTRO.class));
            }
        });


        Button Products=(Button) findViewById(R.id.button7);
        Products.setOnClickListener(new View.OnClickListener() {
            
            public void onClick(View v) {
                startActivity(new Intent(Camera.this, Product.class));
            }
        });

       

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
