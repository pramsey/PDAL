.. _translate_command:

******************************************************************************
Translate Command
******************************************************************************

The *translate* command is used for simple conversion of files based on their 
file extensions. Use the :ref:`pipeline_command` for more significant 
translation operations.

::

    -i [ --input ] arg           input file name
    -o [ --output ] arg          output file name
    --a_srs arg                  Assign input coordinate system (if supported by
                               output format)
    --t_srs arg                  Transform to output coordinate system (if
                               supported by output format)
    -z [ --compress ]            Compress output data (if supported by output
                               format)
    --count arg (=0)             How many points should we write?
    --skip arg (=0)              How many points should we skip?
    --bounds arg                 Extent (in XYZ to clip output to)
    --polygon arg                POLYGON WKT to use for precise crop of data (2d
                               or 3d)
    --scale arg                  A comma-separated or quoted, space-separated
                               list of scales to set on the output file:
                               --scale 0.1,0.1,0.00001
                               --scale "0.1 0.1 0.00001"
    --offset arg                 A comma-separated or quoted, space-separated
                               list of offsets to set on the output file:
                               --offset 0,0,0
                               --offset "1234 5678 91011"
    -m [ --metadata ] [=arg(=1)] Forward metadata (VLRs, header entries, etc)
                               from previous stages

The translate command can be augmented by specifying full-path options at the 
command line invocation. For example, the following invocation will translate 
`1.2-with-color.las` to `output.laz` while doing the following:

* Setting the creation day of year to 42
* Setting the creation year to 2014
* Setting the LAS point format to 1
* Cropping the file with the given polygon

::

    ./bin/pdal translate \
        --drivers.las.writer.creation_doy="42" \
        --drivers.las.writer.creation_year="2014" \
        --drivers.las.writer.format="1" \
        --filters.crop.polygon="POLYGON ((636889.412951239268295 851528.512293258565478 422.7001953125,636899.14233423944097 851475.000686757150106 422.4697265625,636899.14233423944097 851475.000686757150106 422.4697265625,636928.33048324030824 851494.459452757611871 422.5400390625,636928.33048324030824 851494.459452757611871 422.5400390625,636928.33048324030824 851494.459452757611871 422.5400390625,636976.977398241520859 851513.918218758190051 424.150390625,636976.977398241520859 851513.918218758190051 424.150390625,637069.406536744092591 851475.000686757150106 438.7099609375,637132.647526245797053 851445.812537756282836 425.9501953125,637132.647526245797053 851445.812537756282836 425.9501953125,637336.964569251285866 851411.759697255445644 425.8203125,637336.964569251285866 851411.759697255445644 425.8203125,637473.175931254867464 851158.795739248627797 435.6298828125,637589.928527257987298 850711.244121236610226 420.509765625,637244.535430748714134 850511.791769731207751 420.7998046875,636758.066280735656619 850667.461897735483944 434.609375,636539.155163229792379 851056.63721774588339 422.6396484375,636889.412951239268295 851528.512293258565478 422.7001953125))" \
        ./test/data/1.2-with-color.las \
        output.laz
