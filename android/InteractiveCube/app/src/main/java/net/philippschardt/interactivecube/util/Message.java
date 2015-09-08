package net.philippschardt.interactivecube.util;

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
}
