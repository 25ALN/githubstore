```c
- git init
- git add 文件
- git add ./目录
- git commit -m "first commit"
- git remote rm origin
- git remote add origin git@github.com:25ALN/githubstore.git
- git push -u origin +main  //这个要慎重使用，会将新上传的文件覆盖远程仓库的所有文件
- 稳妥方法
- git pull --rebase origin main//可以将本次上传的文件合并在主分支
- git push origin main//最后push即可成功
//当本地的push被拒绝后使用 git pull origin main将远程的main合并到本地分支
