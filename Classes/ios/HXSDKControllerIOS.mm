

#import "HXSDKControllerIOS.h"
#import "EaseMob.h"
#import "EMChatText.h"
#include "IMDATA.h"

static EaseMob* easeMob = NULL;

//HXSDKControllerIOS* getInstance()
//{
//    if(!easeMob)
//    {
//        return EaseMob;
//    }
//}

bool HXSDKControllerIOS::init_ios()
{
    easeMob = [EaseMob sharedInstance];
    NSString *apnsCertName = @"9miao";
    [easeMob registerSDKWithAppKey:@"longtugame#crossappim" apnsCertName:apnsCertName];
    if(easeMob)
    {
        CCLog("HXSDK init success!!!");
        return true;
    }
    
    return false;
}

bool HXSDKControllerIOS::Login_ios(const char* name, const char* passWord)
{
    NSString *string_name = [[NSString alloc] initWithCString:(const char*)name encoding:NSASCIIStringEncoding];
    NSString *string_passWord = [[NSString alloc] initWithCString:(const char*)passWord encoding:NSASCIIStringEncoding];
    
    [easeMob.chatManager asyncLoginWithUsername:string_name
                                                        password:string_passWord
                                                      completion:
     ^(NSDictionary *loginInfo, EMError *error) {

         if (loginInfo && !error) {
             [[NSNotificationCenter defaultCenter] postNotificationName:@KNOTIFICATION_LOGINCHANGE object:@YES];
             EMError *error = [easeMob.chatManager importDataToNewDatabase];
             if (!error) {
                 error = [easeMob.chatManager loadDataFromDatabase];
             }
         }else {
             switch (error.errorCode) {
                 case EMErrorServerNotReachable:
                     CCLog("连接服务器失败!");
                     break;
                 case EMErrorServerAuthenticationFailure:
                     CCLog("%s", [error.description cStringUsingEncoding:NSASCIIStringEncoding]);
                     break;
                 case EMErrorServerTimeout:
                     CCLog("连接服务器超时!");
                     break;
                 default:
                     CCLog("登录失败");
                     break;
             }
         }
     } onQueue:nil];
    
    return true;
}

bool HXSDKControllerIOS::RegisTerAccount_ios(const char* name, const char* passWord)
{
    NSString *string_name = [[NSString alloc] initWithCString:(const char*)name encoding:NSASCIIStringEncoding];
    NSString *string_passWord = [[NSString alloc] initWithCString:(const char*)passWord encoding:NSASCIIStringEncoding];
    
    [easeMob.chatManager asyncRegisterNewAccount:string_name
                                                         password:string_passWord
                                                   withCompletion:
     ^(NSString *username, NSString *password, EMError *error) {
         
         if (!error) {
             CCLog("注册成功,请登录");
         }else{
             switch (error.errorCode) {
                 case EMErrorServerNotReachable:
                     CCLog("连接服务器失败!");
                     break;
                 case EMErrorServerDuplicatedAccount:
                     CCLog("您注册的用户已存在!");
                     break;
                 case EMErrorServerTimeout:
                     CCLog("连接服务器超时!");
                     break;
                 default:
                     CCLog("注册失败");
                     break;
             }
         }
     } onQueue:nil];
     return true;
}

void HXSDKControllerIOS::Logout_ios()
{
    [easeMob.chatManager asyncLogoff];
}

void HXSDKControllerIOS::sendMessage_ios(const char* messageText, const char* toUserName)
{
    NSString *string_messageText = [[NSString alloc] initWithCString:(const char*)messageText encoding:NSASCIIStringEncoding];
    NSString *string_toUserName = [[NSString alloc] initWithCString:(const char*)toUserName encoding:NSASCIIStringEncoding];
    EMChatText *text = [[EMChatText alloc] initWithText:string_messageText];
    EMTextMessageBody *body = [[EMTextMessageBody alloc] initWithChatObject:text];
    EMMessage *msg = [[EMMessage alloc] initWithReceiver:string_toUserName
                                                  bodies:@[body]];
    [easeMob.chatManager sendMessage:msg progress:nil error:nil];
    
}

void HXSDKControllerIOS::sendMessageWithImage_ios(const char* messageImage, const char* toUserName)
{
    NSString *string_messageImage = [[NSString alloc] initWithCString:(const char*)messageImage encoding:NSASCIIStringEncoding];
    NSString *string_toUserName = [[NSString alloc] initWithCString:(const char*)toUserName encoding:NSASCIIStringEncoding];
    //将图片读取到内存
    UIImage *image = [UIImage imageNamed:string_messageImage];
    //初始化一个EMChatImage对象
    EMChatImage *chatImage = [[EMChatImage alloc] initWithUIImage:image displayName:@"image"];
    //初始化一个MessageBody对象
    //chatImage：大图
    //thumbnailImage：缩略图（可不传, 传nil系统会自动生成缩略图）
    EMImageMessageBody *body = [[EMImageMessageBody alloc] initWithImage:chatImage thumbnailImage:nil];
    //初始化一个MessageBody数组(目前暂时只支持一个body)
    NSArray *bodies = [NSArray arrayWithObject:body];
    //初始化一个EMMessage对象
    EMMessage *retureMsg = [[EMMessage alloc] initWithReceiver:string_toUserName bodies:bodies];
    //发送数据是否需要加密
    retureMsg.requireEncryption = false;
    //发送图片消息
    [[EaseMob sharedInstance].chatManager asyncSendMessage:retureMsg progress:nil];
    
}






























