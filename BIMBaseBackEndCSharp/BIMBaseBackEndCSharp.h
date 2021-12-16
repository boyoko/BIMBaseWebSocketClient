// ClassLibrary2.h

#pragma once

using namespace System;

namespace BIMBasePlatform
{
    //ͼƬ��ɫͨ��
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
		// TODO:  �ڴ˴���Ӵ���ķ�����
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
        *  @brief  ���ʹ��ڸı��С��Ϣ
        *  @param[in]  x: �����¿��
        *  @param[in]  y: �����¸߶�
        */
         static void      sendWindowResize(int x, int y);
        /**
        *  @brief  ����timer�¼���������
        */
         static void      sendTimerEvent();
        /**
        *  @brief  ������������Ϣ
        *  @param[in]  delta:������ֵ
        *  @param[in]  pt:��Ļ�����꣬���ӿ������Ͻ�Ϊԭ��
        */
         typedef int MouseFlag;
         static void      sendMouseWheel(MouseFlag nFlags, int delta, ScreenPoint^ pt);
        /**
        *  @brief  ��������ƶ���Ϣ
        *  @param[in]  pt:��Ļ�����꣬���ӿ������Ͻ�Ϊԭ��
        */
         static void      sendMouseMove(MouseFlag nFlags, ScreenPoint^ pt);
        /**
        *  @brief  ��������������
        *  @param[in]  pt:��Ļ�����꣬���ӿ������Ͻ�Ϊԭ��
        */
         static void      sendLeftButtonDown(MouseFlag nFlags, ScreenPoint^ pt);
        /**
        *  @brief  ����������̧��
        *  @param[in]  pt:��Ļ�����꣬���ӿ������Ͻ�Ϊԭ��
        */
         static void      sendLeftButtonUp(MouseFlag nFlags, ScreenPoint^ pt);
        /**
        *  @brief  ��������Ҽ�����
        *  @param[in]  pt:��Ļ�����꣬���ӿ������Ͻ�Ϊԭ��
        */
         static void      sendRightButtonDown(MouseFlag nFlags, ScreenPoint^ pt);
        /**
        *  @brief  ��������Ҽ�̧��
        *  @param[in]  pt:��Ļ�����꣬���ӿ������Ͻ�Ϊԭ��
        */
         static void      sendRightButtonUp(MouseFlag nFlags, ScreenPoint^ pt);
        /**
        *  @brief  ��������м�����
        *  @param[in]  pt:��Ļ�����꣬���ӿ������Ͻ�Ϊԭ��
        */
         static void      sendMButtonDown(MouseFlag nFlags, ScreenPoint^ pt);
        /**
        *  @brief  ��������м�̧��
        *  @param[in]  pt:��Ļ�����꣬���ӿ������Ͻ�Ϊԭ��
        */
         static void      sendMButtonUp(MouseFlag nFlags, ScreenPoint^ pt);
        /**
        *  @brief  ���ͼ��̰�����Ϣ
        *  @param[in] wentDown:�Ƿ���
        *  @param[in] key:������
        */
         static void      sendKeyEvent(bool wentDown, int key);

        /**
        *  @brief  ������ȡ��ĻͼƬ���������֡��
        */
         static void      getBMPData(IntPtr^% datas, int %w, int %h, MChannel^% channel);
        /**
        *  @brief  ��������
        *  @param[in] cmd:������
        */
         static void      sendCommand(String^ cmd);
        /**
        *  @brief  ���ļ�
        *  @param[in] filename:�ļ���
        */
         static void      openFile(String^ filename);
        /**
        *  @brief  �رյ�ǰ�ļ�
        *  @param[in] isSave:�Ƿ񱣴�
        */
         static void      closeFile(bool isSave);
        /**
        *  @brief  �˳�����
        *  @param[in] isSave:�Ƿ񱣴�
        */
        static void      exitProgram(bool isSave);
        /**
        *  @brief  ��ȡ���������ͨ�Ŷ˿�
        *  @return �����л�ȡ���ɹ��򷵻�-1
        */
         static int getServerPort();
	};
}
