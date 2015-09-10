package net.philippschardt.interactivecube.fragments;

import android.app.Activity;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CompoundButton;
import android.widget.LinearLayout;
import android.widget.SeekBar;
import android.widget.Switch;

import net.philippschardt.interactivecube.R;
import net.philippschardt.interactivecube.util.Message;

/**
 * A simple {@link Fragment} subclass.
 * Activities that contain this fragment must implement the
 * {@link OnCommunicationListener} interface
 * to handle interaction events.
 * Use the {@link ClockFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class TemperatureFragment extends Fragment {

    private OnCommunicationListener mListener;
    private LinearLayout tempSeeker;

    private float temp = 14.0f;

    /**
     * Use this factory method to create a new instance of
     * this fragment using the provided parameters.
     *

     * @return A new instance of fragment ClockFragment.
     */
    // TODO: Rename and change types and number of parameters
    public static TemperatureFragment newInstance() {
        TemperatureFragment fragment = new TemperatureFragment();
        return fragment;
    }

    public TemperatureFragment() {
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
        View v = inflater.inflate(R.layout.fragment_temperature, container, false);


         tempSeeker = (LinearLayout) v.findViewById(R.id.linear_layout_tempseeker);

        final SeekBar seekBarTemp = (SeekBar) v.findViewById(R.id.seekBar_temperature);
        seekBarTemp.setMax(160);

        seekBarTemp.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

                temp = progress + 140;
                temp /= 10;


            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                mListener.sendMsg(Message.tempDebugValue(temp));

            }
        });

        Switch toggle = (Switch) v.findViewById(R.id.switch_temp_demomodus);
        toggle.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked) {
                    // The toggle is enabled
                    tempSeeker.setVisibility(View.VISIBLE);
                    mListener.sendMsg(Message.tempDebug(true));
                    mListener.sendMsg(Message.tempDebugValue(temp));
                } else {
                    // The toggle is disabled
                    tempSeeker.setVisibility(View.GONE);
                    mListener.sendMsg(Message.tempDebug(false));
                }
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


}
