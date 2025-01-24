library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity memory_submodule is
    port (
        A      : in std_logic_vector(15 downto 0);
        D      : inout std_logic_vector(15 downto 0);
        Sel_n  : in std_logic;
        WR_n   : in std_logic;
        BHE_n  : in std_logic;
        A0     : in std_logic
    );
end memory_submodule;

architecture structural of memory_submodule is
    component memory_cell
        port (
            A     : in std_logic_vector(15 downto 0);
            D     : inout std_logic_vector(7 downto 0);
            CS_n  : in std_logic;
            WR_n  : in std_logic
        );
    end component;

    signal sel_low_n, sel_high_n : std_logic;
begin
    -- Selection logic for high/low bytes
    sel_low_n  <= Sel_n or (not A0);
    sel_high_n <= Sel_n or BHE_n;
    
    -- Low byte memory
    low_byte: memory_cell
    port map (
        A     => A,
        D     => D(7 downto 0),
        CS_n  => sel_low_n,
        WR_n  => WR_n
    );
    
    -- High byte memory
    high_byte: memory_cell
    port map (
        A     => A,
        D     => D(15 downto 8),
        CS_n  => sel_high_n,
        WR_n  => WR_n
    );
end structural;