#!/bin/tcsh                                                            
 
foreach jobDir (`ls ${1}`)
   
#echo "${jobDir}"
crab kill -d ${1}/${jobDir}
   
end
