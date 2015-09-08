package net.philippschardt.interactivecube.fragments;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

import net.philippschardt.interactivecube.R;
import net.philippschardt.interactivecube.util.ColorPickerDialog;
import net.philippschardt.interactivecube.util.Message;

/**
 * A simple {@link Fragment} subclass.
 * Activities that contain this fragment must implement the
 * {@link OnCommunicationListener} interface
 * to handle interaction events.
 * Use the {@link ClockFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class NightLightFragment extends Fragment implements ColorPickerDialog.OnColorPickerListener {

    private final String TAG = getClass().getName();
    private OnCommunicationListener mListener;
    private Button colorPickerButton;

    private int primaryColor = Color.YELLOW;

    /**
     * Use this factory method to create a new instance of
     * this fragment using the provided parameters.
     *
     * @return A new instance of fragment ClockFragment.
     */
    // TODO: Rename and change types and number of parameters
    public static NightLightFragment newInstance() {
        NightLightFragment fragment = new NightLightFragment();
        return fragment;
    }


    @Override
    public void startActivityForResult(Intent intent, int requestCode) {
        Log.d(TAG, "startActivityForResult");
        super.startActivityForResult(intent, requestCode);
    }

    public void showColorPickerDialog() {
        // Create an instance of the dialog fragment and show it
        ColorPickerDialog dialog = ColorPickerDialog.newInstance(primaryColor);
        dialog.show(getFragmentManager(), "ColorPickerDialog");

        Log.d(TAG, "display color picker dialog");
    }


    public NightLightFragment() {
        // Required empty public constructor
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View v = inflater.inflate(R.layout.fragment_night_light, container, false);

        colorPickerButton = (Button) v.findViewById(R.id.button_color_picker_night_light);

        colorPickerButton.setBackgroundColor(primaryColor);

        colorPickerButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                showColorPickerDialog();
            }
        });

        return v;
    }


    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);
        try {
            mListener = (OnCommunicationListener) activity;
        } catch (ClassCastException e) {
            throw new ClassCastException(activity.toString()
                    + " must implement OnFragmentInteractionListener");
        }
    }

    @Override
    public void onDetach() {
        super.onDetach();
        mListener = null;
    }


    @Override
    public void onCommitColor(int color) {

        Log.d(TAG, "picked Color " + Color.red(color) + " " + Color.green(color) + " " + Color.blue(color));

        colorPickerButton.setBackgroundColor(color);
        primaryColor = color;

        // send primary color to arduino
        mListener.sendMsg(Message.TempPrimaryColor(Color.red(color), Color.green(color), Color.blue(color)));
    }
}
