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
	//创建群
	public static void createGroup_android(String groupname,String groupdescription,boolean ispublic,boolean isAllow)
	{
		if(ispublic)
		{
			try {
				EMGroupManager.getInstance().createPublicGroup(groupname, groupdescription, null, isAllow);
				Log.d("main","创建公有群成功");
			} catch (EaseMobException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				Log.d("main","创建公有群失败");
			}
		}
		else
		{
			try {
				EMGroupManager.getInstance().createPrivateGroup(groupname, groupdescription, null,isAllow);
				Log.d("mian","创建私有群组成功");
			} catch (EaseMobException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				Log.d("main","创建私有群失败");
			}
		}
	}
	//获取公开群
	public static Object[] getPublicGroup_android()
	{
		List<EMGroupInfo> groupsList = null;
		//获取所有公开群列表
		try {
			groupsList = EMGroupManager.getInstance().getAllPublicGroupsFromServer();
			Log.d("main","获取公开群成功");
		} catch (EaseMobException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d("main","获取公开群失败");
		}
		EMGroupInfo[] groupListTo = new EMGroupInfo[groupsList.size()];
		EMGroupInfo[] publicgroupList =(EMGroupInfo[])groupsList.toArray(groupListTo);
		return publicgroupList;
		
	}
	
	//获取我加入的群列表
	public static Object[] getMyGroupList_android()
	{
		try {
			List<EMGroup> grouplist = EMGroupManager.getInstance().getGroupsFromServer();
			Log.d("main","服务器获取列表成功");
		} catch (EaseMobException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d("main","服务器获取列表失败");
		}
		
		//从本地加载群聊列表
		List<EMGroup> grouplistlocal = EMGroupManager.getInstance().getAllGroups();
		
		EMGroup[] groupListTo = new EMGroup[grouplistlocal.size()];
		EMGroup[] groupList = (EMGroup[])grouplistlocal.toArray(groupListTo);
		return groupList;
	}
	
	//加入不需要验证的群
	public static boolean joinNoNeedCheckGroup_android(String groupid)
	{
		try {
			EMGroupManager.getInstance().joinGroup(groupid);
			Log.d("main","加群成功");
			return true;
		} catch (EaseMobException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d("mian","加群失败");
			return false;
		}
	}
	//加入需要验证的群
	public static boolean joinNeedCheckGroup_android(String groupid,String message)
	{
		try {
			EMGroupManager.getInstance().applyJoinToGroup(groupid,message);
			Log.d("main","加群成功");
			return true;
		} catch (EaseMobException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d("main","加群失败");
			return false;
		}
	}
	
	//退出群
	public static boolean exitGroup_android(String groupid)
	{
		try {
			EMGroupManager.getInstance().exitFromGroup(groupid);
			Log.d("main","退出成功");
			return true;
		} catch (EaseMobException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d("main","退出失败");
			return false;
		}
	}
	//删除群
	public static boolean destroyGroup_android(String groupId)
	{
		try {
			EMGroupManager.getInstance().exitAndDeleteGroup(groupId);
			Log.d("main","解散群成功");
			return true;
		} catch (EaseMobException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d("main","解散失败");
			return false;
		}
	}
	//群主添加用户
	public static boolean addUserToGroup_android(String groupid,String[] usernameList)
	{
		
		try {
			EMGroupManager.getInstance().addUsersToGroup(groupid, usernameList);
			Log.d("main","添加用户成功");
			return true;
		} catch (EaseMobException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d("main","添加用户失败");
			return false;
		}
	}
	//私有群添加
	public static boolean inviteUser_android(String groupid,String[] usernameList,String message)
	{
		try {
			EMGroupManager.getInstance().inviteUser(groupid, usernameList, message);
			Log.d("main","添加用户成功");
			return true;
		} catch (EaseMobException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d("main","添加好友失败");
			return false;
		}
	}
	//删除群用户
	public static boolean deleteUserFromGroup_android(String groupId, String username)
	{
		try {
			EMGroupManager.getInstance().removeUserFromGroup(groupId, username);
			Log.d("mian","删除成员成功");
			return true;
		} catch (EaseMobException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d("mian","删除成员失败");
			return false;
		}
	}
	//屏蔽 群消息
	public static boolean blockGroupMessage_android(String groupid)
	{
		 try {
			EMGroupManager.getInstance().blockGroupMessage(groupid);
			Log.d("main","屏蔽成功");
			return true;
		} catch (EaseMobException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d("main","屏蔽失败");
			return false;
		}
	}
	
	//取消屏蔽群消息
	public static boolean unblockGroupMessage_android(String groupid)
	{
		try {
			EMGroupManager.getInstance().unblockGroupMessage(groupid);
			Log.d("main","取消屏蔽群消息成功");
			return true;
		} catch (EaseMobException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d("main","取消屏蔽群消息失败");
			return false;
		}
	}
	//修改群组名称
	public static boolean changeGroupName_android(String groupid,String newgroupname)
	{
		try {
			EMGroupManager.getInstance().changeGroupName(groupid, newgroupname);
			Log.d("main","修改群名称成功");
			return true;
		} catch (EaseMobException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d("main","修改群名称失败");
			return false;
		}
	}
	//设置接受休息但是不提醒
	public static boolean setReceiveNotNoifyGroup_android(String[] groupids)
	{
		List<String> groupIDS = null;
		for(String id:groupids)
		{
			groupIDS.add(id);
		}
		EMChatManager.getInstance().getChatOptions().setReceiveNotNoifyGroup(groupIDS);
		Log.d("main","设置消息成功");
		return true;
	}
	//群用户被加入黑名单
	public static boolean blockUser_android(String groupId,String blackname)
	{
		try {
			EMGroupManager.getInstance().blockUser(groupId, blackname);
			Log.d("main","加入黑名单成功"); 
			return true;
		} catch (EaseMobException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d("main","加入黑名单失败");
			return false;
		}
	}
	//群用户离开黑名单
	public static boolean unblockUser_android(String groupId,String blackname)
	{
		try {
			EMGroupManager.getInstance().unblockUser(groupId, blackname);
			Log.d("main","加入黑名单成功"); 
			return true;
		} catch (EaseMobException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d("main","加入黑名单失败");
			return false;
		}
	}
	//获取黑名单列表
	public static String[] getBlockedUsers_android(String groupid)
	{
		List<String> blacknameList = new ArrayList<String>();
		try {
			blacknameList = EMGroupManager.getInstance().getBlockedUsers(groupid);
			Log.d("main","获取黑名单成功");
		} catch (EaseMobException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.d("main","获取黑名单失败");
		}
		String[] nameTo = new String[blacknameList.size()];
		String[] blackList = (String[])blacknameList.toArray(nameTo);
		Log.i("main","mingzi="+blackList[0]);
		return blackList;
	}
	
}


