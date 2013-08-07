/*
 * This program allows retrieval of ONLY the trusted.glusterfs.pathinfo
 * extended attribute on a file. It is intended to be setuid root.
 *
 * Copyright (C) 2013 Matthew Farrellee
 *
 * With thanks to -
 *  . Josh Bressers for his keen security eye.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
