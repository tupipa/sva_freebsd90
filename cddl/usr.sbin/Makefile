# $FreeBSD: release/9.0.0/cddl/usr.sbin/Makefile 211842 2010-08-26 11:46:38Z rpaulo $

.include <bsd.own.mk>

SUBDIR=	${_dtrace} \
	${_dtruss} \
	${_lockstat} \
	${_zdb}

.if ${MK_ZFS} != "no"
.if ${MK_LIBTHR} != "no"
_zdb=	zdb
.endif
.endif

.if ${MACHINE_ARCH} == "amd64" || ${MACHINE_ARCH} == "i386"
_dtrace=	dtrace
_dtruss=	dtruss
_lockstat=	lockstat
.endif

.include <bsd.subdir.mk>
