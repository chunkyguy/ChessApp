//
//  SjengChessAppDelegate.m
//  SjengChess
//
//  Created by sid on 22/10/11.
//  Copyright 2011 whackylabs. All rights reserved.
//

#import "SjengChessAppDelegate.h"
#import "sjeng/sjeng_engine.h"

@implementation SjengChessAppDelegate


@synthesize window=_window;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
	// Override point for customization after application launch.
	[self.window setBackgroundColor:[UIColor greenColor]];

    [self.window setRootViewController:[[UIViewController alloc] init]];
	
	touches_ = [[NSMutableArray alloc] initWithCapacity:2];
	for(int i = 0; i < 2; i++)
		[touches_ addObject:@""];
	touchCount_ = 0;
	
	start_chess();
	
	for(int r= 0; r < 8; r++){
		for(int f = 0; f < 8; f++){
			CGFloat size = [[UIScreen mainScreen] bounds].size.width/8;
			CGRect sq_frame = CGRectMake(0, 0, size, size);
			CGFloat shift_y = 60;
			UIButton *btn = [UIButton buttonWithType:UIButtonTypeCustom];
			[btn addTarget:self action:@selector(btn_hit:) forControlEvents:UIControlEventTouchUpInside];
			[btn setFrame:CGRectOffset(sq_frame, size * f, (size * 8 - size * r) + shift_y)];
			[btn setBackgroundColor:(r+f)%2?[UIColor darkGrayColor]:[UIColor lightGrayColor]];
			[btn setTag:r*10+f];
			[btn setTitle:[NSString stringWithFormat:@"%c%d",'a'+btn.tag%10,btn.tag/10+1] forState:UIControlStateNormal];
			[btn setTitleColor:[UIColor redColor] forState:UIControlStateNormal];
			[self.window addSubview:btn];
		}
	}
	[self executeCommand:@"new"];

	[self.window makeKeyAndVisible];

    return YES;
}

-(void)btn_hit:(UIButton *)btn{
	[touches_ replaceObjectAtIndex:touchCount_ withObject:[NSString stringWithFormat:@"%c%d",'a'+btn.tag%10,btn.tag/10+1]];
	if(touchCount_ > 0){
		[self executeCommand:[touches_ componentsJoinedByString:@""]];
		touchCount_ = 0;
	}else{
		touchCount_++;
	}
}

-(void)executeCommand:(NSString *)command{
	NSLog(@"command: %@",command);
	
	const char *moves[] = {[command UTF8String],"random"};	//human, computer
	for(int i = 0; i < 2; i++){
		char move[100];
		strcpy(move, moves[i]);
		loop(move, ^(int color){
			NSArray *piece_img = [NSArray arrayWithObjects:@"!!",
				@"WP.png",@"BP.png",@"WN.png",@"BN.png",@"WK.png",@"BK.png",
				@"WR.png",@"BR.png",@"WQ.png",@"BQ.png",@"WB.png",@"BB.png",
				@"  ",nil];
			
			NSArray *subvws = [self.window subviews];
			for(UIButton *btn in subvws){
				if(![btn isKindOfClass:[UIButton class]])
					continue;
				
				int tag = btn.tag;
				int i = tag/10+2;
				int j = tag%10+2;
				[btn setImage:[UIImage imageNamed:[piece_img objectAtIndex:board[i*12+j]]] forState:UIControlStateNormal];
				//				[btn setTitle:[NSString stringWithFormat:@"%s",piece_rep[board[i*12+j]]] forState:UIControlStateNormal];
			}
			
			/*
			for(int i = 2; i < 10; i++){
				for(int j = 2; j < 10; j++){
					printf(" %02d ",board[i*12+j]);
				}
				printf("\n");
			}
			 */
		});
	}
}

- (void)applicationWillResignActive:(UIApplication *)application
{
	/*
	 Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
	 Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
	 */
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
	/*
	 Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
	 If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
	 */
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
	/*
	 Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
	 */
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
	/*
	 Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
	 */
}

- (void)applicationWillTerminate:(UIApplication *)application
{
	/*
	 Called when the application is about to terminate.
	 Save data if appropriate.
	 See also applicationDidEnterBackground:.
	 */
}

- (void)dealloc
{
	[_window release];
    [super dealloc];
}

@end
