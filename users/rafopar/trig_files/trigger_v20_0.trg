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
FADC250_MODE         1
FADC250_NSB         12
FADC250_NSA        156
FADC250_NPEAK        1
FADC250_DAC       3300
FADC250_TET         20
##FADC250_W_OFFSET  7900
FADC250_W_OFFSET  7650
FADC250_W_WIDTH	   400
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
include trigger/CTOF_HTCC/ctof_htcc_newgain_prod.cnf

# CND settings
include trigger/CND/cnd_prod.cnf

#FT CAL AND HODO
include trigger/FT/ft_default.cnf

#SVT
include trigger/SVT/svt_prod.trg

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

##SSP_W_OFFSET 7900
SSP_W_OFFSET 7650
SSP_W_WIDTH  400

# 'SSP_GT_' - sectors trigger logic

SSP_GT_LATENCY            5000


#SSP_GT_HTCC_DELAY         140
#SSP_GT_FTOF_DELAY          80
#SSP_GT_ECAL_CLUSTER_DELAY   0
#SSP_GT_PCAL_CLUSTER_DELAY   0
#SSP_GT_CTOF_DELAY          212
#SSP_GT_CND_DELAY           220
#SSP_GT_PCAL_PCU_DELAY      76

SSP_GT_HTCC_DELAY           1164
SSP_GT_ECAL_CLUSTER_DELAY   1024
SSP_GT_PCAL_CLUSTER_DELAY   1024
SSP_GT_CTOF_DELAY           1236
SSP_GT_CND_DELAY            1244
SSP_GT_FTOF_DELAY           1104
SSP_GT_PCAL_PCU_DELAY       1068


# if use this, add 1024 to all above and SSP_GTC_FT_CLUSTER_DELAY below,
# subtract same from VTP_GT_LATENCY and VTP_W_OFFSET
SSP_GT_DC_SEG_DELAY         0



#pcu
SSP_GT_FTOFPCU_FTOF_WIDTH    32
SSP_GT_FTOFPCU_PCU_WIDTH     32
SSP_GT_FTOFPCU_MATCH_TABLE    0		# 0 is the old map, 1 is the new map Andrea provided after the last run


# 'SSP_GT_STRG_' - sector trigger bits - logic inside single sector

########################
#
# Sector Trigger bit 0 
#
#   DC x HTCC x (PCAL+ECAL)>300MeV x PCAL>60MeV x ECAL>10MeV
########################
SSP_GT_STRG                           0
SSP_GT_STRG_EN                        1

# HTCC trigger logic
SSP_GT_STRG_HTCC_EN                   1
SSP_SLOT 3      # sector 1 SSP
SSP_GT_STRG_HTCC_MASK                 0x0000000000FF
SSP_SLOT 4      # sector 2 SSP
SSP_GT_STRG_HTCC_MASK                 0x00000000FF00
SSP_SLOT 5      # sector 3 SSP
SSP_GT_STRG_HTCC_MASK                 0x000000FF0000
SSP_SLOT 6      # sector 4 SSP
SSP_GT_STRG_HTCC_MASK                 0x0000FF000000
SSP_SLOT 7      # sector 5 SSP
SSP_GT_STRG_HTCC_MASK                 0x00FF00000000
SSP_SLOT 8      # sector 6 SSP
SSP_GT_STRG_HTCC_MASK                 0xFF0000000000
SSP_SLOT all
SSP_GT_STRG_HTCC_WIDTH                0

# PCAL cluster trigger logic
SSP_GT_STRG_PCAL_CLUSTER_EMIN_EN      1
SSP_GT_STRG_PCAL_CLUSTER_EMIN       600
SSP_GT_STRG_PCAL_CLUSTER_WIDTH       96

# ECAL cluster trigger logic
SSP_GT_STRG_ECAL_CLUSTER_EMIN_EN      1
SSP_GT_STRG_ECAL_CLUSTER_EMIN       100
SSP_GT_STRG_ECAL_CLUSTER_WIDTH       96

