library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity memory_cell is
    port (
        A     : in std_logic_vector(15 downto 0);
        D     : inout std_logic_vector(7 downto 0);
        CS_n  : in std_logic;
        WR_n  : in std_logic
    );
end memory_cell;

architecture behavioral of memory_cell is
    type ram_type is array (0 to 65535) of std_logic_vector(7 downto 0);
    signal ram : ram_type;
begin
    process(CS_n, WR_n)
    begin
        if CS_n = '0' then
            if WR_n = '0' then
                ram(to_integer(unsigned(A))) <= D;
            else
                D <= ram(to_integer(unsigned(A)));
            end if;
        else
            D <= (others => 'Z');
        end if;
    end process;
end behavioral;