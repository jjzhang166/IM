//
//  HXSDKHelper.m
//  IM
//
//  Created by chenq on 15-1-26.
//
//

#import "HXSDKHelper.h"
#import "IEMMessageBody.h"
#import "EMMessage.h"
#import "EMTextMessageBody.h"
#import "EMImageMessageBody.h"
#import "IChatManagerDelegate.h"
#import "EaseMob.h"
#include "HXSDKController.h"

@interface HXSDKHelper ()<IChatManagerDelegate>

@end


@implementation HXSDKHelper

HXSDKHelper * mHXSDKHelper;



#pragma mark - IChatManagerDelegate
// 收到好友请求后回调
-(void)didReceiveBuddyRequest:(NSString *)username message:(NSString *)message
{
    NSLog(@"用户%@ ,请求添加你为好友,附加消息%@",username,message);
}
/*!
 @method
 @brief 好友请求被接受时的回调
 @discussion
 @param username 之前发出的好友请求被用户username接受了
 */
- (void)didAcceptedByBuddy:(NSString *)username{
	NSLog(@"%@同意了您的好友请求",username);
}

/*!
 @method
 @brief 好友请求被拒绝时的回调
 @discussion
 @param username 之前发出的好友请求被用户username拒绝了
 */
- (void)didRejectedByBuddy:(NSString *)username{
	NSLog(@"%@拒绝了您的好友请求",username);
}


// 收到好友消息后回调
-(void)didReceiveMessage:(EMMessage *)message
{
    NSLog(@"收到消息");
    id<IEMMessageBody> msgBody = message.messageBodies.firstObject;
    switch (msgBody.messageBodyType) {
        case eMessageBodyType_Text:
        {
            // 收到的文字是
            NSString *txt = ((EMTextMessageBody *)msgBody).text;
            
            NSLog(@"from:%s", [[msgBody message].from UTF8String]);
            NSLog(@"to:%s", [[msgBody message].to UTF8String]);
            NSLog(@"time:%lld", [msgBody message].timestamp);
            
            EMMessage *message;
            NSLog(@"收到的文字是 txt -- %@",txt);
            // 发送notification  HXMSGARRIVAL
            [[NSNotificationCenter defaultCenter] postNotificationName:@"HXMSGARRIVAL" object:@YES];
            HXSDKController::getInstance()->pushMessageDetail([[msgBody message].from UTF8String], 1, [msgBody message].timestamp, [[msgBody message].from UTF8String],  [[msgBody message].to UTF8String], 1, [txt UTF8String]);
        }
            break;
        case eMessageBodyType_Image:
        {
            // 得到一个图片消息body
            EMImageMessageBody *body = ((EMImageMessageBody *)msgBody);
            NSLog(@"大图remote路径 -- %@"   ,body.remotePath);
            NSLog(@"大图local路径 -- %@"    ,body.localPath); // // 需要使用sdk提供的下载方法后才会存在
            NSLog(@"大图的secret -- %@"    ,body.secretKey);
            NSLog(@"大图的W -- %f ,大图的H -- %f",body.size.width,body.size.height);
            //            NSLog(@"大图的下载状态 -- %lu",body.attachmentDownloadStatus);
                
                
            // 缩略图sdk会自动下载
            NSLog(@"小图remote路径 -- %@"   ,body.thumbnailRemotePath);
            NSLog(@"小图local路径 -- %@"    ,body.thumbnailLocalPath);
            NSLog(@"小图的secret -- %@"    ,body.thumbnailSecretKey);
            NSLog(@"小图的W -- %f ,大图的H -- %f",body.thumbnailSize.width,body.thumbnailSize.height);
            //	        NSLog(@"小图的下载状态 -- %lu",body.thumbnailDownloadStatus);
        }
            break;
                
        default:
            break;
        }
}

// 向SDK中注册回调
- (void)registerEaseMobDelegate{
	// 此处先取消一次，是为了保证只将self注册过一次回调。
    [self unRegisterEaseMobDelegate];
	[[EaseMob sharedInstance].chatManager addDelegate:self delegateQueue:nil];
}

// 取消SDK中注册的回调
- (void)unRegisterEaseMobDelegate{
	[[EaseMob sharedInstance].chatManager removeDelegate:self];
}


@end
