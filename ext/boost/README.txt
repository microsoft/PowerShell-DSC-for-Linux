Build instructions:

    These instructions assume using Python version 2.5.  For other versions of
    Python replace 2.5 with the other version number.

    > tar zxvf boost_1_55_0.tar.gz
    > cd boost_1_55_0
    > ./bootstrap.sh --with-python-version=2.5 --prefix=/usr/local \
      --exec-prefix=/usr/local --libdir=/usr/local/lib/boost_1_55_0 \
      --includedir=/usr/local/include/boost_1_55_0

    <edit file> project-config.jam

        change the line:
            'using gcc ;'
        to:
            'using gcc : : : <cxxflags>"-fPIC -DPy_UNICODE_SIZE=4" ;'

        change the line:
            'using python : 2.5 /usr/local ;'
        to:
            'using python : 2.5 : /usr/local/bin/python2.5
             : /usr/local/include/python2.5 ;

    </edit file>

    > sudo ./b2 --build-dir=/tmp/boost link=static install
    > sudo mv /usr/local/lib/boost_1_55_0/libboost_python.a \
        /usr/local/lib/boost_1_55_0/libboost_python2.5.a

