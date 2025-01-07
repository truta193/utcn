----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/02/2023 11:14:39 AM
-- Design Name: 
-- Module Name: LANT_SIM - Behavioral
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

entity LANT_SIM is
end LANT_SIM;

architecture Behavioral of LANT_SIM is
   component LANT is
        Generic (n : integer := 1);
        Port (
            INPUT: in std_logic;
            OUTPUT: out std_logic
        );
   end component;
    signal i,o: std_logic;
begin
    L: LANT port map(i, o);
    i <= '0', '1' after 20ns;

end Behavioral;
