.. _cpp-writer:

******************************************************************************
:cpp:class:`pdal::Writer`
******************************************************************************

:cpp:class:`pdal::Writer` are classes that provide interfaces to various
the various point cloud formats.

.. doxygenclass:: pdal::Writer
   :members:
   :sections: public*

LAS
---------------------------

.. doxygenclass:: pdal::drivers::las::Writer
   :members:

NITF
---------------------------

.. doxygenclass:: pdal::drivers::nitf::Writer
   :members:

OCI
---------------------------

.. doxygenclass:: pdal::drivers::oci::Writer
   :members:

P2G
---------------------------

.. doxygenclass:: pdal::drivers::p2g::P2gWriter
   :members:

PCD
---------------------------

.. doxygenclass:: pdal::drivers::pcd::PcdWriter
   :members:

PCLVisualizer
---------------------------

.. doxygenclass:: pdal::drivers::pclvisualizer::PclVisualizer
   :members:

PgPointCloud
----------------------------

.. doxygenclass:: pdal::drivers::pgpointcloud::Writer
   :members:

SBET
----------------------------

.. doxygenclass:: pdal::drivers::sbet::SbetWriter
   :members:

SQLite
-----------------------------

.. doxygenclass:: pdal::drivers::sqlite::SQLiteWriter
   :members:

Text
-----------------------------

.. doxygenclass:: pdal::drivers::text::Writer
   :members:
