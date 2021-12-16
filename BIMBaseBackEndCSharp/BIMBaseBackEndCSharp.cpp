// 这是主 DLL 文件。

#include "stdafx.h"

#include "BIMBaseBackEndCSharp.h"

#pragma managed(push, off)
#include "BIMBaseBackend.h"
#pragma managed(pop)
static void _proceeBMP11(uint8_t* datas, int w, int h, BP::BPMChannel channel)
{
    IntPtr^ datasCs = gcnew  IntPtr(datas);
    BIMBasePlatform::MChannel^ channelCs = gcnew BIMBasePlatform::MChannel();
    channelCs = BIMBasePlatform::MChannel(channel);
    BIMBasePlatform::BIMBaseBackend::singTon()->fireIBmpReceiverEvent(datasCs, w, h, channelCs);
}
static void getWindowRect11(BP::ScreenRect& rect)
{
    BIMBasePlatform::ScreenRect^ rectCs = gcnew BIMBasePlatform::ScreenRect();
    BIMBasePlatform::BIMBaseBackend::singTon()->fireIWindowRectProviderEvent(rectCs);

    rect.bottom = rectCs->bottom;
    rect.left = rectCs->left;
    rect.right = rectCs->right;
    rect.top = rectCs->top;
}
using namespace BIMBasePlatform;
#pragma managed(push, off)

namespace BIMBaseCPP
{
    class BPIBMPReceiverEvent : public BP::IBMPReceiver
    {
    public:

        //virtual void _proceeBMP(uint8_t* datas, int w, int h, BPMChannel channel) = 0;
        virtual void _proceeBMP(uint8_t* datas, int w, int h, BP::BPMChannel channel) override
        {
            _proceeBMP11(datas,w,h,channel);
        }
    };

    class BPIWindowRectProviderEvent : public BP::IWindowRectProvider
    {
    public:
        virtual void getWindowRect(BP::ScreenRect& rect)
        {
            getWindowRect11(rect);
        }
    };
}

static BIMBaseCPP::BPIBMPReceiverEvent* g_bmpReceiverEvent = nullptr;
static BIMBaseCPP::BPIWindowRectProviderEvent* g_IWindowRectProviderEvent = nullptr;
_declspec(dllexport) void registerFuncs()
{
    g_bmpReceiverEvent = new BIMBaseCPP::BPIBMPReceiverEvent();
    BP::BIMBaseBackend::registerBMPReceiver(g_bmpReceiverEvent);
    g_IWindowRectProviderEvent = new BIMBaseCPP::BPIWindowRectProviderEvent();
    BP::BIMBaseBackend::registerWindowRectProvider(g_IWindowRectProviderEvent);
}
#pragma managed(pop)

BIMBaseBackend^ BIMBaseBackend::singTon()
{
    if (s_singleton == nullptr)
    {
        s_singleton = gcnew BIMBaseBackend();
    }
    return s_singleton;
}

void BIMBaseBackend::fireIBmpReceiverEvent(IntPtr^ dataList, int nWidth, int nHeight, MChannel^ channel)
{
    IBmpReceiverEventArgs^ ev = gcnew IBmpReceiverEventArgs(dataList, nWidth, nHeight, channel);
    IBmpReceiverEvent(this, ev);
}

void BIMBasePlatform::BIMBaseBackend::fireIWindowRectProviderEvent(ScreenRect^% rect)
{
    IWindowRectProviderEventArgs^ ev = gcnew IWindowRectProviderEventArgs();
    IWindowRectProviderEvent(this, ev);
    rect = ev->m_rect;
}

void BIMBasePlatform::BIMBaseBackend::sendWindowResize(int x, int y)
{
    BP::BIMBaseBackend::sendWindowResize(x, y);
}

void BIMBasePlatform::BIMBaseBackend::sendTimerEvent()
{
    BP::BIMBaseBackend::sendTimerEvent();
}

void BIMBasePlatform::BIMBaseBackend::sendMouseWheel(MouseFlag nFlags, int delta, ScreenPoint^ pt)
{
    BP::BIMBaseBackend::ScreenPoint ptc;
    ptc.x = pt->x;
    ptc.y = pt->y;
    BP::BIMBaseBackend::sendMouseWheel(nFlags, delta, ptc);
}

void BIMBasePlatform::BIMBaseBackend::sendMouseMove(MouseFlag nFlags, ScreenPoint^ pt)
{
    BP::BIMBaseBackend::ScreenPoint ptc;
    ptc.x = pt->x;
    ptc.y = pt->y;
    BP::BIMBaseBackend::sendMouseMove(nFlags, ptc);
}

