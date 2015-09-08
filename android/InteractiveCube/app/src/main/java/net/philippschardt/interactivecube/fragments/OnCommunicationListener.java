package net.philippschardt.interactivecube.fragments;

import net.philippschardt.interactivecube.database.DBHelper;

/**
 * Created by philipp on 06.09.15.
 */
public interface OnCommunicationListener {

    boolean sendMsg(String msg);

    DBHelper getDBHelper();


}
