/* $Id: sysctl.h 7722 2014-01-03 13:06:28Z cher $ */
/* Copyright (C) 2004 Alexander Chernov */

/* This file is derived from `sys/sysctl.h' of the GNU C Library,
   version 2.3.2. The original copyright follows. */

/* Copyright (C) 1996, 1999, 2002 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#ifndef __RCC_SYS_SYSCTL_H__
#define __RCC_SYS_SYSCTL_H__ 1

#include <features.h>
#include <sys/types.h>

int enum { CTL_MAXNAME = 10 };
#define CTL_MAXNAME CTL_MAXNAME

struct __sysctl_args
{
  int *name;
  int nlen;
  void *oldval;
  size_t *oldlenp;
  void *newval;
  size_t newlen;
  unsigned long __unused[4];
};

int enum
{
  CTL_KERN = 1,
  CTL_VM = 2,
  CTL_NET = 3,
  CTL_PROC = 4,
  CTL_FS = 5,
  CTL_DEBUG = 6,
  CTL_DEV = 7,
  CTL_BUS = 8,
  CTL_ABI = 9
};

/* CTL_BUS names: */
int enum
{
  BUS_ISA=1
};

/* CTL_KERN names: */
int enum
{
  KERN_OSTYPE = 1,
  KERN_OSRELEASE = 2,
  KERN_OSREV = 3,
  KERN_VERSION = 4,
  KERN_SECUREMASK = 5,
  KERN_PROF = 6,
  KERN_NODENAME = 7,
  KERN_DOMAINNAME = 8,
  KERN_CAP_BSET = 14,
  KERN_PANIC = 15,
  KERN_REALROOTDEV = 16,
  KERN_SPARC_REBOOT = 21,
  KERN_CTLALTDEL = 22,
  KERN_PRINTK = 23,
  KERN_NAMETRANS = 24,
  KERN_PPC_HTABRECLAIM = 25,
  KERN_PPC_ZEROPAGED = 26,
  KERN_PPC_POWERSAVE_NAP = 27,
  KERN_MODPROBE = 28,
  KERN_SG_BIG_BUFF = 29,
  KERN_ACCT = 30,
  KERN_PPC_L2CR = 31,
  KERN_RTSIGNR = 32,
  KERN_RTSIGMAX = 33,
  KERN_SHMMAX = 34,
  KERN_MSGMAX = 35,
  KERN_MSGMNB = 36,
  KERN_MSGPOOL = 37,
  KERN_SYSRQ = 38,
  KERN_MAX_THREADS = 39,
  KERN_RANDOM = 40,
  KERN_SHMALL = 41,
  KERN_MSGMNI = 42,
  KERN_SEM = 43,
  KERN_SPARC_STOP_A = 44,
  KERN_SHMMNI = 45,
  KERN_OVERFLOWUID = 46,
  KERN_OVERFLOWGID = 47,
  KERN_SHMPATH = 48,
  KERN_HOTPLUG = 49,
  KERN_IEEE_EMULATION_WARNINGS = 50,
  KERN_S390_USER_DEBUG_LOGGING = 51,
  KERN_CORE_USES_PID = 52,
  KERN_PROF_PID = 53,
  KERN_CADPID = 54,
  KERN_TAINTED = 55,
};


/* CTL_VM names: */
int enum
{
  VM_SWAPCTL = 1,
  VM_SWAPOUT = 2,
  VM_FREEPG = 3,
  VM_BDFLUSH = 4,
  VM_OVERCOMMIT_MEMORY = 5,
  VM_BUFFERMEM = 6,
  VM_PAGECACHE = 7,
  VM_PAGERDAEMON = 8,
  VM_PGT_CACHE = 9,
  VM_PAGE_CLUSTER = 10,
  VM_MAX_MAP_COUNT = 11,
  VM_MIN_READAHEAD = 12,
  VM_MAX_READAHEAD = 13,
  VM_AGING_TACTIC = 14,
  VM_INACTIVE_TARGET = 15,
  VM_DROP_BEHIND = 16,
};

