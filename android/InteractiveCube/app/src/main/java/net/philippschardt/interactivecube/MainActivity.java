package net.philippschardt.interactivecube;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;

import net.philippschardt.interactivecube.util.MySocketService;

public class MainActivity extends Activity {

    private  final String TAG =  this.getLocalClassName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }


    private BroadcastReceiver mMessageReceiver = new BroadcastReceiver() {

        @Override
        public void onReceive(Context context, Intent intent) {

            if (intent != null) {
                String msg = intent.getStringExtra(MySocketService.EXTRA_MESSAGE_FORWARD);
                handleInput(msg);
            }


        }
    };

    @Override
    protected void onResume() {
        super.onResume();

        // register Receiver
        registerReceiver(mMessageReceiver, new IntentFilter(MySocketService.BROADCAST_ACTION));
    }

    @Override
    protected void onPause() {
        super.onPause();

        // unregister Receiver
        unregisterReceiver(mMessageReceiver);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
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



    /**
     * handle inputs from arduino/lamp
     * */
    public void handleInput(String message) {

        Log.d(TAG, "handleInput " + message);
        /*if (message.startsWith("ms;")) {
            handleMotorUpdate(message);
        } else if (message.startsWith("r;"))
            handleConnectionReply(message);
        else if (message.startsWith("mfr;"))
            handleMoveToFormReply(message);
        else if (message.startsWith("br;"))
            handleBoundReply(message);*/
    }
}
