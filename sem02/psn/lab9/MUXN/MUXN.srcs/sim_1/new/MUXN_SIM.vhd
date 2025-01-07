----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/05/2023 08:03:19 PM
-- Design Name: 
-- Module Name: MUXN_SIM - Behavioral
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

entity MUXN_SIM is
end MUXN_SIM;

architecture Behavioral of MUXN_SIM is
component MUXN is
    generic (
    insize : integer; 
    selsize: integer
    );
    port (
        input: in std_logic_vector(1 to insize);
        sel: in std_logic_vector( 1 to selsize);
        output: out std_logic
    );
end component;
signal intest :std_logic_vector(1 to 4) := "0101";
signal seltest: std_logic_vector(1 to 2) := "00";
signal outp: std_logic;
begin
MUX: MUXN generic map (4, 2) port map (intest, seltest, outp);
seltest <= "00", "01" after 10ns, "10" after 20ns, "11" after 30ns;
end Behavioral;
