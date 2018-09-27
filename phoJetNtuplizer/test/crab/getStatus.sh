#!/bin/tcsh                                                            
 
foreach jobDir (`ls ${1}`)
   
#echo "${jobDir}"
crab status -d ${1}/${jobDir}
   
end
