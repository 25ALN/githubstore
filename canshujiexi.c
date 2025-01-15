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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // 如果命令行没有指定目录
    int cnt=0;
    char *dir;
    char diir[1024];
    printf("%c\n",argv[argc-1][0]);
    if (argv[argc-1][0]!='/') {
        //char cwd[1024];
        char *cwd;
        cwd=(char*)malloc(sizeof(char)*1024);
        if (getcwd(cwd,1024) != NULL) {
            dir=cwd;
            printf("%s\n", cwd);
            printf("%s",dir);
        }
    } else {
        // 如果命令行指定了目录
        printf("argc=%d\n",argc);
        printf("指定的目录: %s\n", argv[argc-1]);
        dir=argv[argc-1];
        cnt=strlen(dir);
        printf("cnt=%d\n",cnt);
        printf("%c\n",dir[cnt-1]);
        strcpy(diir,dir);
        if(argv[argc-1][cnt-1]!='/'){   
            const char *a="/";
            strncat(diir,a,1);
        }
        printf("%s",diir);
    }
    return 0;
}