/* CTL_NET names: */
int enum
{
  NET_CORE = 1,
  NET_ETHER = 2,
  NET_802 = 3,
  NET_UNIX = 4,
  NET_IPV4 = 5,
  NET_IPX = 6,
  NET_ATALK = 7,
  NET_NETROM = 8,
  NET_AX25 = 9,
  NET_BRIDGE = 10,
  NET_ROSE = 11,
  NET_IPV6 = 12,
  NET_X25 = 13,
  NET_TR = 14,
  NET_DECNET = 15,
  NET_ECONET = 16,
  NET_KHTTPD = 17,
  NET_TUX = 18
};

/* /proc/sys/kernel/random */
int enum
{
  RANDOM_POOLSIZE = 1,
  RANDOM_ENTROPY_COUNT = 2,
  RANDOM_READ_THRESH = 3,
  RANDOM_WRITE_THRESH = 4,
  RANDOM_BOOT_ID = 5,
  RANDOM_UUID = 6
};

/* /proc/sys/bus/isa */
int enum
{
  BUS_ISA_MEM_BASE = 1,
  BUS_ISA_PORT_BASE = 2,
  BUS_ISA_PORT_SHIFT = 3
};

/* /proc/sys/net/core */
int enum
{
  NET_CORE_WMEM_MAX = 1,
  NET_CORE_RMEM_MAX = 2,
  NET_CORE_WMEM_DEFAULT = 3,
  NET_CORE_RMEM_DEFAULT = 4,
/* was  NET_CORE_DESTROY_DELAY */
  NET_CORE_MAX_BACKLOG = 6,
  NET_CORE_FASTROUTE = 7,
  NET_CORE_MSG_COST = 8,
  NET_CORE_MSG_BURST = 9,
  NET_CORE_OPTMEM_MAX = 10,
  NET_CORE_HOT_LIST_LENGTH = 11,
  NET_CORE_DIVERT_VERSION = 12,
  NET_CORE_NO_CONG_THRESH = 13,
  NET_CORE_NO_CONG = 14,
  NET_CORE_LO_CONG = 15,
  NET_CORE_MOD_CONG = 16
};

/* /proc/sys/net/ethernet */

/* /proc/sys/net/802 */

/* /proc/sys/net/unix */

int enum
{
  NET_UNIX_DESTROY_DELAY = 1,
  NET_UNIX_DELETE_DELAY = 2,
  NET_UNIX_MAX_DGRAM_QLEN = 3,
};

