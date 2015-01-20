
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
	
	//��½���ţ�����Ϊ�û���������
	public void login_android(String userName,String password) {
		EMChatManager.getInstance().login(userName, password, new EMCallBack(){
			//��½�Ļص�����
			@Override
			public void onSuccess(){
				Log.d("main","��½����������ɹ�");
				//runOnUiThread(new Runnable(){
					//public void run(){
						//Log.d("main","��½����������ɹ�");
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
				Log.d("main","��½���������ʧ��");
			}
			
		});
	}
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
	
	
	
	
	
	
	//��̬��������IM��Ķ���
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