void BIMBasePlatform::BIMBaseBackend::sendLeftButtonDown(MouseFlag nFlags, ScreenPoint^ pt)
{
    BP::BIMBaseBackend::ScreenPoint ptc;
    ptc.x = pt->x;
    ptc.y = pt->y;
    BP::BIMBaseBackend::sendLeftButtonDown(nFlags, ptc);
}

void BIMBasePlatform::BIMBaseBackend::sendLeftButtonUp(MouseFlag nFlags, ScreenPoint^ pt)
{
    BP::BIMBaseBackend::ScreenPoint ptc;
    ptc.x = pt->x;
    ptc.y = pt->y;
    BP::BIMBaseBackend::sendLeftButtonUp(nFlags, ptc);
}

void BIMBasePlatform::BIMBaseBackend::sendRightButtonDown(MouseFlag nFlags, ScreenPoint^ pt)
{
    BP::BIMBaseBackend::ScreenPoint ptc;
    ptc.x = pt->x;
    ptc.y = pt->y;
    BP::BIMBaseBackend::sendRightButtonDown(nFlags, ptc);
}

void BIMBasePlatform::BIMBaseBackend::sendRightButtonUp(MouseFlag nFlags, ScreenPoint^ pt)
{
    BP::BIMBaseBackend::ScreenPoint ptc;
    ptc.x = pt->x;
    ptc.y = pt->y;
    BP::BIMBaseBackend::sendRightButtonUp(nFlags, ptc);
}

void BIMBasePlatform::BIMBaseBackend::sendMButtonDown(MouseFlag nFlags, ScreenPoint^ pt)
{
    BP::BIMBaseBackend::ScreenPoint ptc;
    ptc.x = pt->x;
    ptc.y = pt->y;
    BP::BIMBaseBackend::sendMButtonDown(nFlags, ptc);
}

void BIMBasePlatform::BIMBaseBackend::sendMButtonUp(MouseFlag nFlags, ScreenPoint^ pt)
{
    BP::BIMBaseBackend::ScreenPoint ptc;
    ptc.x = pt->x;
    ptc.y = pt->y;
    BP::BIMBaseBackend::sendMButtonUp(nFlags, ptc);
}

void BIMBasePlatform::BIMBaseBackend::sendKeyEvent(bool wentDown, int key)
{
    BP::BIMBaseBackend::sendKeyEvent(wentDown, key);
}

void BIMBasePlatform::BIMBaseBackend::getBMPData(IntPtr^% datas_, int %w_, int %h_, MChannel^% channel_)
{
    uint8_t *datas;
    int w, h;
    BP::BPMChannel channel;
    BP::BIMBaseBackend::getBMPData(datas,w,h,channel);
    datas_ = gcnew IntPtr(datas);
    w_ = w;
    h_ = h;
    channel_ = gcnew MChannel(MChannel::enRGBA);
    switch (channel)
    {
    case BP::enRGBA:
        channel_ = gcnew MChannel(MChannel::enRGBA);
        break;
    case BP::enABGR:
        channel_ = gcnew MChannel(MChannel::enABGR);
        break;
    case BP::enBGRA:
        channel_ = gcnew MChannel(MChannel::enBGRA);
        break;
    case BP::enARGB:
        channel_ = gcnew MChannel(MChannel::enARGB);
        break;
    case BP::enRGB:
        channel_ = gcnew MChannel(MChannel::enRGB);
        break;
    case BP::enBGR:
        channel_ = gcnew MChannel(MChannel::enBGR);
        break;
    default:
        break;
    }
    
}
#include "vcclr.h"
void BIMBasePlatform::BIMBaseBackend::sendCommand(String^ cmd)
{
    pin_ptr<const wchar_t> nativeString1 = PtrToStringChars(cmd);
    const wchar_t* tt = (const wchar_t*)nativeString1;
    BP::BIMBaseBackend::sendCommand(tt);
}

void BIMBasePlatform::BIMBaseBackend::openFile(String^ filename)
{
    pin_ptr<const wchar_t>  nativeString1 = PtrToStringChars(filename);
    BP::BIMBaseBackend::openFile((const wchar_t*)(nativeString1));
}

void BIMBasePlatform::BIMBaseBackend::closeFile(bool isSave)
{
    BP::BIMBaseBackend::closeFile(isSave);

}

void BIMBasePlatform::BIMBaseBackend::exitProgram(bool isSave)
{
    BP::BIMBaseBackend::exitProgram(isSave);
}

int BIMBasePlatform::BIMBaseBackend::getServerPort()
{
    return BIMBaseBackend::getServerPort();
}

