----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/02/2023 11:22:47 AM
-- Design Name: 
-- Module Name: ANDN - Behavioral
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

entity ANDN is
    Generic (N: integer);
    Port (
        INPUT: std_logic_vector(1 to N); 
        OUTPUT: out std_logic
        );
end ANDN;

architecture Behavioral of ANDN is
signal chk : std_logic_vector(1 to N) := (others => '1');
begin
    OUTPUT <= '1' when INPUT = chk else '0';
    

end Behavioral;
