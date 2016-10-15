package com.example.nmand;

import in.meichai.okhttp.MainOKHttpCallback;
import in.meichai.okhttp.StringParser;

import java.text.SimpleDateFormat;
import java.util.Date;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import com.example.nmand.R;
import com.ppdai.jni.XUtil;
import com.squareup.okhttp.OkHttpClient;
import com.squareup.okhttp.Request;

public class MainActivity extends Activity {
    OkHttpClient okHttpClient=new OkHttpClient();
    StringParser parser=new StringParser();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        
		String skey = XUtil.getAESKey("ppdai");
		TextView btn = (TextView)findViewById(R.id.btn);
        SimpleDateFormat df = new SimpleDateFormat("HH:mm:ss");
		btn.setText(skey+"    "+df.format(new Date()));
        
        
		
		
        findViewById(R.id.btn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                OkHttpClient okHttpClient=new OkHttpClient();
//                StringParser parser=new StringParser();
                Request request = new Request.Builder().url("https://www.baidu.com").build();
                okHttpClient.newCall(request).enqueue(new MainOKHttpCallback() {
                    @Override
                    public void onResponse(String s) {
//                        Toast.makeText(getApplicationContext(),s,Toast.LENGTH_SHORT).show();
                    	showDialog4SelectEnv();
                    }

                });
            }
        });
    }
    
    /**
	 * choose env
	 */
	private void showDialog4SelectEnv() {
		AlertDialog.Builder builder = new AlertDialog.Builder(this);
		builder.setCancelable(false);

		// builder.setTitle("title"); //set title
		builder.setMessage("please choose env"); // set message
		// builder.setIcon(R.mipmap.ic_launcher);//set icon

		builder.setPositiveButton("249env",
				new DialogInterface.OnClickListener() { 
					@Override
					public void onClick(DialogInterface dialog, int which) {
						dialog.dismiss(); // close dialog
					}
				});
		builder.setNeutralButton("145env",
				new DialogInterface.OnClickListener() {
					@Override
					public void onClick(DialogInterface dialog, int which) {
						dialog.dismiss();
					}
				});
		builder.setNegativeButton("prodenv", new DialogInterface.OnClickListener() { 
					@Override
					public void onClick(DialogInterface dialog, int which) {
						dialog.dismiss();
					}
				});
		// show dialog
		builder.create().show();
	}
}
