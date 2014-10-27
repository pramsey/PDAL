.. _info_command:

******************************************************************************
Info Command
******************************************************************************

Dumps information about a point cloud file, such as:

* basic properties (extents, number of points, point format)

* coordinate reference system

* additional metadata

* summary statistics about the points

* the plain text format should be reStructured text if possible to allow 
  a user to retransform the output into whatever they want with ease

::

    $ pdal info  test/data/1.2-with-color.las --count 3 --query "636601.87, 849018.59, 425.10"

Print the first 10 points of the file as `reStructuredText`_

::

    $ pdal info test/data/1.2-with-color.las -p 0-10

Print three selected points of the file as `reStructuredText`_

::

    $ pdal info test/data/1.2-with-color.las -p 4, 16, 28


.. _`reStructuredText`: http://docutils.sourceforge.net/docs/user/rst/quickref.html

:: 

    -p [ --point ] [=arg(=0)] point to dump
    --query arg               A 2d or 3d point query point
    --distance arg            A query distance
    -a [ --stats ]            dump stats on all points (reads entire dataset)
    --count arg (=0)          How many points should we write?
    --dimensions arg          dump stats on all points (reads entire dataset)
    -s [ --schema ]           dump the schema
    -m [ --metadata ]         dump the metadata
    --sdo_pc                  dump the SDO_PC Oracle Metadata
    -r [ --stage ]            dump the stage info
    --xml                     dump XML instead of JSON
    --seed arg (=0)           Seed value for random sample
    --sample_size arg (=1000) Sample size for random sample
