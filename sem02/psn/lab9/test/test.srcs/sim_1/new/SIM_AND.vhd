library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity SIM_AND is

end entity;

architecture Behavioral of SIM_AND is
    component ANDGATE is
        Port ( a : in STD_LOGIC;
               b : in STD_LOGIC;
               y : out STD_LOGIC
               );
    end component;
    
    signal A, B, Y: std_logic;
begin
    SI: ANDGATE port map (A,B,Y);
    A <= '0', '1' after 20ns;
    B <= '0', '1' after 10ns, '0' after 20ns, '1' after 30ns;

end Behavioral;