package com.magicsoftware.magicdev;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import com.magicsoftware.core.CoreApplication;


public class MyFirebaseNotificationClickReceiver extends BroadcastReceiver {

   @Override
   public void onReceive(Context context, Intent intent) {
      // notify the magic application that a message was received and send the "message" from the notification body
      CoreApplication.getInstance().invokeExternalEvent("GCM-message:" + MyFirebaseMessagingService.messages.get(MyFirebaseMessagingService.messages.size() - 1));

      // Upon notification click, reset our messages stack
      MyFirebaseMessagingService.messages.clear();
   }
}
