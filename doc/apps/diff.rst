.. _diff_command:

******************************************************************************
Diff Command
******************************************************************************

The *diff* command is used for executing a simple contextual difference 
between two sources. 

::

    $ pdal diff test/data/1.2-with-color.las test/data/1.2-with-color-clipped.las
    
It will output JSON if there are any differences. It will output nothing 
and return 0 if there are no differences. At this time it supports 
checking the following:

* Different schema
* Expected count
* Metadata
* Actual point count
* Byte-by-byte point data
