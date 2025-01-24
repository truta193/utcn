library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity tb_mux is
end tb_mux;

architecture Behavioral of tb_mux is

component m_mux is
    port (
        a : in std_logic;
        b : in std_logic;
        sel : in std_logic;
        y : out std_logic
    );
end component;

constant T : time := 4ns;
signal a, b, sel, y : std_logic := '0';

begin
    mmux: m_mux port map (
        a => a, b => b, sel => sel, y => y
    );
    
    process begin
        a <= '1';
        b <= '0';
        sel <= '0';
        wait for T;
        
        a <= '0';
        b <= '1';
        sel <= '1';
        wait for T;

        a <= '1';
        b <= '1';
        sel <= '0';
        wait for T;

        a <= '0';
        b <= '0';
        sel <= '1';
        wait for T;
        
        wait;
    end process;
    
end Behavioral;
