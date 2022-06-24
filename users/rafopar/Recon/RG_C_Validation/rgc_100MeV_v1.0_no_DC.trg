#########################################
# CLAS12 daq/trigger default config file #
##########################################

##############################
# TI settings (TI master only)
##############################

###################################
# FADC settings (detector-related)
###################################

# Common settings

FADC250_CRATE all
FADC250_SLOT	   all

# compression: 0-no compression, 1-compression, 2-both (verify mode)
FADC250_COMPRESSION  1

FADC250_MODE         1
##FADC250_W_OFFSET  7900
FADC250_W_OFFSET  7650
FADC250_W_WIDTH	   384
FADC250_CRATE end

TDC1190_CRATE all
TDC1190_SLOT all
TDC1190_W_WIDTH   800 
TDC1190_W_OFFSET -8450
TDC1190_CRATE end

TDC1190_CRATE tdcctof1
TDC1190_SLOT all
TDC1190_W_WIDTH   800 
TDC1190_W_OFFSET -8250
TDC1190_CRATE end

TDC1190_CRATE adccnd1
TDC1190_SLOT all
TDC1190_W_WIDTH   800 
TDC1190_W_OFFSET -8200
TDC1190_CRATE end



VSCM_CRATE all
VSCM_SLOT all
##VSCM_TRIG_WINDOW     96      1064        16 
##VSCM_TRIG_WINDOW     96      1032        16 
##VSCM_TRIG_WINDOW     96      968        16 
##VSCM_TRIG_WINDOW     80      976        16 
#VSCM_TRIG_WINDOW     80      980        16
#VSCM_TRIG_WINDOW     80      978        16
#VSCM_TRIG_WINDOW     80      979        16
VSCM_TRIG_WINDOW     64      979        16
VSCM_CRATE end

DCRB_CRATE all
DCRB_SLOT all
##DCRB_W_OFFSET  7900
DCRB_W_OFFSET  7650
DCRB_CRATE end



#does not work yet !!!!!!!
#SSP_CRATE       rich4
#SSP_SLOT        all
#SSP_RICH_W_WIDTH    300
#SSP_RICH_W_OFFSET  7980
#SSP_CRATE end



#######################################################
#
#######################################################

# ECAL settings
#include trigger/EC/ecal_default.cnf
include trigger/EC/ecal_newgain_prod.cnf

# PCAL settings
#include trigger/EC/pcal_default.cnf
include trigger/EC/pcal_newgain_prod.cnf

# FTOF settings
include trigger/FTOF/ftof_default.cnf

# LTCC settings
include trigger/LTCC/ltcc_default.cnf

# CTOF/HTCC settings
include trigger/CTOF_HTCC/ctof_htcc_prod.cnf

# CND settings
include trigger/CND/cnd_prod.cnf

#FT CAL AND HODO
include trigger/FT/ft_default.cnf

#SVT
include trigger/SVT/svt_prod.trg

#BAND
include trigger/BAND/band_default_prod.cnf

#######################################
# Trigger stage 1 (crates with FADCs) #
#######################################

# ECAL
VTP_CRATE adcecal1vtp
  include trigger/VTP/ecalvtp_low_thres.cnf
VTP_CRATE end

VTP_CRATE adcecal2vtp
  include trigger/VTP/ecalvtp_low_thres.cnf
VTP_CRATE end

VTP_CRATE adcecal3vtp
  include trigger/VTP/ecalvtp_low_thres.cnf
VTP_CRATE end

VTP_CRATE adcecal4vtp
  include trigger/VTP/ecalvtp_low_thres.cnf
VTP_CRATE end

VTP_CRATE adcecal5vtp
  include trigger/VTP/ecalvtp_low_thres.cnf
VTP_CRATE end

VTP_CRATE adcecal6vtp
  include trigger/VTP/ecalvtp_low_thres.cnf
VTP_CRATE end

