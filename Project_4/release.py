#
# Project:    Homework 4
# Programmer: Edwin Flores
# Course:     EN.605.414.81
# Purpose:    Python script that creates either a binary or source release
#
import argparse
import sys
import socket
import subprocess
import platform
import shutil

parser = argparse.ArgumentParser()

parser.add_argument('-s', action="store_true", help ='create a source release')
parser.add_argument('-b', action="store_true", help='create a binary release')

args = parser.parse_args()

no_arg = args.s or args.b

if no_arg == False:
    print ("There was no valid argument")
    sys.exit(0)

platform = platform.platform()
hw = 'homework4'

# Perform a clean and create a tar file with all files and the directory structure

if args.s == True:
    user_in = raw_input('Create a source release (Y/N):') 
    if user_in == "Y":
        subprocess.call(['make','clean'])
        shutil.copytree('bin', hw+'/bin')
        shutil.copytree('include', hw+'/include')
        shutil.copytree('lib', hw+'/lib')
        shutil.copytree('src', hw+'/src')
        shutil.copy('release.py', hw)
        subprocess.call(['tar','cvf',hw+'.tar',hw])
        shutil.rmtree(hw,False,None)

# Performs a clean and install and creates a tar file of just the bin directory
# and the executables

if args.b == True:
    user_in = raw_input('Create a binary release (Y/N):') 
    if user_in == "Y":
        host = socket.gethostname()
        user_in = raw_input('Enter hostname (default=' + host +')')
        if user_in:
            host = user_in
        filename = 'homework4_'+host+'.tar'
        subprocess.call(['make','clean'])
        subprocess.call(['make','install'])
        subprocess.call(['tar','cvf',filename,'bin'])
