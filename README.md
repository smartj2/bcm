# 品质追溯管理系统（Barcode Traceability Management System）
## 重要：本分支将对代码进行重构，并换用SQL SERVER 2000作为本项目的DBMS。
### - For
--------
This is a windows application for outgoing traceability, developing with c++.
### - Tips
1. 项目菜单->项目属性->配置属性->常规->平台工具集，选择“VS2013WindowsXP(v120/v130/v150_xp)”；
2. 项目菜单->项目属性->配置属性->常规->MFC的使用，选择在静态库中使用MFC项目菜单->项目属性->配置属性->常规->MFC的使用，选择在静态库中使用MFC；
3. 项目菜单->项目属性->链接器->系统->子系统->控制台或窗口windows（根据你的项目类型选择），第二项版本号设成5.01；
4. C/C++->代码生成->运行库，选择“多线程调试(/MTd)"；
5. 配置C++标准库boost。