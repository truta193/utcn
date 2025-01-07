----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/02/2023 11:35:21 AM
-- Design Name: 
-- Module Name: ANDN_SIM - Behavioral
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity ANDN_SIM is
end ANDN_SIM;
--NOT WORKING
architecture Behavioral of ANDN_SIM is
    component ANDN is
        Generic (N: integer);
        Port (INPUT: std_logic_vector(1 to N); OUTPUT: out std_logic);
    end component;
    signal i: std_logic_vector(0 to 2);
    signal o: std_logic;
begin
    L: ANDN generic map (3) port map (i, o);
    
    i <= "010", "111" after 10ns;
end Behavioral;
