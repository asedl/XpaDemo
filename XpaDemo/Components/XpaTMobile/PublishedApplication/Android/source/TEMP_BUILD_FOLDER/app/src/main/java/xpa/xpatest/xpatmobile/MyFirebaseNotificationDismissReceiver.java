package xpa.xpatest.xpatmobile;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

public class MyFirebaseNotificationDismissReceiver extends BroadcastReceiver {

   @Override
   public void onReceive(Context context, Intent intent) {
      // Upon notification dismiss, reset our messages stack
      MyFirebaseMessagingService.messages.clear();
   }
}
