journald-logger
---------------

Re-implementation of the logger utility that enters messages directly to
journald. For those who want to log to systemd-journal from a shell script.


Usage
-----
The message that should be send to systemd-journal must be the first argument.
All other arguments are in the form of key value pairs that are delimited by
'='. The key must be in uppercase and consist only characters, numbers and
underscores.

$ journald-logger "Hello, world!"
$ journald-logger "Message by with changed identifier" SYSLOG_IDENTIFIER="foo"