# PCAL+ECAL cluster trigger logic: EMIN in 0.1MeV units
SSP_GT_STRG_ECALPCAL_CLUSTER_EMIN_EN      1
SSP_GT_STRG_ECALPCAL_CLUSTER_EMIN      3000
SSP_GT_STRG_ECALPCAL_CLUSTER_WIDTH       96

# DC
# OLD DC Syntax
#SSP_GT_STRG_DC_MULT_EN                1
#SSP_GT_STRG_DC_MULT_MIN               3
#SSP_GT_STRG_DC_MULT_WIDTH            32

# new DC Syntax
SSP_GT_STRG_DC_EN                     1
SSP_GT_STRG_DC_ROAD_REQUIRED          0
SSP_GT_STRG_DC_ROAD_INBEND_REQUIRED   0
SSP_GT_STRG_DC_ROAD_OUTBEND_REQUIRED  0
SSP_GT_STRG_DC_MULT_MIN               3
SSP_GT_STRG_DC_WIDTH                 32



########################
#
# Sector Trigger bit 1 
#
#    DC x HTCC x PCAL>300MeV
########################
SSP_GT_STRG                           1
SSP_GT_STRG_EN                        1

# HTCC trigger logic
SSP_GT_STRG_HTCC_EN                   1
SSP_SLOT 3      # sector 1 SSP
SSP_GT_STRG_HTCC_MASK                 0x0000000000FF
SSP_SLOT 4      # sector 2 SSP
SSP_GT_STRG_HTCC_MASK                 0x00000000FF00
SSP_SLOT 5      # sector 3 SSP
SSP_GT_STRG_HTCC_MASK                 0x000000FF0000
SSP_SLOT 6      # sector 4 SSP
SSP_GT_STRG_HTCC_MASK                 0x0000FF000000
SSP_SLOT 7      # sector 5 SSP
SSP_GT_STRG_HTCC_MASK                 0x00FF00000000
SSP_SLOT 8      # sector 6 SSP
SSP_GT_STRG_HTCC_MASK                 0xFF0000000000
SSP_SLOT all
SSP_GT_STRG_HTCC_WIDTH                0

# PCAL cluster trigger logic
SSP_GT_STRG_PCAL_CLUSTER_EMIN_EN      1
SSP_GT_STRG_PCAL_CLUSTER_EMIN      3000
SSP_GT_STRG_PCAL_CLUSTER_WIDTH       96

# new DC Syntax
SSP_GT_STRG_DC_EN                     1
SSP_GT_STRG_DC_ROAD_REQUIRED          0
SSP_GT_STRG_DC_ROAD_INBEND_REQUIRED   0
SSP_GT_STRG_DC_ROAD_OUTBEND_REQUIRED  0
SSP_GT_STRG_DC_MULT_MIN               3
SSP_GT_STRG_DC_WIDTH                 32


########################
#
# Sector Trigger bit 2 
#
#    DC x FTOFPCU x PCAL>15 MeV
########################
SSP_GT_STRG                           2
SSP_GT_STRG_EN                        1

# PCU trigger logic
SSP_GT_STRG_FTOFPCU_EN                1
SSP_GT_STRG_FTOFPCU_WIDTH            64
SSP_GT_STRG_FTOFPCU_MATCH_MASK        8

# SSP_GT_STRG_FTOFPCU_MATCH_MASK   N
# N: 1 = +/-0 FTOF strip tolerance
#    2 = +/-1 FTOF strip tolerance
#    4 = +/-2 FTOF strip tolerance
#    8 = +/-3 FTOF strip tolerance
#   16 = +/-4 FTOF strip tolerance
#   32 = +/-5 FTOF strip tolerance


# PCAL cluster trigger logic
SSP_GT_STRG_PCAL_CLUSTER_EMIN_EN      1
SSP_GT_STRG_PCAL_CLUSTER_EMIN       150
SSP_GT_STRG_PCAL_CLUSTER_WIDTH       96

# new DC Syntax
SSP_GT_STRG_DC_EN                     1
SSP_GT_STRG_DC_ROAD_REQUIRED          0
SSP_GT_STRG_DC_ROAD_INBEND_REQUIRED   0
SSP_GT_STRG_DC_ROAD_OUTBEND_REQUIRED  0
SSP_GT_STRG_DC_MULT_MIN               3
SSP_GT_STRG_DC_WIDTH                 32



