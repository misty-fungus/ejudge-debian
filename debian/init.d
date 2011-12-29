#!/bin/sh
### BEGIN INIT INFO
# Provides:          ejudge
# Required-Start:    $network $local_fs $remote_fs
# Required-Stop:     $remote_fs $local_fs
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: ejudge contest management service
### END INIT INFO

# Author: Yaroslav Leonov <alximik43@gmail.com>

# PATH should only include /usr
PATH=/sbin:/usr/sbin:/bin:/usr/bin
DESC="programming contest managment system"
NAME=ejudge
DAEMON=/usr/sbin/ejudge-control
DAEMON_OPTS=""
SCRIPTNAME=/etc/init.d/$NAME

# Exit if the package is not installed
[ -x $DAEMON ] || exit 0

# Read configuration variable file if it is present
[ -r /etc/default/$NAME ] && . /etc/default/$NAME

# Load the VERBOSE setting and other rcS variables
. /lib/init/vars.sh

# Define LSB log_* functions.
# Depend on lsb-base (>= 3.0-6) to ensure that this file is present.
. /lib/lsb/init-functions

do_start()
{
  umask $UMASK
  $DAEMON $DAEMON_OPTS start
  return $?
}

do_stop()
{
  umask $UMASK
  $DAEMON $DAEMON_OPTS stop
  return $?
}

case "$1" in
  start)
    [ "$VERBOSE" != no ] && log_daemon_msg "Starting $DESC " "$NAME"
    do_start
    RETVAL=$?
    case "$RETVAL" in
    0|1)
      [ "$VERBOSE" != no ] && log_end_msg 0
      exit $RETVAL
    ;;
    2)
      [ "$VERBOSE" != no ] && log_end_msg 1
      exit $RETVAL
    ;;
  	esac
  ;;
  stop)
    [ "$VERBOSE" != no ] && log_daemon_msg "Stopping $DESC" "$NAME"
    do_stop
    RETVAL=$?
    case "$RETVAL" in
    0|1)
      [ "$VERBOSE" != no ] && log_end_msg 0
      exit $RETVAL
    ;;
    2)
      [ "$VERBOSE" != no ] && log_end_msg 1
      exit $RETVAL
    ;;
    esac
  ;;
  restart|reload|force-reload)
    log_daemon_msg "Restarting $DESC" "$NAME"
    do_stop
    RETVAL=$?
    case "$RETVAL" in
    0|1)
      do_start
      RETVAL=$?
      case "$RETVAL" in
      0|1)
        [ "$VERBOSE" != no ] && log_end_msg 0
        exit $RETVAL
      ;;
      2)
        [ "$VERBOSE" != no ] && log_end_msg 1
        exit $RETVAL
      ;;
      esac

      exit $RETVAL
    ;;
    2)
      [ "$VERBOSE" != no ] && log_end_msg 1
      exit $RETVAL
    ;;
    esac
  ;;
  *)
    echo "Usage: $SCRIPTNAME {start|stop|restart|reload|force-reload}" >&2
    exit 3
  ;;
esac