# PCAL
VTP_CRATE adcpcal1vtp
  include trigger/VTP/pcalvtp_low_thres.cnf
  include trigger/VTP/pcuvtp_default.cnf
VTP_CRATE end

VTP_CRATE adcpcal2vtp
  include trigger/VTP/pcalvtp_low_thres.cnf
  include trigger/VTP/pcuvtp_default.cnf
VTP_CRATE end

VTP_CRATE adcpcal3vtp
  include trigger/VTP/pcalvtp_low_thres.cnf
  include trigger/VTP/pcuvtp_default.cnf
VTP_CRATE end

VTP_CRATE adcpcal4vtp
  include trigger/VTP/pcalvtp_low_thres.cnf
  include trigger/VTP/pcuvtp_default.cnf
VTP_CRATE end

VTP_CRATE adcpcal5vtp
  include trigger/VTP/pcalvtp_low_thres.cnf
  include trigger/VTP/pcuvtp_default.cnf
VTP_CRATE end

VTP_CRATE adcpcal6vtp
  include trigger/VTP/pcalvtp_low_thres.cnf
  include trigger/VTP/pcuvtp_default.cnf
VTP_CRATE end
#
# HTCC
#
VTP_CRATE adcctof1vtp
  include trigger/VTP/htcc_prod_2phe.cnf
VTP_CRATE end

#FT (3 VTPs inside the file)
include trigger/VTP/ftvtp_prod.cnf

# FTOF
VTP_CRATE adcftof1vtp
  include trigger/VTP/ftofvtp_prod.cnf
VTP_CRATE end
VTP_CRATE adcftof2vtp
  include trigger/VTP/ftofvtp_prod.cnf
VTP_CRATE end
VTP_CRATE adcftof3vtp
  include trigger/VTP/ftofvtp_prod.cnf
VTP_CRATE end
VTP_CRATE adcftof4vtp
  include trigger/VTP/ftofvtp_prod.cnf
VTP_CRATE end
VTP_CRATE adcftof5vtp
  include trigger/VTP/ftofvtp_prod.cnf
VTP_CRATE end
VTP_CRATE adcftof6vtp
  include trigger/VTP/ftofvtp_prod.cnf
VTP_CRATE end

# CTOF
VTP_CRATE adcctof1vtp
  include trigger/VTP/ctofvtp_prod.cnf
VTP_CRATE end

# CND
VTP_CRATE adccnd1vtp
  include trigger/VTP/cndvtp_prod.cnf
VTP_CRATE end


#################################
# Trigger stage 2 (crate trig2) #
#################################

SSP_CRATE trig2
SSP_SLOT all

SSP_W_OFFSET 7650
SSP_W_WIDTH  400

# 'SSP_GT_' - sectors trigger logic

SSP_GT_LATENCY            5000

#SSP_GT_HTCC_DELAY           1164
SSP_GT_HTCC_DELAY           1132
SSP_GT_ECAL_CLUSTER_DELAY   1024
SSP_GT_PCAL_CLUSTER_DELAY   1024
SSP_GT_CTOF_DELAY           1236
SSP_GT_CND_DELAY            1244
SSP_GT_FTOF_DELAY           1104
SSP_GT_PCAL_PCU_DELAY       1068


# if use this, add 1024 to all above and SSP_GTC_FT_CLUSTER_DELAY below,
# subtract same from VTP_GT_LATENCY and VTP_W_OFFSET
SSP_GT_DC_SEG_DELAY         0

# ECAL+PCAL cluster sum coincidence width
SSP_GT_ECPC_WIDTH           96

# DCxPCAL matching: cluster coincidence width and minimum energy
SSP_GT_DCPCAL_PCAL_WIDTH    96
SSP_GT_DCPCAL_PCAL_EMIN    600