/* /proc/sys/net/ipv4 */
int enum
{
  /* v2.0 compatibile variables */
  NET_IPV4_FORWARD = 8,
  NET_IPV4_DYNADDR = 9,
  NET_IPV4_CONF = 16,
  NET_IPV4_NEIGH = 17,
  NET_IPV4_ROUTE = 18,
  NET_IPV4_FIB_HASH = 19,
  NET_IPV4_TCP_TIMESTAMPS = 33,
  NET_IPV4_TCP_WINDOW_SCALING = 34,
  NET_IPV4_TCP_SACK = 35,
  NET_IPV4_TCP_RETRANS_COLLAPSE = 36,
  NET_IPV4_DEFAULT_TTL = 37,
  NET_IPV4_AUTOCONFIG = 38,
  NET_IPV4_NO_PMTU_DISC = 39,
  NET_IPV4_TCP_SYN_RETRIES = 40,
  NET_IPV4_IPFRAG_HIGH_THRESH = 41,
  NET_IPV4_IPFRAG_LOW_THRESH = 42,
  NET_IPV4_IPFRAG_TIME = 43,
  NET_IPV4_TCP_MAX_KA_PROBES = 44,
  NET_IPV4_TCP_KEEPALIVE_TIME = 45,
  NET_IPV4_TCP_KEEPALIVE_PROBES = 46,
  NET_IPV4_TCP_RETRIES1 = 47,
  NET_IPV4_TCP_RETRIES2 = 48,
  NET_IPV4_TCP_FIN_TIMEOUT = 49,
  NET_IPV4_IP_MASQ_DEBUG = 50,
  NET_TCP_SYNCOOKIES = 51,
  NET_TCP_STDURG = 52,
  NET_TCP_RFC1337 = 53,
  NET_TCP_SYN_TAILDROP = 54,
  NET_TCP_MAX_SYN_BACKLOG = 55,
  NET_IPV4_LOCAL_PORT_RANGE = 56,
  NET_IPV4_ICMP_ECHO_IGNORE_ALL = 57,
  NET_IPV4_ICMP_ECHO_IGNORE_BROADCASTS = 58,
  NET_IPV4_ICMP_SOURCEQUENCH_RATE = 59,
  NET_IPV4_ICMP_DESTUNREACH_RATE = 60,
  NET_IPV4_ICMP_TIMEEXCEED_RATE = 61,
  NET_IPV4_ICMP_PARAMPROB_RATE = 62,
  NET_IPV4_ICMP_ECHOREPLY_RATE = 63,
  NET_IPV4_ICMP_IGNORE_BOGUS_ERROR_RESPONSES = 64,
  NET_IPV4_IGMP_MAX_MEMBERSHIPS = 65,
  NET_TCP_TW_RECYCLE = 66,
  NET_IPV4_ALWAYS_DEFRAG = 67,
  NET_IPV4_TCP_KEEPALIVE_INTVL = 68,
  NET_IPV4_INET_PEER_THRESHOLD = 69,
  NET_IPV4_INET_PEER_MINTTL = 70,
  NET_IPV4_INET_PEER_MAXTTL = 71,
  NET_IPV4_INET_PEER_GC_MINTIME = 72,
  NET_IPV4_INET_PEER_GC_MAXTIME = 73,
  NET_TCP_ORPHAN_RETRIES = 74,
  NET_TCP_ABORT_ON_OVERFLOW = 75,
  NET_TCP_SYNACK_RETRIES = 76,
  NET_TCP_MAX_ORPHANS = 77,
  NET_TCP_MAX_TW_BUCKETS = 78,
  NET_TCP_FACK = 79,
  NET_TCP_REORDERING = 80,
  NET_TCP_ECN = 81,
  NET_TCP_DSACK = 82,
  NET_TCP_MEM = 83,
  NET_TCP_WMEM = 84,
  NET_TCP_RMEM = 85,
  NET_TCP_APP_WIN = 86,
  NET_TCP_ADV_WIN_SCALE = 87,
  NET_IPV4_NONLOCAL_BIND = 88,
  NET_IPV4_ICMP_RATELIMIT = 89,
  NET_IPV4_ICMP_RATEMASK = 90
};

int enum {
  NET_IPV4_ROUTE_FLUSH = 1,
  NET_IPV4_ROUTE_MIN_DELAY = 2,
  NET_IPV4_ROUTE_MAX_DELAY = 3,
  NET_IPV4_ROUTE_GC_THRESH = 4,
  NET_IPV4_ROUTE_MAX_SIZE = 5,
  NET_IPV4_ROUTE_GC_MIN_INTERVAL = 6,
  NET_IPV4_ROUTE_GC_TIMEOUT = 7,
  NET_IPV4_ROUTE_GC_INTERVAL = 8,
  NET_IPV4_ROUTE_REDIRECT_LOAD = 9,
  NET_IPV4_ROUTE_REDIRECT_NUMBER = 10,
  NET_IPV4_ROUTE_REDIRECT_SILENCE = 11,
  NET_IPV4_ROUTE_ERROR_COST = 12,
  NET_IPV4_ROUTE_ERROR_BURST = 13,
  NET_IPV4_ROUTE_GC_ELASTICITY = 14,
  NET_IPV4_ROUTE_MTU_EXPIRES = 15,
  NET_IPV4_ROUTE_MIN_PMTU = 16,
  NET_IPV4_ROUTE_MIN_ADVMSS = 17
};

int enum
{
  NET_PROTO_CONF_ALL = -2,
  NET_PROTO_CONF_DEFAULT = -3

  /* And device ifindices ... */
};

