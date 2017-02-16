import argparse
import sys
import socket
import subprocess

parser = argparse.ArgumentParser()

parser.add_argument('-s', action="store_true", help ='create a source release')
parser.add_argument('-b', action="store_true", help='create a binary release')

args = parser.parse_args()

no_arg = args.s or args.b

if no_arg == False:
    print ("There was no valid argument")
    sys.exit(0)

host = socket.gethostname()

if host == "absaroka":
    make = 'gmake'
else:
    make = 'make';

if args.s == True:
    user_in = raw_input('Create a source release (Y/N):') 
    if user_in == "Y":
        subprocess.call([make,'clean'])
        subprocess.call(['tar','cvf','homework1.tar','bin','include','lib','src'])

if args.b == True:
    user_in = raw_input('Create a binary release (Y/N):') 
    if user_in == "Y":
        user_in = raw_input('Enter hostname (default=',host,')')
        if user_in:
            host = user_in
        print(host)
