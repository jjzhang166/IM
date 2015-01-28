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

@interface HXSDKHelper()  <IChatManagerDelegate>

@end


@implementation HXSDKHelper

HXSDKHelper * mHXSDKHelper;


+(HXSDKHelper *) getHXSDKHelper
{
    if (!mHXSDKHelper) {
        mHXSDKHelper = [[HXSDKHelper alloc] init];
    }
    return mHXSDKHelper;

}

-(void)didReceiveMessage:(EMMessage *)message
{
    
    NSLog(@"收到消息");
    id<IEMMessageBody> msgBody = message.messageBodies.firstObject;
    switch (msgBody.messageBodyType) {
        case eMessageBodyType_Text:
        {
            // 收到的文字是
            NSString *txt = ((EMTextMessageBody *)msgBody).text;
            NSLog(@"收到的文字是 txt -- %@",txt);
            // 发送notification  HXMSGARRIVAL
            [[NSNotificationCenter defaultCenter] postNotificationName:@"HXMSGARRIVAL" object:@YES];
            
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


@end
