# Lvgl
Lvgl GUI

1. 改lvgl及makefile
（1）lvgl
东西都是现成了，下了当前最新的lvgl 7.11.0版本，
主要改了lv_conf.h，lv_drv_conf.h，lv_ex_conf.h三个配置文件，以及main函数修改了一下。
具体忘记改哪些了，都是make的时候，哪里报错就改哪里的，直接看我的例程源文件

（2）
参考网上把makefile文件改了一下，主要是把交叉编译链的目录改成自己的目录就可以了，比如我的是
CC = /home/f1c200s/buildroot-2021.02.6/buildroot-2021.02.6/output/host/bin/arm-buildroot-linux-uclibcgnueabi-gcc
然后就可以make 生成执行文件 lvgl_7110_demo

（3）可能需要触摸屏库tslib

2. 运行
将编译出来的lvgl_7110_demo放在tiny200-r3的文件系统，比如我的放在root文件夹下，运行如下
# pwd
/root
# ls
lvgl_7110_demo
# chmod 777 lvgl_7110_demo
# ./lvgl_7110_demo 3
lvgl version:7.11.0
demo num:3
The framebuffer device was opened successfully.
800x480, 32bpp
The framebuffer device was mapped to memory successfully.

总共51个demo,运行第几个demo就加相应的数字，如运行第3个就是
./lvgl_7110_demo 3