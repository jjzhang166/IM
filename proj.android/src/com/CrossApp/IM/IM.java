
package com.CrossApp.IM;

import android.app.Activity;

import android.content.Context;

import org.CrossApp.lib.Cocos2dxActivity;
import org.CrossApp.lib.Cocos2dxGLSurfaceView;

import com.easemob.EMCallBack;
import com.easemob.chat.EMChat;
import com.easemob.chat.EMChatManager;
import com.easemob.chat.EMChatOptions;
import com.easemob.chat.EMGroupManager;

import android.os.Bundle;
import android.util.Log;

public class IM extends Cocos2dxActivity{
	private static IM instance = new IM();
	
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	
	}
    /*test*/
	public static void init_android()
	{
		Log.d("HXSDK","init hxsdk");
	}
	
	//登陆环信，参数为用户名和密码
	public void login_android(String userName,String password) {
		EMChatManager.getInstance().login(userName, password, new EMCallBack(){
			//登陆的回调函数
			@Override
			public void onSuccess(){
				Log.d("main","登陆聊天服务器成功");
				//runOnUiThread(new Runnable(){
					//public void run(){
						//Log.d("main","登陆聊天服务器成功");
					//	EMGroupManager.getInstance().loadAllGroups();
					//	EMChatManager.getInstance().loadAllConversations();
					//}
					
				//});
			}
			@Override
			public void onProgress(int progress,String status){
				
			}
			
			@Override
			public void onError(int code,String message){
				Log.d("main","登陆聊天服务器失败");
			}
			
		});
	}
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
	
	
	
	
	
	
	//静态方法返回IM类的对象
	public static Object getObj()
	{
		return instance;
	}
	
	
	
    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// IM should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }

    static {
        System.loadLibrary("CrossApp_cpp");
    }     
}
