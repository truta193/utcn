library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.all;

entity tb_sreg is
end tb_sreg;

architecture Behavioral of tb_sreg is

component m_sreg is
port (
    clk: in std_logic;
    ce: in std_logic;
    d: in std_logic;
    q: out std_logic
);
end component;

constant T : time := 2ns;
signal clk, ce, d, q : std_logic := '0';

begin
    shift_reg: m_sreg port map (
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
        wait for T;
        ce <= '1';
        
         for i in 0 to 7 loop
            d <= std_logic(to_unsigned(i, 1)(0)); 
            wait for T;
        end loop;
        
        wait;
    end process;

end Behavioral;
