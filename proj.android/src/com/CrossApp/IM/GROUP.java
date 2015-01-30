package com.CrossApp.IM;
import java.util.ArrayList;

import java.util.List;
import com.easemob.EMCallBack;
import com.easemob.chat.EMChat;
import com.easemob.chat.EMChatManager;
import com.easemob.chat.EMChatOptions;
import com.easemob.chat.EMContactListener;
import com.easemob.chat.EMContactManager;
import com.easemob.chat.EMGroup;
import com.easemob.chat.EMGroupInfo;
import com.easemob.chat.EMGroupManager;
import com.easemob.exceptions.EaseMobException;

import android.os.Bundle;
import android.util.Log;

public class GROUP {
	//����Ⱥ
	public static void createGroup_android(String groupname,String groupdescription,boolean ispublic,boolean isAllow)
	{
		if(ispublic)
		{
			try {
				EMGroupManager.getInstance().createPublicGroup(groupname, groupdescription, null, isAllow);
				Log.d("main","��������Ⱥ�ɹ�");
			} catch (EaseMobException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				Log.d("main","��������Ⱥʧ��");
			}
		}
		else
		{
			try {
				EMGroupManager.getInstance().createPrivateGroup(groupname, groupdescription, null,isAllow);
				Log.d("mian","����˽��Ⱥ��ɹ�");
			} catch (EaseMobException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				Log.d("main","����˽��Ⱥʧ��");
			}
		}
	}
	//��ȡ����Ⱥ
	public static Object[] getPublicGroup_android()
	{
		List<EMGroupInfo> groupsList = null;
		//��ȡ���й���Ⱥ�б�
		try {
			groupsList = EMGroupManager.getInstance().getAllPublicGroupsFromServer();
			Log.d("main","��ȡ����Ⱥ�ɹ�");
		} catch (EaseMobException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d("main","��ȡ����Ⱥʧ��");
		}
		EMGroupInfo[] groupListTo = new EMGroupInfo[groupsList.size()];
		EMGroupInfo[] publicgroupList =(EMGroupInfo[])groupsList.toArray(groupListTo);
		for(EMGroupInfo groupinfo:publicgroupList)
		{
			String id = groupinfo.getGroupId();
			String name = groupinfo.getGroupName();
			Log.i("main","����:"+id+name);
		}
		return publicgroupList;
		
	}
	
	//��ȡ�Ҽ����Ⱥ�б�
	public static Object[] getMyGroupList_android()
	{
		try {
			List<EMGroup> grouplist = EMGroupManager.getInstance().getGroupsFromServer();
			Log.d("main","��������ȡ�б�ɹ�");
		} catch (EaseMobException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d("main","��������ȡ�б�ʧ��");
		}
		
		//�ӱ��ؼ���Ⱥ���б�
		List<EMGroup> grouplistlocal = EMGroupManager.getInstance().getAllGroups();
		
		EMGroup[] groupListTo = new EMGroup[grouplistlocal.size()];
		EMGroup[] groupList = (EMGroup[])grouplistlocal.toArray(groupListTo);
		
		for(EMGroup group:groupList)
		{
			String id = group.getGroupId();
			Log.i("MAIN","id="+id);
			String name = group.getGroupName();
			Log.i("MAIN","id="+name);
			String des = group.getDescription();
			Log.i("MAIN","id="+des);
			int numbers = group.getAffiliationsCount();
			Log.i("MAIN","id="+numbers);
			
		}
		
		return groupList;
	}
	
	//���벻��Ҫ��֤��Ⱥ
	public static boolean joinNoNeedCheckGroup_android(String groupid)
	{
		try {
			EMGroupManager.getInstance().joinGroup(groupid);
			Log.d("main","��Ⱥ�ɹ�");
			return true;
		} catch (EaseMobException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d("mian","��Ⱥʧ��");
			return false;
		}
	}
	//������Ҫ��֤��Ⱥ
	public static boolean joinNeedCheckGroup_android(String groupid,String message)
	{
		try {
			EMGroupManager.getInstance().applyJoinToGroup(groupid,message);
			Log.d("main","��Ⱥ�ɹ�");
			return true;
		} catch (EaseMobException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d("main","��Ⱥʧ��");
			return false;
		}
	}
	
	//�˳�Ⱥ
	public static boolean exitGroup_android(String groupid)
	{
		try {
			EMGroupManager.getInstance().exitFromGroup(groupid);
			Log.d("main","�˳��ɹ�");
			return true;
		} catch (EaseMobException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d("main","�˳�ʧ��");
			return false;
		}
	}
	//ɾ��Ⱥ
	public static boolean destroyGroup_android(String groupId)
	{
		try {
			EMGroupManager.getInstance().exitAndDeleteGroup(groupId);
			Log.d("main","��ɢȺ�ɹ�");
			return true;
		} catch (EaseMobException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d("main","��ɢʧ��");
			return false;
		}
	}
	//Ⱥ������û�
	public static boolean addUserToGroup_android(String groupid,String[] usernameList)
	{
		try {
			EMGroupManager.getInstance().addUsersToGroup(groupid, usernameList);
			Log.d("main","����û��ɹ�");
			return true;
		} catch (EaseMobException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d("main","����û�ʧ��");
			return false;
		}
	}
	//˽��Ⱥ���
	public static boolean inviteUser_android(String groupid,String[] usernameList,String message)
	{
		try {
			EMGroupManager.getInstance().inviteUser(groupid, usernameList, message);
			Log.d("main","����û��ɹ�");
			return true;
		} catch (EaseMobException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d("main","��Ӻ���ʧ��");
			return false;
		}
	}
	//ɾ��Ⱥ�û�
	public static boolean deleteUserFromGroup_android(String groupId, String username)
	{
		try {
			EMGroupManager.getInstance().removeUserFromGroup(groupId, username);
			Log.d("mian","ɾ����Ա�ɹ�");
			return true;
		} catch (EaseMobException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d("mian","ɾ����Աʧ��");
			return false;
		}
	}
	//���� Ⱥ��Ϣ
	public static boolean blockGroupMessage_android(String groupid)
	{
		 try {
			EMGroupManager.getInstance().blockGroupMessage(groupid);
			Log.d("main","���γɹ�");
			return true;
		} catch (EaseMobException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d("main","����ʧ��");
			return false;
		}
	}
	
	//ȡ������Ⱥ��Ϣ
	public static boolean unblockGroupMessage_android(String groupid)
	{
		try {
			EMGroupManager.getInstance().unblockGroupMessage(groupid);
			Log.d("main","ȡ������Ⱥ��Ϣ�ɹ�");
			return true;
		} catch (EaseMobException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d("main","ȡ������Ⱥ��Ϣʧ��");
			return false;
		}
	}
	//�޸�Ⱥ������
	public static boolean changeGroupName_android(String groupid,String newgroupname)
	{
		try {
			EMGroupManager.getInstance().changeGroupName(groupid, newgroupname);
			Log.d("main","�޸�Ⱥ���Ƴɹ�");
			return true;
		} catch (EaseMobException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d("main","�޸�Ⱥ����ʧ��");
			return false;
		}
	}
	
}


