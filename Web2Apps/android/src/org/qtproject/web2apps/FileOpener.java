
package org.qtproject.synnext;

import android.content.Context;
import android.content.Intent;
import android.webkit.MimeTypeMap;
import android.app.Notification;
import android.app.NotificationManager;
import org.qtproject.qt5.android.bindings.QtApplication;
import org.qtproject.qt5.android.bindings.QtActivity;
import android.content.Context;
import java.io.File;
import java.lang.Runnable;
import android.util.Log;
import android.net.Uri;

public class FileOpener extends org.qtproject.qt5.android.bindings.QtActivity
{
    public static FileOpener instance;

    FileOpener() {
        instance = this;
    }

    /* Open any type of document based on mime type */

    public static void openAndroidUrl(String url, QtActivity activity) {

        //instance.runOnUiThread(new Runnable() {
        //public void run() {
                //Log.d(QtApplication.QtTAG, "openAndroidUrl" + url);

                File file = new File(url);
                MimeTypeMap map = MimeTypeMap.getSingleton();
                String ext = MimeTypeMap.getFileExtensionFromUrl(file.getName());
                String type = map.getMimeTypeFromExtension(ext);

                if (type == null)
                    type = "*/*";
                //Log.d(QtApplication.QtTAG, "openAndroidUrl type" + type);
                Intent intent = new Intent(Intent.ACTION_VIEW);
                Uri data = Uri.fromFile(file);

                intent.setDataAndType(data, type);

                activity.startActivity(intent);
         //    }
         //  });

    }

    /* Send notification */
/*
    private static NotificationManager m_notificationManager;
    private static Notification.Builder m_builder;
    private static NotificationClient m_instance;
    public static void notify(String s)
    {
        if (m_notificationManager == null) {
            m_notificationManager = (NotificationManager)m_instance.getSystemService(Context.NOTIFICATION_SERVICE);
            m_builder = new Notification.Builder(m_instance);
            m_builder.setSmallIcon(R.drawable.icon);
            m_builder.setContentTitle("A message from Qt!");
        }

        m_builder.setContentText(s);
        m_notificationManager.notify(1, m_builder.build());
    }*/

    /* Share content */
    /* Call using :
    QAndroidJniObject jTitle = QAndroidJniObject::fromString(title);
    QAndroidJniObject jSubject = QAndroidJniObject::fromString(subject);
    QAndroidJniObject jContent = QAndroidJniObject::fromString(content);
    QAndroidJniObject activity = QtAndroid::androidActivity();
    QAndroidJniObject::callStaticMethod<void>(
        "net/exit0/androidshare/ShareIntent",
        "shareText",
        "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;"
              "Lorg/qtproject/qt5/android/bindings/QtActivity;)V",
        jTitle.object<jstring>(),
        jSubject.object<jstring>(),
        jContent.object<jstring>(),
        activity.object<jobject>()
   );
   */
   /*
    static public void shareText(String title, String subject,
                                 String content, QtActivity activity)
    {
        Intent share = new Intent(Intent.ACTION_SEND);
        share.setType("text/plain");

        share.putExtra(Intent.EXTRA_SUBJECT, subject);
        share.putExtra(Intent.EXTRA_TEXT, Html.fromHtml(content).toString());
        share.putExtra(Intent.EXTRA_HTML_TEXT, content);
        activity.startActivity(Intent.createChooser(share, title));
    }
    */

}
