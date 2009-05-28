#!/bin/sh
#
# mysql_adduser.sh
# Sebastien Duquette - 2009
#
# This script outputs the commands needed to create a mysql user
# and a database of the same name with all access granted to that
# user.

if [ $# -ne 2 ]; then
	echo "usage: mysql_adduser <username> <password>";
	exit;
fi

cat << EOF
CREATE USER '$1'@'localhost' IDENTIFIED BY '$2';
CREATE USER '$1'@'%' IDENTIFIED BY '$2';
CREATE DATABASE $1;
GRANT ALL PRIVILEGES ON $1.* TO '$1'@'localhost' WITH GRANT OPTION;
GRANT ALL PRIVILEGES ON $1.* TO '$1'@'%' WITH GRANT OPTION;
EOF

