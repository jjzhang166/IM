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
		//获取到与聊天人的会话对象。参数username为聊天人的userid或者groupid，后文中的username皆是如此
		EMConversation conversation = EMChatManager.getInstance().getConversation(username);
		//创建一条文本消息
		EMMessage message = EMMessage.createSendMessage(EMMessage.Type.TXT);
		//设置消息body
		TextMessageBody txtBody = new TextMessageBody(Message);
		message.addBody(txtBody);
		//设置接收人
		message.setReceipt(username);
		//把消息加入到此会话对象中
		conversation.addMessage(message);
		//发送消息
		EMChatManager.getInstance().sendMessage(message, new EMCallBack(){

			@Override
			public void onError(int arg0, String arg1) {
				// TODO Auto-generated method stub
				Log.d("main","发送消息失败");
			}

			@Override
			public void onProgress(int arg0, String arg1) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void onSuccess() {
				// TODO Auto-generated method stub
				Log.d("main","发送消息成功");
			}
			
		});
	}
	
	public static void receiveMessage_android()
	{
		EMChat.getInstance().setAppInited();
	}
}
