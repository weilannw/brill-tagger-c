# brill-tagger-c
brill tagger in c

How to use:
go to root dir
	make
	make sync
	cd build
Look at the config file and ensure that the values match up with corpus, rule, and frequency map files in the build directory.
The frequency map file requires a corpus file to be run with learning mode turned on. Run with learning mode by specifying -l.
Tagging mode can be run by not specifying the -l option. 

