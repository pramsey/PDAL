.. _random_command:

******************************************************************************
Random Command
******************************************************************************

The *random* command is used to create a random point cloud. It uses
:ref:`drivers.faux.reader` to create a point cloud containing *count* points
drawn randomly from either a uniform or normal distribution. For the uniform
distribution, the bounds can be specified (they default to a unit cube). For
the normal distribution, the mean and standard deviation can both be set for
each of the x, y, and z dimensions.

::

  -o [ --output ] arg           output file name
  -z [ --compress ]             Compress output data (if supported by output
                                format)
  --count arg (=0)              How many points should we write?
  --bounds arg                  Extent (in XYZ to clip output to)
  --mean arg                    A comma-separated or quoted, space-separated
                                list of means (normal mode):
                                --mean 0.0,0.0,0.0
                                --mean "0.0 0.0 0.0"
  --stdev arg                   A comma-separated or quoted, space-separated
                                list of standard deviations (normal mode):
                                --stdev 0.0,0.0,0.0
                                --stdev "0.0 0.0 0.0"
  --distribution arg (=uniform) Distribution (uniform / normal)
