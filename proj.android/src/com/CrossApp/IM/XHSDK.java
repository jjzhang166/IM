
package com.CrossApp.IM;

import java.util.Iterator;

import java.util.List;

import android.app.Activity;
import android.app.ActivityManager;
import android.app.Application;

import com.easemob.EMCallBack;
import com.easemob.chat.EMChat;
import com.easemob.chat.EMChatManager;
import com.easemob.chat.EMChatOptions;

import android.os.Bundle;
import android.util.Log;
import android.content.*;
import android.content.pm.PackageManager;

public class XHSDK extends Application{
	 public static Context appContext;
	    @Override
	    //初始化HXSDK
	    public void onCreate() { 
	       super.onCreate();
	       appContext = this;
	       
	       int pid = android.os.Process.myPid();
	        String processAppName = getAppName(pid);
	        
	        // 如果app启用了远程的service，此application:onCreate会被调用2次
	        // 为了防止环信SDK被初始化2次，加此判断会保证SDK被初始化1次
	        // 默认的app会在以包名为默认的process name下运行，如果查到的process name不是app的process name就立即返回
	        
	        if (processAppName == null ||!processAppName.equalsIgnoreCase("com.CrossApp.IM")){
	            Log.d("TAG","the service process!");
	            //"com.easemob.chatuidemo"为demo的包名，换到自己项目中要改成自己包名
	            
	            // 则此application::onCreate 是被service 调用的，直接返回
	           //return false;
	        }
	       //初始化环信SDK
	       Log.d("Application", "初始化环信SDK");
	       EMChat.getInstance().init(appContext);

	       //获取到EMChatOptions对象
	       EMChatOptions options = EMChatManager.getInstance().getChatOptions();
	       //默认添加好友时，是不需要验证的，改成需要验证
	       options.setAcceptInvitationAlways(false);
	       //设置收到消息是否有新消息通知，默认为true
	       options.setNotificationEnable(false);
	       //设置收到消息是否有声音提示，默认为true
	       options.setNoticeBySound(false);
	       //设置收到消息是否震动 默认为true
	       options.setNoticedByVibrate(false);
	       //设置语音消息播放是否设置为扬声器播放 默认为true
	       options.setUseSpeaker(false);
	    }
	    
	    private String getAppName(int pID) {
			String processName = null;
			ActivityManager am = (ActivityManager) this
					.getSystemService(ACTIVITY_SERVICE);
			List l = am.getRunningAppProcesses();
			Iterator i = l.iterator();
			PackageManager pm = this.getPackageManager();
			while (i.hasNext()) {
				ActivityManager.RunningAppProcessInfo info = (ActivityManager.RunningAppProcessInfo) (i
						.next());
				try {
					if (info.pid == pID) {
						CharSequence c = pm.getApplicationLabel(pm
								.getApplicationInfo(info.processName,PackageManager.GET_META_DATA));
						processName = info.processName;
						return processName;
					}
				} catch (Exception e) {
				}
			}
			return processName;
		}
}