package com.CrossApp.IM;
import java.util.ArrayList;


import java.util.List;
import com.easemob.EMCallBack;
import com.easemob.chat.EMChat;
import com.easemob.chat.EMChatManager;
import com.easemob.chat.EMChatOptions;
import com.easemob.chat.EMContactListener;
import com.easemob.chat.EMContactManager;
import com.easemob.chat.EMGroupManager;
import com.easemob.exceptions.EaseMobException;

import android.content.IntentFilter;
import android.os.Bundle;
import android.util.Log;
public class FRIENDMANAGENT {
	//获取好友列表
			public static String[] getContactUserNames()
			{
				List<String> usernames = new ArrayList<String>();
				try {
					usernames = EMContactManager.getInstance().getContactUserNames();
					Log.d("main","获取好友列表成功");
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
	//添加好友
		public static boolean addContact(String toAddUsername,String reason)
		{
			try {
				EMContactManager.getInstance().addContact(toAddUsername, reason);
				Log.d("main","添加成功");
				return true;
			} catch (EaseMobException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				Log.d("main","添加好友失败");
				return false;
			}
		}
		
		//删除好友
		public static boolean deleteContact(String username)
		{
			try{
				Log.d("mian","start delete");
				EMContactManager.getInstance().deleteContact("chinahypo1");
				Log.d("main","删除好友成功");
				return true;
			} catch (EaseMobException e){
				// TODO Auto-generated catch block
				e.printStackTrace();
			    Log.d("main","删除好友失败");
			    return false;
			}
		}
		
		//同意好友请求
		public static void acceptInvitation(String username)
		{
			try {
				EMChatManager.getInstance().acceptInvitation(username);
			} catch (EaseMobException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				Log.d("main","同意好友请求失败");
			}
		}
		
		//拒绝好友请求
		public static void refuseInvitation(String username)
		{
			try {
				EMChatManager.getInstance().refuseInvitation(username);
			} catch (EaseMobException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				Log.d("main","拒绝好友请求失败");
			}
		}
		
		//监听好友请求
		public static void setContactListener()
		{
			//未完成
		}
		
		//监听好友事件，未完成
		public static void setContactStatus()
		{
			EMContactManager.getInstance().setContactListener(new EMContactListener() {
				
				@Override
				public void onContactAgreed(String username) {
					//好友请求被同意
				}
				
				@Override
				public void onContactRefused(String username) {
					//好友请求被拒绝
				}
				
				@Override
				public void onContactInvited(String username, String reason) {
					//收到好友邀请
				}
				
				@Override
				public void onContactDeleted(List<String> usernameList) {
					//被删除时回调此方法
				}
				
				
				@Override
				public void onContactAdded(List<String> usernameList) {
					//增加了联系人时回调此方法
				}
			});
		}
		
		//获取黑名单列表
		public static String[] getBlackListUsernames()
		{
			List<String> blackUserListname = null;
			blackUserListname = EMContactManager.getInstance().getBlackListUsernames();
			String[] usernameList;
			usernameList = (String[]) blackUserListname.toArray();
			return usernameList;
		}
		
		//把用户加入到黑名单
		public static void  addUserToBlackList(String username,Boolean isboth)
		{
			try {
				EMContactManager.getInstance().addUserToBlackList(username, isboth);
			} catch (EaseMobException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				Log.d("main","添加黑名单失败");
			}
		}
		
		//把用户从黑名单中移除
		public static void deleteUserFromBlackList(String username)
		{
			try {
				EMContactManager.getInstance().deleteUserFromBlackList(username);
			} catch (EaseMobException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				Log.d("main","移除黑名单失败");
			}
		}
		

}