########################
#
# Sector Trigger bit 3 
#
# DC x FTOFPCU x PCAL>15 MeV x PCAL < 60 MeV x ECAL>40 MeV x ECAL < 120 MeV , This is Muon trigger
########################
SSP_GT_STRG                           3
SSP_GT_STRG_EN                        1

# PCU trigger logic
SSP_GT_STRG_FTOFPCU_EN                1
SSP_GT_STRG_FTOFPCU_WIDTH            16
SSP_GT_STRG_FTOFPCU_MATCH_MASK        8

# SSP_GT_STRG_FTOFPCU_MATCH_MASK   N
# N: 1 = +/-0 FTOF strip tolerance
#    2 = +/-1 FTOF strip tolerance
#    4 = +/-2 FTOF strip tolerance
#    8 = +/-3 FTOF strip tolerance
#   16 = +/-4 FTOF strip tolerance
#   32 = +/-5 FTOF strip tolerance

# PCAL cluster trigger logic: EMIN in 0.1 MeV units
SSP_GT_STRG_PCAL_CLUSTER_EMIN_EN          1
SSP_GT_STRG_PCAL_CLUSTER_EMIN           150
SSP_GT_STRG_PCAL_CLUSTER_EMAX           600
SSP_GT_STRG_PCAL_CLUSTER_WIDTH           96

# ECAL cluster trigger logic: EMIN in 0.1MeV units
SSP_GT_STRG_ECAL_CLUSTER_EMIN_EN          1
SSP_GT_STRG_ECAL_CLUSTER_EMIN           400
SSP_GT_STRG_ECAL_CLUSTER_EMAX          1200
SSP_GT_STRG_ECAL_CLUSTER_WIDTH           96

# new DC Syntax
SSP_GT_STRG_DC_EN                     1
SSP_GT_STRG_DC_ROAD_REQUIRED          0
SSP_GT_STRG_DC_ROAD_INBEND_REQUIRED   0
SSP_GT_STRG_DC_ROAD_OUTBEND_REQUIRED  0
SSP_GT_STRG_DC_MULT_MIN               3
SSP_GT_STRG_DC_WIDTH                 32


########################
#
# Sector Trigger bit 4 #
#
# DC x FTOFPCU x PCAL>15 MeV x CTOF
########################
SSP_GT_STRG                           4
SSP_GT_STRG_EN                        1

# PCU trigger logic
SSP_GT_STRG_FTOFPCU_EN                1
SSP_GT_STRG_FTOFPCU_WIDTH            64
SSP_GT_STRG_FTOFPCU_MATCH_MASK        8

# SSP_GT_STRG_FTOFPCU_MATCH_MASK   N
# N: 1 = +/-0 FTOF strip tolerance
#    2 = +/-1 FTOF strip tolerance
#    4 = +/-2 FTOF strip tolerance
#    8 = +/-3 FTOF strip tolerance
#   16 = +/-4 FTOF strip tolerance
#   32 = +/-5 FTOF strip tolerance

# PCAL cluster trigger logic: EMIN in 0.1MeV units
SSP_GT_STRG_PCAL_CLUSTER_EMIN_EN      1
SSP_GT_STRG_PCAL_CLUSTER_EMIN       150
SSP_GT_STRG_PCAL_CLUSTER_WIDTH       96

# CTOF logic
SSP_GT_STRG_CTOF_EN                   1
SSP_GT_STRG_CTOF_WIDTH               64
SSP_GT_STRG_CTOF_MASK              0xFF

# new DC Syntax
SSP_GT_STRG_DC_EN                     1
SSP_GT_STRG_DC_ROAD_REQUIRED          0
SSP_GT_STRG_DC_ROAD_INBEND_REQUIRED   0
SSP_GT_STRG_DC_ROAD_OUTBEND_REQUIRED  0
SSP_GT_STRG_DC_MULT_MIN               3
SSP_GT_STRG_DC_WIDTH                 32



########################
#
# Sector Trigger bit 5 
#
#   HTCC x (PCAL+ECAL)>300MeV x PCAL>60MeV x ECAL>10MeV
########################
SSP_GT_STRG                           5
SSP_GT_STRG_EN                        1

