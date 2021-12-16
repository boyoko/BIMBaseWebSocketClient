using BIMBasePlatform;
using ClassLibrary1;
using System;
using System.IO;
namespace testBackEndCsharp
{
    public class Class1
    {
        WSocketClientHelper _wSocketClient = new WSocketClientHelper("wss://localhost:5001/ws");
        public Class1()
        {
            _wSocketClient.OnOpen -= WSocketClient_OnOpen;
            _wSocketClient.OnMessage -= WSocketClient_OnMessage;
            _wSocketClient.OnClose -= WSocketClient_OnClose;
            _wSocketClient.OnError -= WSocketClient_OnError;

            _wSocketClient.OnOpen += WSocketClient_OnOpen;
            _wSocketClient.OnMessage += WSocketClient_OnMessage;
            _wSocketClient.OnClose += WSocketClient_OnClose;
            _wSocketClient.OnError += WSocketClient_OnError;
            _wSocketClient.Open();
        }

        public void Send(string stringMsg)
        {
            _wSocketClient.Send(stringMsg);
        }


        public void Send(byte[] bytes)
        {
            _wSocketClient.Send(bytes);
        }


        private void WSocketClient_OnError(object sender, Exception ex)
        {
            Console.WriteLine(ex.Message);
        }

        private void WSocketClient_OnClose(object sender, EventArgs e)
        {
            Console.WriteLine("Close");
        }

        /// <summary>
        /// 发送消息
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="data"></param>
        private void WSocketClient_OnMessage(object sender, string data)
        {
            Console.WriteLine(data);
        }

        /// <summary>
        /// 打开连接
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void WSocketClient_OnOpen(object sender, EventArgs e)
        {
            Console.WriteLine("connection OK");
        }


        public static void returnRect(object sender, IWindowRectProviderEventArgs rect)
        {
            rect.m_rect.left = 0;
            rect.m_rect.right = 600;
            rect.m_rect.bottom = 600;
            rect.m_rect.top = 0;
        }
        public static void processBMP(object sender, IBmpReceiverEventArgs bmpdata)
        {
            IntPtr data = (IntPtr)bmpdata.m_dataList;
            int wid = bmpdata.m_nWidth;
            int height = bmpdata.m_nHeight;
            MChannel ch = (MChannel)bmpdata.m_channel;
            unsafe
            {
                byte* src = (byte*)data.ToPointer();
                if (ch == MChannel.enABGR)
                {
                    int length = wid * height * 4;

                }
            }

        }
        public static int EntryPoint(string arg)
        {
            System.Timers.Timer timer = new System.Timers.Timer();

            timer.Interval = 30000;

            timer.Elapsed += delegate
            {
                BIMBaseBackend.singTon().IWindowRectProviderEvent += returnRect;
                BIMBaseBackend.singTon().IBmpReceiverEvent += processBMP;
                timer.Stop();
            };

            timer.Start();

            return 0;
        }




    }


}