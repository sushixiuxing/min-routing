/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/command-line.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");

int
main (int argc, char *argv[])
{
  uint32_t nPackets=1;
  CommandLine cmd;
  cmd.AddValue("nPackets","Number of packets to echo",nPackets);
  cmd.Parse (argc, argv);
  
  Time::SetResolution (Time::NS);
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO); //日志信息的输出（结果输出）
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO); //日志信息的输出（结果输出）
  NS_LOG_INFO("Creating Topology");
  NodeContainer nodes;   //生成两个节点对象
  nodes.Create (2);

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer devices;   //安装网络设备
  devices = pointToPoint.Install (nodes);

  InternetStackHelper stack;   //安装协议栈
  stack.Install (nodes);

  Ipv4AddressHelper address;   //配置ipv4地址
  address.SetBase ("10.1.1.0", "255.255.255.0");   //从10.1.1.0分配IP地址，255.255.255.0为掩码

  Ipv4InterfaceContainer interfaces = address.Assign (devices);

  UdpEchoServerHelper echoServer (9);  //在其中一个节点上使用UDP服务器应用

  ApplicationContainer serverApps = echoServer.Install (nodes.Get (1));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));    //仿真至少持续10秒

  UdpEchoClientHelper echoClient (interfaces.GetAddress (1), 9); //分配IP地址
  echoClient.SetAttribute ("MaxPackets", UintegerValue (nPackets));  //设置在仿真期间能够发送的最大包数
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));//两个包之间的等待时间
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));//包的大小

  ApplicationContainer clientApps = echoClient.Install (nodes.Get (0));
  clientApps.Start (Seconds (2.0)); //在服务器启动1秒之后再启动
  clientApps.Stop (Seconds (10.0));

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