# HTCC trigger logic
SSP_GT_STRG_HTCC_EN                   1
SSP_SLOT 3      # sector 1 SSP
SSP_GT_STRG_HTCC_MASK                 0x0000000000FF
SSP_SLOT 4      # sector 2 SSP
SSP_GT_STRG_HTCC_MASK                 0x00000000FF00
SSP_SLOT 5      # sector 3 SSP
SSP_GT_STRG_HTCC_MASK                 0x000000FF0000
SSP_SLOT 6      # sector 4 SSP
SSP_GT_STRG_HTCC_MASK                 0x0000FF000000
SSP_SLOT 7      # sector 5 SSP
SSP_GT_STRG_HTCC_MASK                 0x00FF00000000
SSP_SLOT 8      # sector 6 SSP
SSP_GT_STRG_HTCC_MASK                 0xFF0000000000
SSP_SLOT all
SSP_GT_STRG_HTCC_WIDTH                0

# PCAL cluster trigger logic
SSP_GT_STRG_PCAL_CLUSTER_EMIN_EN      1
SSP_GT_STRG_PCAL_CLUSTER_EMIN       600
SSP_GT_STRG_PCAL_CLUSTER_WIDTH       96

# ECAL cluster trigger logic
SSP_GT_STRG_ECAL_CLUSTER_EMIN_EN      1
SSP_GT_STRG_ECAL_CLUSTER_EMIN       100
SSP_GT_STRG_ECAL_CLUSTER_WIDTH       96

# PCAL+ECAL cluster trigger logic: EMIN in 0.1MeV units
SSP_GT_STRG_ECALPCAL_CLUSTER_EMIN_EN      1
SSP_GT_STRG_ECALPCAL_CLUSTER_EMIN      3000
SSP_GT_STRG_ECALPCAL_CLUSTER_WIDTH       96



########################
#
# Sector Trigger bit 6 
#
#    HTCC x PCAL>300MeV
########################
SSP_GT_STRG                           6
SSP_GT_STRG_EN                        1

# HTCC trigger logic
SSP_GT_STRG_HTCC_EN                   1
SSP_SLOT 3      # sector 1 SSP
SSP_GT_STRG_HTCC_MASK                 0x0000000000FF
SSP_SLOT 4      # sector 2 SSP
SSP_GT_STRG_HTCC_MASK                 0x00000000FF00
SSP_SLOT 5      # sector 3 SSP
SSP_GT_STRG_HTCC_MASK                 0x000000FF0000
SSP_SLOT 6      # sector 4 SSP
SSP_GT_STRG_HTCC_MASK                 0x0000FF000000
SSP_SLOT 7      # sector 5 SSP
SSP_GT_STRG_HTCC_MASK                 0x00FF00000000
SSP_SLOT 8      # sector 6 SSP
SSP_GT_STRG_HTCC_MASK                 0xFF0000000000
SSP_SLOT all
SSP_GT_STRG_HTCC_WIDTH                0

# PCAL cluster trigger logic
SSP_GT_STRG_PCAL_CLUSTER_EMIN_EN      1
SSP_GT_STRG_PCAL_CLUSTER_EMIN      3000
SSP_GT_STRG_PCAL_CLUSTER_WIDTH       96



########################
# Sector Trigger bit 7 #
#
# PCAL(> 10 MeV) ECAL(>10 MeV)
########################
SSP_GT_STRG                           7
SSP_GT_STRG_EN                        1

# PCAL cluster trigger logic: EMIN in 0.1 MeV units
SSP_GT_STRG_PCAL_CLUSTER_EMIN_EN          1
SSP_GT_STRG_PCAL_CLUSTER_EMIN           100
SSP_GT_STRG_PCAL_CLUSTER_WIDTH           96

# ECAL cluster trigger logic: EMIN in 0.1MeV units
SSP_GT_STRG_ECAL_CLUSTER_EMIN_EN          1
SSP_GT_STRG_ECAL_CLUSTER_EMIN           100
SSP_GT_STRG_ECAL_CLUSTER_WIDTH           96


