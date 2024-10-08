#ifndef _GLOBAL_H_ // include guard
#define _GLOBAL_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_AA         15
#define MAX_CHAINTYPES 15
#define MAX_CHAINLEN   150
#define MAX_BONDS      15
#define MAX_VALENCY    150

// energy parameters
#define E_TOT   0 // index zero must be assigned for total energy
#define E_OVLP  1
#define E_CONT  2
#define E_SC_SC 3
#define E_F_SOL 4
#define E_T_IND 5
#define E_STIFF 6
#define MAX_E   7 // just for counting; must be the last number of this list

// MC move parameters
#define MV_NULL       0 // index zero indicates null move
#define MV_STROT      1
#define MV_LOCAL      2
#define MV_COLOCAL    3
#define MV_MTLOCAL    4
#define MV_SNAKE      5
#define MV_TRANS      6
#define MV_SMCLSTR    7
#define MV_CLSTR      8
#define MV_PIVOT      9
#define MV_BRROT      10
#define MV_DBPVT      11
#define MV_PR_SMCLSTR 12
#define MAX_MV        13 // just for counting; must be the last number of this list

// report parameters
#define REPORT_NULL    0 // index zero
#define REPORT_LOG     1
#define REPORT_ENERGY  2
#define REPORT_CONFIG  3
#define REPORT_MCMOVE  4
#define REPORT_NETWORK 5
#define REPORT_RDFTOT  6
#define REPORT_COMDEN  7
#define MAX_REPORT     8 // just for counting; must be the last number of this list

// auxiliary definitions
#define POS_X   0
#define POS_Y   1
#define POS_Z   2
#define POS_MAX 3

#define BEAD_CHAINID 3
#define BEAD_TYPE    4
#define BEAD_FACE    5
#define BEADINFO_MAX 6

#define CHAIN_TYPE    0
#define CHAIN_LENGTH  1
#define CHAIN_START   2
#define CHAININFO_MAX 3

#define MAX_ROTSTATES 27

typedef int lInt;
typedef long lLong;
typedef double lDub;
typedef long double lLDub;

// configurations and structural info

lInt** bead_info;
lInt** old_bead;
lInt** chain_info;
lInt** topo_info;
lInt** linker_len;

size_t tot_beads;
size_t tot_chains;
size_t tot_chain_types;
lInt nAnnealing_Mode, nTemp_inv;
lInt nInitialPotential_Mode, RotBias_Mode;

// system setup
lInt nBoxSize[POS_MAX];
lInt LocalArr[MAX_ROTSTATES - 1][3]; // Used to quickly iterate over nearby points in an R-cube
lInt Rot_IndArr[MAX_ROTSTATES - 1];
char bReadConf;
char bSystemHasTopo;
char bSystemHasCont;
char bSystemHasOvlp;
char bSystemHasFSol;
char bSystemHasSCSC;

// energy matrices for stickers
lInt nBeadTypes;
float fEnergy[MAX_AA][MAX_AA][MAX_E];
float fEnRad[MAX_AA][MAX_AA][MAX_E];
#define LARGEST_RADIUS 3
lInt rot_trial[MAX_VALENCY][MAX_ROTSTATES]; // Used in orientational-bias MC moves
lLDub bolt_fac[MAX_ROTSTATES - 1];          // Used in orientational-bias
lLDub bolt_norm[MAX_VALENCY];
lLDub dbias_bolt_fac[MAX_AA][MAX_AA]; // For pre-calculating the factors.
lLDub ld_LogOfSmallestPossibleProb;   // Smallest probability possible logl(1/RAND_MAX)

float faCurrEn[MAX_E];                // Vector for current energy

// Arrays to track certain topology and interaction information
lInt nBeadTypeIsSticker[MAX_AA];         // Used to track if that beadType interacts via rotations.
lInt nChainTypeIsLinear[MAX_CHAINTYPES]; // Used to track if this chainType is linear.
lInt nBeadTypeCanOvlp[MAX_AA];           // Used to track if a certain beadType has an overlap cost.
lInt nBeadTypeCanCont[MAX_AA];           // Used to track if a certain beadType has contact interactions
lInt nBeadTypeCanFSol[MAX_AA];           // Used to track if a certain beadType has solvation energies
lInt nBeadTypeCanTInd[MAX_AA];           // Used to track if a certain beadType has temperature independent solvation

float fLinkerLength;
float fLinkerSprCon;
float fLinkerEqLen;

// MC setup
float fKT, fPreKT, fCuTemp, fRot_Bias, f_globRotBias, fdelta_temp, fMC_Temp_Rate, fSquishRad, fSquishRad_Sq;
float* fKT_Cycle;
lLong nMCStepsPerCycle, nMCStepsForTherm;
float fMCFreq[MAX_MV];
lInt  nTot_CycleNum;

// random number generator nRNG_Seed
lInt nRNG_Seed;

// report-related
char strReportPrefix[512];
char fileEnergy[512];
char fileTraj[512];
char fileMCMove[512];
char fileSysProp[512];
char strRestartFile[512];
lLong nReport[MAX_REPORT]; // Array to store report frequencies.
lLong nTrajMode;
// Matrix to store acceptances and rejections 0: Rejected; 1: Accepted
// TODO: Have a more extensive way to record also where/when a particular move fails -- not just if it fails.
lLong naMCAccepMat[2][MAX_MV];

// Cluster analysis
lInt nClusteringMode;
lInt** naCluster;
lInt* naList;
lLong* naClusHistList;
lInt* naChainCheckList;
lInt nTotClusCounter;
lLDub** ld_TOTCLUS_Arr;
lLDub* ldMOLCLUS_Arr;
lLDub* ld_TOTMOLCLUS_Arr;
lInt naTempR[POS_MAX];
lInt nLargestClusterRightNow;
size_t nLimitedClusterSize;

// Neighor search
lInt* oldOvlpNeighs;
lInt* newOvlpNeighs;
lInt* oldContNeighs;
lInt* newContNeighs;

// Radial Densities and PDFs
lLDub* ld_TOTRDF_Arr;
lLDub* ld_TOTRadDen_Arr;
lLDub* ldRDF_Arr;
lLDub* ldRadDen_Arr;
lInt nRDF_TotComps;
lInt nRDFCounter; // This counts how many times the RDF has been calculated for averaging at the end.
lInt nRDF_TotBins;
lInt nRadDen_TotComps;
lInt nRadDen_CompShift;
lInt nRadDenCounter; // This counts for the Radial Density histograms

// Gyration tensor
float fGyrTensor[7]; // Gyration tensor
float fSysGyrRad;    // Gyration radius of the system.
lLDub** ld_TOTRg_Arr;
lInt nTotGyrRadCounter; // Counter for total averaging

// Trajectory Saving
lInt* n_TOTTRAJ_Arr;
lLong nTraj_FramesPerCycle;
lInt nTrajCurFrame;

// Lattice To Remember Things
lInt* naTotLattice;

#define LINKER_RSCALE 1.74f

#endif // _GLOBAL_H_
