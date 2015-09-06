package net.philippschardt.interactivecube;

import android.app.Activity;
import android.app.ActivityManager;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;

import net.philippschardt.interactivecube.util.MySocketService;

import java.util.Calendar;
import java.util.Date;
import java.util.TimeZone;

public class MainActivity extends Activity {

    private final String TAG = this.getClass().getName();
    private int i = 0;
    private TextView debugText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

/*
        debugText = (TextView) findViewById(R.id.text_view_input);
        Button sendButton = (Button) findViewById(R.id.button_send);

        sendButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sendMsg("test " + i++);
            }
        });

*/
        Intent i = new Intent(this, MySocketService.class);
        i.putExtra(MySocketService.EXTRA_RESTART, true);
        startService(i);


    }

    private boolean isMyServiceRunning(Class<?> serviceClass) {
        ActivityManager manager = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
        for (ActivityManager.RunningServiceInfo service : manager.getRunningServices(Integer.MAX_VALUE)) {
            if (serviceClass.getName().equals(service.service.getClassName())) {
                return true;
            }
        }
        return false;
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


        Log.d(TAG, "service is running: " + isMyServiceRunning(MySocketService.class));

        // register Receiver
        registerReceiver(mMessageReceiver, new IntentFilter(MySocketService.BROADCAST_ACTION));


        if (isMyServiceRunning(MySocketService.class)) {
            replyConnectionHandshake();
        }

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


    public boolean sendMsg(String msg) {

        Intent i = new Intent(this, MySocketService.class);
        i.putExtra(MySocketService.EXTRA_MESSAGE, msg);
        if (startService(i) != null) {
            Log.d(TAG, "sent: " + msg);
            return true;
        }
        Log.d(TAG, "sent failed: " + msg);
        return false;
    }


    /**
     * handle inputs from arduino/lamp
     */
    public void handleInput(String message) {

        if (!message.equals("") && !message.isEmpty()) {
            Log.d(TAG, "handleInput " + message);

            debugText.setText(message);

            if (message.startsWith("c")) {
                replyConnectionHandshake();
            }

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


    private void replyConnectionHandshake() {
        Calendar cal = Calendar.getInstance(TimeZone.getTimeZone("GMT+1:00"));
        Date currentLocalTime = cal.getTime();

        int hours = currentLocalTime.getHours();
        int min = currentLocalTime.getMinutes();
        int day = currentLocalTime.getDay();
        int year = currentLocalTime.getYear();
        int sec = currentLocalTime.getSeconds();
        int month = currentLocalTime.getMonth();
        sendMsg("hc;"+hours+ ";"+ min + ";" + sec + ";" + day + ";" + month + ";" + year );
    }


}
