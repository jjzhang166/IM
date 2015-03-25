//
//  HXSDKHelper.h
//  IM
//
//  Created by chenq on 15-1-26.
//
//

#import <UIKit/UIKit.h>

#import "IChatManagerDelegate.h"

@interface HXSDKHelper : NSObject

// 取消SDK中注册的回调
- (void)unRegisterEaseMobDelegate;
// 向SDK中注册回调
- (void)registerEaseMobDelegate;
@end
