/*-
 * Copyright (c) 2009 Ulf Lilleengen
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: release/9.0.0/lib/libutil/kinfo_getproc.c 221807 2011-05-12 10:11:39Z stas $
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: release/9.0.0/lib/libutil/kinfo_getproc.c 221807 2011-05-12 10:11:39Z stas $");

#include <sys/param.h>
#include <sys/user.h>
#include <sys/sysctl.h>
#include <stdlib.h>
#include <string.h>

#include "libutil.h"

struct kinfo_proc *
kinfo_getproc(pid_t pid)
{
	struct kinfo_proc *kipp;
	int mib[4];
	size_t len;

	len = 0;
	mib[0] = CTL_KERN;
	mib[1] = KERN_PROC;
	mib[2] = KERN_PROC_PID;
	mib[3] = pid;
	if (sysctl(mib, 4, NULL, &len, NULL, 0) < 0)
		return (NULL);

	kipp = malloc(len);
	if (kipp == NULL)
		return (NULL);

	if (sysctl(mib, 4, kipp, &len, NULL, 0) < 0)
		goto bad;
	if (len != sizeof(*kipp))
		goto bad;
	if (kipp->ki_structsize != sizeof(*kipp))
		goto bad;
	if (kipp->ki_pid != pid)
		goto bad;
	return (kipp);
bad:
	free(kipp);
	return (NULL);
}
