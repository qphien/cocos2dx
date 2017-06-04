/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2017 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __PLATFORM_CCSTDC_H__
#define __PLATFORM_CCSTDC_H__

#include "/Users/dummy/Downloads/cocos2d-x-3.15/cocos/platform/CCPlatformConfig.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
#include "/Users/dummy/Downloads/cocos2d-x-3.15/cocos/platform/mac/CCStdC-mac.h"
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "/Users/dummy/Downloads/cocos2d-x-3.15/cocos/platform/ios/CCStdC-ios.h"
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "/Users/dummy/Downloads/cocos2d-x-3.15/cocos/platform/android/CCStdC-android.h"
#elif CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include "/Users/dummy/Downloads/cocos2d-x-3.15/cocos/platform/win32/CCStdC-win32.h"
#elif CC_TARGET_PLATFORM == CC_PLATFORM_WINRT
#include "/Users/dummy/Downloads/cocos2d-x-3.15/cocos/platform/winrt/CCStdC.h"
#elif CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
#include "/Users/dummy/Downloads/cocos2d-x-3.15/cocos/platform/linux/CCStdC-linux.h"
#elif CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN
#include "/Users/dummy/Downloads/cocos2d-x-3.15/cocos/platform/tizen/CCStdC-tizen.h"
#endif

#endif /* __PLATFORM_CCSTDC_H__*/