
package com.CrossApp.IM;

import org.CrossApp.lib.Cocos2dxActivity;
import org.CrossApp.lib.Cocos2dxGLSurfaceView;

import com.easemob.EMCallBack;
import com.easemob.chat.EMChat;
import com.easemob.chat.EMChatManager;
import com.easemob.chat.EMChatOptions;

import android.os.Bundle;
import android.util.Log;

public class IM extends Cocos2dxActivity{
	static EMChatOptions options;
	
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	
		EMChat.getInstance().init(getApplicationContext());
	}

	public static void init_android(String userName,String password) {
		EMChatManager.getInstance().login(userName,password,
				new EMCallBack() {//回调
					@Override
					public void onSuccess() {
						Log.d("qiaoxin sdk", "登陆聊天服务器成功！");
//						runOnUiThread(new Runnable() {
//							public void run() {
//								Log.d("main", "登陆聊天服务器成功！");		
//							}
//						});
					}

					@Override
					public void onProgress(int progress, String status) {
						Log.d("qiaoxin sdk", "登陆聊天服务器onProgress！");
					}

					@Override
					public void onError(int code, String message) {
						Log.d("qiaoxin sdk", "登陆聊天服务器失败！");
					}
				});
	}

	public static void logout_android(){
		Log.d("qiaoxin sdk", "logout_android！");
		EMChatManager.getInstance().logout();//此方法为同步方法
		//EMChatManager.getInstance().logout(new EMCallBack(){})//此方法为异步方法
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
