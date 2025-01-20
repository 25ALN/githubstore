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
struct store
{
    char name[1024];
    long time;
    int index;
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
void print(int mark,char *dir_path);
void listpanduan(int mark,char *dir, int depth,int max);
int main(int argc, char *argv[])
{
    char *ext;
    char *optstring = "alRtris";
    int ch, mark = 1;
    const char *a="/";
    for(int i=1;i<argc;i++){
        if(argv[i][0]=='/'&&i!=argc-1){
            int cnt;
            ext=argv[i];
            cnt=strlen(ext);
            char diir[1024];
            strcpy(diir,ext);
            if(argv[i][cnt-1]!='/'){   
                strncat(diir,a,1);
            }
            dir_path = diir;
        }else if(argv[i][0]=='.'){
            char *extl = (char *)malloc(sizeof(char) * 1024);
            if (extl == NULL) {
                perror("malloc failed for ext");
                return 1;
            }
            getcwd(extl, 1024);
            char *path = (char *)malloc(sizeof(char) * 1024);
            if (path == NULL) {
                perror("malloc failed for path");
                free(extl);
                return 1;
            }
            strncpy(path, argv[i], 1024);
            memmove(path, path + 1, strlen(path));
            strncat(extl, path, 1024 - strlen(extl) - 1);
            strncat(extl,a,1);
            dir_path = extl;
            free(path);
        }
    }
    if(dir_path==NULL){
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
    }else if(argv[argc-1][0]!='.'){
        int cnt;
        ext=argv[argc-1];
        cnt=strlen(ext);
        char diir[1024];
        strcpy(diir,ext);
        if(argv[argc-1][cnt-1]!='/'){   
            const char *a="/";
            strncat(diir,a,1);
        }
        dir_path = diir;
    }
    }
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
    if(mark%5==0){
        print(mark,dir_path);
        listpanduan(mark,dir_path,0,4);
    }else{
    print(mark,dir_path);
    }
    dir_path=NULL;
    return 0;
}
void listpanduan(int mark,char *dir, int depth,int max) {
    if (depth > max) {
        return;
    }
    DIR *dirr = opendir(dir);
    if (dirr == NULL) {
        perror("fail open dir");
        return;
    }
    struct dirent *r;
    struct stat filestat;
    while ((r = readdir(dirr)) != NULL) {
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dir, r->d_name); 
        const char *a="/";
        strncat(path,a,1);
        if (strcmp(r->d_name, ".") == 0 || strcmp(r->d_name, "..") == 0) continue;    
        if(mark%2!=0){
            if (r->d_name[0]=='.')
            {
                continue;
            }
        }
        if (stat(path, &filestat) == -1) {
            continue;
        }
        if (S_ISDIR(filestat.st_mode)) {
            print(mark,path);
            printf("\n");
            listpanduan(mark,path,depth+1,4);  
        }
    }
    closedir(dirr);
}
void print(int mark,char *dir_path)
{
    if(mark%5==0) printf("%s:\n", dir_path);
    DIR *dirr = opendir(dir_path);
    if (dirr == NULL)
    {
        perror("fail open dir");
        return;
    }
    char path[10240];
    char rwx[11];
    int j = 0,filenum = 0;
    struct dirent *r;
    struct stat *filestat = malloc(sizeof(struct stat) *10000); 
    struct store *s = malloc(sizeof(struct store) *10000);  
    while ((r = readdir(dirr)) != NULL)
    {
        if(r->d_name=="."||r->d_name=="..") break;
        if(mark%2!=0){
            if (r->d_name[0]=='.')
            {
                continue;
            }
        }
        strcpy(path, dir_path);
        strncat(path, r->d_name, strlen(r->d_name));
        if (stat(path, &filestat[filenum]) == -1)
        {
            perror("files fail");
            continue;
        }
        strcpy(s[filenum].name, r->d_name);
        s[filenum].time = filestat[filenum].st_mtime;
        s[filenum].index = filenum;
        filenum++;
    }
    if(mark%7==0){
        qsort(s, filenum, sizeof(struct store), cmpe);
        struct stat *aboutfilestat = malloc(sizeof(struct stat) * filenum);
        for (int i = 0; i < filenum; i++) {
            aboutfilestat[i] = filestat[s[i].index];
        }
        free(filestat);
        filestat = aboutfilestat;
    }
    if(mark%11==0){
        int end=filenum-1;
        for(int i=0;i<filenum/2;i++){
            struct stat t=filestat[i];
            filestat[i]=filestat[end];
            filestat[end]=t;
            struct store x=s[i];
            s[i]=s[end];
            s[end]=x;
            end--;
        }
    }
    for(int i=0;i<filenum;i++)
    {
        if(mark%13==0){
            printf("%ld ", (long)filestat[i].st_ino);
        }
        if(mark%17==0)
        printf("%2ld ", filestat[i].st_blocks / 2);
        if(mark%3==0){
            mode_t file = filestat[i].st_mode;
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
            struct passwd *user = getpwuid(filestat[i].st_uid);
            struct group *gro = getgrgid(filestat[i].st_gid);
            time_t mod_time = filestat[i].st_mtime;
            struct tm *tt = localtime(&mod_time);
            char ctime[100];
            strftime(ctime, sizeof(ctime), "%m月 %d %H:%M", tt);
            printf("%-s %2ld %-s %-s %5ld %s ", rwx, filestat[i].st_nlink, user->pw_name, gro->gr_name, filestat[i].st_size, ctime);
        }
        if (S_ISDIR(filestat[i].st_mode))
        {
            printf("\033[34;1m %-15s\033[0m", s[i].name);
        }
        else if (S_ISREG(filestat[i].st_mode) && access(s[i].name, X_OK))
        {
            printf("\033[37;1m %-15s\033[0m", s[i].name);
        }
        else
        {
            printf("\033[32;1m %-15s\033[0m", s[i].name);
        }
        if(mark%3==0) printf("\n");
        else{
            j++;
            if (j==3 )
            {
                printf("\n");
                j=0;
            }
        }
    }
    if (filestat != NULL) free(filestat);
    if (s != NULL) free(s);
    closedir(dirr);
}