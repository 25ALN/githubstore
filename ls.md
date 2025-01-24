### ls -a
列出当前目录中的所有文件和目录，包括那些以 .（点）开头的隐藏文件和隐藏目录。
### ls -l
长格式列出目录中的文件和子目录的详细信息
example
```c
-rw-r--r-- 1 user group  1024 Dec  4 12:34 file1.txt
drwxr-xr-x 2 user group  4096 Dec  4 12:35 folder1
```
- 1 文件类型和权限（如 -rw-r--r--）：
 第一个字符表示文件类型：- 表示普通文件，d 表示目录，l 表示符号链接等。
 接下来的九个字符表示文件的权限：前三个是文件所有者的权限，中间三个是同组用户的权限，
 最后三个是其他用户的权限。每个权限字符可以是 r（可读）、w（可写）或 x（可执行）。
- 2 硬链接数（如 1）：表示文件的硬链接数，通常对文件来说是 1，对目录来说是至少 2。
- 3 文件所有者（如 user）：文件的所有者。
- 4 文件所属组（如 group）：文件的所属组。
- 5 文件大小（如 1024）：文件的大小，以字节为单位。
- 6 修改日期和时间（如 Dec 4 12:34）：文件的最后修改日期和时间。
- 7 文件名（如 file1.txt 或 folder1）：文件或目录的名称。
### ls -R
递归地列出指定目录及其所有子目录中的文件和目录。这意味着它会显示目录及其所有嵌套子目录的内容。

### ls -t
用于根据文件或目录的修改时间对其进行排序，默认会按时间降序排列（即最近修改的文件或目录会排在最前面）。

### ls -r
用于反向排序列出文件和目录，即按照字母顺序的倒序排列

### ls -i
用于显示每个文件或目录的 inode 号。inode 是一个存储文件元数据（如文件大小、权限、所有者、修改时间等）
的数据结构。每个文件或目录都有一个唯一的 inode 编号，用于在文件系统中标识文件。

### ls -s
用于列出当前目录下的文件和目录，并显示它们的磁盘空间占用情况（以块为单位）。每个“块”通常是 512 字节，
具体的块大小可能会根据系统配置有所不同。

```
输出优先顺序 i>s>l
```

## stat
```c
struct stat {
  dev_t st_dev;     /* 文件的设备编号 */
  ino_t st_ino;     /* 索引结点编号 */ //innode号
  mode_t st_mode;    /* 文件类型和权限*/
  nlink_t st_nlink;   /*硬链接数 */
  uid_t st_uid;     /*用户ID*/
  gid_t st_gid;     /* 组ID*/
  dev_t st_rdev;    /* 设备类型（若此文件为设备文件，则为设备编号*/
  off_t st_size;    /* 文件大小，以字节为单位*/
  blksize_t st_blksize; /*文件系统的I/O块大小*/
  blkcnt_t st_blocks;  /* 块数 */
  time_t st_atime;   /* 访问时间 */
  time_t st_mtime;   /* 修改时间 */
  time_t st_ctime;   /* 更改时间 */
};

```
获取用户的ID与组ID，可用两个函数将他们转化为对应的用户名
- 例如
getpwuid(file_stat.st_uid)：根据文件的用户 ID (st_uid) 获取对应的用户名。如果获取失败，返回 NULL。
getgrgid(file_stat.st_gid)：根据文件的组 ID (st_gid) 获取对应的组名。如果获取失败，返回 NULL。

## 终端大小的获取

```c
#include<stdio.h>
#include<stdlib.h>
#include<sys/ioctl.h>
#include<termios.h>
#include<signal.h>
#include<unistd.h>

int main(int argc,char *argv[]){                                                         
  struct winsize info;
  ioctl(STDIN_FILENO,TIOCGWINSZ,&info);
  printf("当前终端为%d行%d列\n",info.ws_row,info.ws_col);
  return 0;
}
```
