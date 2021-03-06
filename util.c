#include "util.h"

#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#define DEV_PATH "/dev/"
#define DEV_PREFIXES ((char*[]){"ttyUSB", "ttyACM", NULL})
#define GUESSES 8

char *rr_guess_port() {
  char *name = malloc(NAME_MAX+1);
  DIR *devdir = opendir(DEV_PATH);
  if(!devdir) {
    return NULL;
  }
  
  struct dirent *file;
  while((file = readdir(devdir))) {
    size_t i;
    for(i = 0; DEV_PREFIXES[i]; ++i) {
      char *prefix = DEV_PREFIXES[i];
      if(!strncmp(file->d_name, prefix, strlen(prefix))) {
        /* TODO: Open connection and interrogate device */
        strcpy(name, file->d_name);
        closedir(devdir);
        return name;
      }
    }
  }

  closedir(devdir);
  
  return NULL;
}
