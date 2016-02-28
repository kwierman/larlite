import sys,ROOT,os
import pdb

def pmt_pos():
    xv = ROOT.std.vector("double")()
    yv = ROOT.std.vector("double")()
    zv = ROOT.std.vector("double")()
    for line in open('opt_geo_fixed.txt','r').read().split('\n'):
        words = line.split()
        if not len(words) == 3: continue
        xv.push_back(float(words[0]))
        yv.push_back(float(words[1]))
        zv.push_back(float(words[2]))
    return (xv,yv,zv)

if len(sys.argv) < 2:
    msg  = '\n'
    msg += "Usage 1: %s $INPUT_ROOT_FILE(s)\n" % sys.argv[0]
    msg += '\n'
    sys.stderr.write(msg)
    sys.exit(1)

import ROOT
#ROOT.gSystem.Load("libOpFlashAna_OpT0FinderApp")
from larlite import larlite as fmwk
from ROOT import flashana

# Create ana_processor instance

my_proc = fmwk.ana_processor()

# Set input root file
for x in xrange(len(sys.argv)-1):
    print sys.argv[x+1]
    my_proc.add_input_file(sys.argv[x+1])

infile = sys.argv[1]
indir = infile.split('/')[-2]
np,x,y,z = ( int(indir.split('_')[1]),
             float(indir.split('_')[-3])/10.,
             float(indir.split('_')[-2])/10.,
             float(indir.split('_')[-1])/10.)

# Specify IO mode
my_proc.set_io_mode(fmwk.storage_manager.kREAD)

# Specify output root file name
my_proc.set_ana_output_file("ana.root")

# Attach an analysis unit ... here we use a base class which does nothing.
# Replace with your analysis unit if you wish.
my_unit = fmwk.UBT0Finder()
my_unit.SetEDiff(10.)
my_unit.UseMC(False)
my_unit.PhotonBomb(x,y,z,np);
my_unit.SetROStart(-3200.)
my_unit.SetROEnd(3200.)
my_unit.SetTrigTime(0.)
my_proc.add_process(my_unit)

# TPC Filter Algo
my_unit.Manager().SetAlgo(flashana.NPtFilter())
# PMT Filter Algo
my_unit.Manager().SetAlgo(flashana.MaxNPEWindow())
# Match Prohibit Algo
#my_unit.Manager().SetAlgo(flashana.TimeCompatMatch())
# Hypothesis Algo
my_unit.Manager().SetAlgo(flashana.PhotonLibHypothesis())
# Match Algo
#my_unit.Manager().SetAlgo( flashana.LLMatch.GetME() )
my_unit.Manager().SetAlgo( flashana.QLLMatch.GetME() )
#my_unit.Manager().SetAlgo( flashana.QWeightPoint()   )
#my_unit.Manager().SetAlgo( flashana.CommonAmps()      )

#
# Other algorithms
#

#my_unit.Manager().AddCustomAlgo( flashana.LightPath() )

my_unit.Manager().Configure( "%s/SelectionTool/OpT0Finder/App/mac/flashmatch.fcl" % os.environ['LARLITE_USERDEVDIR'])

print
print  "Finished configuring ana_processor. Start event loop!"
print

# Let's run it.
my_proc.run()

# done!
print
print "Finished running ana_processor event loop!"
print

sys.exit(0)
