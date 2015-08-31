package com.example.is_ultrasonic_android;

import android.support.v7.app.ActionBarActivity;
import android.support.v7.app.ActionBar;
import android.support.v4.app.Fragment;
import android.content.Intent;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.Button;
import android.os.Build;

public class INTRO extends ActionBarActivity implements OnClickListener{


	protected void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_intro);
		Button Product=(Button)findViewById(R.id.Product);
		Button Query=(Button)findViewById(R.id.Query);
		Button Manual=(Button)findViewById(R.id.Manual);
		Query.setOnClickListener(this);
		Product.setOnClickListener(this);		
		Manual.setOnClickListener(this);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {

		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.intro, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}

	/**
	 * A placeholder fragment containing a simple view.
	 */
	public static class PlaceholderFragment extends Fragment {

		public PlaceholderFragment() {
		}

	//	@Override
		public View onCreateView(LayoutInflater inflater, ViewGroup container,
				Bundle savedInstanceState) {
		View rootView = inflater.inflate(R.layout.fragment_intro,
				container, false);
			return rootView;
		}
	}

	public void onClick(View v) 
	{
		switch(v.getId())
		{
			case R.id.Product:
			startActivity(new Intent(this,Product.class));
			break;
			
			case R.id.Query:
			startActivity(new Intent(this,Query.class));
			break;
			
			case R.id.Manual:
			startActivity(new Intent(this,Mancontrol.class));
			break;
		}
		
	}

}