#######################################
# 'SSP_GTC_' - central detectors logic
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

########################
# Central Trigger bit 0    CTRG0:  FT(300-4000)xHD(2)
########################
SSP_GTC_CTRG 0

SSP_GTC_CTRG_EN                    1
SSP_GTC_CTRG_FT_CLUSTER_EN         1
SSP_GTC_CTRG_FT_CLUSTER_EMIN       300
SSP_GTC_CTRG_FT_CLUSTER_EMAX       4000
SSP_GTC_CTRG_FT_CLUSTER_HODO_NMIN  2
SSP_GTC_CTRG_FT_CLUSTER_NMIN       1
SSP_GTC_CTRG_FT_CLUSTER_WIDTH      0
SSP_GTC_CTRG_FT_ESUM_EN            0
SSP_GTC_CTRG_FT_ESUM_EMIN          0
SSP_GTC_CTRG_FT_ESUM_WIDTH         0


########################
# Central Trigger bit 1    CTRG1:  FT(500-8500) 2 clusters 
########################
SSP_GTC_CTRG                       1
SSP_GTC_CTRG_EN                    1

SSP_GTC_CTRG_FT_CLUSTER_MULT_EN             1
SSP_GTC_CTRG_FT_CLUSTER_MULT_COINCIDENCE   16
SSP_GTC_CTRG_FT_CLUSTER_MULT_MIN            2

SSP_GTC_CTRG_FT_CLUSTER_EMIN              500
SSP_GTC_CTRG_FT_CLUSTER_EMAX             8500
SSP_GTC_CTRG_FT_CLUSTER_HODO_NMIN           0
SSP_GTC_CTRG_FT_CLUSTER_NMIN                1
SSP_GTC_CTRG_FT_CLUSTER_WIDTH               0

########################
# Central Trigger bit 2    CTRG2:   FT(100-16000)
########################
SSP_GTC_CTRG                       2
SSP_GTC_CTRG_EN                    1

SSP_GTC_CTRG_FT_CLUSTER_EN         1
SSP_GTC_CTRG_FT_CLUSTER_EMIN       100
SSP_GTC_CTRG_FT_CLUSTER_EMAX       16000
SSP_GTC_CTRG_FT_CLUSTER_HODO_NMIN  0
SSP_GTC_CTRG_FT_CLUSTER_NMIN       1
SSP_GTC_CTRG_FT_CLUSTER_WIDTH      0
SSP_GTC_CTRG_FT_ESUM_EN            0
SSP_GTC_CTRG_FT_ESUM_EMIN          0
SSP_GTC_CTRG_FT_ESUM_WIDTH         0

########################
# Central Trigger bit 3    CTRG3:  FT(300-8500)xHD(2) 
########################
SSP_GTC_CTRG                       3
SSP_GTC_CTRG_EN                    1

SSP_GTC_CTRG_FT_CLUSTER_EN         1
SSP_GTC_CTRG_FT_CLUSTER_EMIN       300
SSP_GTC_CTRG_FT_CLUSTER_EMAX       8500
SSP_GTC_CTRG_FT_CLUSTER_HODO_NMIN  2
SSP_GTC_CTRG_FT_CLUSTER_NMIN       1
SSP_GTC_CTRG_FT_CLUSTER_WIDTH      0
SSP_GTC_CTRG_FT_ESUM_EN            0
SSP_GTC_CTRG_FT_ESUM_EMIN          0
SSP_GTC_CTRG_FT_ESUM_WIDTH         0


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
VTP_GT_LATENCY 5426


VTP_GT_WIDTH   16

# TRIGGER BITS: 
#              trig number 
#              |   ssp trig mask 
#              |   |   ssp sector mask        
#              |   |   |  multiplicity 
#              |   |   |  |  coincidence=#extended_clock_cycles 
#              |   |   |  |  |  ssp central trig mask
#              |   |   |  |  |  |
#
# Electron, All Sectors with DC
VTP_GT_TRGBIT  0   3  63  1  1  0  # SSP STRG0|STRG1, SECTOR 1-6

