-------------------------------------------------------------------------------
-- Title       : Difference and Add
-- Project     : Default Project Name
-------------------------------------------------------------------------------
-- File        : sum_diff.vhd
-- Author      : Jan Stocker (jan.stocker@students.fhnw.ch)
-- Company     : User Company Name
-- Created     : Wed Nov 22 15:53:25 2017
-- Last update : Thu Jul 12 09:24:16 2018
-- Platform    : Default Part Number
-- Standard    : <VHDL-2008 | VHDL-2002 | VHDL-1993 | VHDL-1987>
-------------------------------------------------------------------------------
-- Copyright (c) 2017 User Company Name
-------------------------------------------------------------------------------
-- Description: Calculate the difference from two inputs and sum them up
-------------------------------------------------------------------------------
-- Revisions:  Revisions and documentation are controlled by
-- the revision control system (RCS).  The RCS should be consulted
-- on revision history.
-------------------------------------------------------------------------------


library IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.NUMERIC_STD.ALL;


entity sum_diff is
    generic (
    	constant IN_WIDTH : positive := 8;
    	constant OUT_WIDTH : positive := 17
    );
    port (
        -- clk and reset
        ------------------------------------------------------------------------
        clk     : in    std_logic;
        rst_n   : in    std_logic;

        -- inputs
        ------------------------------------------------------------------------
        inp 	: in 	std_logic_vector(IN_WIDTH - 1 downto 0);
        inm 	: in 	std_logic_vector(IN_WIDTH - 1 downto 0);

        -- outputs
        ------------------------------------------------------------------------
        sum 	: out	std_logic_vector(OUT_WIDTH - 1 downto 0);

        -- controls
        ------------------------------------------------------------------------
        en 		: in 	std_logic;
        clear	: in 	std_logic

    );
end entity sum_diff;

architecture rtl of sum_diff is

	signal difference : signed(IN_WIDTH downto 0);
	signal sumi : signed(OUT_WIDTH downto 0);

	signal inpi : signed(IN_WIDTH downto 0);
	signal inmi : signed(IN_WIDTH downto 0);
begin

	inpi(IN_WIDTH - 1 downto 0) <= signed(inp);
	inpi(IN_WIDTH downto IN_WIDTH) <= (others => '0');
	inmi(IN_WIDTH - 1 downto 0) <= signed(inm);
	inmi(IN_WIDTH downto IN_WIDTH) <= (others => '0');

	difference <= inpi - inmi;
	sum <= std_logic_vector(sumi(OUT_WIDTH - 1 downto 0));

	p_add : process(clk) is
	begin
		if rising_edge(clk) then
			if (rst_n = '0') then
				sumi <= (others  => '0');
			else
				if (clear = '1') then
					sumi <= (others  => '0');
				else	
					if (en = '1') then
						sumi <= sumi + difference;
					else 
						sumi <= sumi;
					end if;	
				end if;
			end if;
		end if;		
	end process; -- add
end architecture rtl;
