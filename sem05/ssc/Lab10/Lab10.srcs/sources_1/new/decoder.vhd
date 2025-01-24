library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity decoder is
    port (
        A      : in std_logic_vector(23 downto 17);
        RD_n   : in std_logic;
        WR_n   : in std_logic;
        Sel_n  : out std_logic_vector(7 downto 0);
        Enable : out std_logic
    );
end decoder;

architecture behavioral of decoder is
    constant START_ADDR : std_logic_vector(6 downto 0) := "1100000"; -- C0.0000H
begin
    process(A, RD_n, WR_n)
    begin
        -- Check if address is in range (C0.0000H to C7.FFFFH)
        if A(23 downto 17) = START_ADDR and (RD_n = '0' or WR_n = '0') then
            Enable <= '1';
            -- Decode lower 3 bits for sub-module selection
            Sel_n <= (others => '1');
            Sel_n(to_integer(unsigned(A(19 downto 17)))) <= '0';
        else
            Enable <= '0';
            Sel_n <= (others => '1');
        end if;
    end process;
end behavioral;