# Electron, Individual Sectors with DC
VTP_GT_TRGBIT  1   3   1  1  1  0  # SSP STRG0|STRG1, SECTOR 1
VTP_GT_TRGBIT  2   3   2  1  1  0  # SSP STRG0|STRG1, SECTOR 2
VTP_GT_TRGBIT  3   3   4  1  1  0  # SSP STRG0|STRG1, SECTOR 3
VTP_GT_TRGBIT  4   3   8  1  1  0  # SSP STRG0|STRG1, SECTOR 4
VTP_GT_TRGBIT  5   3  16  1  1  0  # SSP STRG0|STRG1, SECTOR 5
VTP_GT_TRGBIT  6   3  32  1  1  0  # SSP STRG0|STRG1, SECTOR 6

# Electron, All sectors without DC
VTP_GT_TRGBIT  7  96  63  1  1  0  # SSP STRG5|STRG6, SECTOR 1-6

# PCAL(>10)xECAL(>10 MeV) All sectors without DC
VTP_GT_TRGBIT  8 128  63  1  1  0  # SSP STRG7, SECTOR 1-6


# DC x FTOFPCU x PCAL>15MeV, Individual Sectors (for tagging/efficiency studies)
VTP_GT_TRGBIT 13   4   1  1  1  0  # SSP STRG2, SECTOR 1
VTP_GT_TRGBIT 14   4   2  1  1  0  # SSP STRG2, SECTOR 2
VTP_GT_TRGBIT 15   4   4  1  1  0  # SSP STRG2, SECTOR 3
VTP_GT_TRGBIT 16   4   8  1  1  0  # SSP STRG2, SECTOR 4
VTP_GT_TRGBIT 17   4  16  1  1  0  # SSP STRG2, SECTOR 5
VTP_GT_TRGBIT 18   4  32  1  1  0  # SSP STRG2, SECTOR 6


# FTOF x PCAL>15MeV x ECAL>40MeV (2 Sectors)
VTP_GT_TRGBIT 19   8   9  2  1  0  # SSP STRG3, SECTOR 1 & 4
VTP_GT_TRGBIT 20   8  18  2  1  0  # SSP STRG3, SECTOR 2 & 5
VTP_GT_TRGBIT 21   8  36  2  1  0  # SSP STRG3, SECTOR 3 & 6



# FT(300 - 8500) MeV x DC x FTOFPCU x PCAL>15MeV x CTOF (2 Sectors)
VTP_GT_TRGBIT 24  16  63  1  1  8 # SSP STRG4, SECTOR 1-6, CTRG3

# FT(300-4000)MeV x DC x FTOFPCU x PCAL>15MeV (2 Sectors)
VTP_GT_TRGBIT 25   4  63  2  1  1  # SSP STRG2, SECTOR 1-6, CTRG0

# 2 FT clusters (500-8500)MeV
VTP_GT_TRGBIT 26   0  63  1  0  2  #  CTRG1 

# FT(100-8000)MeV without hodoscope
VTP_GT_TRGBIT 27   0  63  1  0  4  #  CTRG2

# PULSER
VTP_GT_TRG             31
VTP_GT_TRG_PULSER_FREQ 100.0

VTP_CRATE end

############################
# TS settings (trig1 crate)
############################

TS_CRATE trig1

#lock-roc mode
#TS_BLOCK_LEVEL   1
#TS_BUFFER_LEVEL  1


# with micromega
#TS_BLOCK_LEVEL   10
#TS_BUFFER_LEVEL   8
#TS_HOLDOFF   1 30 1
#TS_HOLDOFF   2 30 1
#TS_HOLDOFF   3 30 1
#TS_HOLDOFF   4 30 1

# production: 5 5 15 10
TS_BLOCK_LEVEL   40
TS_BUFFER_LEVEL   8
TS_HOLDOFF   1  5 1
TS_HOLDOFF   2  5 1
TS_HOLDOFF   3 15 1
TS_HOLDOFF   4 10 1

# crashes VTPs
#TS_BLOCK_LEVEL   40
#TS_BUFFER_LEVEL   8
#TS_HOLDOFF   1 10 1
#TS_HOLDOFF   2 10 1
#TS_HOLDOFF   3  7 1
#TS_HOLDOFF   4  5 1

