package com.CrossApp.IM;

import java.io.File;

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

import com.easemob.chat.ImageMessageBody;
import com.easemob.chat.TextMessageBody;
import com.easemob.chat.VoiceMessageBody;
import com.easemob.exceptions.EaseMobException;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

import android.content.IntentFilter;
import android.os.Bundle;
import android.util.Log;


public class MESSAGE{


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
	
	//发送图片消息
	public void sendMessageWithImage_android(String imagepath,String username)
	{
		EMConversation conversation = EMChatManager.getInstance().getConversation(username);
		EMMessage message = EMMessage.createSendMessage(EMMessage.Type.IMAGE);
		ImageMessageBody body = new ImageMessageBody(new File(imagepath));
		// 默认超过100k的图片会压缩后发给对方，可以设置成发送原图
		// body.setSendOriginalImage(true);
		message.addBody(body);
		message.setReceipt(username);
		conversation.addMessage(message);
		EMChatManager.getInstance().sendMessage(message, new EMCallBack(){

			@Override
			public void onError(int arg0, String arg1) {
				// TODO Auto-generated method stub
				Log.d("main","发送图片失败");
			}

			@Override
			public void onProgress(int arg0, String arg1) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void onSuccess() {
				// TODO Auto-generated method stub
				Log.d("main","发送图片成功");
			}
			
		});
	}
	

	//接收消息
	public static void receiveMessage_android()
	{

		EMChat.getInstance().setAppInited();
	}

}
