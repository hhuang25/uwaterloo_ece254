/**
* @file: lab0.c
* @brief: Lab0-A, deliverable assignment
* @author: y27park, h53huang
* @date: 2013/09/12
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

/* Main function*/
int main(int argc, char *argv[])
{
	DIR *dir;

	char *ptr, *permission;

	struct stat *info;
	struct dirent *ent; 

	//open current directory
	dir = opendir(".");

	//find every file in the directory
	while((ent = readdir(dir)) != NULL)
	{
		//skip the parent directory and current directory
		if (strcmp(ent->d_name, ".") && strcmp(ent->d_name, ".."))
		{
			//allocate memory for stat
			info = malloc(sizeof(struct stat));
			//error checking and setting value for info
			if (stat(ent->d_name, info) < 0)
			{
				perror("error getting file");
				continue;
			}
			//converting file type
			if      (S_ISREG(info->st_mode))  ptr = "regular";
			else if (S_ISDIR(info->st_mode))  ptr = "directory";
			else if (S_ISCHR(info->st_mode))  ptr = "character special";
			else if (S_ISBLK(info->st_mode))  ptr = "block special";
			else if (S_ISFIFO(info->st_mode)) ptr = "fifo";
			else if (S_ISLNK(info->st_mode))  ptr = "symbolic link";
			else if (S_ISSOCK(info->st_mode)) ptr = "socket";
			else                              ptr = "**unknown mode**";
			//printing out information of each file
			printf("------------------=\n");
			printf("%4s\t%12s\n","Name",ent->d_name);
			printf("%4s\t%12s\n","Type",ptr);
			printf("%3s\t%13d\n","UID",info->st_uid);
			printf("%3s\t%13d\n","GID",info->st_gid);
			printf("%4s\t%12d\n","Size",info->st_size);
			printf("%13s\t%26s","Last accessed",ctime(&( info->st_atime)));
			printf("%12s\t%26s","Created time",ctime(&( info->st_ctime)));
			printf("%13s\t%26s","Last modified",ctime(&( info->st_mtime)));
			printf("Permission\t");
			printf( (S_ISDIR(info->st_mode)) ? "d" : "-");
			printf( (info->st_mode & S_IRUSR) ? "r" : "-");
			printf( (info->st_mode & S_IWUSR) ? "w" : "-");
			printf( (info->st_mode & S_IXUSR) ? "x" : "-");
			printf( (info->st_mode & S_IRGRP) ? "r" : "-");
			printf( (info->st_mode & S_IWGRP) ? "w" : "-");
			printf( (info->st_mode & S_IXGRP) ? "x" : "-");
			printf( (info->st_mode & S_IROTH) ? "r" : "-");
			printf( (info->st_mode & S_IWOTH) ? "w" : "-");
			printf( (info->st_mode & S_IXOTH) ? "x" : "-");
			printf("\n");
			//free memory
			free(info);

		}
	}
	//close directory
	closedir(dir);

	return 0;
	
}