int enum
{
  NET_IPV4_CONF_FORWARDING = 1,
  NET_IPV4_CONF_MC_FORWARDING = 2,
  NET_IPV4_CONF_PROXY_ARP = 3,
  NET_IPV4_CONF_ACCEPT_REDIRECTS = 4,
  NET_IPV4_CONF_SECURE_REDIRECTS = 5,
  NET_IPV4_CONF_SEND_REDIRECTS = 6,
  NET_IPV4_CONF_SHARED_MEDIA = 7,
  NET_IPV4_CONF_RP_FILTER = 8,
  NET_IPV4_CONF_ACCEPT_SOURCE_ROUTE = 9,
  NET_IPV4_CONF_BOOTP_RELAY = 10,
  NET_IPV4_CONF_LOG_MARTIANS = 11,
  NET_IPV4_CONF_TAG = 12,
  NET_IPV4_CONF_ARPFILTER = 13
};

/* /proc/sys/net/ipv6 */
int enum
{
  NET_IPV6_CONF = 16,
  NET_IPV6_NEIGH = 17,
  NET_IPV6_ROUTE = 18
};

int enum
{
  NET_IPV6_ROUTE_FLUSH = 1,
  NET_IPV6_ROUTE_GC_THRESH = 2,
  NET_IPV6_ROUTE_MAX_SIZE = 3,
  NET_IPV6_ROUTE_GC_MIN_INTERVAL = 4,
  NET_IPV6_ROUTE_GC_TIMEOUT = 5,
  NET_IPV6_ROUTE_GC_INTERVAL = 6,
  NET_IPV6_ROUTE_GC_ELASTICITY = 7,
  NET_IPV6_ROUTE_MTU_EXPIRES = 8,
  NET_IPV6_ROUTE_MIN_ADVMSS = 9
};

int enum
{
  NET_IPV6_FORWARDING = 1,
  NET_IPV6_HOP_LIMIT = 2,
  NET_IPV6_MTU = 3,
  NET_IPV6_ACCEPT_RA = 4,
  NET_IPV6_ACCEPT_REDIRECTS = 5,
  NET_IPV6_AUTOCONF = 6,
  NET_IPV6_DAD_TRANSMITS = 7,
  NET_IPV6_RTR_SOLICITS = 8,
  NET_IPV6_RTR_SOLICIT_INTERVAL = 9,
  NET_IPV6_RTR_SOLICIT_DELAY = 10
};

/* /proc/sys/net/<protocol>/neigh/<dev> */
int enum
{
  NET_NEIGH_MCAST_SOLICIT = 1,
  NET_NEIGH_UCAST_SOLICIT = 2,
  NET_NEIGH_APP_SOLICIT = 3,
  NET_NEIGH_RETRANS_TIME = 4,
  NET_NEIGH_REACHABLE_TIME = 5,
  NET_NEIGH_DELAY_PROBE_TIME = 6,
  NET_NEIGH_GC_STALE_TIME = 7,
  NET_NEIGH_UNRES_QLEN = 8,
  NET_NEIGH_PROXY_QLEN = 9,
  NET_NEIGH_ANYCAST_DELAY = 10,
  NET_NEIGH_PROXY_DELAY = 11,
  NET_NEIGH_LOCKTIME = 12,
  NET_NEIGH_GC_INTERVAL = 13,
  NET_NEIGH_GC_THRESH1 = 14,
  NET_NEIGH_GC_THRESH2 = 15,
  NET_NEIGH_GC_THRESH3 = 16
};

/* /proc/sys/net/ipx */
int enum
{
  NET_IPX_PPROP_BROADCASTING = 1,
  NET_IPX_FORWARDING = 2
};


/* /proc/sys/net/appletalk */
int enum
{
  NET_ATALK_AARP_EXPIRY_TIME = 1,
  NET_ATALK_AARP_TICK_TIME = 2,
  NET_ATALK_AARP_RETRANSMIT_LIMIT = 3,
  NET_ATALK_AARP_RESOLVE_TIME = 4
};


