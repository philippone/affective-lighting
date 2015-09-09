package net.philippschardt.interactivecube.util;

import android.database.Cursor;
import android.graphics.Color;

import net.philippschardt.interactivecube.database.Contract;

/**
 * Created by philipp on 07.09.15.
 */
public class Message {



    public static String NightLightPrimaryColor(int r, int g, int b) {
        return "nlm_c1;"+r+";"+g+";"+b+";";
    }

    public static String ClockSetMode(int position) {
        return "cm_d;"+position + ";";
    }


    public static String sendPersonArray(Cursor persons) {

        String s = "pm_pa;";

        if (persons.moveToFirst()) {

            while (!persons.isLast()) {

                long id = persons.getLong(persons.getColumnIndexOrThrow(Contract.PresenceMode._ID));
                int color = persons.getInt(persons.getColumnIndexOrThrow(Contract.PresenceMode.COLUMN_NAME_COLOR));

                int r = Color.red(color);
                int g = Color.green(color);
                int b = Color.blue(color);

                s+= id + ";" + r + ";" + g + ";" + b + ";";

                // delimiter for person
                s+= "#";
            }

            //s+= ";";
            return s;

        }
        return "";
    }


    /**
     * add person on arduino
     * */
    public static String addPersonOnArduino(long id, int color) {
        return "pm_ap;"+ id + ";" + Color.red(color) + ";" + Color.green(color) + ";" + Color.blue(color) + ";";
    }

    /**
     * remove person on arduino
     * */
    public static String removePersonOnArduino(long id) {
        return "pm_rp;"+ id + ";";
    }

    /**
     * set person present on arduino
     * */
    public static String setPresencePresent(long id) {
        return "pm_p;"+ id + ";" ;
    }

    /**
     * set person absent on arduino
     * */
    public static String setPresenceAbsent(long id) {
        return "pm_a;"+ id + ";";
    }


}
