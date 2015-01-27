
package com.CrossApp.IM;

import java.util.ArrayList;

import java.util.List;

import com.easemob.EMCallBack;
import com.easemob.chat.EMChat;
import com.easemob.chat.EMChatManager;
import com.easemob.chat.EMChatOptions;
import com.easemob.chat.EMContactManager;
import com.easemob.chat.EMGroupManager;
import com.easemob.exceptions.EaseMobException;

import android.os.Bundle;
import android.util.Log;

public class IMINIT{
    /*test*/
	public static void init_android()
	{
		Log.d("HXSDK","init hxsdk");
	}
	
	//ע�ỷ�ţ�����Ϊ�û���������
	public static void registerAccount_android(String userName,String password)
	{
		 try {
	         // ����sdkע�᷽��
	        EMChatManager.getInstance().createAccountOnServer(userName, password);
	      } catch (final Exception e) {
	    	  Log.d("main","ע��ʧ��");
	    	  isRegister(false);
	      }
		 isRegister(true);
	}
	//��½���ţ�����Ϊ�û���������
	public static void login_android(String userName,String password) {
		EMChatManager.getInstance().login(userName, password, new EMCallBack(){
			//��½�Ļص�����
			@Override
			public void onSuccess(){
				Log.d("main","��½����������ɹ�");
				isLogin(true);
				//EMGroupManager.getInstance().loadAllGroups();
				//EMChatManager.getInstance().loadAllConversations();	
			}
			@Override
			public void onProgress(int progress,String status){
			}
			@Override
			public void onError(int code,String message){
				Log.d("FAIL","��½���������ʧ��");
				isLogin(false);
				
			}
		});
	}
	private static native void isLogin(boolean islogin);
	private static native void isRegister(boolean isregister);
	
	//�˳�
	public static void logout_android(){
		//EMChatManager.getInstance().logout();//�˷�����ͬ������
		EMChatManager.getInstance().logout(new EMCallBack(){ //�˷������첽����

			@Override
			public void onSuccess() {
				// TODO Auto-generated method stub
				Log.d("main","�˳��������ɹ�");
				isLogin(false);
			}
			@Override
			public void onProgress(int progress,String status){
				
			}
			@Override
			public void onError(int code,String message){
				Log.d("main","�˳����������ʧ��");
				isLogin(true);
			}
			
		});
	}
	
	
	
}
