Build instructions:
    > tar zxvf boost_1_55_0.tar.gz
    > cd boost_1_55_0
    > ./bootstrap.sh --with-python-version=2.5 --prefix=/usr/local \
      --exec-prefix=/usr/local --libdir=/usr/local/lib/boost_1_55_0 \
      --includedir=/usr/local/include/boost_1_55_0

    <edit file> project-config.jam
        change the line:
            'using python : 2.5 /usr/local ;'
        to:
            'using python : 2.5 : /usr/local/bin/python2.5
             : /usr/local/include/python2.5 ;
            using python : 2.7 : /usr/local/bin/python2.7
             : /usr/local/include/python2.7 ;'
        change the line 'using gcc ;'
        to 'using gcc : : : <cxxflags>"-fPIC -DPy_UNICODE_SIZE=4" ;'
    </edit file>

    > sudo ./b2 --build-dir=/tmp/boost link=static install

