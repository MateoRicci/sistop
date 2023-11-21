#include "big_brother.h"
#include <stdio.h>
#include <string.h>
#include "fat_filename_util.h"

int is_log_file_dentry(unsigned char *base_name, unsigned char *extension) {
    return strncmp(LOG_FILE_BASENAME, (char *)base_name, 3) == 0 &&
           strncmp(LOG_FILE_EXTENSION, (char *)extension, 3) == 0;
}

int is_log_filepath(char *filepath) {
    return strncmp(LOG_FILE, filepath, 8) == 0;
}

int is_log_file_0xe5(char *base_name, char *extension){
    char log_name[] = LOG_FILE_BASENAME;
    log_name[0] = (char)FAT_FILENAME_DELETED_CHAR;
    return strncmp(base_name, log_name, 8) == 0 && strncmp(extension, LOG_FILE_EXTENSION, 3) == 0;     
}