#pcu
SSP_GT_FTOFPCU_FTOF_WIDTH    32
SSP_GT_FTOFPCU_PCU_WIDTH     32
SSP_GT_FTOFPCU_MATCH_TABLE    0		# 0 is the old map, 1 is the new map Andrea provided after the last run


# 'SSP_GT_STRG_' - sector trigger bits - logic inside single sector

#################
#                       Electron NO DC ROADS  
# Sector Trigger bit 0  STRG0: HTCC x (PCAL+ECAL)>100MeV x PCAL>60MeV
#   
#################
SSP_GT_STRG                           0
SSP_GT_STRG_EN                        1

# HTCC trigger logic
SSP_GT_STRG_HTCC_EN                   1
SSP_GT_STRG_HTCC_WIDTH                0

# PCAL cluster trigger logic
SSP_GT_STRG_PCAL_CLUSTER_EMIN_EN      1
SSP_GT_STRG_PCAL_CLUSTER_EMIN       600
SSP_GT_STRG_PCAL_CLUSTER_WIDTH       96

# PCAL+ECAL cluster trigger logic: EMIN in 0.1MeV units

SSP_GT_STRG_ECALPCAL_CLUSTER_EMIN_EN      1
SSP_GT_STRG_ECALPCAL_CLUSTER_EMIN      1000

#################
#                      electron/poitron INBENDING with DC ROADS
# Sector Trigger bit 1 STRG1 (DCROADxPCALU) x HTCC x (PCAL+ECAL)>300MeV x PCAL>60MeV
# 
##################
SSP_GT_STRG                           1
SSP_GT_STRG_EN                        1

# HTCC trigger logic
SSP_GT_STRG_HTCC_EN                   1
SSP_GT_STRG_HTCC_WIDTH                0

# PCAL cluster trigger logic
SSP_GT_STRG_PCAL_CLUSTER_EMIN_EN      1
SSP_GT_STRG_PCAL_CLUSTER_EMIN       600
SSP_GT_STRG_PCAL_CLUSTER_WIDTH       96

# PCAL+ECAL cluster trigger logic: EMIN in 0.1MeV units
SSP_GT_STRG_ECALPCAL_CLUSTER_EMIN_EN      1
SSP_GT_STRG_ECALPCAL_CLUSTER_EMIN       3000

#DCROADxPCALClusterU
SSP_GT_STRG_DCPCAL_EN                 1

#################
#                      electron/positron outbending with DC roads
# Sector Trigger bit 2 STRG2 DCROAD x HTCC x (PCAL+ECAL)>300MeV x PCAL>60MeV
# 
##################
SSP_GT_STRG                           2
SSP_GT_STRG_EN                        1

# HTCC trigger logic
SSP_GT_STRG_HTCC_EN                   1
SSP_GT_STRG_HTCC_WIDTH                0

# PCAL cluster trigger logic
SSP_GT_STRG_PCAL_CLUSTER_EMIN_EN      1
SSP_GT_STRG_PCAL_CLUSTER_EMIN       600
SSP_GT_STRG_PCAL_CLUSTER_WIDTH       96

# PCAL+ECAL cluster trigger logic: EMIN in 0.1MeV units
SSP_GT_STRG_ECALPCAL_CLUSTER_EMIN_EN      1
SSP_GT_STRG_ECALPCAL_CLUSTER_EMIN      3000

# DC ROAD outbending
SSP_GT_STRG_DC_EN                     1
SSP_GT_STRG_DC_ROAD_REQUIRED          0
SSP_GT_STRG_DC_ROAD_INBEND_REQUIRED   0
SSP_GT_STRG_DC_ROAD_OUTBEND_REQUIRED  1
SSP_GT_STRG_DC_MULT_MIN               5
SSP_GT_STRG_DC_WIDTH                 32

#################
#                      MUON TRIGGER
#
# Sector Trigger bit 6 STRG6: FTOFPCU=+/-5 x PCAL=(10)MeV x ECAL=(40)MeV
# 
#################
SSP_GT_STRG                           6
SSP_GT_STRG_EN                        1

