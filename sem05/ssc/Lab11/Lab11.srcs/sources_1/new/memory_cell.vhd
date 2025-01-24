library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

-- Memory Cell (1M x 8 basic unit)
entity memory_cell is
    port (
        A      : in std_logic_vector(9 downto 0);
        D      : inout std_logic_vector(7 downto 0);
        RAS_n  : in std_logic;
        CAS_n  : in std_logic;
        WR_n   : in std_logic
    );
end memory_cell;

architecture behavioral of memory_cell is
    type ram_type is array (0 to 1048575) of std_logic_vector(7 downto 0);
    signal ram : ram_type;
    signal row_addr : std_logic_vector(9 downto 0);
    signal concat_addr : std_logic_vector(19 downto 0);
begin
    -- Explicit address concatenation
    concat_addr <= row_addr & A;

    process(RAS_n, CAS_n, WR_n)
    begin
        if RAS_n = '0' then
            -- Latch row address
            row_addr <= A;
        elsif CAS_n = '0' then
            -- Column address active
            if WR_n = '0' then
                -- Write operation
                ram(to_integer(unsigned(concat_addr))) <= D;
            else
                -- Read operation
                D <= ram(to_integer(unsigned(concat_addr)));
            end if;
        else
            -- High impedance when not selected
            D <= (others => 'Z');
        end if;
    end process;
end behavioral;