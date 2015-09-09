package net.philippschardt.interactivecube.fragments;

import android.app.Activity;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ListView;

import com.melnykov.fab.FloatingActionButton;

import net.philippschardt.interactivecube.AddPersonActivity;
import net.philippschardt.interactivecube.R;
import net.philippschardt.interactivecube.database.Contract;
import net.philippschardt.interactivecube.database.PersonListAdapter;
import net.philippschardt.interactivecube.util.Message;

/**
 * A simple {@link Fragment} subclass.
 * Activities that contain this fragment must implement the
 * {@link OnCommunicationListener} interface
 * to handle interaction events.
 * Use the {@link ClockFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class PresenceFragment extends Fragment {

    private OnCommunicationListener mListener;
    private ListView listView;

    /**
     * Use this factory method to create a new instance of
     * this fragment using the provided parameters.
     *
     * @return A new instance of fragment ClockFragment.
     */
    // TODO: Rename and change types and number of parameters
    public static PresenceFragment newInstance() {
        PresenceFragment fragment = new PresenceFragment();
        return fragment;
    }

    public PresenceFragment() {
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
        View v = inflater.inflate(R.layout.fragment_presence, container, false);


        listView = (ListView) v.findViewById(R.id.listView_presence);

        FloatingActionButton fab = (FloatingActionButton) v.findViewById(R.id.fab);
        //fab.attachToListView(listView);


        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(getActivity(), AddPersonActivity.class);
                startActivity(i);
            }
        });

        return v;
    }


    @Override
    public void onStart() {
        super.onStart();

        mListener.sendMsg(Message.clearPersons());

        SQLiteDatabase db = mListener.getDBHelper().getReadableDatabase();
        Cursor c = Contract.getPersons(db);
        PersonListAdapter adapter = new PersonListAdapter(getActivity(), c, true, mListener);
        listView.setAdapter(adapter);


        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                Intent i = new Intent(getActivity(), AddPersonActivity.class);
                i.putExtra(AddPersonActivity.EXTRA_ID, id);
                startActivity(i);
            }
        });
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
