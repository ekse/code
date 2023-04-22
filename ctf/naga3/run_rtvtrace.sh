rm pid
echo Waiting for pid...
while test ! -f pid; do true; done
python rtvtrace.py $(cat pid)