/* /proc/sys/net/netrom */
int enum
{
  NET_NETROM_DEFAULT_PATH_QUALITY = 1,
  NET_NETROM_OBSOLESCENCE_COUNT_INITIALISER = 2,
  NET_NETROM_NETWORK_TTL_INITIALISER = 3,
  NET_NETROM_TRANSPORT_TIMEOUT = 4,
  NET_NETROM_TRANSPORT_MAXIMUM_TRIES = 5,
  NET_NETROM_TRANSPORT_ACKNOWLEDGE_DELAY = 6,
  NET_NETROM_TRANSPORT_BUSY_DELAY = 7,
  NET_NETROM_TRANSPORT_REQUESTED_WINDOW_SIZE = 8,
  NET_NETROM_TRANSPORT_NO_ACTIVITY_TIMEOUT = 9,
  NET_NETROM_ROUTING_CONTROL = 10,
  NET_NETROM_LINK_FAILS_COUNT = 11
};

/* /proc/sys/net/ax25 */
int enum
{
  NET_AX25_IP_DEFAULT_MODE = 1,
  NET_AX25_DEFAULT_MODE = 2,
  NET_AX25_BACKOFF_TYPE = 3,
  NET_AX25_CONNECT_MODE = 4,
  NET_AX25_STANDARD_WINDOW = 5,
  NET_AX25_EXTENDED_WINDOW = 6,
  NET_AX25_T1_TIMEOUT = 7,
  NET_AX25_T2_TIMEOUT = 8,
  NET_AX25_T3_TIMEOUT = 9,
  NET_AX25_IDLE_TIMEOUT = 10,
  NET_AX25_N2 = 11,
  NET_AX25_PACLEN = 12,
  NET_AX25_PROTOCOL = 13,
  NET_AX25_DAMA_SLAVE_TIMEOUT = 14
};

/* /proc/sys/net/rose */
int enum
{
  NET_ROSE_RESTART_REQUEST_TIMEOUT = 1,
  NET_ROSE_CALL_REQUEST_TIMEOUT = 2,
  NET_ROSE_RESET_REQUEST_TIMEOUT = 3,
  NET_ROSE_CLEAR_REQUEST_TIMEOUT = 4,
  NET_ROSE_ACK_HOLD_BACK_TIMEOUT = 5,
  NET_ROSE_ROUTING_CONTROL = 6,
  NET_ROSE_LINK_FAIL_TIMEOUT = 7,
  NET_ROSE_MAX_VCS = 8,
  NET_ROSE_WINDOW_SIZE = 9,
  NET_ROSE_NO_ACTIVITY_TIMEOUT = 10
};

/* /proc/sys/net/x25 */
int enum
{
  NET_X25_RESTART_REQUEST_TIMEOUT = 1,
  NET_X25_CALL_REQUEST_TIMEOUT = 2,
  NET_X25_RESET_REQUEST_TIMEOUT = 3,
  NET_X25_CLEAR_REQUEST_TIMEOUT = 4,
  NET_X25_ACK_HOLD_BACK_TIMEOUT = 5
};

/* /proc/sys/net/token-ring */
int enum
{
  NET_TR_RIF_TIMEOUT = 1
};

/* /proc/sys/net/decnet/ */
int enum
{
  NET_DECNET_NODE_TYPE = 1,
  NET_DECNET_NODE_ADDRESS = 2,
  NET_DECNET_NODE_NAME = 3,
  NET_DECNET_DEFAULT_DEVICE = 4,
  NET_DECNET_TIME_WAIT = 5,
  NET_DECNET_DN_COUNT = 6,
  NET_DECNET_DI_COUNT = 7,
  NET_DECNET_DR_COUNT = 8,
  NET_DECNET_DST_GC_INTERVAL = 9,
  NET_DECNET_CONF = 10,
  NET_DECNET_NO_FC_MAX_CWND = 11,
  NET_DECNET_DEBUG_LEVEL = 255
};

