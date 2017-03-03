#
# Project:    Homework 2
# Programmer: Edwin Flores
# Course:     EN.605.414.81
# Purpose:    Python script that creates either a binary or source release
#
import argparse
import os
import sys
import socket
import subprocess
import platform

parser = argparse.ArgumentParser()

parser.add_argument('-s', action="store_true", help ='create a source release')
parser.add_argument('-b', action="store_true", help='create a binary release')

args = parser.parse_args()

no_arg = args.s or args.b

if no_arg == False:
    print ("There was no valid argument")
    sys.exit(0)

platform = platform.platform()

# Perform a clean and create a tar file with all files and the directory structure

if args.s == True:
    user_in = raw_input('Create a source release (Y/N):') 
    if user_in == "Y":
        dir = os.getcwd()
        subprocess.call(['make','clean'])
        subprocess.call(['tar','cvf','homework2.tar',"--exclude='*.tar'",dir])

# Performs a clean and install and creates a tar file of just the bin directory
# and the executables

if args.b == True:
    user_in = raw_input('Create a binary release (Y/N):') 
    if user_in == "Y":
        host = socket.gethostname()
        user_in = raw_input('Enter hostname (default=' + host +')')
        if user_in:
            host = user_in
        filename = 'homework2_'+host+'.tar'
        subprocess.call(['make','clean'])
        subprocess.call(['make','install'])
        subprocess.call(['tar','cvf',filename,'bin'])
