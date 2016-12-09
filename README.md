# sweepminer
Simple terminal minesweeper game using ncurses


Dependencies: ncurses

    Ubuntu and friends: $ sudo apt-get install libncurses-dev
  
                  Arch: $ sudo pacman -S ncurses
                
                 Other: you can figure it out, I believe at you


To install:

      $ make
  
      $ sudo make install


To uninstall:

      $ sudo make uninstall
  
  
To run:

    $ sweepminer width height number_of_mines
  

Where width, height, and number_of_mines are integers

  
Controls:

    Arrow Keys / HJKL : Move Cursor
 
                    F : Click on mine
                  
                    G : Toggle flag
                  
                    Q : Quit Game (quitter)
                 
