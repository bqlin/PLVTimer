//
//  GCDTimer.h
//  GCDTimer
//
//  Created by LinBq on 16/12/23.
//  Copyright © 2016年 Bq. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GCDTimer;
typedef void(^GCDTimerCallbackBlock)(GCDTimer *timer);

@protocol GCDTimerDelegate <NSObject>
@optional

/**
 定时器取消回调

 @param timer 定时器对象
 */
- (void)gcdTimerDidCancel:(GCDTimer *)timer;

@end

/**
 GCD 定时器
 */
@interface GCDTimer : NSObject

@property (nonatomic, weak) id<GCDTimerDelegate> delegate;

/// 定时器任务是否运行，定时器执行时为 YES，否则为 NO
@property (nonatomic, assign, readonly) BOOL running;

/// 定时器是否可用，定时器未创建或取消后为 NO，此时不可再对定时器进行操作，否则为 YES
@property (nonatomic, assign, readonly) BOOL valid;

/// 当前运行累计时间（单位：秒）
@property (nonatomic, assign, readonly) NSTimeInterval currentTime;

/// 定时器指定间隔（单位：秒），默认为 1s
@property (nonatomic, assign) NSTimeInterval timerInterval;

/// 定时器指定精度（单位：秒），默认为 0，即为最精确
@property (nonatomic, assign) NSTimeInterval timerLeeway;

/// 是否开启自引用。
/// 开启后在执行任务时进行自引用，在任务执行过程中不会被销毁，仅当取消后且无强引用定时器对象才会被销毁；否则需要外部对定时器对象进行强引用方可确保定时器任务执行。
@property (nonatomic, assign) BOOL enableSelfRetain;

- (instancetype)init __attribute__((unavailable("init not available, call other initialization method instead")));
+ (instancetype)new __attribute__((unavailable("new not available, call other initialization method instead")));

/**
 创建定时器对象

 @param dispatchQueue 定时器任务执行队列，传入 ni 则使用主队列
 @return 定时器对象
 */
- (instancetype)initWithDispatchQueue:(dispatch_queue_t)dispatchQueue;

/**
 立即启动定时器
 */
- (void)fire;

/**
 取消定时器及其操作
 */
- (void)cancel;

/**
 创建倒计时定时器对象

 @param countdownInSeconds 倒计时（单位：秒）
 @param countdownHandler 定时器任务
 @param fire 是否立即执行
 */
- (void)countdownWithTime:(NSTimeInterval)countdownInSeconds countdownHandler:(GCDTimerCallbackBlock)countdownHandler fire:(BOOL)fire;

/**
 便利创建自引用定时器对象
 
 若不对定时器对象强引用，则其自动在倒计时归零时自动销毁。

 @param countdownInSeconds 倒计时（单位：秒）
 @param intervalInSeconds 执行间隔
 @param countdownHandler 定时器任务
 @return 定时器对象
 */
+ (instancetype)countdownWithTime:(NSTimeInterval)countdownInSeconds interval:(NSTimeInterval)intervalInSeconds countdownHandler:(GCDTimerCallbackBlock)countdownHandler;

/**
 创建重复定时器对象

 @param repeatActionHandler 定时器任务
 @param fire 是否立即执行
 */
- (void)repeatWithActionHandler:(GCDTimerCallbackBlock)repeatActionHandler fire:(BOOL)fire;

/**
 便利创建自引用定时器对象
 
 需外部主动调用 -cancel 方法才能销毁定时器对象。

 @param intervalInSeconds 执行间隔
 @param repeatActionHandler 定时器任务
 @return 定时器对象
 */
+ (instancetype)repeatWithInterval:(NSTimeInterval)intervalInSeconds actionHandler:(GCDTimerCallbackBlock)repeatActionHandler;

@end
