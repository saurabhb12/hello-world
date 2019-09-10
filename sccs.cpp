SCCS Lab:

1. Terminologies:

1.1. S-file: File in which all changes and versions of a file are stored. You can do three operations:
      (a) Retrieving a version for compiling/any other purpose. Any changes made here are deleted.
      (b) Editing an existing version
      (c) Comitting the changes made in previous step

1.2 Deltas: Changes made in s-file. Each delta can be used to indicate a new version.

1.3 SIDs: To uniquely identify deltas. Contain two numbers: release and level. Release mostly remains the same
unless a big change is being made 

1.4 ID Keywords: Of the form- %x% (x== upper case letter)

%I% - Keyword for latest delta applied
%W% - Keyword for module  name,  SID,  and  a mark that makes it findable by a program
%G% - the date of the latest delta applied

2. mkdir sccs_test
   cd sccs_test 
   echo 'This is the first line' > prog.c 
   mkdir SCCS 

   2.1 Creating an s-file 
        sccs create prog.c 
        //Creates file s.prog.c and stores it in SCCS 
        subdirectory//

    2.2 Getting recent version of a file in Read only mode 
        sccs get prog.c 

    2.3 Getting a copy of prog.c file for editing 
        sccs edit prog.c
    
    2.4 sccs info 
        //tells you whether any file is being edited 
        and if so then who is editing it.//

    2.5 sccs info -u saurabh
        //gives info on whether user saurabh is editing 
        any file or not//

    *Append a new line*
    echo 'This is the second line' >> prog.c

    2.6 Print all changes you've made so far
        sccs diffs prog.c

    2.7 Now, we want to make a delta file storing our
        changes, and store that file in our s-file 

        sccs delta prog.c
        /*Puts your changes in SCCS/s.prog.c/ by creating a delta file */
        //This command will ask you for a comment. Type in comment for mentioning why you made those changes//

    2.8 sccs edit prog.c 
        *Make some changes, let's say: echo 'Third line' >> prog.c *

        Now, we want to revert to previous version of prog.c by undoing recent changes. We do:
        sccs unedit prog.c
    
    2.9 Get a particular version of a file 
        sccs get -r1.1 prog.c (Gets version 1.1 of prog.c)
        sccs edit -r1.1 prog.c (For editing purpose)

    
3. Print all delta comments in a file: sccs prt prog.c 

4.  sccs cdc -r1.2 prog.c 
    Allows you to edit a comment in version 1.2 of prog.c 

5. Exclude a particular delta i.e. changes made in a particular version 
    sccs edit -x1.2 prog.c

    *Changes made in version 1.2 shall now be excluded from file/*
    When we do cat prog.c We'lll see
    This is the first line. 

    sccs delta prog.c /*Storing recent changes in new delta */

    sccs edit -x1.3-1.5 prog.c (Excludes range of deltas from 1.3
                                 to 1.5)

    sccs edit -x1.2-1 prog.c (Excludes ranges of deltas from 
                              1.3 to last version in 1)

6. Version numbers: x.y (x= major release, y= minor changes)
   Suppose, currently we're in version 1.3 and we want a copy 
   of it for our next major release i.e. 2.
   We write: sccs get -r2 prog.c


7. Change release number of all files in current directory 
   sccs edit -r2 SCCS 

   