# PCU trigger logic
SSP_GT_STRG_FTOFPCU_EN                1
SSP_GT_STRG_FTOFPCU_WIDTH             0
SSP_GT_STRG_FTOFPCU_MATCH_MASK       32

# PCAL cluster trigger logic: EMIN in 0.1 MeV units
SSP_GT_STRG_PCAL_CLUSTER_EMIN_EN          1
SSP_GT_STRG_PCAL_CLUSTER_EMIN           100
SSP_GT_STRG_PCAL_CLUSTER_WIDTH           96

# ECAL cluster trigger logic: EMIN in 0.1MeV units
SSP_GT_STRG_ECAL_CLUSTER_EMIN_EN          1
SSP_GT_STRG_ECAL_CLUSTER_EMIN           400
SSP_GT_STRG_ECAL_CLUSTER_WIDTH           96

#################
#
# Sector Trigger bit 7 STRG7: FTOFxPCALU
#
#################
SSP_GT_STRG                           7
SSP_GT_STRG_EN                        1

# PCU trigger logic
SSP_GT_STRG_FTOFPCU_EN                1
SSP_GT_STRG_FTOFPCU_WIDTH             0
SSP_GT_STRG_FTOFPCU_MATCH_MASK        1

#######################################
#
# 'SSP_GTC_' - central detectors logic
#
#######################################

SSP_GTC_LATENCY           5000

SSP_GTC_FT_ESUM_DELAY     0
SSP_GTC_FT_CLUSTER_DELAY  1180
SSP_GTC_FT_ESUM_INTWIDTH  0

SSP_GTC_FANOUT_ENABLE_CTOFHTCC 1
SSP_GTC_FANOUT_ENABLE_CND      1

###################################################
# 'SSP_GTC_CTRG_' - central detectors trigger bits
###################################################

###################
# Central Trigger bit 0    CTRG0: CTOF
###################
SSP_GTC_CTRG                       0
SSP_GTC_CTRG_EN                    1
SSP_GTC_CTRG_CTOF_EN               1
SSP_GTC_CTRG_CTOF_WIDTH            64

###################
# Central Trigger bit 1    CTRG1:  FT(500-8500) 2 clusters 
###################
#SSP_GTC_CTRG                       1
#SSP_GTC_CTRG_EN                    1

###################
# Central Trigger bit 2    CTRG2:  FT(100-16000)
###################
#SSP_GTC_CTRG                       2
#SSP_GTC_CTRG_EN                    1

###################
# Central Trigger bit 3    CTRG3:  FT(500-8500) 3 clusters
###################
#SSP_GTC_CTRG                       3
#SSP_GTC_CTRG_EN                    1

SSP_CRATE end


########################################
# Trigger stage 3 (vtp in trig2 crate) #
########################################

VTP_CRATE trig2vtp

##VTP_W_OFFSET 7900
#VTP_W_OFFSET 7650
VTP_W_OFFSET 6624
VTP_W_WIDTH   400

#        slot: 10 13  9 14  8 15  7 16  6 17  5 18  4 19  3 20
#     payload:  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
VTP_PAYLOAD_EN  0  0  1  0  1  0  1  0  1  0  1  0  1  0  1  0


# global latency
##VTP_GT_LATENCY 6450
VTP_GT_LATENCY 5420


VTP_GT_WIDTH   16

# TRIGGER BITS: 
#               trig number 
#               |
#               |   ssp trig mask 0       ###############
#               |   |   ssp sector mask 0 # Condition 0 #
#               |   |   |  multiplicity 0 ###############
#               |   |   |  |
#               |   |   |  |    ssp trig mask 1      #######################################################
#               |   |   |  |    |  ssp sector mask 1 # Condition 1 - used for VTP_GT_TRG2 definition types #
#               |   |   |  |    |  |  multiplicity 1 #######################################################
#               |   |   |  |    |  |  |
#               |   |   |  |    |  |  |    coincidence=#extended_clock_cycles 
#               |   |   |  |    |  |  |    |  ssp central trig mask
#               |   |   |  |    |  |  |    |  |  delay(in 4ns ticks)
#               |   |   |  |    |  |  |    |  |  |   prescaler (0=disable, 1-65535=divider)
#               |   |   |  |    |  |  |    |  |  |   |

