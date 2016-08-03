#!/usr/bin/env python3

import time
import sys
import socket
from threading import Thread, Event
from collections import deque

MAX_THREADS = 10
DEBUG = False
output_filename = "resolved.txt"
    
class ThreadManager:
    def __init__(self,max_threads=MAX_THREADS):
       self.max_threads = max_threads
       self.current_threads = 0
       self.threads = deque()
       self.running_threads = list()
       self.event = Event()
       pass
        
    def add_thread(self, task):
        task.daemon = True
        self.threads.append(task)
        
    def start(self):
        while len(self.threads) > 0:
            if self.current_threads >= MAX_THREADS:
                # we have reached the maximum number of threads running, we need to wait for a thread to finish.
                if DEBUG: print("waiting for a thread to finish")
                self.event.wait()
                self.current_threads -= 1
                self.event.clear()

            thread = self.threads.popleft()
            thread.start()
            self.running_threads.append(thread)
            self.current_threads += 1
        
        for thread in self.running_threads:
            thread.join()
            
                   
class ResolverThread(Thread):
    def __init__(self, domain,event):
        Thread.__init__(self)
        self.domain = domain
        self.event = event
        
    def run(self):
            if DEBUG: print("Resolving %s" % self.domain)
            try:
                ip = socket.gethostbyname(self.domain)
                print(self.domain + "," + ip)
                fout.write(self.domain + "," + ip + "\n")
            except (socket.timeout, socket.gaierror):
                print(self.domain + " NORESOLV")
                fout.write(self.domain + ",NORESOLV\n")
            self.event.set()

        
if __name__ == '__main__':

    if len(sys.argv) == 3:
        output_filename = sys.argv[2]

    f = open(sys.argv[1], 'r')
    fout = open(output_filename,'w')

    socket.setdefaulttimeout(2)
    manager = ThreadManager()

    for line in f:
        hostname = line.strip()
        manager.add_thread(ResolverThread(hostname,manager.event))
        
    manager.start()
    fout.close()
    f.close()
