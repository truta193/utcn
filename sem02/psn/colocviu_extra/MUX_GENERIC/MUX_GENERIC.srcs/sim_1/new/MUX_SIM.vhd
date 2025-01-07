----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/21/2023 12:24:07 PM
-- Design Name: 
-- Module Name: MUX_SIM - Behavioral
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

entity MUX_SIM is
end MUX_SIM;

architecture Behavioral of MUX_SIM is
component MUX_GEN is
    generic (n:integer := 4);
    port (
        input: in std_logic_vector(n-1 downto 0);
        sel: in std_logic_vector(integer(ceil(log2(real(n))))-1 downto 0);
        outp: out std_logic
    );
end component;

signal x : std_logic_vector(3 downto 0);
signal s : std_logic_vector(1 downto 0);
signal opt: std_logic;
begin
MX : MUX_GEN generic map (4) port map (x, s, opt);
    process
    begin
        x <= "1010";
        s <= "00";
        wait for 10ns;
        s <= "01";
        wait for 10ns;
        s <= "10";
        wait for 10ns;
        s <= "11";
        wait;
    end process;

end Behavioral;
