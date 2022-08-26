#CodeQL [python/responsible-ai/using-python2] old python version: support still needed for older python version
#!/usr/bin/env python
#============================================================================
# Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
#============================================================================
import os
import sys
import glob

orig_dir=os.path.realpath(os.getcwd())
os.system('rm /tmp/omstest_cleanup* 2> /dev/null')
os.system('rm -rf /tmp/omsext 2> /dev/null')

if os.path.exists('/opt/micosoft/omsconfig'):
    sys.stdout.write('Cannot run test_OMS_nxProviders.py when omsagent is present!') 
    sys.exit(0)

print 'Running test_OMS_nxProviders.py'

# Extract the build
os.system('touch /tmp/omstest_cleanup')
bundle = sys.argv[1]
bundle += '/omsagent*.universal.x64.sh' 
bundle = glob.glob(bundle)[0]
print 'Target = ' + bundle
os.system('mkdir /tmp/omsext; cd /tmp/omsext ; ' + bundle + ' --extract')
if os.system('which dpkg-deb &> /dev/null') == 0:
    for pkg in glob.glob('/tmp/omsext/omsbundle*/100/*.deb'):
        os.system('dpkg-deb -x ' + pkg + ' /tmp/omsconfig')
else:
    os.system('mkdir /tmp/omsconfig')
    os.chdir('/tmp/omsconfig')
    for pkg in glob.glob('/tmp/omsext/omsbundle*/100/*.rpm'):
        os.system('rpm2cpio ' + pkg + ' | cpio -idmv')
os.chdir('/tmp/omsconfig/opt/microsoft/omsconfig/module_packages')
for pkg in glob.glob('./*.zip'):
    os.system('unzip ' + pkg)
os.system('cp -r  /tmp/omsconfig/opt/microsoft/omsconfig/module_packages/*/DSCResources/*/x*/Scripts/* /tmp/omsconfig/opt/microsoft/omsconfig/Scripts/')

# Setup the directories and files
if not os.path.exists('/var/opt'):
    os.symlink('/tmp/omsconfig/var/opt','/var/opt')
    #os.system('cp -r /tmp/omsconfig/var/opt /var/opt')
if not os.path.exists('/etc/opt'):
    os.symlink('/tmp/omsconfig/etc/opt','/etc/opt')
    #os.system('cp -r /tmp/omsconfig/etc/opt /etc/opt')
if not os.path.exists('/opt/microsoft/'):
    os.makedirs('/opt/microsoft/')
if not os.path.exists('/opt/microsoft/omsconfig'):
    os.symlink('/tmp/omsconfig/opt/microsoft/omsconfig','/opt/microsoft/omsconfig')
    #os.system('cp -r /tmp/omsconfig/opt/microsoft/omsconfig /opt/microsoft/omsconfig')
if os.system('grep -q "omsagent:" /etc/group'):
    os.system('groupadd -r omsagent')
os.system('touch /tmp/omstest_cleanup_group')
if os.system('grep -q "omsagent:" /etc/passwd'):
    os.system('useradd -r -c "OMS agent" -d /var/opt/microsoft/omsagent/run -g omsagent -s /bin/bash omsagent')
os.system('touch /tmp/omstest_cleanup_user')
os.system('mkdir -p /tmp/omsconfig/var/opt/microsoft/omsagent/run; mkdir -p /var/opt') 
#os.symlink('/tmp/omsconfig/var/opt/microsoft/', '/var/opt/microsoft')
#os.system('mkdir -p /etc/opt/')
#os.symlink('/tmp/omsconfig/etc/opt/microsoft/', '/etc/opt/microsoft')
os.system('chmod a+wrx /tmp/omsconfig/etc/opt/omi/conf/omsconfig/')
os.system('chown -R omsagent.omsagent /tmp/omsconfig')
#os.system('chown -R omsagent.omsagent /etc/opt')
#os.system('chown -R omsagent.omsagent /opt/microsoft/omsconfig/Scripts')
#os.system('chgrp -R omsagent /etc/opt/omi/conf/omsconfig')
#os.system('chgrp -R omsagent /opt/microsoft/omsconfig/Scripts')
os.system('touch /var/opt/microsoft/omsagent/run/.bash_profile')
os.system('chmod 755 /etc/opt')
os.system('mkdir -p /tmp/omsconfig/var/opt/microsoft/omsconfig')
os.system('chown -R omsagent /tmp/omsconfig/var/opt')
#os.system('chown -R omsagent /var/opt/microsoft/omsagent/run')
#os.system('chgrp -R omsagent /var/opt/microsoft/omsagent/run')

