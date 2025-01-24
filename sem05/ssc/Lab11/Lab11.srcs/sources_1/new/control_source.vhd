library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;


entity control_unit is
    port (
        CLK       : in std_logic;
        RD_n      : in std_logic;
        WR_n      : in std_logic;
        Refresh_n : in std_logic;
        Enable    : in std_logic;
        AddrSel   : out std_logic;  -- Row/Column select
        RAS_n     : out std_logic;
        CAS_n     : out std_logic;
        Ready     : out std_logic
    );
end control_unit;

architecture behavioral of control_unit is
    type state_type is (IDLE, ROW_ADDR, COL_ADDR, REFRESH);
    signal state, next_state : state_type;
    signal refresh_counter : unsigned(9 downto 0) := (others => '0');
    signal refresh_needed : std_logic := '0';
begin
    -- State and refresh counter process
    process(CLK)
    begin
        if rising_edge(CLK) then
            state <= next_state;
            
            -- Refresh counter (2ms = 2000 cycles at 1MHz)
            if refresh_counter = 1999 then
                refresh_counter <= (others => '0');
                refresh_needed <= '1';
            else
                refresh_counter <= refresh_counter + 1;
            end if;
            
            -- Clear refresh_needed when refresh cycle starts
            if state = REFRESH then
                refresh_needed <= '0';
            end if;
        end if;
    end process;

    -- Next state logic
    process(state, RD_n, WR_n, Refresh_n, Enable, refresh_needed)
    begin
        next_state <= state;
        case state is
            when IDLE =>
                if Refresh_n = '0' or refresh_needed = '1' then
                    next_state <= REFRESH;
                elsif Enable = '1' and (RD_n = '0' or WR_n = '0') then
                    next_state <= ROW_ADDR;
                end if;
            
            when ROW_ADDR =>
                next_state <= COL_ADDR;
            
            when COL_ADDR =>
                next_state <= IDLE;
            
            when REFRESH =>
                next_state <= IDLE;
        end case;
    end process;

    -- Output logic
    Ready <= '1' when state = IDLE else '0';
    AddrSel <= '1' when state = ROW_ADDR else '0';
    RAS_n <= '0' when (state = ROW_ADDR or state = COL_ADDR or state = REFRESH) else '1';
    CAS_n <= '0' when state = COL_ADDR else '1';
end behavioral;