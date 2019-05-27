#! /bin/bash
# vim:ft=python
PYTHON_BIN="${PYTHON_BIN-python}"
PLUMED_PYTHON_BIN="${PLUMED_PYTHON_BIN-${PYTHON_BIN}}"
TEMP=$(mktemp -t plumed.XXXXXX)
trap "rm -rf $TEMP" EXIT
cat > $TEMP << \EOF
# here's the real script

from __future__ import print_function
import sys
import re
import readline

# When possible, we use python3 specific stuff
if (sys.version_info > (3, 0)):
   _HAS_PYTHON3=True
else:
   _HAS_PYTHON3=False

def read_mda(path):
    import MDAnalysis
    return MDAnalysis.Universe(path)

def read_mdt(path):
    import mdtraj
    return mdtraj.load(path).top

def read_vmd(path):
    import subprocess
    vmd = subprocess.Popen(["vmd", "-dispdev", "none",path,"-eofexit"],
          stdin=subprocess.PIPE, stdout=subprocess.PIPE,universal_newlines=True)
    # print("fconfigure stdout -buffering none",file=vmd.stdin) # does not work as expected
    vmd.stdin.flush()
    return vmd

dummyline="DUMMYLINE"

def select_vmd(vmd,selection):
    import os
    try:
        bufferlines=int(os.environ['PLUMED_VMD_BUFFERLINES'])
    except:
        bufferlines=1000
        
    print("puts 'NEXT'",file=vmd.stdin)
    print("[atomselect top { " + selection + " }] get index\n",file=vmd.stdin)
    for i in range(bufferlines):
      print("puts '"+dummyline+"'",file=vmd.stdin)
    # print("for {set i 1} {$i < 2000} {incr i} { puts '" + dummyline +"' }",file=vmd.stdin) # does not work
    print("flush stdout",file=vmd.stdin) # useless
    vmd.stdin.flush()
    is_next=False
    is_error=False
    error_msg=""
    for line in vmd.stdout:
        lines=line.rstrip()
        if is_error:
          if(lines=="'"+dummyline+"'"):
            raise RuntimeError(error_msg)
          error_msg+=" " + lines
        elif is_next:
          if re.match(".*ERROR.*",line):
            is_error=True
          else:
            sel=[]
            for w in line.split():
                if not w.isdigit():
                   sel=[]
                   break
                sel.append(int(w))
            return sel
        elif(lines=="'NEXT'"):
          is_next=True

path=None

mda=None
mdt=None
vmd=None

help="""
Example:
echo "
mda:nucleic
mdt:resname RG
" | selector.sh --pdb ref.pdb
"""


for i in range(1,len(sys.argv)):
  opt=sys.argv[i]
  if opt=="-h" or opt=="--help":
    print(help)
    sys.exit(0)
  elif opt=="--description":
    print("create lists of serial atom numbers")
    sys.exit(0)
  elif opt=="--options":
    print("--description --help -h --options --pdb")
    sys.exit(0)
  elif opt=="--pdb":
    path=sys.argv[i+1]

while True:
    try:
        if _HAS_PYTHON3:
            input_=input("")
        else:
            input_=raw_input("")
    except EOFError:
        break
    input_=re.sub("#.*","",input_)
    cmd=re.sub(":.*$","",input_)
    arg=re.sub("^[^:]*:","",input_)
    if cmd == "" :
      continue
    elif cmd == "quit" :
        sys.exit(0)
    elif cmd == "pdb" :
        path=arg
        mda=None
        mdt=None
        vmd=None
    else:
      if path is None:
           sys.stdout.write("Error: provide pdb file");
           sys.stdout.write("\n")
           sys.stdout.flush()
      if cmd == "mda" :
        if mda is None:
           mda=read_mda(path)
        try:
           sel=mda.select_atoms(arg).indices
        except Exception as e:
           sys.stdout.write("Error parsing MDAnalysis expression: ");
           sys.stdout.write(str(e));
           sys.stdout.write("\n")
           sys.stdout.flush()
           continue
      elif cmd == "mdt" :
        if mdt is None:
           mdt=read_mdt(path)
        try:
           sel=mdt.select(arg)
        except Exception as e:
           sys.stdout.write("Error parsing mdtraj expression: ");
           sys.stdout.write(str(e));
           sys.stdout.write("\n")
           sys.stdout.flush()
           continue
      elif cmd == "vmd" :
         if vmd is None:
           vmd=read_vmd(path)
         try:
           sel=select_vmd(vmd,arg)
         except Exception as e:
           sys.stdout.write("Error parsing vmd expression: ");
           sys.stdout.write(str(e));
           sys.stdout.write("\n")
           sys.stdout.flush()
           continue
      else:
         sys.stdout.write("Error: unknown command ")
         sys.stdout.write(cmd)
         sys.stdout.write("\n")
         sys.stdout.flush()
      outstr=""
      for i in range(len(sel)):
          if i>0:
              outstr+=" "
          outstr+=str(sel[i]+1)
      outstr+="\n"
      sys.stdout.write(outstr)
      sys.stdout.flush()

EOF

"${PLUMED_PYTHON_BIN}" $TEMP $@