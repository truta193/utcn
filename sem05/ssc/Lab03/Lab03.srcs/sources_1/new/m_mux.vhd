library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity m_mux is
    port (
        a : in std_logic;
        b : in std_logic;
        sel : in std_logic;
        y : out std_logic
    );
end m_mux;

architecture Behavioral of m_mux is

begin
    process (a, b, sel) begin
        if sel = '0' then
            y <= a;  -- Select input a
        else
            y <= b;  -- Select input b
        end if;
    end process;

end Behavioral;
