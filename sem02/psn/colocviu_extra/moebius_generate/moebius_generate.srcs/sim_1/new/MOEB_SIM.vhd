----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/21/2023 09:53:41 PM
-- Design Name: 
-- Module Name: MOEB_SIM - Behavioral
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

entity MOEB_SIM is
--  Port ( );
end MOEB_SIM;

architecture Behavioral of MOEB_SIM is
component MOEB_GEN is
    port(
        clk : in std_logic;
        outp : out std_logic_vector(7 downto 0)
    );
end component;
signal clk : std_logic := '0';
signal o : std_logic_vector(7 downto 0);
begin
    MB: MOEB_GEN port map(clk, o);
    process
    begin
    clk <= not clk;
    wait for 10ns;
    end process;

end Behavioral;
