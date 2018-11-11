package com.magicsoftware.magicdev;

// This file is required for a generic application (empty URL)

import android.app.Activity;
import android.content.SharedPreferences;
import android.content.SharedPreferences.OnSharedPreferenceChangeListener;
import android.os.Bundle;
import android.preference.EditTextPreference;
import android.preference.PreferenceFragment;

public class SettingsActivity extends Activity{
	
	static EditTextPreference urlPreference;
	static OnSharedPreferenceChangeListener listener;
    
    @Override
	protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Display the fragment as the main content.
        getFragmentManager().beginTransaction().replace(android.R.id.content,
                new PrefsFragment()).commit();
    }


    public static class PrefsFragment extends PreferenceFragment {

        @Override
        public void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);

            // Load the preferences from an XML resource
            addPreferencesFromResource(R.xml.settings);
            
    		urlPreference = (EditTextPreference) findPreference("URL");
    		if (urlPreference != null && urlPreference.getText() != null)
    			urlPreference.setSummary(urlPreference.getText().toString());
    		listener = new OnSharedPreferenceChangeListener() {
    			@Override
    			public void onSharedPreferenceChanged(SharedPreferences prefs, String key) {
    				if (key.equals("URL"))
    					urlPreference.setSummary(urlPreference.getText().toString());
    			}
    		};
        }
    }
}