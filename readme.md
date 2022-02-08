

进入MyShell可执行文件所在目录执行如下命令即可

```sh
./MyShell
```

得到输出如下

```sh
myshell:/home/hy/myCppProject/cmake_demo/myshell$ 
```

执行ls

```
myshell:/home/hy/myCppProject/cmake_demo/myshell$ ls
MyShell  MyShell.cpp  readme.md
```

执行ls -l：

```sh
myshell:/home/hy/myCppProject/cmake_demo/myshell$ ls -l
total 176
-rwxrwxr-x 1 hy hy 159632 12月 18 23:51 MyShell
-rw-rw-r-- 1 hy hy   3020 12月 19 16:08 MyShell.cpp
-rw-rw-r-- 1 hy hy  13420 12月  9 22:43 readme.md

```

执行ps

```sh
myshell:/home/hy/myCppProject/cmake_demo/myshell$ ps
    PID TTY          TIME CMD
 135724 pts/0    00:00:00 bash
 135766 pts/0    00:00:00 MyShell
 135847 pts/0    00:00:00 ps
```

执行cd：

```sh
myshell:/home/hy/myCppProject/cmake_demo/myshell$ cd /
myshell:/$ 
```

执行pwd和ls命令

```sh
myshell:/$ pwd
/
myshell:/$ ls
bin   cdrom  etc   lib	  lib64   media  opt   root  sbin  srv	     sys  usr
boot  dev    home  lib32  libx32  mnt	 proc  run   snap  swapfile  tmp  var
```

