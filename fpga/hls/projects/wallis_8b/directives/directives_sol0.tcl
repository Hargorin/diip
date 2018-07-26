############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
############################################################
set_directive_interface -mode axis -register -register_mode reverse "wallis" inData
set_directive_interface -mode axis -register -register_mode forward "wallis" outData
set_directive_interface -mode s_axilite -bundle SCALAR_BUS "wallis" g_Mean
set_directive_interface -mode s_axilite -bundle SCALAR_BUS "wallis" g_Var
set_directive_interface -mode s_axilite -bundle SCALAR_BUS "wallis" contrast
set_directive_interface -mode s_axilite -bundle SCALAR_BUS "wallis" brightness
set_directive_interface -mode s_axilite -bundle SCALAR_BUS "wallis" g_Width
set_directive_interface -mode ap_ctrl_hs "wallis"
set_directive_pipeline "wallis/loop_rdata"
set_directive_inline "Cal_Mean"
set_directive_inline "Cal_Variance"
set_directive_inline "Wallis_Filter"
