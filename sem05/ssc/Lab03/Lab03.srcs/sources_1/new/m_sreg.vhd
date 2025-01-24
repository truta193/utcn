library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.all;

entity m_sreg is
port (
    clk: in std_logic;
    ce: in std_logic;
    d: in std_logic;
    q: out std_logic
);
end m_sreg;

architecture Behavioral of m_sreg is

signal tmp: std_logic_vector (7 downto 0);

begin
    process (clk)
    begin
        if rising_edge(clk)  then
            if (ce = '1') then
                for i in 0 to 6 loop
                    tmp(i + 1) <= tmp(i);
                end loop;
                
                tmp(0) <= d;
            end if;
        end if;
    end process;
    
    q <= tmp(7);
end Behavioral;
