#!/bin/bash

temp=make_rootmap.$$.temp

rootlibmap() {
 ROOTMAP=$1
 SOFILE=$2
 LINKDEF=$3
 shift 3
 DEPS=$*
 if [[ -e $SOFILE && -e $LINKDEF ]]; then
     rlibmap -f -o $ROOTMAP -l $SOFILE -d $DEPS -c $LINKDEF 2>> $temp
     rm -f $temp
 fi
}

######################################################
# ShowerPdfTool
rootlibmap libSelectionTool_SPTApp.rootmap libSelectionTool_SPTApp.so \
    $LARLITE_USERDEVDIR/SelectionTool/ShowerPdfTool/SPTApp/LinkDef.h \
    libLArLite_Analysis.so \
    libSelectionTool_SPTBase.so












