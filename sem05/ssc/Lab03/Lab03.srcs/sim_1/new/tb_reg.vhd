library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.all;

entity tb_reg is
end tb_reg;

architecture Behavioral of tb_reg is

component m_reg is
port (
    clk: in std_logic;
    ce: in std_logic;
    d: in std_logic_vector (7 downto 0);
    q: out std_logic_vector (7 downto 0)
);
end component;

signal clk, ce : std_logic := '0';
signal d, q : std_logic_vector(7 downto 0);
constant T : time := 4ns;

begin

    rgstr: m_reg port map (
        clk => clk, ce => ce, d => d, q => q
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
        d <= "00000001";
        wait for T;
        d <= "00000010";
        wait for T;
        d <= "00000011";
        
        ce <= '1';
        wait for T;
        
        wait for T;
        d <= "00000100";
        wait for T;
        d <= "00000101";
        wait for T;
        d <= "00000110";
        wait for T;
        
        wait;
    end process;

end Behavioral;
