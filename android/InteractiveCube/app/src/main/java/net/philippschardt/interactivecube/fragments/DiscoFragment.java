package net.philippschardt.interactivecube.fragments;

import android.app.Activity;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import net.philippschardt.interactivecube.R;

/**
 * A simple {@link Fragment} subclass.
 * Activities that contain this fragment must implement the
 * {@link OnCommunicationListener} interface
 * to handle interaction events.
 * Use the {@link ClockFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class DiscoFragment extends Fragment {

    private OnCommunicationListener mListener;

    /**
     * Use this factory method to create a new instance of
     * this fragment using the provided parameters.
     *

     * @return A new instance of fragment ClockFragment.
     */
    // TODO: Rename and change types and number of parameters
    public static DiscoFragment newInstance() {
        DiscoFragment fragment = new DiscoFragment();
        return fragment;
    }

    public DiscoFragment() {
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
        return inflater.inflate(R.layout.fragment_disco, container, false);
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
