.. _delta_command:

******************************************************************************
Delta Command
******************************************************************************

The *delta* command is used to select a nearest point from a candidate file
for each point in the source file. If the ``--2d`` option is used, the
query only happens in XY coordinate space.

::

    $ pdal delta test/data/1.2-with-color.las test/data/1.2-with-color.las > deltas

A simple CSV-style text is output with delta information:

::

    [hobu@pyro pdal (master)]$ ./bin/pdal delta test/data/1.2-with-color.las test/data/1.2-with-color.las
    ------------------------------------------------------------------------------------------
     Delta summary for source 'test/data/1.2-with-color.las' and candidate 'test/data/1.2-with-color.las'
    ------------------------------------------------------------------------------------------

    ----------- --------------- --------------- --------------
     Dimension       X             Y                  Z
    ----------- --------------- --------------- --------------
     Min        0.0000            0.0000            0.0000
     Min        0.0000            0.0000            0.0000
     Mean       0.0000            0.0000            0.0000
    ----------- --------------- --------------- --------------

::

        [hobu@pyro pdal (master)]$ ./bin/pdal delta test/data/1.2-with-color.las test/data/1.2-with-color.las --detail

::

    "ID","DeltaX","DeltaY","DeltaZ"
    0,0.00,0.00,0.00
    1,0.00,0.00,0.00
    2,0.00,0.00,0.00
    3,0.00,0.00,0.00
    4,0.00,0.00,0.00
    5,0.00,0.00,0.00

::

      --source arg          source file name
      --candidate arg       candidate file name
      --output arg          output file name
      --2d                  only 2D comparisons/indexing
