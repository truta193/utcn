----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/21/2023 01:10:35 PM
-- Design Name: 
-- Module Name: DMUX_GEN - Behavioral
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

entity DMUX_GEN is
    generic (n:integer := 4);
    port (
        input : in std_logic;
        sel: in std_logic_vector(integer(ceil(log2(real(n))))-1 downto 0);
        output : out std_logic_vector(n-1 downto 0)
    );
end DMUX_GEN;

architecture Behavioral of DMUX_GEN is

begin
    process(input, sel)
    begin
    output <= (others => '0');
    output(conv_integer(sel)) <= input;    
    end process;
end Behavioral;
