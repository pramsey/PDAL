.. _ground_command:

******************************************************************************
Ground Command
******************************************************************************

The *ground* command is used to segment the input point cloud into ground
versus non-ground returns. The output is a point cloud containing only ground
returns. Internally, the tool is calling the Point Cloud Library's
`ProgressiveMorphologicalFilter`_. As such, *ground* is only available when
PDAL is linked with PCL.

.. _`ProgressiveMorphologicalFilter`: http://pointclouds.org/documentation/tutorials/progressive_morphological_filtering.php#progressive-morphological-filtering.

::

    -i [ --input ] arg            input file name
    -o [ --output ] arg           output file name
    --maxWindowSize arg (=33)     max window size
    --slope arg (=1)              slope
    --maxDistance arg (=2.5)      max distance
    --initialDistance arg (=0.15) initial distance
    --cellSize arg (=1)           cell size
    --base arg (=2)               base
    --exponential arg (=1)        exponential?
