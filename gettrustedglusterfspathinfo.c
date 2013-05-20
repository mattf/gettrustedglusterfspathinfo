/*
 * Allow retrieval of ONLY the trusted.glusterfs.pathinfo extended
 * attribute on a file.
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <attr/xattr.h>

#define PATHINFO "trusted.glusterfs.pathinfo"

int
main(int argc, char *argv[])
{
   char *filename = NULL;
   char *value = NULL;
   ssize_t size0, size1;

   if (argc < 2) {
      fprintf(stderr, "%s: no filename provided\n", argv[0]);
      return 1;
   }

   filename = argv[1];

   do {
      size0 = size1 = 0;
      if (value) { free(value); value = NULL; }

      if (-1 == (size0 = getxattr(filename, PATHINFO, NULL, 0))) {
         perror("getxattr");
         return 10;
      }

      // The getxattr man page does not state if size0 will
      // include a terminating null. For safety we'll just
      // increment the buffer size by 1.
      value = calloc(sizeof(char), size0 + 1);
      if (!value) {
         perror("calloc");
         return 20;
      }

      if (-1 == (size1 = getxattr(filename, PATHINFO, value, size0))) {
         perror("getxattr");
         return 11;
      }
   } while (size0 != size1);

   printf(PATHINFO "=\"%s\"\n", value);

   free(value); value = NULL;

   return 0;
}
