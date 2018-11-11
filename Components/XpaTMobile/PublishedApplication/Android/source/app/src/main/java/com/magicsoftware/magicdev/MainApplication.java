package com.magicsoftware.magicdev;

import java.util.Locale;

import com.google.firebase.iid.FirebaseInstanceId;
import com.magicsoftware.core.CoreApplication;

public class MainApplication extends CoreApplication {
	
	@Override
	public String userDefinedFunction(String str) {
		if ("getargs".equals(str.toLowerCase(Locale.getDefault()))) {
			// Return the URI intent args (when launched from another application)
			return MainActivity.intentArgs; 
		}
		else if ("getpushid".equals(str.toLowerCase(Locale.getDefault()))) {
			// Return the push notification unique GCM ID - for push notification
			return FirebaseInstanceId.getInstance().getToken();
		}
		else {
			//User to add free code
			return "Return String";
		}
	}
}
