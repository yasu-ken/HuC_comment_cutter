echo off
set temp=%path%
set path="C:\borland\bcc55\Bin"

BCC32.EXE HuC_comment_cut.cpp >err.txt
