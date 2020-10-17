# Xyla
Xyla is a rouge-like game. A rouge like game is a game in which death is imminent and the future is random and unpredictable.

Xyla is an implementation of the original Rouge game. To develop that, I have implemented multiple graph algorithms. I used efficient path-finding algorithms for enemy chase. To create dungeons and to make rooms that are neither strongly nor weakly connected, I used a combination of minimum spanning tree and Delaunay triangulation. The Delaunay algorithm used in the project is _asymptotically optimal_. 

## Installation
To play the game, download the project by pressing the green button “code” and then “Download Zip”. After extracting the project, go to Xyla/output/Debug-windows-x86_64/Xyla/ and then run Xyla.exe. Please note that Xyla is a windows x64 program.
If an error occurred and the message states that a dynamic library file missing ( a file that ends with .dll ie. “filename.dll”), then you need the Visual C++ run time library. You could download the Visual C++ redistributable from [here]( https://support.microsoft.com/en-us/help/2977003/the-latest-supported-visual-c-downloads) .

## Play
You can play the game by using your keyboard. You can move the player through using the arrow keys. To fight the enemy, use "w" key.

## Acknowledgment 
* Read more about the original Rouge from [here](https://en.wikipedia.org/wiki/Rogue_(video_game))
* Learn about the Delaunay algorithm used in the project from [here](http://www.personal.psu.edu/cxc11/AERSP560/DELAUNEY/13_Two_algorithms_Delauney.pdf)
