.. _pcl_command:

******************************************************************************
PCL Command
******************************************************************************

The *pcl* command is used to invoke a PCL JSON pipeline. See
:ref:`pcl_block_tutorial` for more information.

::

    -i [ --input ] arg      input file name
    -o [ --output ] arg     output file name
    -p [ --pcl ] arg        pcl file name
    -z [ --compress ]       Compress output data (if supported by output format)

The *pcl* command is only available when PDAL is build with PCL support.
