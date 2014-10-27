.. _cpp-reader:

******************************************************************************
:cpp:class:`pdal::Reader`
******************************************************************************

:cpp:class:`pdal::Reader` are classes that provide interfaces to various
the various point cloud formats and hands them off to a PDAL pipeline in a
common format.

.. doxygenclass:: pdal::Reader
   :members:
   :sections: public*

BPF
------------------------------------------------------------------------------

.. doxygenclass:: pdal::BpfReader
   :members:

Buffer
------------------------------------------------------------------------------

.. doxygenclass:: pdal::drivers::buffer::BufferReader
   :members:

Caris
------------------------------------------------------------------------------

.. doxygenclass:: pdal::csar::CloudReader
   :members:

Faux
------------------------------------------------------------------------------

.. doxygenclass:: pdal::drivers::faux::Reader
   :members:

Greyhound
------------------------------------------------------------------------------

.. doxygenclass:: pdal::drivers::greyhound::GreyhoundReader
   :members:

Icebridge
------------------------------------------------------------------------------

.. doxygenclass:: pdal::drivers::icebridge::Reader
   :members:

LAS
------------------------------------------------------------------------------

The `ASPRS LAS`_ format is a sequential binary format used to store data from
LiDAR sensors and by LiDAR processing software for data interchange and archival.


.. _`ASPRS LAS`: http://www.asprs.org/Committee-General/LASer-LAS-File-Format-Exchange-Activities.html

.. doxygenclass:: pdal::drivers::las::Reader
   :members:

MrSID
------------------------------------------------------------------------------

.. doxygenclass:: pdal::drivers::mrsid::Reader
   :members:

NITF
------------------------------------------------------------------------------

.. .. doxygenclass:: pdal::drivers::nitf::NitfReader
   :members:

OCI
------------------------------------------------------------------------------

The OCI reader provides `Oracle Point Cloud`_ support to PDAL.

.. _`Oracle Point Cloud`: http://docs.oracle.com/cd/B28359_01/appdev.111/b28400/sdo_pc_pkg_ref.htm

.. doxygenclass:: pdal::drivers::oci::OciReader
   :members:

PCD
------------------------------------------------------------------------------

.. doxygenclass:: pdal::drivers::pcd::PcdReader
 :members:

PgPointCloud
------------------------------------------------------------------------------

.. .. doxygenclass:: pdal::drivers::pgpointcloud::PgReader
   :members:

QFIT
------------------------------------------------------------------------------
`QFIT`_ is a format for the NASA IceBridge sea ice sensor.
 
.. _`QFIT`: http://nsidc.org/data/ilatm1b.html

.. doxygenclass:: pdal::drivers::qfit::Reader
  :members:

SBET
------------------------------------------------------------------------------

.. doxygenclass:: pdal::drivers::sbet::SbetReader
   :members:

SQLite
------------------------------------------------------------------------------

.. doxygenclass:: pdal::drivers::sqlite::SQLiteReader
   :members:

TerraSolid
------------------------------------------------------------------------------

.. doxygenclass:: pdal::drivers::terrasolid::Reader
 :members:
