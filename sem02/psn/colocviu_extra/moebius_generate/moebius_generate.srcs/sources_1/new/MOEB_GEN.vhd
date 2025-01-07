----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/21/2023 09:46:23 PM
-- Design Name: 
-- Module Name: MOEB_GEN - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all;

entity MOEB_GEN is
    port(
        clk : in std_logic;
        outp : out std_logic_vector(7 downto 0)
    );
end MOEB_GEN;

architecture Behavioral of MOEB_GEN is
component BISTABIL_D is
	port (
		clk, d, s, r: in std_logic;
		outp: out std_logic
	);
end component;
signal num : std_logic_vector(7 downto 0) := "00000000";
signal flip: std_logic;
begin
flip <= not num(0);
M0 : BISTABIL_D port map(clk, flip, '0', '0', num(7));
MOEB_STRIP: for i in 7 downto 1 generate
    MI : BISTABIL_D port map(clk, num(i), '0', '0', num(i-1));
 
end generate;
outp <= num;
end Behavioral;




LIBRARY ieee;
USE ieee.std_logic_1164.all;


entity BISTABIL_D is
	port (
		clk, d, s, r: in std_logic;
		outp: out std_logic
	);
end BISTABIL_D;

architecture Behav of BISTABIL_D is
signal q : std_logic := '0';
begin
	process(clk, s, r)
	begin
		if r = '1' then
			q <= '0';
		elsif s = '1' then
			q <= '1';
		elsif rising_edge(clk) then
			q <= d;
		end if;
		outp <= q;
	end process;
end Behav;