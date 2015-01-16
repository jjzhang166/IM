
package com.CrossApp.IM;

import android.app.Activity;
import org.CrossApp.lib.Cocos2dxActivity;
import org.CrossApp.lib.Cocos2dxGLSurfaceView;

import com.easemob.EMCallBack;
import com.easemob.chat.EMChat;
import com.easemob.chat.EMChatManager;
import com.easemob.chat.EMChatOptions;

import android.os.Bundle;
import android.util.Log;

public class IM extends Cocos2dxActivity{
	
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	
		
		
	}
    /*test*/
	public static native int getInt(int a, int b);
	public static native String getString(String name);
	
	public static native int callAdd();
	public static native boolean callJudge(); 
	public static native void aaaaaaaa(); 
	public static native void bbbbbb(String userName,String password);
	
	public static void init_android(String userName,String password) {
		Log.d("qiaoxin sdk", "init_android  userName is: "+userName+"password is: "+password);
	
	}

	public static void logout_android(){
		Log.d("qiaoxin sdk", "logout_android！");
		//EMChatManager.getInstance().logout();//此方法为同步方法
		//EMChatManager.getInstance().logout(new EMCallBack(){})//此方法为异步方法
	}
    /*test end*/
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