# Setup omsconfig sudoers and add python as passwordless root.
os.system('echo "omsagent ALL=(ALL) NOPASSWD: `which python` " >> /etc/opt/microsoft/omsagent/sysconf/sudoers')
os.system('cp /etc/sudoers /etc/sudoers.back')
os.system('cat /etc/opt/microsoft/omsagent/sysconf/sudoers >> /etc/sudoers')
os.system('chmod 440 /etc/sudoers')
# Setup python __init__.py.
os.system('su omsagent -c "/opt/microsoft/omsconfig/Scripts/RegenerateInitFiles.py"')
# Import the keys
os.system('su omsagent -c "/opt/microsoft/omsconfig/Scripts/ImportGPGKey.sh /opt/microsoft/omsconfig/keys/msgpgkey.asc keymgmtring.gpg"')
os.system('su omsagent -c "/opt/microsoft/omsconfig/Scripts/ImportGPGKey.sh /opt/microsoft/omsconfig/keys/dscgpgkey.asc keyring.gpg"')
#os.system('mkdir -p /var/opt/microsoft/omsconfig')
#os.system('chgrp -R omsagent /var/opt/microsoft/omsconfig')

# Setup fake syslog/rsyslog oms conf files.
if not os.path.exists('/etc/opt/omi/conf/omsconfig/syslog-ng-oms.conf'):
    os.system('touch /etc/opt/omi/conf/omsconfig/syslog-ng-oms.conf')
if not os.path.exists('/etc/opt/omi/conf/omsconfig/rsyslog-oms.conf'):
    os.system('touch /etc/opt/omi/conf/omsconfig/rsyslog-oms.conf')

if os.path.exists('/etc/rsyslog.d/'):
    os.system('cp /etc/opt/omi/conf/omsconfig/rsyslog-oms.conf /etc/rsyslog.d/95-omsagent.conf')
    os.system('chown omsagent:omsagent /etc/rsyslog.d/95-omsagent.conf')
os.system('mkdir -p /etc/opt/microsoft/omsagent/conf/')
os.system('touch /etc/opt/microsoft/omsagent/conf/omsagent.conf')
os.system('chown -R omsagent /etc/opt/microsoft/omsagent/conf/')
os.system('mkdir -p /opt/microsoft/omsagent/bin')
os.system('/bin/echo -e "#!/bin/bash\necho \n" > /opt/microsoft/omsagent/bin/service_control')
os.system('chmod +x /opt/microsoft/omsagent/bin/service_control')
'/opt/microsoft/omsagent/bin/service_control'
os.system('chown -R omsagent /var/opt/microsoft/omsconfig')
os.system('chmod +w /etc/opt/omi/conf/omsconfig/*')
os.system('chown -R omsagent /etc/opt/omi/conf/omsconfig')

# Copy the Tests
destpath = '/opt/microsoft/omsconfig/Scripts/' + sys.argv[2] + '/Scripts/'
srcpath = '/' + os.path.join(*os.path.realpath(__file__).split('/')[:-1])
os.system('cp -r ' + srcpath + ' ' + destpath)
os.system('chown -R omsagent /opt/microsoft/omsconfig/Scripts')
#os.system('chgrp -R omsagent /opt/microsoft/omsconfig/Scripts')
os.chdir(destpath + 'Tests')

#Don't restart the service as it is not installed.
os.system("echo '#!/bin/bash' > /opt/microsoft/omsagent/bin/service_control")

#nxUser
os.system('/usr/sbin/useradd -d "/home/jojoma" -m  -g mail jojoma')
os.system('/usr/sbin/usermod -c "JO JO MA,JOJOMA" jojoma')

#nxGroup
os.system('/usr/sbin/groupadd -g 1101 jojomamas')

#nxPackage
if os.system('which dpkg 2> /dev/null') == 0:
    os.system('/usr/bin/dpkg -i ' + destpath + 'Tests/dummy-1.0.deb')
else:
    os.system('/bin/rpm -i ' + destpath + 'Tests/dummy-1.0-1.x86_64.rpm')
# Call the test!
result = os.system('su -c " python ' + destpath + 'Tests/test_OMS_nxProviders.py" omsagent')
#result = os.system('su -c " python ' + destpath + 'Tests/test_OMS_nxProviders.py &> /tmp/test_nxOMSProviders_results.txt" omsagent')

# Cleanup.
if os.path.exists('/tmp/omstest_cleanup_user'):
    os.system('userdel omsagent &> /dev/null')
    os.system('userdel jojoma &> /dev/null')
if os.path.exists('/tmp/omstest_cleanup_group'):
    os.system('groupdel omsagent')
    os.system('groupdel jojomamas')
os.chdir(orig_dir)
if os.path.exists('/tmp/omstest_cleanup'):
    os.system('rm -rf /var/opt')
    os.system('rm -rf /etc/opt')
    os.system('rm -rf /opt/microsoft')
os.system('cp /etc/sudoers.back /etc/sudoers')
os.system('chmod 440 /etc/sudoers')
if os.system('which dpkg 2> /dev/null') == 0:
    os.system('/usr/bin/dpkg -P dummy')
else:
    os.system('/bin/rpm -e dummy')
os.system('rm -rf /tmp/omsext /tmp/omsconfig/  /tmp/omstest*')
sys.exit(0)
