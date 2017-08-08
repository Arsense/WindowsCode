# WindowsCode

这是都是关于Windows的一些代码 主要有注入集合，有关线程，进程的操作，驱动等等，算是我写代码的主要地方吧

1. 先完成的是CreateRemoteThread Hook远程注入 后面跟它的两兄弟

2. NtCreateThreadEx()注入

3. RtlCreateUserThread()注入
想要看详细的分析 可以关注我的博客 谢谢，
if  you have more interests,you can focus on my blog  
http://www.cnblogs.com/arsense/
4. 后面是windows核心编程学习源代码

前面带序号的是windows核心编程的源码，觉得不错 放在这儿
##Fuzzer工具编写

- 8.8完成所有界面和控件
##Preapare包含

###线程的枚举
- CreateToolhelp32Snapshot()
- EnumProcess()
###窗口枚举
- EnumProcess
###一些注入和其他的
- ImeInject()
- ImportInjection()
- ProcessToken()
- SetWindowsDll()
- SetWindowsEx()
- SetWindowsHook2()
- UsnUpdataDemo()
##gitHub BlackBone学习
- 重量级程序 一言难尽
##VA Hook