
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
	
	//注册环信，参数为用户名和密码
	public static void registerAccount_android(String userName,String password)
	{
		 try {
	         // 调用sdk注册方法
	        EMChatManager.getInstance().createAccountOnServer(userName, password);
	      } catch (final Exception e) {
	    	  Log.d("main","注册失败");
	    	  isRegister(false);
	      }
		 isRegister(true);
	}
	//登陆环信，参数为用户名和密码
	public static void login_android(String userName,String password) {
		EMChatManager.getInstance().login(userName, password, new EMCallBack(){
			//登陆的回调函数
			@Override
			public void onSuccess(){
				Log.d("main","登陆聊天服务器成功");
				isLogin(true);
				//EMGroupManager.getInstance().loadAllGroups();
				//EMChatManager.getInstance().loadAllConversations();	
			}
			@Override
			public void onProgress(int progress,String status){
			}
			@Override
			public void onError(int code,String message){
				Log.d("FAIL","登陆聊天服务器失败");
				isLogin(false);
				
			}
		});
	}
	private static native void isLogin(boolean islogin);
	private static native void isRegister(boolean isregister);
	
	//退出
	public static void logout_android(){
		//EMChatManager.getInstance().logout();//此方法是同步方法
		EMChatManager.getInstance().logout(new EMCallBack(){ //此方法是异步方法

			@Override
			public void onSuccess() {
				// TODO Auto-generated method stub
				Log.d("main","退出服务器成功");
				isLogin(false);
			}
			@Override
			public void onProgress(int progress,String status){
				
			}
			@Override
			public void onError(int code,String message){
				Log.d("main","退出聊天服务器失败");
				isLogin(true);
			}
			
		});
	}
	
	
	
}
