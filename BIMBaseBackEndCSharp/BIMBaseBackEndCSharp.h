// ClassLibrary2.h

#pragma once

using namespace System;

namespace BIMBasePlatform
{
    //图片颜色通道
    public enum class MChannel
    {
        enRGBA,
        enABGR,
        enBGRA,
        enARGB,
        enRGB ,
        enBGR ,
    };
    
    public ref class ScreenRect
    {
    public:
        int left;
        int top;
        int right;
        int bottom;
    };
    public ref class BPEventArgs : public System::EventArgs
    {
    public:
        BPEventArgs()
        {

        }
        virtual ~BPEventArgs()
        {

        }
    };

    public ref class IBmpReceiverEventArgs : public BPEventArgs
    {
    public:
        IBmpReceiverEventArgs(IntPtr^ dataList, int nWidth, int nHeight, MChannel^ channel)
            : m_dataList(dataList), m_nWidth(nWidth), m_nHeight(nHeight), m_channel(channel)
        {

        }


    public:
        //uint8_t* datas, int w, int h, BPMChannel channel
        IntPtr^ m_dataList;
        int m_nWidth;
        int m_nHeight;
        MChannel^ m_channel;

    };

    public ref class IWindowRectProviderEventArgs : public BPEventArgs
    {
    public:
        IWindowRectProviderEventArgs()
        {
            m_rect = gcnew ScreenRect;
        }
        ScreenRect^ m_rect;
    };
    public ref class ScreenPoint
    {
    public:
        int x;
        int y;
    };
    public ref class BIMBaseBackend
	{
		// TODO:  在此处添加此类的方法。
    private:
        static BIMBaseBackend^ s_singleton = nullptr;

    public:
        static BIMBaseBackend^ singTon();

    public:
        event System::EventHandler<IBmpReceiverEventArgs^>^ IBmpReceiverEvent;
        event System::EventHandler<IWindowRectProviderEventArgs^>^ IWindowRectProviderEvent;

        void fireIBmpReceiverEvent(IntPtr^ dataList, int nWidth, int nHeight, MChannel^ channel);
        void fireIWindowRectProviderEvent(ScreenRect^% rect);

        /**
        *  @brief  发送窗口改变大小消息
        *  @param[in]  x: 窗口新宽度
        *  @param[in]  y: 窗口新高度
        */
         static void      sendWindowResize(int x, int y);
        /**
        *  @brief  发送timer事件，如心跳
        */
         static void      sendTimerEvent();
        /**
        *  @brief  发送鼠标滚动消息
        *  @param[in]  delta:鼠标滚动值
        *  @param[in]  pt:屏幕点坐标，以视口区左上角为原点
        */
         typedef int MouseFlag;
         static void      sendMouseWheel(MouseFlag nFlags, int delta, ScreenPoint^ pt);
        /**
        *  @brief  发送鼠标移动消息
        *  @param[in]  pt:屏幕点坐标，以视口区左上角为原点
        */
         static void      sendMouseMove(MouseFlag nFlags, ScreenPoint^ pt);
        /**
        *  @brief  发送鼠标左键按下
        *  @param[in]  pt:屏幕点坐标，以视口区左上角为原点
        */
         static void      sendLeftButtonDown(MouseFlag nFlags, ScreenPoint^ pt);
        /**
        *  @brief  发送鼠标左键抬起
        *  @param[in]  pt:屏幕点坐标，以视口区左上角为原点
        */
         static void      sendLeftButtonUp(MouseFlag nFlags, ScreenPoint^ pt);
        /**
        *  @brief  发送鼠标右键按下
        *  @param[in]  pt:屏幕点坐标，以视口区左上角为原点
        */
         static void      sendRightButtonDown(MouseFlag nFlags, ScreenPoint^ pt);
        /**
        *  @brief  发送鼠标右键抬起
        *  @param[in]  pt:屏幕点坐标，以视口区左上角为原点
        */
         static void      sendRightButtonUp(MouseFlag nFlags, ScreenPoint^ pt);
        /**
        *  @brief  发送鼠标中键按下
        *  @param[in]  pt:屏幕点坐标，以视口区左上角为原点
        */
         static void      sendMButtonDown(MouseFlag nFlags, ScreenPoint^ pt);
        /**
        *  @brief  发送鼠标中键抬起
        *  @param[in]  pt:屏幕点坐标，以视口区左上角为原点
        */
         static void      sendMButtonUp(MouseFlag nFlags, ScreenPoint^ pt);
        /**
        *  @brief  发送键盘按键消息
        *  @param[in] wentDown:是否按下
        *  @param[in] key:按键码
        */
         static void      sendKeyEvent(bool wentDown, int key);

        /**
        *  @brief  主动拉取屏幕图片，设置最大帧率
        */
         static void      getBMPData(IntPtr^% datas, int %w, int %h, MChannel^% channel);
        /**
        *  @brief  发送命令
        *  @param[in] cmd:命令名
        */
         static void      sendCommand(String^ cmd);
        /**
        *  @brief  打开文件
        *  @param[in] filename:文件名
        */
         static void      openFile(String^ filename);
        /**
        *  @brief  关闭当前文件
        *  @param[in] isSave:是否保存
        */
         static void      closeFile(bool isSave);
        /**
        *  @brief  退出程序
        *  @param[in] isSave:是否保存
        */
        static void      exitProgram(bool isSave);
        /**
        *  @brief  获取与服务器端通信端口
        *  @return 命令行获取不成功则返回-1
        */
         static int getServerPort();
	};
}
