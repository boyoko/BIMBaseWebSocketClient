#pragma once
#ifdef BIMBASEBACKEND_EXPORTS
#define BIMBASEBACKEND_API __declspec(dllexport)
#else
#define BIMBASEBACKEND_API __declspec(dllimport)
#endif
#include <stdint.h>
namespace BP
{
    struct ScreenRect
    {
        int left;
        int top;
        int right;
        int bottom;
    };
    //图片颜色通道
    enum BPMChannel
    {
        enRGBA,
        enABGR,
        enBGRA,
        enARGB,
        enRGB,
        enBGR
    };
    class IBMPReceiver
    {
    public:
        virtual ~IBMPReceiver(){}
        virtual void _proceeBMP(uint8_t* datas, int w, int h, BPMChannel channel) = 0;
    };
    class IWindowRectProvider
    {
    public:
        virtual ~IWindowRectProvider(){}
        virtual void getWindowRect(ScreenRect& rect) = 0;
    };
#ifndef MK_SHIFT
#define MK_SHIFT            0x0004
#define MK_CONTROL          0x0008
#endif
    typedef unsigned int  MouseFlag; //鼠标发生事件同时按下Shift键或control键，按下shift键是4，按下control是8，两个同时按下是4|8=12
    class BIMBaseBackend
    {
    public:
        struct ScreenPoint
        {
            int x;
            int y;
        };
        typedef ScreenPoint const& ScreenPointCR;
        typedef ScreenPoint & ScreenPointR;
        /**
        *  @brief  发送窗口改变大小消息
        *  @param[in]  x: 窗口新宽度
        *  @param[in]  y: 窗口新高度
        */
        BIMBASEBACKEND_API static void      sendWindowResize(int x, int y);
        /**
        *  @brief  发送timer事件，如心跳
        */
        BIMBASEBACKEND_API static void      sendTimerEvent();
        /**
        *  @brief  发送鼠标滚动消息
        *  @param[in]  delta:鼠标滚动值
        *  @param[in]  pt:屏幕点坐标，以视口区左上角为原点
        */
        BIMBASEBACKEND_API static void      sendMouseWheel(MouseFlag nFlags, int delta, ScreenPointCR pt);
        /**
        *  @brief  发送鼠标移动消息
        *  @param[in]  pt:屏幕点坐标，以视口区左上角为原点
        */
        BIMBASEBACKEND_API static void      sendMouseMove(MouseFlag nFlags, ScreenPointCR pt);
        /**
        *  @brief  发送鼠标左键按下
        *  @param[in]  pt:屏幕点坐标，以视口区左上角为原点
        */
        BIMBASEBACKEND_API static void      sendLeftButtonDown(MouseFlag nFlags, ScreenPointCR pt);
        /**
        *  @brief  发送鼠标左键抬起
        *  @param[in]  pt:屏幕点坐标，以视口区左上角为原点
        */
        BIMBASEBACKEND_API static void      sendLeftButtonUp(MouseFlag nFlags, ScreenPointCR pt);
        /**
        *  @brief  发送鼠标右键按下
        *  @param[in]  pt:屏幕点坐标，以视口区左上角为原点
        */
        BIMBASEBACKEND_API static void      sendRightButtonDown(MouseFlag nFlags, ScreenPointCR pt);
        /**
        *  @brief  发送鼠标右键抬起
        *  @param[in]  pt:屏幕点坐标，以视口区左上角为原点
        */
        BIMBASEBACKEND_API static void      sendRightButtonUp(MouseFlag nFlags, ScreenPointCR pt);
        /**
        *  @brief  发送鼠标中键按下
        *  @param[in]  pt:屏幕点坐标，以视口区左上角为原点
        */
        BIMBASEBACKEND_API static void      sendMButtonDown(MouseFlag nFlags, ScreenPointCR pt);
        /**
        *  @brief  发送鼠标中键抬起
        *  @param[in]  pt:屏幕点坐标，以视口区左上角为原点
        */
        BIMBASEBACKEND_API static void      sendMButtonUp(MouseFlag nFlags, ScreenPointCR pt);
        /**
        *  @brief  发送键盘按键消息
        *  @param[in] wentDown:是否按下
        *  @param[in] key:按键码
        */
        BIMBASEBACKEND_API static void      sendKeyEvent(bool wentDown, int key); 
        /**
        *  @brief  注册接收图片接口
        *  @param[in] bmpReceiver:接收图片接口,只要发出的图片肯定是变化的
        */
        BIMBASEBACKEND_API static void      registerBMPReceiver(IBMPReceiver* bmpReceiver);
        /**
        *  @brief  主动拉取屏幕图片，设置最大帧率
        */
        BIMBASEBACKEND_API static void      getBMPData(uint8_t*& datas, int &w, int &h, BPMChannel& channel);
        /**
        *  @brief  注册返回窗口大小接口
        *  @param[in] rectProvider:返回窗口大小接口
        */
        BIMBASEBACKEND_API static void      registerWindowRectProvider(IWindowRectProvider * rectProvider);
        /**
        *  @brief  发送命令
        *  @param[in] cmd:命令名
        */
        BIMBASEBACKEND_API static void      sendCommand(wchar_t const* cmd);
        /**
        *  @brief  打开文件
        *  @param[in] filename:文件名
        */
        BIMBASEBACKEND_API static void      openFile(wchar_t const* filename);
        /**
        *  @brief  关闭当前文件
        *  @param[in] isSave:是否保存
        */
        BIMBASEBACKEND_API static void      closeFile(bool isSave);
        /**
        *  @brief  退出程序
        *  @param[in] isSave:是否保存
        */
        BIMBASEBACKEND_API static void      exitProgram(bool isSave);
        /**
        *  @brief  获取与服务器端通信端口
        *  @return 命令行获取不成功则返回-1
        */
        BIMBASEBACKEND_API static int getServerPort();
    };
}