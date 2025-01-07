----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/21/2023 01:24:17 PM
-- Design Name: 
-- Module Name: DMUX_SIM - Behavioral
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
use ieee.math_real.all;

entity DMUX_SIM is
end DMUX_SIM;

architecture Behavioral of DMUX_SIM is
component DMUX_GEN is
    generic (n:integer := 4);
    port (
        input : in std_logic;
        sel: in std_logic_vector(integer(ceil(log2(real(n))))-1 downto 0);
        output : out std_logic_vector(n-1 downto 0)
    );
end component;
signal x : std_logic := '1';
signal s : std_logic_vector(2 downto 0);
signal outp: std_logic_vector(7 downto 0) := (others => '0');
begin
DM: DMUX_GEN generic map(n => 8) port map(x, s, outp);
    process
    begin
        s <= "111";
        wait for 10ns;
        s <= "110";
        wait for 10ns;
        s <= "101";
        wait for 10ns;
        s <= "100";
        wait for 10ns;
        s <= "011";
        wait for 10ns;
        s <= "010";
        wait for 10ns;
        s <= "001";
        wait for 10ns;
        s <= "000";
        wait;
    end process;

end Behavioral;