################################
# Physics Triggers
################################

# electron/positron inbending with DC roads
VTP_GT_TRGBIT   0   2  63  1               1  0  0   0  #  STRG1, SECTOR 1-6
VTP_GT_TRGBIT   1   2   1  1               1  0  0   0  #  STRG1, SECTOR 1
VTP_GT_TRGBIT   2   2   2  1               1  0  0   0  #  STRG1, SECTOR 2
VTP_GT_TRGBIT   3   2   4  1               1  0  0   0  #  STRG1, SECTOR 3
VTP_GT_TRGBIT   4   2   8  1               1  0  0   0  #  STRG1, SECTOR 4
VTP_GT_TRGBIT   5   2  16  1               1  0  0   0  #  STRG1, SECTOR 5
VTP_GT_TRGBIT   6   2  32  1               1  0  0   0  #  STRG1, SECTOR 6

# electron/positron oubending with DC roads
VTP_GT_TRGBIT   7   4  63  1               1  0  0   0  #  STRG2, SECTOR 1-6
VTP_GT_TRGBIT   8   4   1  1               1  0  0   0  #  STRG2, SECTOR 1
VTP_GT_TRGBIT   9   4   2  1               1  0  0   0  #  STRG2, SECTOR 2
VTP_GT_TRGBIT  10   4   4  1               1  0  0   0  #  STRG2, SECTOR 3
VTP_GT_TRGBIT  11   4   8  1               1  0  0   0  #  STRG2, SECTOR 4
VTP_GT_TRGBIT  12   4  16  1               1  0  0   0  #  STRG2, SECTOR 5
VTP_GT_TRGBIT  13   4  32  1               1  0  0   0  #  STRG2, SECTOR 6
 
# electron/positron,  NO DC roads
VTP_GT_TRGBIT  14   1  63  1               1  0  0   1  #  STRG0, SECTOR 1-6
VTP_GT_TRGBIT  15   1   1  1               1  0  0   1  #  STRG0, SECTOR 1
VTP_GT_TRGBIT  16   1   2  1               1  0  0   1  #  STRG0, SECTOR 2
VTP_GT_TRGBIT  17   1   4  1               1  0  0   1  #  STRG0, SECTOR 3
VTP_GT_TRGBIT  18   1   8  1               1  0  0   1  #  STRG0, SECTOR 4
VTP_GT_TRGBIT  19   1  16  1               1  0  0   1  #  STRG0, SECTOR 5
VTP_GT_TRGBIT  20   1  32  1               1  0  0   1  #  STRG0, SECTOR 6

# FTOF x PCAL=(>10eV x ECAL=(>40)MeV  MUON TRIGGER
VTP_GT_TRGBIT  21  64   9  2              17  0  6   0  #  STRG6, SECTOR 1 & 4
VTP_GT_TRGBIT  22  64  18  2              17  0  6   0  #  STRG6, SECTOR 2 & 5
VTP_GT_TRGBIT  23  64  36  2              17  0  6   0  #  STRG6, SECTOR 3 & 6

# Central Trigger CTOF
VTP_GT_TRGBIT  24   0  63  1               0  1  0    0  #  CTRG0,  CTOF

# FTOFxPCU
VTP_GT_TRGBIT  30 128  63  1               1  0  6    0  #  STRG7, All sectors

# PULSER
VTP_GT_TRG     31
VTP_GT_TRG_PULSER_FREQ 100.0

############################
# Trigger names
############################