#
# TS GTP trigger mask
#
TS_GTP_INPUT_MASK 0xFFFFFFFF

#bit 28
##TS_GTP_INPUT_MASK 0x10000000
##TS_GTP_INPUT_MASK 0x00000000


#
# TS FP trigger mask
#
# 0x80  - FARADAY
# 0x100 - SVT
# 0x200 - CTOF
# 0x400 - CND
# 0x800 - MVT
# 0x1000 - helicity

TS_FP_INPUT_MASK 0x00001080

### Faraday cup prescale
TS_FP_PRESCALE  8 5


# TS_GTP_PRESCALE bit prescale
# TS_FP_PRESCALE  bit prescale
# Note: actual prescale is 2^(prescale-1)+1
#       prescale from 0 to 15
#       bit from 0 to 31  Prescale=(1-32)

#
# NO PRESCALE ON MAIN TRIGGER BITS 1-7
# PRESCALE BIT NUMBER HERE IS +1 wrt BIT DEFINITION, I.E. BIT 0 ABOVE IS BIT 1 HERE, .. , BIT 31 ABOVE is BIT 32 HERE


# TriggerBits 7-Sector 1 
TS_GTP_PRESCALE  8 6

# TriggerBits 8-Sector 4 
TS_GTP_PRESCALE  9 12

####### Not used ########

#   TriggerBit   9 
TS_GTP_PRESCALE 10  15

#   TriggerBit  10 
TS_GTP_PRESCALE 11  15

#   TriggerBit  11 
TS_GTP_PRESCALE 12 15

#   TriggerBit  12 
TS_GTP_PRESCALE 13 15


#
##### FTOF*PCU tagging triggers
#
#   TriggerBit  13  DC x FTOFPCU x PCAL>15MeV, S1
TS_GTP_PRESCALE 14 15

#   TriggerBit  14  DC x FTOFPCU x PCAL>15MeV, S2
TS_GTP_PRESCALE 15 15

#   TriggerBit  15  DC x FTOFPCU x PCAL>15MeV, S3
TS_GTP_PRESCALE 16  15

#   TriggerBit  16  DC x FTOFPCU x PCAL>15MeV, S4
TS_GTP_PRESCALE 17  15

#   TriggerBit  17  DC x FTOFPCU x PCAL>15MeV, S5
TS_GTP_PRESCALE 18  15

#   TriggerBit  18  DC x FTOFPCU x PCAL>15MeV, S6
TS_GTP_PRESCALE 19  15

#
######    OPPOSITE SECTOR TRIGGERS ####
#

#   TriggerBit  19 FTOFxPCALxECAL S1-4
TS_GTP_PRESCALE 20   0

#   TriggerBit  20 FTOFxPCALxECAL S2-5
TS_GTP_PRESCALE 21   0

#   TriggerBit  21 FTOFxPCALxECAL S3-6
TS_GTP_PRESCALE 22   0

##### Not used #####

#   TriggerBit  22 
TS_GTP_PRESCALE 23  15

#   TriggerBit  23 
TS_GTP_PRESCALE 24  15

#
#####     FT TRIGGERS    ####
#

#   TriggerBit  24 Sector4xDC
TS_GTP_PRESCALE 25  6

#   TriggerBit  25 FTx[FTOFxPCAL]^2
TS_GTP_PRESCALE 26  0

#   TriggerBit  26 FTx[FTOFxPCAL]^3
TS_GTP_PRESCALE 27  6

#   TriggerBit  27 Sector5xDC
TS_GTP_PRESCALE 28 15




#   TriggerBit  28 
TS_GTP_PRESCALE 29 15

#   TriggerBit  29 
TS_GTP_PRESCALE 30 15

#   TriggerBit  30 
TS_GTP_PRESCALE 31 15

#Pulser
TS_GTP_PRESCALE 32  0

# First arg:      0-disable, 
#                 1-enable; 
#                 |   Prescale (15-7Hz, 7-3.5kHz, 5-15kHz, 4-30kHz, 3-60kHz)
#                 |   |
TS_RANDOM_TRIGGER 0   5

TS_CRATE end
