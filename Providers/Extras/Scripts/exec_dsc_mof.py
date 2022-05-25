#!/usr/bin/env python2
import os
import sys
import re
import traceback
import copy
import inspect

def CallMOF (req):
    d = req[2]
    if req[1] not in globals().keys():
        sys.stderr.write('Unable to find module: ' + req[1])
        return None
    the_module = globals ()[req[1]]
    method_name = req[0] + '_Marshall'
    if not method_name in the_module.__dict__.keys():
        sys.stderr.write ('Unable to find method: ' + method_name)
        return None
    #add args that are missing from the mof.
    argspec=inspect.getargspec(the_module.__dict__[method_name])
    if type(argspec) == tuple :
        args=argspec[0]
    else :
        args=argspec.args
    for arg in args:
        if arg not in d.keys():
            d[arg]=None
    ret = the_module.__dict__[method_name](**d)
    sys.stdout.write (req[1]+'.'+method_name+'('+repr(d)+') returned '+repr(ret)+'\n')
    if len(ret) >1:
        return translate_protocol(ret[1])
    else:
        return ret
    
def ParseMOF():
    srch_list_elem=r'(=[ ]+)({)(.*?)(})([ ]?;)'
    repl_list_elem = r'\1[\3]\5'
    srch_instance=r'(?P<instance>instance)[ ,\n]+of[ ,\n]+(?!OMI)(?P<inst_type>.*?)[ ,\n]+as[ ,\n]+(?P<inst_value>.*?)[ ,\n]?{([ ,\n]+)?(?P<inst_text>.*?)}[ ,\n]?;'
    value_srch_str=r'([ ,\n]+)?(?P<name>.*?)([ ]+)?=([ ]+)?(?P<value>.*?)([ ]+)?;'
    instance_srch_str=r'([ ,\n]+)?ResourceID([ ]+)?=([ ]+)?"\[(?P<module>.*?)\](?P<ResourceID>.*?)"([ ]+)?;'
    list_elem=re.compile(srch_list_elem,re.M|re.S)
    instance=re.compile(srch_instance,re.M|re.S)
    value_srch=re.compile(value_srch_str,re.M|re.S)
    instance_srch=re.compile(instance_srch_str,re.M|re.S)
    mof_text=open(sys.argv[1],'r').read()
    mof_text=list_elem.sub(repl_list_elem,mof_text)
    matches=instance.finditer(mof_text)
    d={}
    curinst=''
    for match in matches:
        values=match.group('inst_text')
        values=re.sub('(/[*].*?[*]/)','',values)
        i=instance_srch.search(values)
        curinst='['+i.group('module')+']'+i.group('ResourceID').strip('"')
        d[curinst]={}
        d[curinst]['module']=i.group('module')
        v=value_srch.finditer(values)
        for pair in v:
            name=pair.group('name')
            value=pair.group('value')
            if value.lower().strip() == 'false':
                value='False'
            if value.lower().strip() == 'true':
                value='True'
            d[curinst][name]=eval(value)
    return d

def ProcessMOF():
    d = ParseMOF()
    if d == None:
        return None
    oplist=sys.argv[2:]
    for i in range(len(oplist)):
        oplist[i]=oplist[i][0].upper()+oplist[i][1:].lower()
    # loop until complete
    for op in oplist:
        for i in d.keys():
            d[i]['done']=False
        resultd=copy.deepcopy(d)
        curinst=list(d.keys())[0]
        cycle_countdown=len(d)
        while len(curinst):
            cycle_countdown-=1
            if cycle_countdown < -1:
                sys.stdout.write('Cycle count exceeded in ProcessMOF(), bailing out!')
                return None
            if 'DependsOn' in d[curinst].keys():
                if curinst == d[curinst]['DependsOn']:  #cannot depend on self
                    d[curinst].pop('DependsOn')
                else:
                    curinst=d[curinst]['DependsOn']
                    continue
            # no more DependsOn
            #strip out non-args before call
            resultd[curinst].pop('done')
            resultd[curinst].pop('module')
            resultd[curinst].pop('ResourceID')
            resultd[curinst].pop('ModuleName')
            resultd[curinst].pop('ModuleVersion')
            if 'DependsOn' in resultd[curinst].keys():
                resultd[curinst].pop('DependsOn')
            ret=CallMOF((op,d[curinst]['module'],resultd[curinst]))
            if ret == None:
                sys.stdout.write('Error in ProcessMOF(), bailing out!')
                return ret
            # save the Get
            if op == 'Get':
                WriteMOF(ret,curinst)
            # prune DependsOn for curinst
            for k in d.keys():
                if 'DependsOn' in d[k].keys():
                    if d[k]['DependsOn'] == curinst:
                        d[k].pop('DependsOn')
            d[curinst]['done']=True
            curinst=''
            for k in d.keys():
                if d[k]['done'] == False:
                    curinst=k
            continue
        # end while
    # end for
    return True       

def WriteMOF(retd,curinst):
    d = ParseMOF()
    for n in retd.keys():
        if type(retd[n]) is not bool and type(retd[n]) is not int:
            retd[n]=repr(retd[n])
            retd[n]=retd[n].replace("u'","'")
            retd[n]=retd[n].replace('u"','"')
        if n != 'ResourceID' and type(retd[n]) is not bool and type(retd[n]) is not int:
            retd[n]=retd[n].replace('[','{')
            retd[n]=retd[n].replace(']','}')
    txt='Instance of '+curinst+'_GetConfiguration\n{\n'
    for n in retd.keys():
        if type(retd[n]) is not bool and type(retd[n]) is not int:
            txt+='  '+n+' = '+retd[n]+';\n'
        else:
            txt+='  '+n+' = '+repr(retd[n])+';\n'
    txt+='};\n'
    txt=txt.replace("'",'"')
    txt=txt.replace('False','false')
    txt=txt.replace('True','true')
    sys.stdout.write(txt)
    return

def translate_protocol(d):
    oldStyleD = dict()
    if sys.version > '2.9':
        for key, value in d.items():
            if type(key) != str:
                key=str(key)
            if hasattr(value,'value') and hasattr(value.value,'value') :
                oldStyleD[key] = value.value.value
            else :
                oldStyleD[key] = value.value
    else:
        for key, value in d.iteritems():
            if type(key) != str:
                key=str(key)
            if hasattr(value,'value') and hasattr(value.value,'value') :
                oldStyleD[key] = value.value.value
            else:
                oldStyleD[key] = value.value
    return oldStyleD

                    
try:
    cur=os.path.realpath(os.curdir)
    if 'OMI_HOME' in os.environ.keys():
        prefix=os.environ['OMI_HOME']
    else:
        prefix='/opt/omi'
    os.chdir(prefix+'/lib/Scripts')
    sys.path.insert(0,'') # put the cwd in the path so we can find our module
    if sys.version < '2.6':
        os.chdir('./2.4x-2.5x')
    elif sys.version < '3':
        os.chdir('./2.6x-2.7x')
    else:
        os.chdir ('./3.x')
    from Scripts import *
    os.chdir(cur)
    if len(sys.argv)<3:
        sys.stdout.write('\nexec_dsc_mof.py <path_to_mof> <operation>...\ne.g.  exec_dsc_mof.py ./test.mof test set get\n')
    ret=ProcessMOF()
    if ret is None:
        sys.exit(1)
except:
    sys.stderr.write ('\nException: ')
    sys.stderr.write (repr(sys.exc_info())+'\n')
    traceback.print_tb (sys.exc_info()[2])
    sys.stderr.write ('\n')


