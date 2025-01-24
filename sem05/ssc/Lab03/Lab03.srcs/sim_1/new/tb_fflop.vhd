library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity tb_fflop is
end tb_fflop;

architecture Behavioral of tb_fflop is

component m_fflop is
port (clk: in std_logic;
        d: in std_logic;
        q: out std_logic);
end component;

constant T : time := 2ns;
signal clk, d, q : std_logic := '0';

begin
    dff: m_fflop port map (
        clk => clk, d => d, q => q
    );
    
    process begin
        while true loop
            clk <= '0';
            wait for T/2;
            clk <= '1';
            wait for T/2;
        end loop;
    end process;
    
    process begin
        d <= '0';
        wait for 2*T;

        d <= '1';
        wait for T;

        d <= '0';
        wait for T;

        wait;
    end process;

end Behavioral;
