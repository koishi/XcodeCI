//
//  XCIMasterViewController.h
//  XcodeCI iPad
//
//  Created by 桜井雄介 on 2013/11/29.
//  Copyright (c) 2013年 Yusuke Sakurai. All rights reserved.
//

#import <UIKit/UIKit.h>

@class XCIDetailViewController;

@interface XCIMasterViewController : UITableViewController

@property (strong, nonatomic) XCIDetailViewController *detailViewController;

@end
