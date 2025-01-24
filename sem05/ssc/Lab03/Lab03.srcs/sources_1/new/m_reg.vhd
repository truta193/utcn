library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity m_reg is
port (
    clk: in std_logic;
    ce: in std_logic;
    d: in std_logic_vector (7 downto 0);
    q: out std_logic_vector (7 downto 0)
);
end m_reg;

architecture Behavioral of m_reg is

begin
    process (clk) begin
        if (clk'event and clk = '1') then
            if (ce = '1') then
                q <= d;
            end if;
        end if;
    end process;
end Behavioral;
