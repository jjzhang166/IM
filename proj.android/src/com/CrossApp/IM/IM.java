
package com.CrossApp.IM;
import android.app.Activity;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;

import org.CrossApp.lib.Cocos2dxActivity;
import org.CrossApp.lib.Cocos2dxGLSurfaceView;

import com.easemob.chat.EMChatManager;
import com.easemob.chat.EMMessage;



import android.os.Bundle;
import android.util.Log;

public class IM extends Cocos2dxActivity{
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		NewMessageBroadcastReceiver msgReceiver = new NewMessageBroadcastReceiver();
		IntentFilter intentFilter = new IntentFilter(EMChatManager.getInstance().getNewMessageBroadcastAction());
		intentFilter.setPriority(3);
		registerReceiver(msgReceiver, intentFilter);
	}
	
	private class NewMessageBroadcastReceiver extends BroadcastReceiver {
	    @Override
	    public void onReceive(Context context, Intent intent) {
	        //��Ϣid
	        String msgId = intent.getStringExtra("msgid");
	        //����Ϣ���˵�username(userid)
	        String msgFrom = intent.getStringExtra("from");
	        //��Ϣ���ͣ��ı���ͼƬ��������Ϣ��,���ﷵ�ص�ֵΪmsg.type.ordinal()��
	        //������Ϣtypeʵ��Ϊ��enum����
	        int msgType = intent.getIntExtra("type", 0);
	        Log.d("main", "new message id:" + msgId + " from:" + msgFrom + " type:" + msgType);
	        //������ķ�����ͨ��msgIdֱ�ӻ�ȡ����message
	        EMMessage message = EMChatManager.getInstance().getMessage(msgId);
	        String content = message.toString();
	        Log.d("main","����:"+content);
	        }
		}
	
	
	
	
	
	
    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// IM should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }

    static {
    	System.loadLibrary("ffmpeg"); 
        System.loadLibrary("CrossApp_cpp");
    }     
}