/* /proc/sys/net/tux/ */
int enum
{
  NET_TUX_DOCROOT =  1,
  NET_TUX_LOGFILE =  2,
  NET_TUX_EXTCGI =  3,
  NET_TUX_STOP =  4,
  NET_TUX_CLIENTPORT =  5,
  NET_TUX_LOGGING =  6,
  NET_TUX_SERVERPORT =  7,
  NET_TUX_THREADS =  8,
  NET_TUX_KEEPALIVE_TIMEOUT =  9,
  NET_TUX_MAX_KEEPALIVE_BW = 10,
  NET_TUX_DEFER_ACCEPT = 11,
  NET_TUX_MAX_FREE_REQUESTS = 12,
  NET_TUX_MAX_CONNECT = 13,
  NET_TUX_MAX_BACKLOG = 14,
  NET_TUX_MODE_FORBIDDEN = 15,
  NET_TUX_MODE_ALLOWED = 16,
  NET_TUX_MODE_USERSPACE = 17,
  NET_TUX_MODE_CGI = 18,
  NET_TUX_CGI_UID = 19,
  NET_TUX_CGI_GID = 20,
  NET_TUX_CGIROOT = 21,
  NET_TUX_LOGENTRY_ALIGN_ORDER = 22,
  NET_TUX_NONAGLE = 23,
  NET_TUX_ACK_PINGPONG = 24,
  NET_TUX_PUSH_ALL = 25,
  NET_TUX_ZEROCOPY_PARSE = 26,
  NET_CONFIG_TUX_DEBUG_BLOCKING = 27,
  NET_TUX_PAGE_AGE_START = 28,
  NET_TUX_PAGE_AGE_ADV = 29,
  NET_TUX_PAGE_AGE_MAX = 30,
  NET_TUX_VIRTUAL_SERVER = 31,
  NET_TUX_MAX_OBJECT_SIZE = 32,
  NET_TUX_COMPRESSION = 33,
  NET_TUX_NOID = 34,
  NET_TUX_CGI_INHERIT_CPU = 35,
  NET_TUX_CGI_CPU_MASK = 36,
  NET_TUX_ZEROCOPY_HEADER = 37,
  NET_TUX_ZEROCOPY_SENDFILE = 38,
  NET_TUX_ALL_USERSPACE = 39,
  NET_TUX_REDIRECT_LOGGING = 40,
  NET_TUX_REFERER_LOGGING = 41,
  NET_TUX_MAX_HEADER_LEN = 42,
  NET_TUX_404_PAGE = 43,
  NET_TUX_APPLICATION_PROTOCOL = 44,
  NET_TUX_MAX_KEEPALIVES = 45,
};

/* /proc/sys/net/khttpd/ */
int enum
{
  NET_KHTTPD_DOCROOT = 1,
  NET_KHTTPD_START = 2,
  NET_KHTTPD_STOP = 3,
  NET_KHTTPD_UNLOAD = 4,
  NET_KHTTPD_CLIENTPORT = 5,
  NET_KHTTPD_PERMREQ = 6,
  NET_KHTTPD_PERMFORBID = 7,
  NET_KHTTPD_LOGGING = 8,
  NET_KHTTPD_SERVERPORT = 9,
  NET_KHTTPD_DYNAMICSTRING = 10,
  NET_KHTTPD_SLOPPYMIME = 11,
  NET_KHTTPD_THREADS = 12,
  NET_KHTTPD_MAXCONNECT = 13
};

/* /proc/sys/net/decnet/conf/<dev> */
int enum
{
  NET_DECNET_CONF_LOOPBACK = -2,
  NET_DECNET_CONF_DDCMP = -3,
  NET_DECNET_CONF_PPP = -4,
  NET_DECNET_CONF_X25 = -5,
  NET_DECNET_CONF_GRE = -6,
  NET_DECNET_CONF_ETHER = -7

  /* ... and ifindex of devices */
};

/* /proc/sys/net/decnet/conf/<dev>/ */
int enum
{
  NET_DECNET_CONF_DEV_PRIORITY = 1,
  NET_DECNET_CONF_DEV_T1 = 2,
  NET_DECNET_CONF_DEV_T2 = 3,
  NET_DECNET_CONF_DEV_T3 = 4,
  NET_DECNET_CONF_DEV_FORWARDING = 5,
  NET_DECNET_CONF_DEV_BLKSIZE = 6,
  NET_DECNET_CONF_DEV_STATE = 7
};

