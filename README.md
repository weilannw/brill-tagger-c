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

To test with different files, make sure they are specified in the config file as such. We get length and num_lines with: 
	wc -c 
and 
	wc -l
 respectively. On The cluster in /scratch/shared/NOWCorpusFiles, 
clean_wlp.txt is 70GB and contains all of the data you could ever need.
