package net.philippschardt.interactivecube.database;

import android.content.Context;
import android.database.Cursor;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.CursorAdapter;
import android.widget.Switch;
import android.widget.TextView;

import net.philippschardt.interactivecube.R;
import net.philippschardt.interactivecube.fragments.OnCommunicationListener;
import net.philippschardt.interactivecube.util.Message;

/**
 * Created by philipp on 08.09.15.
 */
public class PersonListAdapter extends CursorAdapter {


    private  OnCommunicationListener mListener;

    public PersonListAdapter(Context context, Cursor c, boolean autoRequery, OnCommunicationListener mListener) {
        super(context, c, autoRequery);
        this.mListener = mListener;
    }

    public PersonListAdapter(Context context, Cursor c, int flags) {
        super(context, c, flags);
    }

    @Override
    public View newView(Context context, Cursor cursor, ViewGroup parent) {
        return LayoutInflater.from(context).inflate(R.layout.item_person, parent, false);
    }

    @Override
    public void bindView(View view, Context context, Cursor cursor) {

        TextView firstName = (TextView) view.findViewById(R.id.textView_first_name);
        TextView lastName = (TextView) view.findViewById(R.id.textView_last_name);
        Button colorIndicator = (Button) view.findViewById(R.id.button_color_indicator);
        Switch presentSwitch = (Switch) view.findViewById(R.id.switch_present);

        String fName = cursor.getString(cursor.getColumnIndexOrThrow(Contract.PresenceMode.COLUMN_NAME_FIRST_NAME));
        String lName = cursor.getString(cursor.getColumnIndexOrThrow(Contract.PresenceMode.COLUMN_NAME_LAST_NAME));
        final int color = cursor.getInt(cursor.getColumnIndexOrThrow(Contract.PresenceMode.COLUMN_NAME_COLOR));
        final long id = cursor.getLong(cursor.getColumnIndexOrThrow(Contract.PresenceMode._ID));

        presentSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked) {
                    // add person on arduino
                    mListener.sendMsg(Message.addPersonOnArduino(id, color));
                } else {
                    // remove person on arduino
                    mListener.sendMsg(Message.removePersonOnArduino(id));
                }
            }
        });




        firstName.setText(fName);
        lastName.setText(lName);
        colorIndicator.setBackgroundColor(color);
    }
}
