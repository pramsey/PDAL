.. _apps:

******************************************************************************
PDAL Applications
******************************************************************************

:Author: Howard Butler
:Contact: hobu.inc at gmail dot com
:Date: 9/1/2014

PDAL contains a single `git`_-style application, called *pdal*. The `pdal` 
application currently contains six commands:

.. toctree::
   
   delta
   diff
   ground
   info
   pcl
   pipeline
   random
   translate
   view

Applications are run by invoking the *pdal* application along with the 
command name:

::

    $ pdal info myfile.las
    $ pdal translate input.las output.las
    $ pdal pipeline --stdin < myxml.xml

.. note::
    
    The :ref:`ground <ground_command>`, :ref:`pcl <pcl_command>`, and
    :ref:`view <view_command>` commands are only available if PCL is linked.

Help about each command can be retrieved via the ``--help`` switch. 
The ``--drivers`` and ``--options`` switches can tell you more about 
particular drivers and their options:

::

    $ pdal info --help
    $ pdal translate --drivers
    $ pdal pipeline --options drivers.las.writer

Additional, driver-specific options may be specified by using a 
namespace-prefixed option name. For example, it is possible to 
set the LAS day of year at translation time with the following 
option:

::

    $ pdal translate \
    --drivers.las.writer.creation_doy="42" \
    input.las
    output.las

.. note::

        Driver specific options can be identified using the 
        ``pdal info --options`` invocation.
        
.. _`git`: http://git-scm.com/
