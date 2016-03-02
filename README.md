# ctools
### Command Line Tools for Composers
### Version 2.0

### Download
Download using Git.

    $ git clone https://github.com/ctcchan/ctools.git

### Installation
Build the program.

    $ cd ctools
    $ make

You can run it directly with the executable file "ctools" while you are in the ctools directory.

    $ ./ctools

...or you can install it to your /usr/local/bin directory and be able to run it anywhere in the shell environment

    $ make install
    $ ctools

### Un-installation
Un-install from your computer.

    $ make uninstall

### Input/output text files are handled in the CURRENT directory
The files "setTable.txt" and "setTableDescription.txt" should be in the current path for the program to recognize them.
