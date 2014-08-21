package org.cocos2dx.lib;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.ProtocolException;
import java.net.URL;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.util.Log;

public class QuickHTTPInterface {
    static HttpURLConnection createURLConnect(String strURL) {
        Log.i("QuickHTTPInterface", "createURLConnect");
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
        Log.i("QuickHTTPInterface", "setRequestMethod");
        try {
            http.setRequestMethod(strMedthod);
        } catch (ProtocolException e) {
            Log.e("QuickHTTPInterface", e.toString());
        }
    }

    static void addRequestHeader(HttpURLConnection http, String strkey, String strValue) {
        Log.i("QuickHTTPInterface", "addRequestHeader");
        http.addRequestProperty(strkey, strValue);
    }

    static void setTimeout(HttpURLConnection http, int msTime) {
        Log.i("QuickHTTPInterface", "setTimeout");
        http.setConnectTimeout(msTime);
        http.setReadTimeout(msTime);
    }

    static int connect(HttpURLConnection http) {
        int nSuc = 0;

        Log.i("QuickHTTPInterface", "connect");
        try {
            http.connect();
        } catch (IOException e) {
            Log.e("QuickHTTPInterface", e.toString());
            nSuc = 1;
        }

        return nSuc;
    }

    static void postContent(HttpURLConnection http, String name, String value) {
        Log.i("QuickHTTPInterface", "postContent");
        try {
            DataOutputStream out = new DataOutputStream(http.getOutputStream());
            String content = name + "=" + value;
            out.writeBytes(content);
            out.flush();
            out.close();
        } catch (IOException e) {
            Log.e("QuickHTTPInterface", e.toString());
        }
    }

    static void postFile(HttpURLConnection http, String fileName, String filePath) {
        Log.i("QuickHTTPInterface", "postFile");
        try {
            FileInputStream fin = new FileInputStream(filePath);
            OutputStream out = http.getOutputStream();

            byte[] buffer = new byte[1024];
            int len = 0;
            while((len = fin.read(buffer)) != -1) {
                out.write(buffer, 0, len);
            }
            out.flush();
            out.close();
            fin.close();
        } catch (IOException e) {
            Log.e("QuickHTTPInterface", e.toString());
        }
    }

    static int getResponedCode(HttpURLConnection http) {
        Log.i("QuickHTTPInterface", "getResponedCode");
        int code = 0;
        try {
            code = http.getResponseCode();
        } catch (IOException e) {
            Log.e("QuickHTTPInterface", e.toString());
        }
        return code;
    }

    static String getResponedErr(HttpURLConnection http) {
        Log.i("QuickHTTPInterface", "getResponedErr");
        String msg;
        try {
            msg = http.getResponseMessage();
        } catch (IOException e) {
            msg = e.toString();
            Log.e("QuickHTTPInterface", msg);
        }

        return msg;
    }

    static String getResponedHeader(HttpURLConnection http) {
        Log.i("QuickHTTPInterface", "getResponedHeader");
        Map<String, List<String>> headers = http.getHeaderFields();

        JSONObject json = new JSONObject();
        try {
            for (Entry<String, List<String>> entry: headers.entrySet()) {
                String key = entry.getKey();
                if (null == key) {
                    key = "";
                }
                List<String> value = entry.getValue();
                JSONArray jsonArray = new JSONArray();
                for(String strVal : value) {
                    jsonArray.put(strVal);
                }
                json.put(key, jsonArray);
            }
        } catch(JSONException e) {
            Log.e("QuickHTTPInterface", e.toString());
        }

        return json.toString();
    }

    static String getResponedHeaderByIdx(HttpURLConnection http, int idx) {
        //                Log.i("QuickHTTPInterface", "getResponedHeader");
        Map<String, List<String>> headers = http.getHeaderFields();
        if (null == headers) {
            return null;
        }

        String header = null;

        int counter = 0;
        for (Entry<String, List<String>> entry: headers.entrySet()) {
            if (counter == idx) {
                String key = entry.getKey();
                if (null == key) {
                    header = listToString(entry.getValue(), ",") + "\n";
                } else {
                    header = key + ":" + listToString(entry.getValue(), ",") + "\n";
                }
                break;
            }
            counter++;
        }

        return header;
    }

    static String getResponedHeaderByKey(HttpURLConnection http, String key) {
        return http.getHeaderField(key);
    }

    static String getResponedString(HttpURLConnection http) {
        Log.i("QuickHTTPInterface", "getResponedString");
        try {
            DataInputStream in = new DataInputStream(http.getInputStream());

            byte[] buffer = new byte[1024];
            int len = in.read(buffer);
            StringBuilder strBuilder = null;
            if (-1 == len) {
                strBuilder = new StringBuilder("\0");
            } else {
                strBuilder = new StringBuilder("\1");
                strBuilder.append(new String(buffer, 0, len));
            }
            return strBuilder.toString();
        } catch (IOException e) {
            Log.e("QuickHTTPInterface", e.toString());
        }

        return null;
    }

    static void close(HttpURLConnection http) {
        Log.i("QuickHTTPInterface", "close");
        try {
            http.getInputStream().close();
        } catch (IOException e) {
            Log.e("QuickHTTPInterface", e.toString());
        }
    }

    public static String listToString(List<String> list, String strInterVal) {
        if (list == null) {
            return null;
        }
        StringBuilder result = new StringBuilder();
        boolean flag = false;
        for (String str : list) {
            if (flag) {
                result.append(strInterVal);
            }
            if (null == str) {
                str = "";
            }
            result.append(str);
            flag = true;
        }
        return result.toString();
    }

}
