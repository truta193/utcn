library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all;

entity m_cnt is
port (
    clk: in std_logic;
    count: out std_logic_vector (2 downto 0)
);
end m_cnt;

architecture Behavioral of m_cnt is

signal tmp : std_logic_vector (2 downto 0) := (others => '0');

begin
    process (clk) begin
        if (clk'event and clk = '1') then
            tmp <= tmp + 1;
        end if;
    end process;
    
    count <= tmp;
end Behavioral;
