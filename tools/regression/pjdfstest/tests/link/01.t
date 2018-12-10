#!/bin/sh
# $FreeBSD: release/9.0.0/tools/regression/pjdfstest/tests/link/01.t 211474 2010-08-18 22:06:43Z pjd $

desc="link returns ENOTDIR if a component of either path prefix is not a directory"

dir=`dirname $0`
. ${dir}/../misc.sh

echo "1..32"

n0=`namegen`
n1=`namegen`
n2=`namegen`

expect 0 mkdir ${n0} 0755
for type in regular fifo block char socket; do
	create_file ${type} ${n0}/${n1}
	expect ENOTDIR link ${n0}/${n1}/test ${n0}/${n2}
	create_file ${type} ${n0}/${n2}
	expect ENOTDIR link ${n0}/${n2} ${n0}/${n1}/test
	expect 0 unlink ${n0}/${n1}
	expect 0 unlink ${n0}/${n2}
done
expect 0 rmdir ${n0}
