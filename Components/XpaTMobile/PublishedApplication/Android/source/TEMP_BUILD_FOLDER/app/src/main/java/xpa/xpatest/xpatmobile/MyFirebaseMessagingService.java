/**
 * Copyright 2016 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package xpa.xpatest.xpatmobile;

import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.media.RingtoneManager;
import android.net.Uri;
import android.support.v4.app.NotificationCompat;
import android.support.v4.app.NotificationManagerCompat;
import android.util.Log;
import com.google.firebase.messaging.FirebaseMessagingService;
import com.google.firebase.messaging.RemoteMessage;
import com.magicsoftware.core.CoreApplication;
import com.magicsoftware.core.EmptyWindow;

import java.util.ArrayList;

public class MyFirebaseMessagingService extends FirebaseMessagingService {

    private static final String TAG = "MyFirebaseMsgService";
    public static ArrayList<String> messages = new ArrayList<>();

    /**
     * Called when message is received.
     *
     * @param remoteMessage Object representing the message received from Firebase Cloud Messaging.
     */
    // [START receive_message]
    @Override
    public void onMessageReceived(RemoteMessage remoteMessage) {
        // [START_EXCLUDE]
        // There are two types of messages data messages and notification messages. Data messages are handled
        // here in onMessageReceived whether the app is in the foreground or background. Data messages are the type
        // traditionally used with GCM. Notification messages are only received here in onMessageReceived when the app
        // is in the foreground. When the app is in the background an automatically generated notification is displayed.
        // When the user taps on the notification they are returned to the app. Messages containing both notification
        // and data payloads are treated as notification messages. The Firebase console always sends notification
        // messages. For more see: https://firebase.google.com/docs/cloud-messaging/concept-options
        // [END_EXCLUDE]

        String title = "";
        String body = "";

        // TODO(developer): Handle FCM messages here.
        // Not getting messages here? See why this may be: https://goo.gl/39bRNJ
        Log.d(TAG, "From: " + remoteMessage.getFrom());

        // Check if message contains a data payload.
        if (remoteMessage.getData().size() > 0) {
            Log.d(TAG, "Message data payload: " + remoteMessage.getData());

            body = remoteMessage.getData().get("body");
            title = remoteMessage.getData().get("title");
        }

        // Check if message contains a notification payload.
        if (remoteMessage.getNotification() != null) {
            Log.d(TAG, "Message Notification Body: " + remoteMessage.getNotification().getBody());
        }

        sendNotification(body, title);
        // Also if you intend on generating your own notifications as a result of a received FCM
        // message, here is where that should be initiated. See sendNotification method below.
    }
    // [END receive_message]

    /**
     * Create and show a simple notification containing the received FCM message.
     *
     * @param messageBody FCM message body received.
     */
    private void sendNotification(String messageBody, String messageTitle) {
        Intent intent = null;

        NotificationManagerCompat notificationManager =
                NotificationManagerCompat.from(this);

        if (CoreApplication.getInstance().MainAct == null)
        {
            intent = new Intent(this, MainActivity.class);
            PendingIntent p = PendingIntent.getService(this, 0, intent, 0);
            if (messages.size() == 0)
                intent.putExtra("gcm-message", messageBody);
            else
                intent.removeExtra("gcm-message");

            intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        }
        else
        {
            intent = new Intent(this, EmptyWindow.class);
            intent.addFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP);

            // notify the magic application that a message was received and send the "message" from the notification body
            // ENABLE THE NEXT LINE IF YOU WANT TO RAISE THE EVENT IMMEDIATELY WHEN THE NOTIFICATION ARRIVES
            //CoreApplication.getInstance().invokeExternalEvent("GCM-message:" + messageBody);
        }

        intent.putExtra("firebaseNotification", true);
        messages.add(messageBody);

        PendingIntent pendingIntent = PendingIntent.getActivity(this, 0 /* Request code */, intent,
                PendingIntent.FLAG_UPDATE_CURRENT);

        StringBuilder builder = new StringBuilder();
        for(String s : messages) {
            builder.append(s + "\r\n");
        }

        Uri defaultSoundUri= RingtoneManager.getDefaultUri(RingtoneManager.TYPE_NOTIFICATION);
        NotificationCompat.Builder notificationBuilder = new NotificationCompat.Builder(this)
                .setSmallIcon(R.drawable.icon)
                .setContentTitle(messageTitle)
                .setAutoCancel(true)
                .setSound(defaultSoundUri)
                .setContentText(messageBody)
                .setNumber(messages.size()) // Comment this if you do not want to see the number of messages
                .setContentIntent(pendingIntent)
                .setDeleteIntent(createOnDismissedIntent(this, 0));

        NotificationCompat.InboxStyle inboxStyle =
                new NotificationCompat.InboxStyle();

        // Moves messages into the expanded layout
        for (int i=0; i < messages.size(); i++) {
            inboxStyle.addLine(messages.get(i));
        }
        // Moves the expanded layout object into the notification object.
        notificationBuilder.setStyle(inboxStyle);

        notificationManager.notify(0 /* ID of notification */, notificationBuilder.build());
    }

    private PendingIntent createOnDismissedIntent(Context context, int notificationId) {
        Intent intent = new Intent(context, MyFirebaseNotificationDismissReceiver.class);
        intent.putExtra("com.my.app.notificationId", notificationId);

        PendingIntent pendingIntent =
                PendingIntent.getBroadcast(context.getApplicationContext(),
                        notificationId, intent, 0);
        return pendingIntent;
    }
}
