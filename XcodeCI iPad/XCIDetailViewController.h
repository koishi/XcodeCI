//
//  XCIDetailViewController.h
//  XcodeCI iPad
//
//  Created by 桜井雄介 on 2013/11/29.
//  Copyright (c) 2013年 Yusuke Sakurai. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface XCIDetailViewController : UIViewController <UISplitViewControllerDelegate>

@property (strong, nonatomic) id detailItem;

@property (weak, nonatomic) IBOutlet UILabel *detailDescriptionLabel;
@end
