----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/20/2023 12:33:38 PM
-- Design Name: 
-- Module Name: XOR_SIM - Behavioral
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

entity XOR_SIM is
end XOR_SIM;

architecture Behavioral of XOR_SIM is
component XORR is
    port (
      A: in std_logic; 
      B: in std_logic;
      output: out std_logic
    );
end component;
signal x, y, outp: std_logic := '0';
begin
    SIM: XORR port map (x,y,outp);
    x <= '1', '0' after 10ns, '1' after 20ns, '0' after 30ns;
    y <= '1', '0' after 20ns;

end Behavioral;
