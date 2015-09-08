package net.philippschardt.interactivecube;

import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.Color;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import net.philippschardt.interactivecube.database.Contract;
import net.philippschardt.interactivecube.database.DBHelper;
import net.philippschardt.interactivecube.util.ColorPickerDialog;

public class AddPersonActivity extends ActionBarActivity implements ColorPickerDialog.OnColorPickerListener {


    public static final String EXTRA_ID = "net.philippschardt.addpersonactivity.id";

    int color = Color.WHITE;
    private EditText firstName;
    private EditText lastName;
    private Button colorPickerButton;
    private Button commitButton;
    private DBHelper mDbHelper;
    private boolean update = false;
    private long pers_id;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_person);




        mDbHelper = new DBHelper(this);

        firstName = (EditText) findViewById(R.id.editText_first_name);
        lastName = (EditText) findViewById(R.id.editText_last_name);
        colorPickerButton = (Button) findViewById(R.id.button_person_color);

        colorPickerButton.setBackgroundColor(color);
        colorPickerButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                showColorPickerDialog();
            }
        });

        commitButton = (Button) findViewById(R.id.button_commit_person);
        commitButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                SQLiteDatabase db = mDbHelper.getWritableDatabase();

                if (update) {
                    Contract.updatePerson(db, firstName.getText().toString(), lastName.getText().toString(), color);
                } else {
                    //insert
                    Contract.insertPerson(db, firstName.getText().toString(), lastName.getText().toString(), color);
                }


                AddPersonActivity.this.finish();
            }
        });


        if (getIntent().hasExtra(EXTRA_ID)) {

            update = true;

             pers_id = getIntent().getLongExtra(EXTRA_ID, 1);

            SQLiteDatabase db = mDbHelper.getWritableDatabase();
            Cursor c_person = Contract.getPerson(db, pers_id);

            if (c_person.moveToFirst()) {

                String fName = c_person.getString(c_person.getColumnIndexOrThrow(Contract.PresenceMode.COLUMN_NAME_FIRST_NAME));
                String lName = c_person.getString(c_person.getColumnIndexOrThrow(Contract.PresenceMode.COLUMN_NAME_LAST_NAME));
                final int color = c_person.getInt(c_person.getColumnIndexOrThrow(Contract.PresenceMode.COLUMN_NAME_COLOR));


                firstName.setText(fName);
                lastName.setText(lName);
                colorPickerButton.setBackgroundColor(color);
            }

        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.


        if (update) {
            getMenuInflater().inflate(R.menu.menu_add_person, menu);

        }


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
        } else if (id == R.id.action_delete_person) {
            Contract.deletePerson(mDbHelper.getWritableDatabase(), pers_id);
            this.finish();
            return true;
        }

        return super.onOptionsItemSelected(item);
    }


    public void showColorPickerDialog() {
        // Create an instance of the dialog fragment and show it
        ColorPickerDialog dialog = ColorPickerDialog.newInstance(color);
        dialog.show(getSupportFragmentManager(), "ColorPickerDialog");

    }

    @Override
    public void onCommitColor(int color) {

        this.color = color;
        colorPickerButton.setBackgroundColor(color);

    }
}
