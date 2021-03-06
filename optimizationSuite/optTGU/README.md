### optTGU
Belongs to package: `optimizationSuite`

Created: 2014-05-06, 13:49 CST

#### Overview:
Two-dimensional optimize the transverse gradient of undulator
('TGUalpha' in genesis input panel) and the transverse dispersion 
('itram16' in genesis input panel) for an free-electron laser. 

The script `optTGU_p.sh` is designed for parameters setup, distributing
work to multithreaded workers, by default all CPU cores would be called.

Script `optTGU.sh` is the main functional procedure for TGUalpha and 
itram16 optimization, the input parameters would be transferred from 
the main script `optTGU_p.sh`, all the workers would start to work.

When all the workers finished the job, main script `optTGU_p.sh`
would collect all the results data and merge into single file as the
final result. Further the optimized values would be figured out
and substitute the value in the input file.
