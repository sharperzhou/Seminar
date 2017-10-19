目录介绍
=========

1、服务器程序
  1）CalculationSimpleCOM，是一个进程外COM服务器，拥有一个ICalc接口；
  2）CalculationSimpleCOMProxy，是服务器端和客户端共用的存根代理dll；
  3）CalculationAutomation，是一个进程外自动化服务器，拥有一个ICalc2接口。

2、本地调用客户端程序
  1）TestSimpleCOM，用于调用CalculationSimpleCOM服务器进行本地调用测试；
  2）TestAutomation，用于调用CalculationAutomation服务器进行本地调用测试。

3、远程调用客户端程序
  1）TestRemote，分别调用上述两个服务器进行远程调用测试；
  2）TestRemoteAutomation，假设客户端只有服务端的tlb文件，将tlb转化为代理存根dll进行远程调用；
  3）TestRemoteAutomationProxy，自动化服务器的tlb转化为代理存根dll项目。


使用方法
=========

1、服务端通过Calculation_Instal/Uninstall.reg文件安装/卸载组件，CalculationSimpleCOMProxy
   的代理dll文件通过RegSvr32命令安装卸载。(使用*.reg时根据需要修改exe和tlb文件的路径)

2、本地调用直接使用客户端即可实现调用；远程调用需在客户端进行配置，一种方法是跟服务端配置
   相同环境(如1所示)，另一种方法是客户端只需要配置所用到的代理存根即可。

3、对于TestRemote项目，调用CalculationSimpleCOM只需安装CalculationSimpleCOMProxy代理存根dll
   即可，调用CalculationAutomation需安装同服务器一样完整的组件。

4、对于TestRemoteAutomation，由于对CalculationAutomation的tlb文件进行了转化，得到了其代理存
   根dll，只需像调用CalculationSimpleCOM一样安装代理存根dll即可。