package net.philippschardt.interactivecube;

import android.app.Activity;
import android.app.ActivityManager;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBar;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;

import net.philippschardt.interactivecube.database.DBHelper;
import net.philippschardt.interactivecube.fragments.ClockFragment;
import net.philippschardt.interactivecube.fragments.DiscoFragment;
import net.philippschardt.interactivecube.fragments.NightLightFragment;
import net.philippschardt.interactivecube.fragments.OnCommunicationListener;
import net.philippschardt.interactivecube.fragments.PresenceFragment;
import net.philippschardt.interactivecube.fragments.TemperatureFragment;
import net.philippschardt.interactivecube.util.ColorPickerDialog;
import net.philippschardt.interactivecube.util.MySocketService;

import java.util.Calendar;
import java.util.Date;
import java.util.TimeZone;

public class InteractiveCubeActivity extends ActionBarActivity
        implements NavigationDrawerFragment.NavigationDrawerCallbacks, OnCommunicationListener, ColorPickerDialog.OnColorPickerListener {


    private final String TAG = this.getClass().getName();
    /**
     * Fragment managing the behaviors, interactions and presentation of the navigation drawer.
     */
    private NavigationDrawerFragment mNavigationDrawerFragment;

    /**
     * Used to store the last screen title. For use in {@link #restoreActionBar()}.
     */
    private CharSequence mTitle;
    private DBHelper mDbHelper;
    private Fragment currentFragment;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_interactive_cube);

        mNavigationDrawerFragment = (NavigationDrawerFragment)
                getSupportFragmentManager().findFragmentById(R.id.navigation_drawer);
        mTitle = getTitle();

        // Set up the drawer.
        mNavigationDrawerFragment.setUp(
                R.id.navigation_drawer,
                (DrawerLayout) findViewById(R.id.drawer_layout));


        mDbHelper = new DBHelper(this);


        // start socket service if not started
        Intent i = new Intent(this, MySocketService.class);
        i.putExtra(MySocketService.EXTRA_RESTART, true);
        startService(i);

    }

    @Override
    public void onNavigationDrawerItemSelected(int position) {
        // update the main content by replacing fragments
        FragmentManager fragmentManager = getSupportFragmentManager();
        switch (position) {
            case 0:
                currentFragment = ClockFragment.newInstance();
                break;

            case 1:
                currentFragment = NightLightFragment.newInstance();
                break;
            case 2:
                currentFragment = TemperatureFragment.newInstance();
                break;
            case 3:
                currentFragment = DiscoFragment.newInstance();
                break;
            case 4:
                currentFragment = PresenceFragment.newInstance();
                break;
            default:
                currentFragment = PlaceholderFragment.newInstance(position + 1);
                break;
        }

        fragmentManager.beginTransaction()
                .replace(R.id.container, currentFragment)
                .commit();


    }

    public void onSectionAttached(int number) {
        switch (number) {
            case 1:
                mTitle = getString(R.string.mode_clock);
                break;
            case 2:
                mTitle = getString(R.string.mode_nightlight);
                break;
            case 3:
                mTitle = getString(R.string.mode_temperature);
                break;
            case 4:
                mTitle = getString(R.string.mode_disco);
                break;
            case 5:
                mTitle = getString(R.string.mode_presence);
                break;

        }
    }

    public void restoreActionBar() {
        ActionBar actionBar = getSupportActionBar();
        actionBar.setNavigationMode(ActionBar.NAVIGATION_MODE_STANDARD);
        actionBar.setDisplayShowTitleEnabled(true);
        actionBar.setTitle(mTitle);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        if (!mNavigationDrawerFragment.isDrawerOpen()) {
            // Only show items in the action bar relevant to this screen
            // if the drawer is not showing. Otherwise, let the drawer
            // decide what to show in the action bar.
            getMenuInflater().inflate(R.menu.interactive_cube, menu);
            restoreActionBar();
            return true;
        }
        return super.onCreateOptionsMenu(menu);
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

    @Override
    public void onCommitColor(int color) {
        //if current fragment is a onColorPickerListener
        ColorPickerDialog.OnColorPickerListener colorPickerListener = null;
        try {
            colorPickerListener = (ColorPickerDialog.OnColorPickerListener) currentFragment;
        } catch (ClassCastException e) {
            // The activity doesn't implement the interface, throw exception
            throw new ClassCastException(this.toString()
                    + " must implement OnColorPickerListener");
        }

        colorPickerListener.onCommitColor(color);

    }

    /**
     * A placeholder fragment containing a simple view.
     */
    public static class PlaceholderFragment extends Fragment {
        /**
         * The fragment argument representing the section number for this
         * fragment.
         */
        private static final String ARG_SECTION_NUMBER = "section_number";

        /**
         * Returns a new instance of this fragment for the given section
         * number.
         */
        public static PlaceholderFragment newInstance(int sectionNumber) {
            PlaceholderFragment fragment = new PlaceholderFragment();
            Bundle args = new Bundle();
            args.putInt(ARG_SECTION_NUMBER, sectionNumber);
            fragment.setArguments(args);
            return fragment;
        }

        public PlaceholderFragment() {
        }

        @Override
        public View onCreateView(LayoutInflater inflater, ViewGroup container,
                                 Bundle savedInstanceState) {
            View rootView = inflater.inflate(R.layout.fragment_interactive_cube, container, false);
            return rootView;
        }

        @Override
        public void onAttach(Activity activity) {
            super.onAttach(activity);
            ((InteractiveCubeActivity) activity).onSectionAttached(
                    getArguments().getInt(ARG_SECTION_NUMBER));
        }
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

            //debugText.setText(message);

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
        sendMsg("hc;" + hours + ";" + min + ";" + sec + ";" + day + ";" + month + ";" + year);
    }


}
