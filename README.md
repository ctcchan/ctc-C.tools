# ctools
### Command Line Tools for Composers
### Version 2.0

### Download
Download the source code using Git (most up-to-date version).

    $ git clone https://github.com/ctcchan/ctools.git

Download the latest build release for Max OSX (2016-04-17): [ctools-2.0-release-Mac.zip](https://www.dropbox.com/s/gxc2flseeepu4cu/ctools-2.0-release-Mac.zip?dl=0)

Download the latest build release for Windows 10 (2016-04-17): [ctools-2.0-release-Win.zip](https://www.dropbox.com/s/jjvy7eyw7mp05w2/ctools-2.0-release-Win.zip?dl=0)

### Installation
Build the program, if downloaded using Git.

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
The files "setTable.txt" and "setTableDescription.txt" should be in the current path for the program to recognize them. This applies to all the download options.
