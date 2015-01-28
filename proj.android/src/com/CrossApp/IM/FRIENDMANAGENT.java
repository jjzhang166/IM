package com.CrossApp.IM;
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
	//��Ӻ���
		public static void addContact(String toAddUsername,String reason)
		{
			try {
				EMContactManager.getInstance().addContact(toAddUsername, reason);
			} catch (EaseMobException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				Log.d("main","��Ӻ���ʧ��");
			}
		}
		
		//ɾ������
		public static void deleteContact(String username)
		{
			try{
				EMContactManager.getInstance().deleteContact(username);
			} catch (EaseMobException e){
				// TODO Auto-generated catch block
				e.printStackTrace();
			    Log.d("main","ɾ������ʧ��");
			}
		}
		
		//ͬ���������
		public static void acceptInvitation(String username)
		{
			try {
				EMChatManager.getInstance().acceptInvitation(username);
			} catch (EaseMobException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				Log.d("main","ͬ���������ʧ��");
			}
		}
		
		//�ܾ���������
		public static void refuseInvitation(String username)
		{
			try {
				EMChatManager.getInstance().refuseInvitation(username);
			} catch (EaseMobException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				Log.d("main","�ܾ���������ʧ��");
			}
		}
		
		//������������
		public static void setContactListener()
		{
			//δ���
		}
		
		//���������¼���δ���
		public static void setContactStatus()
		{
			EMContactManager.getInstance().setContactListener(new EMContactListener() {
				
				@Override
				public void onContactAgreed(String username) {
					//��������ͬ��
				}
				
				@Override
				public void onContactRefused(String username) {
					//�������󱻾ܾ�
				}
				
				@Override
				public void onContactInvited(String username, String reason) {
					//�յ���������
				}
				
				@Override
				public void onContactDeleted(List<String> usernameList) {
					//��ɾ��ʱ�ص��˷���
				}
				
				
				@Override
				public void onContactAdded(List<String> usernameList) {
					//��������ϵ��ʱ�ص��˷���
				}
			});
		}
		
		//��ȡ�������б�
		public static String[] getBlackListUsernames()
		{
			List<String> blackUserListname = null;
			blackUserListname = EMContactManager.getInstance().getBlackListUsernames();
			String[] usernameList;
			usernameList = (String[]) blackUserListname.toArray();
			return usernameList;
		}
		
		//���û����뵽������
		public static void  addUserToBlackList(String username,Boolean isboth)
		{
			try {
				EMContactManager.getInstance().addUserToBlackList(username, isboth);
			} catch (EaseMobException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				Log.d("main","��Ӻ�����ʧ��");
			}
		}
		
		//���û��Ӻ��������Ƴ�
		public static void deleteUserFromBlackList(String username)
		{
			try {
				EMContactManager.getInstance().deleteUserFromBlackList(username);
			} catch (EaseMobException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				Log.d("main","�Ƴ�������ʧ��");
			}
		}
		

}
