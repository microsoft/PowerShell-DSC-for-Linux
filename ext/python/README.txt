Build notes:

Before building:
     If you want to preserve a previous version of Python that is already on
     the system, save "/usr/local/bin/python" so that you can restore it
     afterwards.

Building:
     > tar zxvf Python-2.5.tgz
     > cd Python-2.5
     > ./configure --enable-unicode=ucs4 --enable-shared --with-cxx-main=g++
     <edit Makefile>
     change: 'CXX= g++ -pthread'
     to: 'CXX= g++ -pthread -fPIC'
     > make
     > sudo make install
     > sudo ln -s /usr/local/lib/libpython2.5.so.1.0 /usr/lib64/libpython2.5.so.1.0
Post building:
     Restore '/usr/local/bin/python' if you saved it in the first step.
