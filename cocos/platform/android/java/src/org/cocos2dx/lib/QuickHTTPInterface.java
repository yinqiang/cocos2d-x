package org.cocos2dx.lib;

import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.ProtocolException;
import java.net.URL;

import android.util.Log;

public class QuickHTTPInterface {
    static HttpURLConnection createURLConnect(String strURL) {
        URL url;
        HttpURLConnection urlConnection;
        try {
            url = new URL(strURL);
            urlConnection = (HttpURLConnection)url.openConnection();
        } catch (Exception e) {
            Log.e("QuickHTTPInterface", e.toString());
            return null;
        }

        return urlConnection;
    }

    static void setRequestMethod(HttpURLConnection http, String strMedthod) {
        try {
            http.setRequestMethod(strMedthod);
        } catch (ProtocolException e) {
            Log.e("QuickHTTPInterface", e.toString());
        }
    }

    static void addRequestHeader(HttpURLConnection http, String strkey, String strValue) {
        http.addRequestProperty(strkey, strValue);
    }

    static void setTimeout(HttpURLConnection http, int msTime) {
        http.setConnectTimeout(msTime);
        http.setReadTimeout(msTime);
    }

    static void connect(HttpURLConnection http) {
        try {
            http.connect();
        } catch (IOException e) {
            Log.e("QuickHTTPInterface", e.toString());
        }
    }


}
