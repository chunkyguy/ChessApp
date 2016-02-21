//
//  SjengChessAppDelegate.h
//  SjengChess
//
//  Created by sid on 22/10/11.
//  Copyright 2011 whackylabs. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface SjengChessAppDelegate : NSObject <UIApplicationDelegate> {

	NSMutableArray *touches_;
	int touchCount_;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
-(void)executeCommand:(NSString *)command;
@end
