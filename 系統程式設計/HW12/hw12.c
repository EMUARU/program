#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>
#include <sys/inotify.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>

#define errExit(x) perror(x), exit(1)

#define MAX_DIRS 1024
#define EVENT_SIZE    ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN    ( 1024 * ( EVENT_SIZE + 16 ) )

int inotifyFd;
int wd[MAX_DIRS];
char *wd_names[MAX_DIRS];
int wd_count = 1;

void monitor_directory(const char *path)
{
    wd[wd_count] = inotify_add_watch(inotifyFd, path, IN_CREATE | IN_DELETE | IN_MOVED_FROM | IN_MOVED_TO);
    wd_names[wd_count] = strdup(path);
    wd_count++;
}

int list_subdirectories(const char *name, const struct stat *status, int type, struct FTW *ftw)
{
    if (type == FTW_D && ftw->level > 0)
        monitor_directory(name);

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    if ((inotifyFd = inotify_init()) == -1)
        errExit("inotify_init");

    monitor_directory(argv[1]);

    if (nftw(argv[1], list_subdirectories, 20, FTW_PHYS) == -1)
        errExit("nftw");

    char buffer[EVENT_BUF_LEN];
    while (1) 
    {
        int numRead;
        if ((numRead = read(inotifyFd, buffer, EVENT_BUF_LEN)) < 0)
            errExit("read");

        int i = 0;
        while (i < numRead)
        {
            struct inotify_event *event = (struct inotify_event *)&buffer[i];
            if (event->len)
            {
                if (event->mask & IN_ISDIR)
                {
                    if (event->mask & IN_CREATE)
                    {
                        printf("New dir %s created in %s\n", event->name, wd_names[event->wd]);
                        char new_dir_path[PATH_MAX];
                        snprintf(new_dir_path, PATH_MAX, "%s/%s", wd_names[event->wd], event->name);
                        monitor_directory(new_dir_path);
                    }
                    else if (event->mask & IN_DELETE)
                        printf("Dir %s deleted from %s\n", event->name, wd_names[event->wd]);
                    else if (event->mask & IN_MOVED_FROM)
                        printf("Dir %s moved out of %s\n", event->name, wd_names[event->wd]);
                    else if (event->mask & IN_MOVED_TO)
                        printf("Dir %s moved into %s\n", event->name, wd_names[event->wd]);
                }
                else
                {
                    if (event->mask & IN_CREATE)
                        printf("New file %s created in %s\n", event->name, wd_names[event->wd]);
                    else if (event->mask & IN_DELETE)
                        printf("File %s deleted from %s\n", event->name, wd_names[event->wd]);
                    else if (event->mask & IN_MOVED_FROM)
                        printf("File %s moved out of %s\n", event->name, wd_names[event->wd]);
                    else if (event->mask & IN_MOVED_TO)
                        printf("File %s moved into %s\n", event->name, wd_names[event->wd]);
                }
            }
            i += EVENT_SIZE + event->len;
        }
    }

    for (int j = 0; j < wd_count; j++)
    {
        inotify_rm_watch(inotifyFd, wd[j]);
        free(wd_names[j]);
    }
    close(inotifyFd);
    return 0;
}
