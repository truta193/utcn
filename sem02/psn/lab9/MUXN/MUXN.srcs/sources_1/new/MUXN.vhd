----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/05/2023 07:58:50 PM
-- Design Name: 
-- Module Name: MUXN - Behavioral
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

entity MUXN is
    generic (
    insize : integer; 
    selsize: integer
    );
    port (
        input: in std_logic_vector(1 to insize);
        sel: in std_logic_vector( 1 to selsize);
        output: out std_logic
    );
end MUXN;

architecture Behavioral of MUXN is

begin
    output <= input(conv_integer(sel)+1);
end Behavioral;
