package net.philippschardt.interactivecube.util;

import android.app.Activity;
import android.app.Dialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.support.v4.app.DialogFragment;
import android.support.v7.app.AlertDialog;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.larswerkman.holocolorpicker.ColorPicker;
import com.larswerkman.holocolorpicker.SVBar;

import net.philippschardt.interactivecube.R;

/**
 * Created by philipp on 07.09.15.
 */
public class ColorPickerDialog extends DialogFragment {

    private final String TAG = getClass().getName();
    private ColorPicker picker;
    private int initColor = 0;


    private static final String initColorParam = "initColorparam";

    public ColorPickerDialog() {

    }

    public interface OnColorPickerListener {
        public void onCommitColor(int color);

    }


    public static ColorPickerDialog newInstance(int color) {

        Bundle args = new Bundle();

        ColorPickerDialog fragment = new ColorPickerDialog();
        args.putInt(initColorParam, color);
        fragment.setArguments(args);
        return fragment;
    }


    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (getArguments() != null) {
            initColor = getArguments().getInt(initColorParam);

        }
    }



    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {



        //Dialog d =  super.onCreateDialog(savedInstanceState);

        Log.d(TAG, "onCreateDialog");

        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());

        builder.setMessage("testdialog");

        // Get the layout inflater
        LayoutInflater inflater = getActivity().getLayoutInflater();
        View v = inflater.inflate(R.layout.color_picker, null);

        // Inflate and set the layout for the dialog
        // Pass null as the parent view because its going in the dialog layout
        builder.setView(v)
                // Add action buttons
                .setPositiveButton("commit", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int id) {
                        mListener.onCommitColor(picker.getColor());

                    }
                })
                .setNegativeButton(R.string.cancel, new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int id) {

                    }
                });

        picker = (ColorPicker) v.findViewById(R.id.picker);
        SVBar svBar = (SVBar) v.findViewById(R.id.svbar);
        //OpacityBar opacityBar = (OpacityBar) v.findViewById(R.id.opacitybar);
        //SaturationBar saturationBar = (SaturationBar) v.findViewById(R.id.saturationbar);
        //ValueBar valueBar = (ValueBar) v.findViewById(R.id.valuebar);

        picker.addSVBar(svBar);
        //picker.addOpacityBar(opacityBar);
        //picker.addSaturationBar(saturationBar);
        //picker.addValueBar(valueBar);

        picker.setColor(initColor);
        //svBar.setColor(initColor);
        

        return builder.create();
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View v = super.onCreateView(inflater, container, savedInstanceState);




        return v;
    }





    // Use this instance of the interface to deliver action events
    OnColorPickerListener mListener;

    // Override the Fragment.onAttach() method to instantiate the NoticeDialogListener
    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);
        // Verify that the host activity implements the callback interface
        try {
            // Instantiate the NoticeDialogListener so we can send events to the host
            mListener = (OnColorPickerListener) activity;
        } catch (ClassCastException e) {
            // The activity doesn't implement the interface, throw exception
            throw new ClassCastException(activity.toString()
                    + " must implement NoticeDialogListener");
        }
    }


}
