This is a task for Unigine school July 2017, STL direction.
The task called "Logs parsing".

Input will consist of log-file, the file name set in command line.
The log is a text file includes in some lines URLs.
URL is a substring surely consisting of a prefix and the domain and perhaps additional path.
Prefix is one of "http://" or "https://".
Domain is any character set "a-z A-Z 0-9 . -" (Latin chars, digits, point, dash).
Path is always start from "/" and can consist from "a-z A-Z 0-9 . , / + _"(Latin chars, digits and five special characters).
In case absence empty path replaced on "/" path. That's why "http://google.com/" has domain "google.com" plus path "/". And "http://...oh" has domain "...oh" and empty path is replaced on "/". These are a little simplified rules.

In output you will get a report, the filename set in command line.
Report is a text file in which at first the general statistics is written, and top-N of domains and top-N of ways are listed further according the frequency of their mention in the log-file.
In case of the same frequency domains and paths sorted in a lexicographic order (without the encoding, that is byte by byte).
Pay attention, a path "/" as a part of 4 different URL from 4 different domains these are 4 mentions.

N can be set by an optional key in the command line "-n".
	mytest [-n NNN] in.txt out.txt

Thus the format of the files have to be strictly such, as in the example.

Example of input file:

ssl1001 129960997 2014-01-21T08:36:33.097 0.426 1.2.3.4 -/200 12324 GET https://en.wikipedia.org/w/index.php?title=Kirschkuchen&action=edit&section=8	NONE/wikimedia - https://en.wikipedia.org/wiki/Kirschkuchen	- Mozilla/5.0 (Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/32.0.1700.76 Safari/537.36 en-US,en;q=0.8 -
	sq18.wikimedia.org 1715898 2010-12-01T21:57:22.331 0 1.2.3.4 TCP_MEM_HIT/200 13208 GET http://en.wikipedia.org/wiki/Main_Page	NONE/- text/html - - Mozilla/4.0%20(compatible;%20MSIE%206.0;%20Windows%20NT%205.1;%20.NET%20CLR%201.1.4322) en-US -
	cp1048.eqiad.wmnet 8883921154 2013-09-26T06:28:16 0.001308203 1.2.3.4 hit/200 52362 GET http://en.wikipedia.org/wiki/Free_software	- text/html https://www.google.com/search?q=free+software	4.3.2.1 Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/29.0.1547.76 Safari/537.36 en-US,en;q=0.8 - 

Example of output file:

total urls 5, domains 2, paths 5

	top domains
	4 en.wikipedia.org
	1 www.google.com

	top paths
	1 /search
	1 /w/index.php
	1 /wiki/Free_software
	1 /wiki/Kirschkuchen
	1 /wiki/Main_Page

Restrictions:
It is possible to use language according the standart, i.e. C++ and STL.

Loki, Boost, Qt amd other third-party libraries cannot be used.