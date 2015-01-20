
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
	    //��ʼ��HXSDK
	    public void onCreate() { 
	       super.onCreate();
	       appContext = this;
	       
	       int pid = android.os.Process.myPid();
	        String processAppName = getAppName(pid);
	        
	        // ���app������Զ�̵�service����application:onCreate�ᱻ����2��
	        // Ϊ�˷�ֹ����SDK����ʼ��2�Σ��Ӵ��жϻᱣ֤SDK����ʼ��1��
	        // Ĭ�ϵ�app�����԰���ΪĬ�ϵ�process name�����У�����鵽��process name����app��process name����������
	        
	        if (processAppName == null ||!processAppName.equalsIgnoreCase("com.CrossApp.IM")){
	            Log.d("TAG","the service process!");
	            //"com.easemob.chatuidemo"Ϊdemo�İ����������Լ���Ŀ��Ҫ�ĳ��Լ�����
	            
	            // ���application::onCreate �Ǳ�service ���õģ�ֱ�ӷ���
	           //return false;
	        }
	       //��ʼ������SDK
	       Log.d("Application", "��ʼ������SDK");
	       EMChat.getInstance().init(appContext);

	       //��ȡ��EMChatOptions����
	       EMChatOptions options = EMChatManager.getInstance().getChatOptions();
	       //Ĭ����Ӻ���ʱ���ǲ���Ҫ��֤�ģ��ĳ���Ҫ��֤
	       options.setAcceptInvitationAlways(false);
	       //�����յ���Ϣ�Ƿ�������Ϣ֪ͨ��Ĭ��Ϊtrue
	       options.setNotificationEnable(false);
	       //�����յ���Ϣ�Ƿ���������ʾ��Ĭ��Ϊtrue
	       options.setNoticeBySound(false);
	       //�����յ���Ϣ�Ƿ��� Ĭ��Ϊtrue
	       options.setNoticedByVibrate(false);
	       //����������Ϣ�����Ƿ�����Ϊ���������� Ĭ��Ϊtrue
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