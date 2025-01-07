----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/20/2023 12:56:56 PM
-- Design Name: 
-- Module Name: OR_SIM - Behavioral
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

entity OR_SIM is
end OR_SIM;

architecture Behavioral of OR_SIM is
component OR_GENERIC is
    generic (n:integer := 2);
    port (input: in std_logic_vector(n-1 downto 0);
          output: out std_logic
          );
end component;
signal x, y, outp: std_logic;
signal inpt: std_logic_Vector(1 downto 0);
begin
    inpt <= x & y;
    x <= '1', '0' after 10ns, '1' after 20ns, '0' after 30ns;
    y <= '1', '0' after 20ns;
    ORSIM: OR_GENERIC port map (inpt, outp);

end Behavioral;
