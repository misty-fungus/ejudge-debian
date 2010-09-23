#!/bin/sh
### BEGIN INIT INFO
# Provides:          ejudge
# Required-Start:    $network $local_fs $remote_fs
# Required-Stop:     $remote_fs $local_fs
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: ejudge contest management service
# Description:       this script provides ejudge contest management service 
#                    <...>
#                    <...>
### END INIT INFO

# Author: Yaroslav Leonov <alximik43@gmail.com>

# PATH should only include /usr
PATH=/sbin:/usr/sbin:/bin:/usr/bin
DESC=ejudge             # Introduce a short description here
NAME=ejudge             # Introduce the short server's name here
DAEMON=/usr/sbin/ejudge-control # Introduce the server's location here
DAEMON_ARGS=""             # Arguments to run the daemon with
PIDFILE=/var/run/$NAME.pid
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

#
# Function that starts the daemon/service
#
do_start()
{
	# Return
	#   0 if daemon has been started
	#   1 if daemon was already running
	#   2 if daemon could not be started
	#start-stop-daemon --start --quiet --pidfile $PIDFILE --exec $DAEMON --test > /dev/null \
	#	|| return 1
	#start-stop-daemon --start --quiet --pidfile $PIDFILE --exec $DAEMON -- \
  #		$DAEMON_ARGS \
	#	|| return 2
	# Add code here, if necessary, that waits for the process to be ready
	# to handle requests from services started subsequently which depend
	# on this one.  As a last resort, sleep for some time.

  $DAEMON $DAEMON_OPTS start
  return $?
}

#
# Function that stops the daemon/service
#
do_stop()
{
	# Return
	#   0 if daemon has been stopped
	#   1 if daemon was already stopped
	#   2 if daemon could not be stopped
	#   other if a failure occurred
  $DAEMON $DAEMON_OPTS stop
  return $?

	#start-stop-daemon --stop --quiet --retry=TERM/30/KILL/5 --pidfile $PIDFILE --name $NAME
	#RETVAL="$?"
	#[ "$RETVAL" = 2 ] && return 2
	# Wait for children to finish too if this is a daemon that forks
	# and if the daemon is only ever run from this initscript.
	# If the above conditions are not satisfied then add some other code
	# that waits for the process to drop all resources that could be
	# needed by services started subsequently.  A last resort is to
	# sleep for some time.
	#start-stop-daemon --stop --quiet --oknodo --retry=0/30/KILL/5 --exec $DAEMON
	#[ "$?" = 2 ] && return 2
	# Many daemons don't delete their pidfiles when they exit.
	#rm -f $PIDFILE
	#return "$RETVAL"
}

#
# Function that sends a SIGHUP to the daemon/service
#
do_reload() {
  $DAEMON $DAEMON_OPTS restart
  return $?


	#
	# If the daemon can reload its configuration without
	# restarting (for example, when it is sent a SIGHUP),
	# then implement that here.
	#
	#start-stop-daemon --stop --signal 1 --quiet --pidfile $PIDFILE --name $NAME
	#return 0
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
  #status)
  #     status_of_proc "$DAEMON" "$NAME" && exit 0 || exit $?
  #     ;;
  #reload|force-reload)
	#
	# If do_reload() is not implemented then leave this commented out
	# and leave 'force-reload' as an alias for 'restart'.
	#
	#log_daemon_msg "Reloading $DESC" "$NAME"
	#do_reload
	#log_end_msg $?
	#;;
  restart)
	#
	# If the "reload" option is implemented then remove the
	# 'force-reload' alias
	#
	log_daemon_msg "Restarting $DESC" "$NAME"
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
	  *)
	  	# Failed to stop
		log_end_msg 1
		;;
	esac
	;;
  *)
	#echo "Usage: $SCRIPTNAME {start|stop|restart|reload|force-reload}" >&2
	echo "Usage: $SCRIPTNAME {start|stop|restart}" >&2
	exit 3
	;;
esac


