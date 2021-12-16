using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using testBackEndCsharp;

namespace ConsoleApp
{
    class Program
    {
        static void Main(string[] args)
        {
            Class1 c1 = new Class1();

            var str = JsonConvert.SerializeObject(new BimBaseWebSocketMessage 
            { 
                CommandName = "sendCommand",
                CommandContext = "测试数据",//发送的数据
            });


            c1.Send(str);

            Console.ReadKey();
        }
    }


    public class BimBaseWebSocketMessage
    {
        /// <summary>
        /// cmd:命令名
        /// </summary>
        public string CommandName { get; set; }
        /// <summary>
        /// 命令内容
        /// </summary>
        public string CommandContext { get; set; }
    }


}
