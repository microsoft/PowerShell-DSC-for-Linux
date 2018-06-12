import json
from pprint import pprint
from subprocess import Popen, PIPE
proc = Popen("inspec exec /home/nitin/InSpecProfiles/linux-baseline --reporter=json-min:data.json", shell=True)
proc.wait()
data = json.load(open('data.json'))
#pprint(data)
pprint(data["version"])

pprint(data["statistics"]["duration"])
pprint(data["controls"][0]["code_desc"])
