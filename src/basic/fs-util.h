#pragma once

/***
  This file is part of systemd.

  Copyright 2010 Lennart Poettering

  systemd is free software; you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation; either version 2.1 of the License, or
  (at your option) any later version.

  systemd is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with systemd; If not, see <http://www.gnu.org/licenses/>.
***/

#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/inotify.h>
#include <sys/types.h>
#include <unistd.h>

#include "time-util.h"

int unlink_noerrno(const char *path);

#if 0 /// UNNEEDED by elogind
int rmdir_parents(const char *path, const char *stop);

int rename_noreplace(int olddirfd, const char *oldpath, int newdirfd, const char *newpath);
#endif // 0

int readlinkat_malloc(int fd, const char *p, char **ret);
int readlink_malloc(const char *p, char **r);
#if 0 /// UNNEEDED by elogind
int readlink_value(const char *p, char **ret);
int readlink_and_make_absolute(const char *p, char **r);
int readlink_and_canonicalize(const char *p, const char *root, char **r);
int readlink_and_make_absolute_root(const char *root, const char *path, char **ret);
#endif // 0

int chmod_and_chown(const char *path, mode_t mode, uid_t uid, gid_t gid);

int fchmod_umask(int fd, mode_t mode);

int fd_warn_permissions(const char *path, int fd);

#ifdef __GLIBC__
#define laccess(path, mode) faccessat(AT_FDCWD, (path), (mode), AT_SYMLINK_NOFOLLOW)
#else
#define laccess(path, mode) faccessat(AT_FDCWD, (path), (mode), 0)
#endif


int touch_file(const char *path, bool parents, usec_t stamp, uid_t uid, gid_t gid, mode_t mode);
int touch(const char *path);

#if 0 /// UNNEEDED by elogind
int symlink_idempotent(const char *from, const char *to);

int symlink_atomic(const char *from, const char *to);
int mknod_atomic(const char *path, mode_t mode, dev_t dev);
int mkfifo_atomic(const char *path, mode_t mode);
#endif // 0

int get_files_in_directory(const char *path, char ***list);

#if 0 /// UNNEEDED by elogind
int tmp_dir(const char **ret);
int var_tmp_dir(const char **ret);

#define INOTIFY_EVENT_MAX (sizeof(struct inotify_event) + NAME_MAX + 1)

#define FOREACH_INOTIFY_EVENT(e, buffer, sz) \
        for ((e) = &buffer.ev;                                \
             (uint8_t*) (e) < (uint8_t*) (buffer.raw) + (sz); \
             (e) = (struct inotify_event*) ((uint8_t*) (e) + sizeof(struct inotify_event) + (e)->len))

union inotify_event_buffer {
        struct inotify_event ev;
        uint8_t raw[INOTIFY_EVENT_MAX];
};

int inotify_add_watch_fd(int fd, int what, uint32_t mask);

#endif // 0
int chase_symlinks(const char *path_with_prefix, const char *root, char **ret);
int chase_symlinks_prefix(const char *path_without_prefix, const char *root, char **ret);
