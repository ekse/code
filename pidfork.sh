if [ $# -lt 1 ]; then
	echo -n "usage: $0 <command>";
	exit
fi
$*&
echo $!
exit