VTP_GT_TRGBIT_NAMES   0   Inbending_S1-6  Inbending_electron_or_positron_Sector1-6
VTP_GT_TRGBIT_NAMES   1   Inbending_S1    Inbending_electron_or_positron_Sector1
VTP_GT_TRGBIT_NAMES   2   Inbending_S2    Inbending_electron_or_positron_Sector2
VTP_GT_TRGBIT_NAMES   3   Inbending_S3    Inbending_electron_or_positron_Sector3
VTP_GT_TRGBIT_NAMES   4   Inbending_S4    Inbending_electron_or_positron_Sector4
VTP_GT_TRGBIT_NAMES   5   Inbending_S5    Inbending_electron_or_positron_Sector5
VTP_GT_TRGBIT_NAMES   6   Inbending_S6    Inbending_electron_or_positron_Sector6

VTP_GT_TRGBIT_NAMES   7   Outbending_S1-6 Outbending_electron_or_positron_Sector1-6
VTP_GT_TRGBIT_NAMES   8   Outbending_S1   Outbending_electron_or_positron_Sector1
VTP_GT_TRGBIT_NAMES   9   Outbending_S2   Outbending_electron_or_positron_Sector2
VTP_GT_TRGBIT_NAMES  10   Outbending_S3   Outbending_electron_or_positron_Sector3
VTP_GT_TRGBIT_NAMES  11   Outbending_S4   Outbending_electron_or_positron_Sector4
VTP_GT_TRGBIT_NAMES  12   Outbending_S5   Outbending_electron_or_positron_Sector5
VTP_GT_TRGBIT_NAMES  13   Outbending_S6   Outbending_electron_or_positron_Sector6

VTP_GT_TRGBIT_NAMES  14   No_DC_S1-6      Outbending_electron_or_positron_Sector1-6
VTP_GT_TRGBIT_NAMES  15   No_DC_S1        Outbending_electron_or_positron_Sector1
VTP_GT_TRGBIT_NAMES  16   No_DC_S2        Outbending_electron_or_positron_Sector2
VTP_GT_TRGBIT_NAMES  17   No_DC_S3        Outbending_electron_or_positron_Sector3
VTP_GT_TRGBIT_NAMES  18   No_DC_S4        Outbending_electron_or_positron_Sector4
VTP_GT_TRGBIT_NAMES  19   No_Dc_S5        Outbending_electron_or_positron_Sector5
VTP_GT_TRGBIT_NAMES  20   No_DC_S6        Outbending_electron_or_positron_Sector6

VTP_GT_TRGBIT_NAMES  21   Muons_S1-4      Muons_Sectors_1-4
VTP_GT_TRGBIT_NAMES  22   Muons_S2-5      Muons_Sectors_2-5
VTP_GT_TRGBIT_NAMES  23   Muons_S3-6      Muons_Sectors_3-6

VTP_GT_TRGBIT_NAMES  24   CTOF             Central_CTOF

VTP_GT_TRGBIT_NAMES  30   FTOFxPCU_S1-6   FTOFxPCalU_Sector_1-6
VTP_GT_TRGBIT_NAMES  31   Pulser_100_Hz   Pulser_100_Hz

##################
# Trigger Flags           | View in the trigger GUI (=1)
##################           | Sum in the total trigger rate (=1)

VTP_GT_TRGBIT_FLAGS   0   0  0
VTP_GT_TRGBIT_FLAGS   1   0  0
VTP_GT_TRGBIT_FLAGS   2   0  0
VTP_GT_TRGBIT_FLAGS   3   0  0
VTP_GT_TRGBIT_FLAGS   4   0  0
VTP_GT_TRGBIT_FLAGS   5   0  0
VTP_GT_TRGBIT_FLAGS   6   0  0

