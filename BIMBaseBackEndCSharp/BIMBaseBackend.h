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
    //ͼƬ��ɫͨ��
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
    typedef unsigned int  MouseFlag; //��귢���¼�ͬʱ����Shift����control��������shift����4������control��8������ͬʱ������4|8=12
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
        *  @brief  ���ʹ��ڸı��С��Ϣ
        *  @param[in]  x: �����¿��
        *  @param[in]  y: �����¸߶�
        */
        BIMBASEBACKEND_API static void      sendWindowResize(int x, int y);
        /**
        *  @brief  ����timer�¼���������
        */
        BIMBASEBACKEND_API static void      sendTimerEvent();
        /**
        *  @brief  ������������Ϣ
        *  @param[in]  delta:������ֵ
        *  @param[in]  pt:��Ļ�����꣬���ӿ������Ͻ�Ϊԭ��
        */
        BIMBASEBACKEND_API static void      sendMouseWheel(MouseFlag nFlags, int delta, ScreenPointCR pt);
        /**
        *  @brief  ��������ƶ���Ϣ
        *  @param[in]  pt:��Ļ�����꣬���ӿ������Ͻ�Ϊԭ��
        */
        BIMBASEBACKEND_API static void      sendMouseMove(MouseFlag nFlags, ScreenPointCR pt);
        /**
        *  @brief  ��������������
        *  @param[in]  pt:��Ļ�����꣬���ӿ������Ͻ�Ϊԭ��
        */
        BIMBASEBACKEND_API static void      sendLeftButtonDown(MouseFlag nFlags, ScreenPointCR pt);
        /**
        *  @brief  ����������̧��
        *  @param[in]  pt:��Ļ�����꣬���ӿ������Ͻ�Ϊԭ��
        */
        BIMBASEBACKEND_API static void      sendLeftButtonUp(MouseFlag nFlags, ScreenPointCR pt);
        /**
        *  @brief  ��������Ҽ�����
        *  @param[in]  pt:��Ļ�����꣬���ӿ������Ͻ�Ϊԭ��
        */
        BIMBASEBACKEND_API static void      sendRightButtonDown(MouseFlag nFlags, ScreenPointCR pt);
        /**
        *  @brief  ��������Ҽ�̧��
        *  @param[in]  pt:��Ļ�����꣬���ӿ������Ͻ�Ϊԭ��
        */
        BIMBASEBACKEND_API static void      sendRightButtonUp(MouseFlag nFlags, ScreenPointCR pt);
        /**
        *  @brief  ��������м�����
        *  @param[in]  pt:��Ļ�����꣬���ӿ������Ͻ�Ϊԭ��
        */
        BIMBASEBACKEND_API static void      sendMButtonDown(MouseFlag nFlags, ScreenPointCR pt);
        /**
        *  @brief  ��������м�̧��
        *  @param[in]  pt:��Ļ�����꣬���ӿ������Ͻ�Ϊԭ��
        */
        BIMBASEBACKEND_API static void      sendMButtonUp(MouseFlag nFlags, ScreenPointCR pt);
        /**
        *  @brief  ���ͼ��̰�����Ϣ
        *  @param[in] wentDown:�Ƿ���
        *  @param[in] key:������
        */
        BIMBASEBACKEND_API static void      sendKeyEvent(bool wentDown, int key); 
        /**
        *  @brief  ע�����ͼƬ�ӿ�
        *  @param[in] bmpReceiver:����ͼƬ�ӿ�,ֻҪ������ͼƬ�϶��Ǳ仯��
        */
        BIMBASEBACKEND_API static void      registerBMPReceiver(IBMPReceiver* bmpReceiver);
        /**
        *  @brief  ������ȡ��ĻͼƬ���������֡��
        */
        BIMBASEBACKEND_API static void      getBMPData(uint8_t*& datas, int &w, int &h, BPMChannel& channel);
        /**
        *  @brief  ע�᷵�ش��ڴ�С�ӿ�
        *  @param[in] rectProvider:���ش��ڴ�С�ӿ�
        */
        BIMBASEBACKEND_API static void      registerWindowRectProvider(IWindowRectProvider * rectProvider);
        /**
        *  @brief  ��������
        *  @param[in] cmd:������
        */
        BIMBASEBACKEND_API static void      sendCommand(wchar_t const* cmd);
        /**
        *  @brief  ���ļ�
        *  @param[in] filename:�ļ���
        */
        BIMBASEBACKEND_API static void      openFile(wchar_t const* filename);
        /**
        *  @brief  �رյ�ǰ�ļ�
        *  @param[in] isSave:�Ƿ񱣴�
        */
        BIMBASEBACKEND_API static void      closeFile(bool isSave);
        /**
        *  @brief  �˳�����
        *  @param[in] isSave:�Ƿ񱣴�
        */
        BIMBASEBACKEND_API static void      exitProgram(bool isSave);
        /**
        *  @brief  ��ȡ���������ͨ�Ŷ˿�
        *  @return �����л�ȡ���ɹ��򷵻�-1
        */
        BIMBASEBACKEND_API static int getServerPort();
    };
}