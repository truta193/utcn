----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/22/2023 03:18:32 PM
-- Design Name: 
-- Module Name: DEB_SIM - Behavioral
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

entity DEB_SIM is
--  Port ( );
end DEB_SIM;

architecture Behavioral of DEB_SIM is
component debouncer_100ns IS
  PORT (
	clk, inp: in std_logic;
	o: out std_logic;
	w: out std_logic_vector(9 downto 0)
    );
END component;
signal clock, inp, outp: std_logic := '0';
signal w: std_logic_vector(9 downto 0);
begin
DEB: debouncer_100ns port map (clock, inp, outp, w);
    inp <= '1';
    process
    begin
    wait for 5ns;
    clock <= not clock;
    wait for 5ns;
    clock <= not clock;
    end process;


end Behavioral;
