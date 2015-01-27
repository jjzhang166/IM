
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
	
	//登陆环信，参数为用户名和密码
	public static boolean login_android(String userName,String password) {
		EMChatManager.getInstance().login(userName, password, new EMCallBack(){
			//登陆的回调函数
			@Override
			public void onSuccess(){
				Log.d("main","登陆聊天服务器成功");
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
				Log.d("FAIL","登陆聊天服务器失败");
				//isLogin(false);
				
			}
		});
		return true;
	}
	//private static native void isLogin(boolean islogin);
	
	//退出
	public static void logout_android(){
		//EMChatManager.getInstance().logout();//此方法是同步方法
		EMChatManager.getInstance().logout(new EMCallBack(){ //此方法是异步方法

			@Override
			public void onSuccess() {
				// TODO Auto-generated method stub
				Log.d("main","退出服务器成功");
				
			}
			@Override
			public void onProgress(int progress,String status){
				
			}
			@Override
			public void onError(int code,String message){
				Log.d("main","退出聊天服务器失败");
			}
			
		});
	}
	
	
	//修改用户nickname
	public static void updateCurrentUserNick_android(String userName)
	{
		EMChatManager.getInstance().updateCurrentUserNick(userName);
	}
	
	//获取好友列表
		public static String[] getAllContactUserNames()
		{
			List<String> usernames = new ArrayList<String>();
			try {
				usernames = EMContactManager.getInstance().getContactUserNames();
			} catch (EaseMobException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				Log.d("main","获取好友列表失败");
			}
			String[] userListTo = new String[usernames.size()];
			String[] userList = (String[])usernames.toArray(userListTo);
			Log.i("main","名字:"+userList[0]);
			return userList;

		}
		
		public static String[] getContactUserNames()
		{
			
			return UserNameList;
		}
}
