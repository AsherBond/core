#
#  Copyright 2021 Northern.tech AS
#
#  This file is part of CFEngine 3 - written and maintained by Northern.tech AS.
#
#  This program is free software; you can redistribute it and/or modify it
#  under the terms of the GNU General Public License as published by the
#  Free Software Foundation; version 3.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA
#
# To the extent this program is licensed as part of the Enterprise
# versions of CFEngine, the applicable Commercial Open Source License
# (COSL) may apply to this file if you as a licensee so wish it. See
# included file COSL.txt.
#
#
# OS kernels conditionals. Don't use those unless it is really needed (if code
# depends on the *kernel* feature, and even then -- some kernel features are
# shared by different kernels).
#
# Good example: use LINUX to select code which uses inotify and netlink sockets.
# Bad example: use LINUX to select code which parses output of coreutils' ps(1).
#
AM_CONDITIONAL([LINUX], [echo ${target_os} | grep -q linux])
AM_CONDITIONAL([MACOSX], [echo ${target_os} | grep -q darwin])
AM_CONDITIONAL([SOLARIS], [echo ${target_os} | grep -qE 'solaris|sunos'])
AM_CONDITIONAL([NT], [echo ${target_os} | grep -qE 'mingw|cygwin'])
AM_CONDITIONAL([CYGWIN], [echo ${target_os} | grep -qE 'cygwin'])
AM_CONDITIONAL([AIX], [echo ${target_os} | grep -q aix])
AM_CONDITIONAL([HPUX], [echo ${target_os} | grep -qE 'hpux|hp-ux'])
AM_CONDITIONAL([FREEBSD], [echo ${target_os} | grep -q freebsd])
AM_CONDITIONAL([NETBSD], [echo ${target_os} | grep -q netbsd])
AM_CONDITIONAL([XNU], [echo ${target_os} | grep -q darwin])
