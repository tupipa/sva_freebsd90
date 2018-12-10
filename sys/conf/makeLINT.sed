#!/usr/bin/sed -E -n -f
# $FreeBSD: release/9.0.0/sys/conf/makeLINT.sed 111582 2003-02-26 23:36:59Z ru $

/^(machine|ident|device|nodevice|makeoptions|nomakeoption|options|option|nooption|profile|cpu|maxusers)[[:space:]]/ {
    s/[[:space:]]*#.*$//
    p
}
