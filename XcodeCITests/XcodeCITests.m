//
//  XcodeCITests.m
//  XcodeCITests
//
//  Created by 桜井雄介 on 2013/11/15.
//  Copyright (c) 2013年 Yusuke Sakurai. All rights reserved.
//

#import <XCTest/XCTest.h>

@interface XcodeCITests : XCTestCase

@end

@implementation XcodeCITests

- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testExample
{
    XCTFail(@"No implementation for \"%s\"", __PRETTY_FUNCTION__);
}

@end
