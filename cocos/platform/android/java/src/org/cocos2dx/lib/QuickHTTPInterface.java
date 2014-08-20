package org.cocos2dx.lib;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.io.StringBufferInputStream;
import java.net.HttpURLConnection;
import java.net.ProtocolException;
import java.net.URL;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

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
    
    static void postContent(HttpURLConnection http, String name, String value) {
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
    
    static void postFile(HttpURLConnection http, String fileName) {
		try {
			FileInputStream fin = new FileInputStream(fileName);
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
    	int code = 0;
    	try {
			code = http.getResponseCode();
		} catch (IOException e) {
			Log.e("QuickHTTPInterface", e.toString());
		}
    	return code;
    }
    
    static String getResponedHeader(HttpURLConnection http) {
    	Map<String, List<String>> headers = http.getHeaderFields();

        JSONObject json = new JSONObject();
        try {
	        for (Entry<String, List<String>> entry: headers.entrySet()) {
	            String key = entry.getKey();
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
    
    static String getResponedString(HttpURLConnection http) {
    	try {
	    	DataInputStream in = new DataInputStream(http.getInputStream());
	
	    	byte[] buffer = new byte[1024];
	        int len = in.read(buffer);
	        String strResp = new String(buffer, 0, len);
	        return strResp;
    	} catch (IOException e) {
    		Log.e("QuickHTTPInterface", e.toString());
    	}
    	return null;
    }
    
    static void close(HttpURLConnection http) {
    	try {
			http.getInputStream().close();
		} catch (IOException e) {
			Log.e("QuickHTTPInterface", e.toString());
		}
    }

}
