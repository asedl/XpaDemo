package xpa.xpatest.xpatmobile;

import com.magicsoftware.core.startact;

import android.app.NotificationManager;
import android.content.Context;
import android.os.Bundle;
import android.accounts.Account;
import android.accounts.AccountManager;

public class MainActivity extends startact {
	
	static String intentArgs;
	
	@Override
	public int getExecutionPropertiesResource() {
		return R.raw.execution;
	}
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

		boolean shouldCreateAccount = !(getResources().getString(R.string.app_account).equals(""));
		// Adds the application as an account in the Android settings screen (For empty URL generic apps).
		// It will be executed if the account permission exists in the manifest.
		if (shouldCreateAccount)
		{
			Account appAccount = new Account(getResources().getString(R.string.app_name), getResources().getString(R.string.app_account));
			AccountManager accountManager = AccountManager.get(getApplicationContext());
			accountManager.addAccountExplicitly(appAccount, null, null);
		}

		// handle the URI intent args (when launched from another application)
		intentArgs = "";
		if (getIntent().getData() != null)
		{
			intentArgs = getIntent().getData().getQuery();
		}
		// handle the URI intent args (when launched from a push notification)
		if (getIntent().getStringExtra("gcm-message") != null) {
			intentArgs = getIntent().getStringExtra("gcm-message");
			MyFirebaseMessagingService.messages.clear();
		}
	}

	@Override
	public void finish() {
		super.finish();

		NotificationManager notificationManager =
				(NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
		notificationManager.cancelAll();
	}
}