VTP_GT_TRGBIT_FLAGS   7   0  0
VTP_GT_TRGBIT_FLAGS   8   0  0
VTP_GT_TRGBIT_FLAGS   9   0  0
VTP_GT_TRGBIT_FLAGS  10   0  0
VTP_GT_TRGBIT_FLAGS  11   0  0
VTP_GT_TRGBIT_FLAGS  12   0  0
VTP_GT_TRGBIT_FLAGS  13   0  0

VTP_GT_TRGBIT_FLAGS  14   1  1
VTP_GT_TRGBIT_FLAGS  15   1  0
VTP_GT_TRGBIT_FLAGS  16   1  0
VTP_GT_TRGBIT_FLAGS  17   1  0
VTP_GT_TRGBIT_FLAGS  18   1  0
VTP_GT_TRGBIT_FLAGS  19   1  0
VTP_GT_TRGBIT_FLAGS  20   1  0

VTP_GT_TRGBIT_FLAGS  21   0  0
VTP_GT_TRGBIT_FLAGS  22   0  0
VTP_GT_TRGBIT_FLAGS  23   0  0

VTP_GT_TRGBIT_FLAGS  24   0  0

VTP_GT_TRGBIT_FLAGS  30   0  0
VTP_GT_TRGBIT_FLAGS  31   1  1

VTP_CRATE end

############################
# TS settings (trig1 crate)
############################

TS_CRATE trig1
###      Open ONLY triger bits 14-20, 31
### TS_GTP_INPUT_MASK 0x801FC000

###      Open ALL trigers bits 
TS_GTP_INPUT_MASK 0x801FFFFF

#lock-roc mode
#TS_BLOCK_LEVEL  1
#TS_BUFFER_LEVEL 1

#NOTE: prescales and masks for GTP are set above in VTP_GT_TRGBIT lines
#Don't use the following anymore
#TS_GTP_INPUT_MASK 0x807FFFFF
#TS_GTP_PRESCALE  1   0    #   TriggerBit   0

TS_BLOCK_LEVEL   10
TS_BUFFER_LEVEL   8
#normal production: 5 5 15 10
TS_HOLDOFF   1  5 1
TS_HOLDOFF   2  5 1
TS_HOLDOFF   3 15 1
TS_HOLDOFF   4 10 1

####################
# TS FP trigger mask
####################
# 0x80  - FARADAY
# 0x100 - SVT or BAND
# 0x200 - CTOF
# 0x400 - CND
# 0x800 - MVT
# 0x1000 - helicity

#  Faraday cup only
 TS_FP_INPUT_MASK 0x00000080

#  BAND, Faraday cup
#TS_FP_INPUT_MASK 0x00000180



### BAND prescale
TS_FP_PRESCALE  9 4

### Faraday cup prescale
#                      |Front panel bit number starting from 1
#                      |  | Parameter "n" -->  Prescale=2^(n-1)+1
# parameter "n"        |  | 0 1 2 3 4  5  6  7   8   9  10   11   12   13   14    15
# prescale value       |  | 1 2 3 5 9 17 33 65 129 257 513 1025 2049 4097 8193 16385
TS_FP_PRESCALE         8  5


# First arg:      0-disable, 
#                 1-enable; 
#                 |   Prescale (15-7Hz, .., 7-3.5kHz, 6-7kHz, 5-15kHz, 4-30kHz, 3-60kHz)
#                 |   |
TS_RANDOM_TRIGGER 0   4

###########################################################
# Random Trigger Setting  30 kHz 
###########################################################
#!!! TS_FP_INPUT_MASK  0x00000000
#!!! TS_FP_PRESCALE    16 0
#!!! TS_RANDOM_TRIGGER 1 4
### TS GTP trigger inputs: disable all, so that we can enable all VTP outputs
###          TS will then be able record trigger type with these bits
#!!! TS_GTP_INPUT_MASK 0x0
#    AND SET ALL VTP_HPS_PRESCALE to 1 for ALL TRIGGERS !
##################################



TS_CRATE end
