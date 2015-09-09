package net.philippschardt.interactivecube.database;

import android.content.ContentValues;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.provider.BaseColumns;

/**
 * Created by philipp on 07.09.15.
 */
public class Contract {


    private static final String TEXT_TYPE = " TEXT";
    private static final String FLOAT_TYPE = " REAL";
    private static final String INT_TYPE = " INTEGER";
    private static final String COMMA_SEP = ",";




    public static abstract class PresenceMode implements BaseColumns {

        public static final String TABLE_NAME = "presence_mode";
        public static final String COLUMN_NAME_ENTRY_ID = "presence_id";

        public static final String COLUMN_NAME_LAST_NAME = "last_name";
        public static final String COLUMN_NAME_FIRST_NAME = "first_name";

        public static final String COLUMN_NAME_COLOR = "color";

        public static final java.lang.String SQL_CREATE_ENTRIES = "CREATE TABLE IF NOT EXISTS " + PresenceMode.TABLE_NAME + " (" +
                PresenceMode._ID + " INTEGER PRIMARY KEY," +
                PresenceMode.COLUMN_NAME_ENTRY_ID + INT_TYPE  + COMMA_SEP +
                PresenceMode.COLUMN_NAME_FIRST_NAME + TEXT_TYPE + COMMA_SEP +
                PresenceMode.COLUMN_NAME_LAST_NAME + TEXT_TYPE + COMMA_SEP +
                PresenceMode.COLUMN_NAME_COLOR + INT_TYPE +
                " )";
    }


    public static abstract class Settings implements BaseColumns {

        public static final String TABLE_NAME = "settings";
        public static final String COLUMN_NAME_ENTRY_ID = "settings_id";


        // CLOCK Mode design
        public static final String COLUMN_NAME_CLOCK_DESIGN_SITE_0 = "clock_design_0";
        public static final String COLUMN_NAME_CLOCK_DESIGN_SITE_1 = "clock_design_1";
        public static final String COLUMN_NAME_CLOCK_DESIGN_SITE_2 = "clock_design_2";
        public static final String COLUMN_NAME_CLOCK_DESIGN_SITE_3 = "clock_design_3";
        public static final String COLUMN_NAME_CLOCK_PRIMARY_COLOR = "clock_color_0";
        public static final String COLUMN_NAME_CLOCK_SECONDARY_COLOR = "clock_color_1";
        public static final String COLUMN_NAME_CLOCK_TERTIARY_COLOR = "clock_color_2";

        // NIGHTLIGHT Mode
        public static final String COLUMN_NAME_NIGHTLIGHT_COLOR = "nightlight_color";

        // DISCO Mode
        public static final String COLUMN_NAME_DISCO_PRIMARY_COLOR = "disco_color_0";
        public static final String COLUMN_NAME_DISCO_SECONDARY_COLOR = "disco_color_1";
        public static final String COLUMN_NAME_DISCO_TERTIARY_COLOR = "disco_color_2";

/*
        public static final String SQL_CREATE_ENTRIES =
                "CREATE TABLE IF NOT EXISTS " + Settings.TABLE_NAME + " (" +
                        Settings._ID + " INTEGER PRIMARY KEY," +
                        Settings.COLUMN_NAME_ENTRY_ID + TEXT_TYPE + COMMA_SEP +
                        Settings.COLUMN_NAME_CLOCK_DESIGN_SITE_0 + INT_TYPE + COMMA_SEP +
                        Settings.COLUMN_NAME_CLOCK_DESIGN_SITE_1 + INT_TYPE + COMMA_SEP +
                        Settings.COLUMN_NAME_CLOCK_DESIGN_SITE_2 + INT_TYPE + COMMA_SEP +
                        Settings.COLUMN_NAME_CLOCK_DESIGN_SITE_3 + INT_TYPE + COMMA_SEP +
                        Settings.COLUMN_NAME_CLOCK_PRIMARY_COLOR + INT_TYPE + COMMA_SEP +
                        Settings.COLUMN_NAME_CLOCK_SECONDARY_COLOR + INT_TYPE + COMMA_SEP +
                        Settings.COLUMN_NAME_CLOCK_TERTIARY_COLOR + INT_TYPE + COMMA_SEP +

                        Settings.COLUMN_NAME_NIGHTLIGHT_COLOR + INT_TYPE + COMMA_SEP +
                        Settings.COLUMN_NAME_DISCO_PRIMARY_COLOR + INT_TYPE + COMMA_SEP +
                        Settings.COLUMN_NAME_DISCO_SECONDARY_COLOR + INT_TYPE + COMMA_SEP +
                        Settings.COLUMN_NAME_DISCO_TERTIARY_COLOR + INT_TYPE +

                        " )";*/


    }

    public static Cursor getPersons(SQLiteDatabase db) {
        return db.rawQuery("SELECT  * FROM " + PresenceMode.TABLE_NAME, null);
    }

    public static Cursor getPerson(SQLiteDatabase db, long id) {

        // Define a projection that specifies which columns from the database
        // you will actually use after this query.
        String[] projection = {
                PresenceMode._ID,
                PresenceMode.COLUMN_NAME_FIRST_NAME,
                PresenceMode.COLUMN_NAME_LAST_NAME,
                PresenceMode.COLUMN_NAME_COLOR
        };

        // Which row to update, based on the ID
        String selection = PresenceMode._ID + " = ?";
        String[] selectionArgs = {String.valueOf(id)};


        Cursor c = db.query(
                PresenceMode.TABLE_NAME,                  // The table to query
                projection,                               // The columns to return
                selection,                                // The columns for the WHERE clause
                selectionArgs,                            // The values for the WHERE clause
                null,                                     // don't group the rows
                null,                                     // don't filter by row groups
                null                                      // The sort order
        );

        return c;
    }

    public static long insertPerson(SQLiteDatabase db, String first, String last, int color) {
        // New value for one column
        ContentValues values = new ContentValues();
        values.put(PresenceMode.COLUMN_NAME_FIRST_NAME, first);
        values.put(PresenceMode.COLUMN_NAME_LAST_NAME, last);
        values.put(PresenceMode.COLUMN_NAME_COLOR, color);

        // Which row to update, based on the ID
        //String selection = PresenceMode._ID + " = ?";
        //String[] selectionArgs = {String.valueOf(id)};

        long id = db.insert(
                PresenceMode.TABLE_NAME,
                null,
                values);

        return id;
    }

    public static int updatePerson(SQLiteDatabase db, String first, String last, int color) {
        // New value for one column
        ContentValues values = new ContentValues();

        values.put(PresenceMode.COLUMN_NAME_COLOR, color);

        // Which row to update, based on the ID
        String selection = PresenceMode.COLUMN_NAME_FIRST_NAME + " = ? AND "
                + PresenceMode.COLUMN_NAME_LAST_NAME + " = ? ";
        String[] selectionArgs = {first, last};

        int count = db.update(
                PresenceMode.TABLE_NAME,
                values,
                selection,
                selectionArgs);

        return count;
    }


    public static int deletePerson(SQLiteDatabase db, long id) {
        String selection = PresenceMode._ID + " LIKE ?";
        String[] selectionArgs = {String.valueOf(id)};
        return db.delete(PresenceMode.TABLE_NAME, selection, selectionArgs);
    }

}
