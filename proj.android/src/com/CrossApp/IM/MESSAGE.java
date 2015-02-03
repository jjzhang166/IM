package com.CrossApp.IM;

import java.util.ArrayList;
import java.util.List;
import com.easemob.EMCallBack;
import com.easemob.chat.EMChat;
import com.easemob.chat.EMChatManager;
import com.easemob.chat.EMChatOptions;
import com.easemob.chat.EMContactListener;
import com.easemob.chat.EMContactManager;
import com.easemob.chat.EMConversation;
import com.easemob.chat.EMGroupManager;
import com.easemob.chat.EMMessage;
import com.easemob.chat.TextMessageBody;
import com.easemob.exceptions.EaseMobException;

import android.content.IntentFilter;
import android.os.Bundle;
import android.util.Log;

public class MESSAGE {

	public static void sendMessage_android(String Message,String username)
	{
		//��ȡ���������˵ĻỰ���󡣲���usernameΪ�����˵�userid����groupid�������е�username�������
		EMConversation conversation = EMChatManager.getInstance().getConversation(username);
		//����һ���ı���Ϣ
		EMMessage message = EMMessage.createSendMessage(EMMessage.Type.TXT);
		//������Ϣbody
		TextMessageBody txtBody = new TextMessageBody(Message);
		message.addBody(txtBody);
		//���ý�����
		message.setReceipt(username);
		//����Ϣ���뵽�˻Ự������
		conversation.addMessage(message);
		//������Ϣ
		EMChatManager.getInstance().sendMessage(message, new EMCallBack(){

			@Override
			public void onError(int arg0, String arg1) {
				// TODO Auto-generated method stub
				Log.d("main","������Ϣʧ��");
			}

			@Override
			public void onProgress(int arg0, String arg1) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void onSuccess() {
				// TODO Auto-generated method stub
				Log.d("main","������Ϣ�ɹ�");
			}
			
		});
	}
	
	public static void receiveMessage_android()
	{
		EMChat.getInstance().setAppInited();
	}
}
