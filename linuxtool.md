#  1、Clion的简单介绍
    CLion是以IntelliJ为基础，专为开发C及C++所设计的跨平台IDE，可以在Windows、Linux及MacOS使用，这里我是在ubuntu 16.0.4基础上安装。
## 2、下载 Linux版Clion的.tar.gz的压缩包 
    wget https://download.jetbrains.8686c.com/cpp/CLion-2016.2.2.tar.gz
## 3、解压CLion-2016.2.2.tar.gz到当前文件夹
    tar -zxvf CLion-2016.2.2.tar.gz  
## 4、运行clion.sh 安装脚本
    cd clion-2016.2.2/bin/  
    ./clion.sh  
## 5、打开workspace
    第一次打开点击ok
    然后同意就行
    CLion是收费的，可以选择试用30天，搭建了一个破解的服务器，
    地址是：
    http://bash.pub:1017 可能连接不上
    选择自己喜欢的主题。
    然后一直往下走，插件先不安装。
    然后新建一个C项目
## 6、激活码激活
    获取  激活码  http://idea.lanyus.com/
    
# nfs服务器搭建
    多台电脑之间创建共享文件夹
## nfs服务器端配置
### 1、安装nfs服务
    1.1-安装Ubuntu nfs服务器端：
        sudo apt-get install nfs-kernel-server
        (在安装nsf-kernel-server的时候，也会安装nfs-commom。如果没有安装这个软件包，则要执行1.2中的命令了)
    1.2-安装nfs的客户端：
    sudo apt-get install nfs-common
### 2、修改配置文件   
    sudo vim /etc/exports

    修改内容如下：
    /home *(rw,sync,no_root_squash)

    /home   ：共享的目录
    *       ：指定哪些用户可以访问
                *  所有可以ping通该主机的用户
                192.168.1.*  指定网段，在该网段中的用户可以挂载
                192.168.1.12 只有该用户能挂载
    (ro,sync,no_root_squash)：  权限
            ro : 只读
            rw : 读写
            sync :  同步
            no_root_squash: 不降低root用户的权限
        其他选项man 5 exports 查看
    前面那个目录是与nfs服务客户端共享的目录，
    *代表允许所有的网段访问（也可以使用具体的IP）
    rw：挂接此目录的客户端对该共享目录具有读写权限
    sync：资料同步写入内存和硬盘
    no_root_squash：客户机用root访问该共享文件夹时，不映射root用户。
    root_squash：客户机用root用户访问该共享文件夹时，将root用户映射成匿名用户
    no_subtree_check：不检查父目录的权限。

    2.2-nfs是一个RPC程序，使用它前，需要映射好端口，通过rpcbind 设定：
        sudo service rpcbind restart restart
    2.3-重启nfs服务：
        sudo service restartnfs-kernel-server restart

        sudo /etc/init.d/nfs-kernel-server restart
    2.4-测试运行以下命令来显示一下共享出来的目录：
        showmount -e


    ## 客户端访问配置


### window  安装 nfs 客户端
    win10 控制面板 程序和功能 启用或关闭Windows功能 勾选NFS服务 确定后系统进行自动安装
    打开 cmd 
    mount \\10.65.223.171\目录 x:

   挂载 umount x:
### winscp 访问 远程服务器文件 ftp协议
[百度参考](https://jingyan.baidu.com/article/d621e8da79ee562865913fce.html)

### 远程 命令行登陆服务器 shell
[Xmanager 服务器远程控制程序 ](https://www.netsarang.com/products/xme_overview.html)