/* CTL_PROC names: */

/* CTL_FS names: */
int enum
{
  FS_NRINODE = 1,
  FS_STATINODE = 2,
  FS_MAXINODE = 3,
  FS_NRDQUOT = 4,
  FS_MAXDQUOT = 5,
  FS_NRFILE = 6,
  FS_MAXFILE = 7,
  FS_DENTRY = 8,
  FS_NRSUPER = 9,
  FS_MAXSUPER = 10,
  FS_OVERFLOWUID = 11,
  FS_OVERFLOWGID = 12,
  FS_LEASES = 13,
  FS_DIR_NOTIFY = 14,
  FS_LEASE_TIME = 15,
};

/* CTL_DEBUG names: */

/* CTL_DEV names: */
int enum
{
  DEV_CDROM = 1,
  DEV_HWMON = 2,
  DEV_PARPORT = 3,
  DEV_RAID = 4,
  DEV_MAC_HID = 5
};

/* /proc/sys/dev/cdrom */
int enum
{
  DEV_CDROM_INFO = 1,
  DEV_CDROM_AUTOCLOSE = 2,
  DEV_CDROM_AUTOEJECT = 3,
  DEV_CDROM_DEBUG = 4,
  DEV_CDROM_LOCK = 5,
  DEV_CDROM_CHECK_MEDIA = 6
};

/* /proc/sys/dev/parport */
int enum
{
  DEV_PARPORT_DEFAULT = -3
};

/* /proc/sys/dev/raid */
int enum
{
  DEV_RAID_SPEED_LIMIT_MIN = 1,
  DEV_RAID_SPEED_LIMIT_MAX = 2
};

/* /proc/sys/dev/parport/default */
int enum
{
  DEV_PARPORT_DEFAULT_TIMESLICE = 1,
  DEV_PARPORT_DEFAULT_SPINTIME = 2
};

/* /proc/sys/dev/parport/parport n */
int enum
{
  DEV_PARPORT_SPINTIME = 1,
  DEV_PARPORT_BASE_ADDR = 2,
  DEV_PARPORT_IRQ = 3,
  DEV_PARPORT_DMA = 4,
  DEV_PARPORT_MODES = 5,
  DEV_PARPORT_DEVICES = 6,
  DEV_PARPORT_AUTOPROBE = 16
};

/* /proc/sys/dev/parport/parport n/devices/ */
int enum
{
  DEV_PARPORT_DEVICES_ACTIVE = -3,
};

/* /proc/sys/dev/parport/parport n/devices/device n */
int enum
{
  DEV_PARPORT_DEVICE_TIMESLICE = 1,
};

/* /proc/sys/dev/mac_hid */
int enum
{
  DEV_MAC_HID_KEYBOARD_SENDS_LINUX_KEYCODES = 1,
  DEV_MAC_HID_KEYBOARD_LOCK_KEYCODES = 2,
  DEV_MAC_HID_MOUSE_BUTTON_EMULATION = 3,
  DEV_MAC_HID_MOUSE_BUTTON2_KEYCODE = 4,
  DEV_MAC_HID_MOUSE_BUTTON3_KEYCODE = 5,
  DEV_MAC_HID_ADB_MOUSE_SENDS_KEYCODES = 6
};

/* /proc/sys/abi */
int enum
{
  ABI_DEFHANDLER_COFF = 1,
  ABI_DEFHANDLER_ELF = 2,
  ABI_DEFHANDLER_LCALL7 = 3,
  ABI_DEFHANDLER_LIBCSO = 4,
  ABI_TRACE = 5,
  ABI_FAKE_UTSNAME = 6,
};

/* Read or write system parameters.  */
int sysctl(int *name, int nlen, void *oldval,
           size_t *oldlenp, void *newval, size_t newlen);

#endif  /* __RCC_SYS_SYSCTL_H__ */