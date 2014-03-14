Build instructions:
    > tar zxvf boost_1_55_0.tar.gz
    > cd boost_1_55_0
    > ./bootstrap.sh --with-python-version=2.5 --prefix=/usr/local \
      --exec-prefix=/usr/local --libdir=/usr/local/lib \
      --includedir=/usr/local/include/boost_1_55_0

    <edit file> project-config.jam
        change the line 'using python : 2.5 ;'
        to 'using python : 2.5 : /usr/local/bin/python2.5 : /usr/local/include/python2.5 ;'
    </edit file>

    > sudo ./b2 --build-dir=/tmp/boost install

