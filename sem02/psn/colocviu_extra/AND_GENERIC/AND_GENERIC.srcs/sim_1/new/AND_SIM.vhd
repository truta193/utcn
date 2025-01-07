----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/20/2023 12:46:51 PM
-- Design Name: 
-- Module Name: AND_SIM - Behavioral
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

entity AND_SIM is
end AND_SIM;

architecture Behavioral of AND_SIM is
component AND_GENERIC is
    generic (n:integer := 2);
    port (input: in std_logic_vector(n-1 downto 0);
          output: out std_logic
          );
end component;
signal x, y, outp: std_logic;
signal inpt : std_logic_vector(1 downto 0);
begin
x <= '0', '1' after 10ns, '0' after 20ns, '1' after 30ns;
y <= '0', '1' after 20ns;
inpt <= x & y;
SIMT: AND_GENERIC port map (inpt, outp);


end Behavioral;
