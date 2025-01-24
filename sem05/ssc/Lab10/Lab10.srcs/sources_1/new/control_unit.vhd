library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity control_unit is
    port (
        CLK      : in std_logic;
        RD_n     : in std_logic;
        WR_n     : in std_logic;
        Enable   : in std_logic;
        READY    : out std_logic;
        MEM_RD_n : out std_logic;
        MEM_WR_n : out std_logic
    );
end control_unit;

architecture behavioral of control_unit is
    type state_type is (IDLE, READ_WAIT, WRITE_WAIT);
    signal state, next_state : state_type;
    signal counter : integer range 0 to 3;
begin
    -- State register
    process(CLK)
    begin
        if rising_edge(CLK) then
            state <= next_state;
            if state = IDLE then
                counter <= 0;
            else
                if counter < 3 then
                    counter <= counter + 1;
                end if;
            end if;
        end if;
    end process;

    -- Next state logic
    process(state, RD_n, WR_n, Enable, counter)
    begin
        next_state <= state;
        case state is
            when IDLE =>
                if Enable = '1' then
                    if RD_n = '0' then
                        next_state <= READ_WAIT;
                    elsif WR_n = '0' then
                        next_state <= WRITE_WAIT;
                    end if;
                end if;
            
            when READ_WAIT =>
                if counter = 3 or RD_n = '1' then
                    next_state <= IDLE;
                end if;
            
            when WRITE_WAIT =>
                if counter = 2 or WR_n = '1' then
                    next_state <= IDLE;
                end if;
        end case;
    end process;

    -- Output logic
    READY <= '1' when state = IDLE else '0';
    MEM_RD_n <= '0' when state = READ_WAIT else '1';
    MEM_WR_n <= '0' when state = WRITE_WAIT else '1';
end behavioral;
