// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <dirent.h>
// #include <unistd.h>
// #include <sys/stat.h>
// void listdir(const char *dir, int showhide) {
//     printf("%s:\n", dir);
//     DIR *od = opendir(dir);
//     if (od == NULL) {
//         perror("fail open dir");
//         return;
//     }
//     struct dirent *rd;
//     struct stat rf;
//     int num = 0;
//     while ((rd = readdir(od)) != NULL) {
//         if (!showhide && rd->d_name[0] == '.') {
//             continue;
//         }
//         char pathd[1024];
//         snprintf(pathd, sizeof(pathd), "%s/%s", dir, rd->d_name);
//         if (stat(pathd, &rf) == -1) {
//             perror("stat failed");
//             continue;
//         }
//         if (S_ISDIR(rf.st_mode)) {
//             printf("\033[34;1m%-14s\033[0m", rd->d_name);
//         } else if (S_ISREG(rf.st_mode)) {
//             if (access(pathd, X_OK) == 0) {
//                 printf("\033[32;1m%-14s\033[0m", rd->d_name);
//             } else {
//                 printf("\033[37;1m%-14s\033[0m", rd->d_name);
//             } 
//         }
//         num++;
//         if (num == 5) {
//             printf("\n");
//             num = 0;
//         }
//     }
//     if (num != 0) {
//         printf("\n");
//     }
//     closedir(od);
// }
// void listpanduan(const char *dir, int showhide, int depth, int max) {
//     if (depth > max) {
//         return;
//     }
//     DIR *dirr = opendir(dir);
//     if (dirr == NULL) {
//         perror("fail open dir");
//         return;
//     }
//     struct dirent *r;
//     struct stat filestat;
//     while ((r = readdir(dirr)) != NULL) {
//         char path[1024];
//         snprintf(path, sizeof(path), "%s/%s", dir, r->d_name);       
//         if (!showhide && r->d_name[0] == '.') {
//             continue;
//         }
//         if (stat(path, &filestat) == -1) {
//             continue;
//         }
//         if (S_ISDIR(filestat.st_mode)) {
//             listdir(path, showhide);  
//             listpanduan(path, showhide, depth + 1, max);  
//         }
//     }
//     closedir(dirr);
// }
// int main(int argc, char *argv[]) {
//     char *dir_path;
//     int showhide = 0;
//     int max = 5;  
//     if (argc > 1) {
//         if (strcmp(argv[1], "-a") == 0) {
//             showhide = 1;
//             if (argc > 2) { 
//                 dir_path = argv[2];
//             }
//         } else {
//             dir_path = argv[1];
//         }
//     }
//     listdir(dir_path, showhide);
//     listpanduan(dir_path, showhide, 0, max);
//     return EXIT_SUCCESS;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>

// int main(int argc, char *argv[]) {
//     // 如果命令行没有指定目录
//     int cnt=0;
//     char *dir;
//     char diir[1024];
//     printf("%c\n",argv[argc-1][0]);
//     if (argv[argc-1][0]!='/') {
//         //char cwd[1024];
//         char *cwd;
//         cwd=(char*)malloc(sizeof(char)*1024);
//         if (getcwd(cwd,1024) != NULL) {
//             dir=cwd;
//             printf("%s\n", cwd);
//             printf("%s",dir);
//         }
//     } else {
//         // 如果命令行指定了目录
//         printf("argc=%d\n",argc);
//         printf("指定的目录: %s\n", argv[argc-1]);
//         dir=argv[argc-1];
//         cnt=strlen(dir);
//         printf("cnt=%d\n",cnt);
//         printf("%c\n",dir[cnt-1]);
//         strcpy(diir,dir);
//         if(argv[argc-1][cnt-1]!='/'){   
//             const char *a="/";
//             strncat(diir,a,1);
//         }
//         printf("%s",diir);
//     }
//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> 
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <getopt.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

