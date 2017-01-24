如何下载android源代码：

1.获取repo工具：
curl https://storage.googleapis.com/git-repo-downloads/repo > ~/bin/repo
## 如果上述 URL 不可访问，可以用下面的：
## curl https://storage-googleapis.lug.ustc.edu.cn/git-repo-downloads/repo > ~/bin/repo
chmod a+x ~/bin/repo

2.初始化repo：
repo init -u git://mirrors.ustc.edu.cn/aosp/platform/manifest
## 如果提示无法连接到 gerrit.googlesource.com，可以编辑 ~/bin/repo，把 REPO_URL 一行替换成下面的：
## REPO_URL = 'https://gerrit-googlesource.lug.ustc.edu.cn/git-repo'

3.repo sync
如果要获取特点的版本：
repo init -u git://mirrors.ustc.edu.cn/aosp/platform/manifest -b android-4.0.1_r1



安卓开发相关网站：
http://zmywly8866.github.io/2014/11/22/android-developer-guide.html

环境准备：

1.安装ubuntu系统，或者虚拟机。
2.安装java的sdk
3.安装依赖包 ，命令是：sudo apt-get install flex bison gperf libsdl-dev libesd0-dev libwxgtk2.6-dev build-essential zip curl
4.安装调试工具，命令是：sudo apt-get install valgrind
