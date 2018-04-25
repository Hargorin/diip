############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
############################################################
open_project -reset stream_dummy
set_top stream_dummy_top
add_files ../user/source/stream_dummy.cpp
add_files -tb ../user/testbench/stream_dummy_tb.cpp


# Solution
open_solution -reset "stream_dummy"
set_part {xc7a200tfbg676-2} -tool vivado
create_clock -period 8 -name default
#source "./stream_dummy/stream_dummy/directives.tcl"

csim_design -compiler gcc
csynth_design
cosim_design -rtl vhdl -tool xsim
export_design -flow impl -rtl vhdl -format ip_catalog -description "diip stream_dummy" -vendor "ime" -library "diip" -version "1.0.0" -display_name "diip_stream_dummy"
exit
