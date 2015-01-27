
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
	public static String[] UserNameList;
    /*test*/
	public static void init_android()
	{
		Log.d("HXSDK","init hxsdk");
	}
	
	//��½���ţ�����Ϊ�û���������
	public static boolean login_android(String userName,String password) {
		EMChatManager.getInstance().login(userName, password, new EMCallBack(){
			//��½�Ļص�����
			@Override
			public void onSuccess(){
				Log.d("main","��½����������ɹ�");
				//isLogin(true);
				//UserNameList = getAllContactUserNames();
				//EMGroupManager.getInstance().loadAllGroups();
				//EMChatManager.getInstance().loadAllConversations();	
			}
			@Override
			public void onProgress(int progress,String status){
			}
			@Override
			public void onError(int code,String message){
				Log.d("FAIL","��½���������ʧ��");
				//isLogin(false);
				
			}
		});
		return true;
	}
	//private static native void isLogin(boolean islogin);
	
	//�˳�
	public static void logout_android(){
		//EMChatManager.getInstance().logout();//�˷�����ͬ������
		EMChatManager.getInstance().logout(new EMCallBack(){ //�˷������첽����

			@Override
			public void onSuccess() {
				// TODO Auto-generated method stub
				Log.d("main","�˳��������ɹ�");
				
			}
			@Override
			public void onProgress(int progress,String status){
				
			}
			@Override
			public void onError(int code,String message){
				Log.d("main","�˳����������ʧ��");
			}
			
		});
	}
	
	
	//�޸��û�nickname
	public static void updateCurrentUserNick_android(String userName)
	{
		EMChatManager.getInstance().updateCurrentUserNick(userName);
	}
	
	//��ȡ�����б�
		public static String[] getAllContactUserNames()
		{
			List<String> usernames = new ArrayList<String>();
			try {
				usernames = EMContactManager.getInstance().getContactUserNames();
			} catch (EaseMobException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				Log.d("main","��ȡ�����б�ʧ��");
			}
			String[] userListTo = new String[usernames.size()];
			String[] userList = (String[])usernames.toArray(userListTo);
			Log.i("main","����:"+userList[0]);
			return userList;

		}
		
		public static String[] getContactUserNames()
		{
			
			return UserNameList;
		}
}
