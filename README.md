# Youtube-View-Bot

/*

This is a view bot that i just started to make in cpp for pactice.

I have just started on this project, it will get better as time goes on for now the bot
will ask you for a few inputs through the terminal it will collect the following input

* first it will collect the url that you will be visiting, {https://www.example.com/etc?r} is 
the format.

* next two will be asking you for the retention of the video in seconds, for example
the first input will be the minimum time to spend watching the video and the second
will be the maximum time you will spend watching the video. then it will select a rand
number somewhere in between the two specified.

* after you will specify the Directory of you .txt file carring the proxies, for now
note that the proxies a just that and no :[PORT] tags, example format is '192.168.1.1'
not '192.168.1.1:80'

when finished it will open chrome.exe with terminal and visit the site specified, it 
will the wait 2 seconds and press the space bar to start the video 'for now it will 
suffice, not that clicking around during this process may bug it and require human input
to start the video' after, it will minimize the window so you dont gotta have the window 
open, after it reaches the time end of the sleep command it will close out of the chrome.exe
and start the loop over until you reach the amount of loops specified. Each time it will run
for a rand set time somewhere in specification.

and also i plan to make this all run in the background with chromium and be multi-threaded
for now it is single thread so i can build this up a little bit.

- I plan to silence the window
- make it so you dont have to make a user input to start videos by telling command to press space key
- clean the code a bit
- make it multi threading capable with a way to select how many processes you start
- give you more customization as well as setting for such
- probably will create a user friendly ui that i then put behind a paywall
- well paywall no but ui maybe / it will depend

0000000000000000000000000000000000000000000000000000
000000000000000000000000000000000000000000000000000000000
00000000000000000                                         0
00000000000000000     Tutorial == {LOL NOT POSTED YET}     0
00000000000000000                                           0
0000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000000000

*/