char *dir_path;
int cmp(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}
struct store
{
    char name[1024];
    long time;
};
int cmpe(const void *a, const void *b)
{
    struct store *file_a = (struct store *)a;
    struct store *file_b = (struct store *)b;
    if (file_a->time > file_b->time)
        return -1;
    if (file_a->time < file_b->time)
        return 1;
    return 0;
}
void print(int mark)
{
    DIR *dirr = opendir(dir_path);
    if (dirr == NULL)
    {
        perror("fail open dir");
        return;
    }
    char rwx[11];
    struct store s[5000];
    int j = 0,filenum = 0;
    int i = 0;
    struct dirent *r;
    struct stat filestat;
    while ((r = readdir(dirr)) != NULL)
    {
        if(mark%2!=0){
            if (r->d_name[0]=='.')
            {
                continue;
            }
        }
        char path[1024];
        strcpy(path, dir_path);
        strncat(path, r->d_name, strlen(r->d_name));
        if (stat(path, &filestat) == -1)
        {
            perror("files fail");
            continue;
        }
        if(mark%7==0){
            strcpy(s[filenum].name, r->d_name);
            s[filenum].time = filestat.st_mtime;
            filenum++;
            qsort(s, filenum, sizeof(struct store), cmpe);
        }
        if(mark%13==0){
            printf("%ld ", (long)filestat.st_ino);
        }
        if(mark%17==0)
        printf("%2ld ", filestat.st_blocks / 2);
        if(mark%3==0){
            mode_t file = filestat.st_mode;
            if (S_ISDIR(file))
                rwx[0] = 'd';
            else if (S_ISLNK(file))
                rwx[0] = 'l';
            else
                rwx[0] = '-';
            rwx[1] = (file & S_IRUSR) ? 'r' : '-';
            rwx[2] = (file & S_IWUSR) ? 'w' : '-';
            rwx[3] = (file & S_IXUSR) ? 'x' : '-';
            rwx[4] = (file & S_IRGRP) ? 'r' : '-';
            rwx[5] = (file & S_IWGRP) ? 'w' : '-';
            rwx[6] = (file & S_IXGRP) ? 'x' : '-';
            rwx[7] = (file & S_IROTH) ? 'r' : '-';
            rwx[8] = (file & S_IWOTH) ? 'w' : '-';
            rwx[9] = (file & S_IXOTH) ? 'x' : '-';
            rwx[10] = '\0';
            struct passwd *user = getpwuid(filestat.st_uid);
            struct group *gro = getgrgid(filestat.st_gid);
            time_t mod_time = filestat.st_mtime;
            struct tm *tt = localtime(&mod_time);
            char ctime[100];
            strftime(ctime, sizeof(ctime), "%m月 %d %H:%M", tt);
            printf("%-s %2ld %-s %-s %5ld %s ", rwx, filestat.st_nlink, user->pw_name, gro->gr_name, filestat.st_size, ctime);
        }
        if (S_ISDIR(filestat.st_mode))
        {
            printf("\033[34;1m %-14s\033[0m", r->d_name);
        }
        else if (S_ISREG(filestat.st_mode) && access(path, X_OK))
        {
            printf("\033[37;1m %-14s\033[0m", r->d_name);
        }
        else
        {
            printf("\033[32;1m %-14s\033[0m", r->d_name);
        }
        if(mark%3==0) printf("\n");
        else{
            i++;
            if (i==3 )
            {
                printf("\n");
                i=0;
            }
        }
    }
    closedir(dirr);
}
int main(int argc, char *argv[])
{
    int max=5;
    char *ext;
    if(argc==1||argv[argc-1][0]!='/'){
        ext=(char*)malloc(sizeof(char)*1024);
        getcwd(ext,1024);
        if(ext[strlen(ext)-1]!='/'){   
            char diir[1024];
            strcpy(diir,ext);
            const char *a="/";
            strncat(diir,a,1);
            dir_path=diir;
        }else dir_path=ext;
        free(ext);
    }else {
        int cnt;
        ext=argv[argc-1];
        cnt=strlen(ext);
        char diir[1024];
        strcpy(diir,ext);
        if(argv[argc-1][cnt-1]!='/'){   
            const char *a="/";
            strncat(diir,a,1);
        }
        dir_path=diir;
    }
    char *optstring = "alRtris";
    int ch, mark = 1;
    while ((ch = getopt(argc, argv, optstring))!= -1)
    {
        switch (ch)
        {
        case 'a':
            mark *= 2;
            break;
        case 'l':
            mark *= 3;
            break;
        case 'R':
            mark *= 5;
            break;
        case 't':
            mark *= 7;
            break;
        case 'r':
            mark *= 11;
            break;
        case 'i':
            mark *= 13;
            break;
        case 's':
            mark *= 17;
            break;
        default:
            break;
        }
    }
    print(mark);
    return 0;
}