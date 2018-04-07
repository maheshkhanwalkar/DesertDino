README: Mahesh Khanwalkar
=======================================================================

This game is similar to Google Chrome's dinosaur game [when the network
is down], but not as complex.

Controls:
  * START - start the game
  * SELECT - end the game/restart at any time
  * UP - jump up (and *ever so slightly* horizontally)

File layout:
  * drivers/font/: text and character printing routines
  * drivers/button/: button handling
  * drivers/video/: pixel and image drawing
  * lib/: "frame" (image collection) and misc routines that are useful
  * main/main.c: main game file (starting point)

Misc:
  * drawImage3(...) is called draw_img(...) in the source
  * waitForVBlank() exists within drivers/video/video.c

