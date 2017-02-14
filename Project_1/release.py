import argparse
import sys
import subprocess

parser = argparse.ArgumentParser()

parser.add_argument('-s', action="store_true")
parser.add_argument('-b', action="store_true")

args = parser.parse_args()

no_arg = args.s or args.b

if no_arg == False:
    print ("NO VALUE")
    sys.exit(0)

if args.s == True:
    user_in = raw_input('Create a source release (Y/N):') 
    if user_in == "Y":
        subprocess.call(['make', 'clean'])
if args.b == True:
    user_in = raw_input('Create a binary release (Y/N):') 
    print (user_in)
